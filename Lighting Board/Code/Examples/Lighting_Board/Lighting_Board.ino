#include "LightingRev1.h"

void setup() 
{
  Serial.begin(9600);

  //Set up rovecomm with the correct IP and the TCP server
  RoveComm.begin(RC_MULTIMEDIABOARD_FOURTHOCTET, &TCPServer);
  delay(100);

  Serial.println("Started Lighing Board");
    

  //update timekeeping
  last_update_time = millis();

  
  autonomy.begin();
  //underglow.begin();

  //speaker.begin();
  //interior.begin();
  autonomy.setBrightness(5);
  //underglow.setBrightness(20);
}

void loop()
{
  packet = RoveComm.read();
  if (packet.data_id != 0)
  {
    switch (packet.data_id)
      {
        case RC_MULTIMEDIABOARD_HEADLIGHTINTENSITY_DATA_ID:
          break;
        case RC_MULTIMEDIABOARD_LEDRGB_DATA_ID:
          break;
        case RC_MULTIMEDIABOARD_LEDPATTERNS_DATA_ID:
          break;
        case RC_MULTIMEDIABOARD_STATEDISPLAY_DATA_ID:
          uint8_t* displayState = (uint8_t*)packet.data;
          switch (displayState[0])
            {
              case TELEOP:
                for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(0,0,255));
                  autonomy.show();
                  //speaker.setPixelColor(i, speaker.Color(0,0,255));
                  //speaker.show();
                }
                /*for( uint16_t i=0; i<UNDERGLOW_COUNT; i++)
                {
                  underglow.setPixelColor(i, underglow.Color(0,0,255));
                  underglow.show();
                }
                /*for( uint16_t i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(0,0,255));
                  interior.show();
                }*/
                break;
              case AUTONOMY:
                for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(255,0,0));
                  autonomy.show();
                  //speaker.setPixelColor(i, speaker.Color(255,0,0));
                  //speaker.show();
                  //underglow.setPixelColor(i, underglow.Color(255,0,0));
                  //underglow.show();
                }
                /*for( uint16_t i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(255,0,0));
                  interior.show();
                }*/
                break;
              case REACHED_GOAL:
                for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(0,255,0));
                  autonomy.show();
                  //speaker.setPixelColor(i, speaker.Color(0,255,0));
                  //speaker.show();
                  //underglow.setPixelColor(i, underglow.Color(0,255,0));
                  //underglow.show();
                }
                /*for( uint16_t i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(0,255,0));
                  interior.show();
                }*/
                break;
            }
          break;
      }
  }
}