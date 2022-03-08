#ifndef _LightingBoard
#define _LightingBoard

#include <Energia.h> 
#include "RoveComm.h"
#include "Adafruit_NeoPixel.h"

RoveCommEthernet RoveComm;
rovecomm_packet packet;

//timekeeping variables
uint32_t last_update_time;

//declare the Ethernet Server in the top level sketch with the requisite port ID any time you want to use RoveComm
EthernetServer TCPServer(RC_ROVECOMM_MULTIMEDIABOARD_PORT);

#define BRIGTNESS       20
#define AUTONOMY_COUNT  550 // 256+256+135

#define HEADLIGHT_TOGGLE  PE_3  
#define AUTONOMY_PANEL		3 //PF_1


Adafruit_NeoPixel autonomy = Adafruit_NeoPixel(AUTONOMY_COUNT,AUTONOMY_PANEL,NEO_GRB);

#endif