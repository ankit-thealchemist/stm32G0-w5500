/**
 * @file app.c
 * @author Ankit Bansal (iotdevelope@gmail.com)
 * @brief contain the main function of the application
 * @version 0.1
 * @date 2024-05-12
 *
 * @copyright Copyright (c) 2024
 *
 */

/******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "app.h"
#include "main.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "socket.h"
#include <stdio.h>
#include <string.h>
#include "retarget.h"
#include "wizchip_conf.h"
#include <stdbool.h>
#include "dhcp.h"
#include "sntp.h"
/******************************************************************************
 * EXTERN VARIABLES
 ******************************************************************************/

/******************************************************************************
 * PRIVATE MACROS AND DEFINES
 ******************************************************************************/
#define DHCP_SOCKET 0


/******************************************************************************
 * PRIVATE TYPEDEFS
 ******************************************************************************/

/******************************************************************************
 * STATIC VARIABLES
 ******************************************************************************/

uint8_t dhcp_buffer[1024];

volatile bool ip_assigned = false;

/******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************/

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ******************************************************************************/

/******************************************************************************
 * STATIC FUNCTIONS
 ******************************************************************************/

/**
 * @brief Enables the W5500's Chip Select pin
 *
 * @return void
 */
static void csEnable(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

/**
 * @brief Disables the W5500's Chip Select pin
 *
 * @return void
 */
static void csDisable(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

/**
 * @brief Writes a single byte to the W5500 via SPI
 *
 * @param[in] tx The byte to write
 *
 * @return void
 */
static void spiWriteByte(uint8_t tx)
{

    uint8_t rx = 0;
    HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 10);
}

/**
 * @brief Reads a single byte from the W5500 via SPI
 *
 * @return The byte read
 */
static uint8_t spiReadByte(void)
{

    uint8_t rx = 0, tx = 0xFF;
    HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, 10);
    return rx;
}

/**
 * @brief Reads data from the W5500
 *
 * @param[out] buff The buffer to store the read data
 * @param[in] len The number of bytes to read
 *
 * @return void
 */
static void W5500_ReadBuff(uint8_t *buff, uint16_t len)
{
    HAL_SPI_Receive(&hspi1, buff, len, HAL_MAX_DELAY);
    __NOP();
}

/**
 * @brief Writes data to the W5500
 *
 * @param[in] buff The data to write
 * @param[in] len The number of bytes to write
 *
 * @return void
 */
static void W5500_WriteBuff(uint8_t *buff, uint16_t len)
{
    HAL_SPI_Transmit(&hspi1, buff, len, HAL_MAX_DELAY);
    __NOP();
}

/**
 * @brief Callback function called when the IP is assigned
 *
 * @return void
 */
static void Callback_IPAssigned(void)
{
    printf("Callback: IP assigned! Leased time: %d sec\r\n", getDHCPLeasetime());
    ip_assigned = true;
}

/**
 * @brief Callback function called when there is an IP conflict
 *
 * @return void
 */
static void Callback_IPConflict(void)
{
    printf("Callback: IP conflict!\r\n");
}

/******************************************************************************
 * GLOBAL FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/

/******************************************************************************
 * Function Definitions
 *******************************************************************************/

void W5500_Init(void)
{
    printf("Registering SPI callback...\r\n");
    /* SPI method callback registration */
    reg_wizchip_spi_cbfunc(spiReadByte, spiWriteByte);

    /* CS function register */
    reg_wizchip_cs_cbfunc(csEnable, csDisable);

    reg_wizchip_spiburst_cbfunc(W5500_ReadBuff, W5500_WriteBuff);

    uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
    wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);

    printf("Calling DHCP_init()...\r\n");
    wiz_NetInfo net_info = {
        .mac = {0xEA, 0x11, 0x22, 0x33, 0x44, 0xEA},
        .dhcp = NETINFO_DHCP};

    // set MAC address before using DHCP
    setSHAR(net_info.mac);
    DHCP_init(DHCP_SOCKET, dhcp_buffer);

    printf("Registering DHCP callbacks...\r\n");
    reg_dhcp_cbfunc(
        Callback_IPAssigned,
        Callback_IPAssigned,
        Callback_IPConflict);

    printf("Calling DHCP_run()...\r\n");
    // actually should be called in a loop, e.g. by timer
    uint32_t ctr = 10000;
    uint8_t dhcp_ret = DHCP_FAILED;
    
    uint32_t now = HAL_GetTick();
    // wait for IP assigned
    while(dhcp_ret < DHCP_IP_ASSIGN )
    {   
        dhcp_ret = DHCP_run();
        if ((HAL_GetTick() - now) > (10 *1000))
        {   
            now = HAL_GetTick();
            printf("DHCP_run() timeout!\r\n");
            DHCP_init(DHCP_SOCKET, dhcp_buffer);
        }
        
    }
    if (dhcp_ret < DHCP_IP_ASSIGN )
    {
        printf("\r\nIP was not assigned :(\r\n");
        return;
    }

    getIPfromDHCP(net_info.ip);
    getGWfromDHCP(net_info.gw);
    getSNfromDHCP(net_info.sn);

    uint8_t dns[4];
    getDNSfromDHCP(dns);

    printf("IP:  %d.%d.%d.%d\r\nGW:  %d.%d.%d.%d\r\nNet: %d.%d.%d.%d\r\nDNS: %d.%d.%d.%d\r\n",
           net_info.ip[0], net_info.ip[1], net_info.ip[2], net_info.ip[3],
           net_info.gw[0], net_info.gw[1], net_info.gw[2], net_info.gw[3],
           net_info.sn[0], net_info.sn[1], net_info.sn[2], net_info.sn[3],
           dns[0], dns[1], dns[2], dns[3]);

    printf("Calling wizchip_setnetinfo()...\r\n");
    wizchip_setnetinfo(&net_info);

    
}
