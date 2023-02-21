#include "Multimedia.h"

void setup()
{
    Serial.begin(9600);
    delay(100);
    // Set up rovecomm with the correct IP and the TCP server
    RoveComm.begin(RC_MULTIMEDIABOARD_FOURTHOCTET, &TCPServer, RC_ROVECOMM_MULTIMEDIABOARD_MAC);
    delay(100);

    Serial.println("Started Lighting Board");

    autonomy.begin();
    autonomy.setBrightness(BRIGHTNESS);
    autonomy.fill(autonomy.Color(0, 0, 255));
    autonomy.show();
}

void loop()
{
    packet = RoveComm.read();
    switch (packet.data_id)
    {
        case RC_MULTIMEDIABOARD_LEDRGB_DATA_ID:
            uint8_t *LEDRGB = (uint8_t *)packet.data;
            autonomy.clear();
            autonomy.fill(autonomy.Color(LEDRGB[0], LEDRGB[1], LEDRGB[2]));
            autonomy.show();
            break;
        
        case RC_MULTIMEDIABOARD_STATEDISPLAY_DATA_ID:
            uint8_t *displayState = (uint8_t *)packet.data;
            switch (displayState[0])
            {
                case TELEOP:
                    autonomy.fill(autonomy.Color(0, 0, 255));
                    autonomy.show();
                    break;
                
                case AUTONOMY:
                    autonomy.fill(autonomy.Color(255, 0, 0));
                    autonomy.show();
                    break;
                
                case REACHED_GOAL:
                    for (int i = 0; i < 5; i++)
                    {
                        autonomy.fill(autonomy.Color(0, 255, 0));
                        autonomy.show();
                        delay(500);
                        autonomy.clear(); //Sets pixels to black
                        autonomy.show();
                        delay(500);
                    }
                    break;
            }
            break;
        
        case RC_MULTIMEDIABOARD_BRIGHTNESS_DATA_ID:
            uint8_t *brightness = (uint8_t *)packet.data;
            if (brightness[0] >= BRIGHTNESS)
            {
                autonomy.setBrightness(BRIGHTNESS);
                autonomy.show();
            }
            else
            {
                autonomy.setBrightness(brightness[0]);
                autonomy.show();
            }
            break;
    }
}
