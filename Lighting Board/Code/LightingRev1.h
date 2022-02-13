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
EthernetServer TCPServer(RC_ROVECOMM_DRIVEBOARD_PORT);

#define Headlight_Toggle    PE_3  
#define Autonomy_Panel		PD_7
#define Underglow_Panel		PA_6
#define Speaker_Panel		PM_4
#define Interior_Strip      PM_5

#endif