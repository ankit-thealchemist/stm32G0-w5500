cmake_minimum_required(VERSION 3.22)

project(wizchip C ASM)
set(CMAKE_C_STANDARD 11)
add_library(wizchip INTERFACE)

target_include_directories(wizchip INTERFACE
    Ethernet/
    Internet/FTPClient/
    Internet/FTPClient/
    Internet/DHCP/
    Internet/MQTT/
    Internet/MQTT/
    Internet/TFTP/
    Internet/TFTP/
    Internet/httpServer/
    Internet/httpServer/
    Internet/httpServer/
    Internet/SNTP/
    Internet/SNMP/
    Internet/SNMP/
    Internet/DNS/
    Internet/FTPServer/
    Internet/FTPServer/
    Internet/MQTT/MQTTPacket/src/
    Internet/MQTT/MQTTPacket/src/
    Internet/MQTT/MQTTPacket/src/
    Internet/MQTT/MQTTPacket/src/
    Internet/MQTT/MQTTPacket/src/
    Internet/MQTT/MQTTPacket/src/
    Internet/MQTT/MQTTPacket/src/
    Application/loopback/
    Application/multicast/
    Ethernet/W5100/
    Ethernet/W5500/
    Ethernet/W5200/
    Ethernet/W5100S/
    Ethernet/W5300/
)

target_sources(wizchip INTERFACE
    Ethernet/socket.c
    Ethernet/wizchip_conf.c
    Internet/FTPClient/ftpc.c
    Internet/DHCP/dhcp.c
    Internet/MQTT/MQTTClient.c
    Internet/MQTT/mqtt_interface.c
    Internet/TFTP/tftp.c
    Internet/TFTP/netutil.c
    Internet/httpServer/httpParser.c
    Internet/httpServer/httpUtil.c
    Internet/httpServer/httpServer.c
    Internet/SNTP/sntp.c
    Internet/SNMP/snmp.c
    Internet/SNMP/snmp_custom.c
    Internet/DNS/dns.c
    Internet/FTPServer/ftpd.c
    Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c
    Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c
    Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c
    Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c
    Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c
    Internet/MQTT/MQTTPacket/src/MQTTPacket.c
    Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c
    Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c
    Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c
    Internet/MQTT/MQTTPacket/src/MQTTFormat.c
    Application/loopback/loopback.c
    Application/multicast/multicast.c
    Ethernet/W5100/w5100.c
    Ethernet/W5500/w5500.c
    Ethernet/W5200/w5200.c
    Ethernet/W5100S/w5100s.c
    Ethernet/W5300/w5300.c
)