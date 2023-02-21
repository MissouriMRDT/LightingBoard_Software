#include "Multimedia.h"

void setup()
{
    Serial.begin(9600);
    delay(100);

    RoveComm.begin(RC_MULTIMEDIABOARD_FOURTHOCTET, &TCPServer, RC_ROVECOMM_MULTIMEDIABOARD_MAC);
    delay(100);

    autonomy.begin();
    autonomy.setBrightness(BRIGHTNESS);
}

void loop()
{
    packet = RoveComm.read();
    data = (uint8_t*)packet.data;
    if(packet.data_id != 0)
    {
        switch(packet.data_id)
        {
            case RC_MULTIMEDIABOARD_LEDRGB_DATA_ID:
                autonomy.fill(autonomy.Color(data[0], data[1], data[2]));
                break;

            case RC_MULTIMEDIABOARD_STATEDISPLAY_DATA_ID:
                switch (data[0])
                {
                    case TELEOP:
                        autonomy.fill(autonomy.Color(0, 0, 255));
                        break;
                    
                    case AUTONOMY:
                        autonomy.fill(autonomy.Color(255, 0, 0));
                        break;

                    case REACHED_GOAL:
                        for(uint8_t i = 0; i < 5; i++)
                        {
                            autonomy.fill(autonomy.Color(0, 255, 0));
                            autonomy.show();
                            delay(500);
                            autonomy.clear();
                            autonomy.show();
                            delay(500);
                        }
                        break;
                }
                break;

            case RC_MULTIMEDIABOARD_BRIGHTNESS_DATA_ID:
                if(data[0] >= BRIGHTNESS)
                {
                    autonomy.setBrightness(BRIGHTNESS);
                }
                else
                {
                    autonomy.setBrightness(data[0]);
                }
                break;
        }
    }
    autonomy.show();
}
