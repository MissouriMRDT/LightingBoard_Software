#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include "RoveComm.h"
#include "Adafruit_NeoPixel.h"

RoveCommEthernet RoveComm;
rovecomm_packet packet;
uint8_t* data;
EthernetServer TCPServer(RC_ROVECOMM_MULTIMEDIABOARD_PORT);

#define BRIGHTNESS      130
#define AUTONOMY_COUNT  256
#define AUTONOMY_PANEL  11

Adafruit_NeoPixel autonomy = Adafruit_NeoPixel(AUTONOMY_COUNT, AUTONOMY_PANEL);

#endif