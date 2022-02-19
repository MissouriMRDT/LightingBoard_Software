#ifndef _LightingBoard
#define _LightingBoard

#include <Energia.h> 
#include "RoveComm.h"
#include "Adafruit_NeoPixel.h"
#include "RoveWatchdog.h"

RoveCommEthernet RoveComm;
rovecomm_packet packet;
RoveWatchdog    Watchdog;

//timekeeping variables
uint32_t last_update_time;

//declare the Ethernet Server in the top level sketch with the requisite port ID any time you want to use RoveComm
EthernetServer TCPServer(RC_ROVECOMM_DRIVEBOARD_PORT);

#define BRIGTNESS       50
#define AUTONOMY_COUNT  256
#define UNDERGLOW_COUNT 256
#define SPEAKER_COUNT   256
#define INTERIOR_COUNT  0

#define HEADLIGHT_TOGGLE  PE_3  
#define AUTONOMY_PANEL		PD_7
#define UNDERGLOW_PANEL		PA_6
#define SPEAKER_PANEL		  PM_4
#define INTERIOR_STRIP    PM_5

Adafruit_NeoPixel autonomy(AUTONOMY_COUNT,AUTONOMY_PANEL);
Adafruit_NeoPixel underglow(UNDERGLOW_COUNT,UNDERGLOW_PANEL);
Adafruit_NeoPixel speaker(SPEAKER_COUNT,SPEAKER_PANEL);
Adafruit_NeoPixel interior(INTERIOR_COUNT,INTERIOR_STRIP);


void Estop();

#endif