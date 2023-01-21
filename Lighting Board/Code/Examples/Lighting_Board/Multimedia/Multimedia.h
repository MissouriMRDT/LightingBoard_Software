#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include "RoveComm.h"
#include "Adafruit_NeoPixel.h"

RoveCommEthernet RoveComm;
rovecomm_packet packet;

//declare the Ethernet Server in the top level sketch with the requisite port ID any time you want to use RoveComm
EthernetServer TCPServer(RC_ROVECOMM_MULTIMEDIABOARD_PORT);

#define BRIGHTNESS      130 //max at 130
#define AUTONOMY_COUNT  256 // 256 for NeoPixel

#define AUTONOMY_PANEL	11 //PF_1

Adafruit_NeoPixel autonomy = Adafruit_NeoPixel(AUTONOMY_COUNT,AUTONOMY_PANEL,NEO_GRB);

#endif