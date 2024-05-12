/**
 * @file app.h
 * @author Ankit Bansal (iotdevelope@gmail.com)
 * @brief This is the header file for the application
 * @version 0.1
 * @date 2024-05-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************
 * INCLUDES
 **********************************************************************************************************/
#include <stdint.h>

/**********************************************************************************************************
 * MACROS AND DEFINES
 **********************************************************************************************************/

/**********************************************************************************************************
 * TYPEDEFS
 **********************************************************************************************************/

/**********************************************************************************************************
 * EXPORTED VARIABLES
 **********************************************************************************************************/

/**********************************************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************/

/**
 * @brief Initializes the W5500 Ethernet controller
 *
 * This function sets up the W5500 Ethernet controller by configuring the necessary
 * registers and initializing the network interface. It should be called at the
 * start of the application to prepare the Ethernet connection.
 *
 * @return void
 */
void W5500_Init();


#ifdef __cplusplus
}
#endif


#endif // __APP_H__