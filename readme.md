# stm32G0-w5500

This repository provides an implementation for connecting an STM32G0 microcontroller to a network
using the Wiznet W5500 Ethernet module and obtaining an IP address via DHCP
(Dynamic Host Configuration Protocol).

## Features

* Implements a DHCP client
* Connects to a network router and obtains IP address automatically
* Includes example code for basic network communication

## Hardware Supported

* STM32G0 microcontroller
* Wiznet W5500 Ethernet module

## Pin configuration

The W5500 Ethernet module is connected to the following pins of the STM32G0 microcontroller:

| W5500 pin   | STM32G0 pin     |
|-------------|-----------------|
| MISO        | PA6             |
| MOSI        | PA7             |
| SCK         | PB3             |
| CS          | PA5             |
| GND         | GND             |
| VCC         | 3.3V/5v         |

This example code runs without the interupt pin.


## Debug Output

The library uses the standard printf() function for debugging output. The default
configuration uses the USART2 peripheral on the STM32G0 microcontroller.

The default configuration of the serial output uses 115200 baud, 8 data bits, no
parity bit and 1 stop bit (8N1).

After running the example, you can check the serial output in the serial monitor of
the STM32G0 microcontroller.

```
Registering SPI callback...
Calling DHCP_init()...
Registering DHCP callbacks...
Calling DHCP_run()...
> Send DHCP_DISCOVER
DHCP message : 10.42.0.1(67) 300 received.
> Receive DHCP_OFFER
> Send DHCP_REQUEST
DHCP message : 10.42.0.1(67) 300 received.
> Receive DHCP_ACK

> Check leased IP - OK
Callback: IP assigned! Leased time: 10 sec
IP:  10.42.0.128
GW:  10.42.0.1
Net: 255.255.255.0
DNS: 10.42.0.1
Calling wizchip_setnetinfo()...
```

