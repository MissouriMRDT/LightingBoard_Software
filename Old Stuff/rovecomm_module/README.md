# RoveComm
The UDP/TCP packet protocol used by all MRDT computing devices

## Dependencies
This implementation of RoveComm uses the Python3 socket library to handle sending custom messages using the UDP and TCP transport protocols.

## Packet Structure
The RoveComm udp packet header is 5 bytes long:
* uint8_t rovecomm_version
* uint16_t data_id   
* uint8_t  data_type
* uint8_t  data_count

The packet then countains a data_count number of data elements. The size of each element depends on the data type.