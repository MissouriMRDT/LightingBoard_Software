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
  autonomy.setBrightness(BRIGTNESS);
  autonomy.show();
  underglow.begin();
  underglow.setBrightness(BRIGTNESS);
  underglow.show();
  speaker.begin();
  speaker.setBrightness(BRIGTNESS);
  speaker.show();
  interior.begin();
  interior.setBrightness(BRIGTNESS);
  interior.show();
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
                for( int i=0; i<autonomy.numPixels(); i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(0,0,255));
                  autonomy.show();
                  speaker.setPixelColor(i, speaker.Color(0,0,255));
                  speaker.show();
                  underglow.setPixelColor(i, underglow.Color(0,0,255));
                  underglow.show();
                }
                for( int i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(0,0,255));
                  interior.show();
                }
                break;
              case AUTONOMY:
                for( int i=0; i<autonomy.numPixels(); i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(255,0,0));
                  autonomy.show();
                  speaker.setPixelColor(i, speaker.Color(255,0,0));
                  speaker.show();
                  underglow.setPixelColor(i, underglow.Color(255,0,0));
                  underglow.show();
                }
                for( int i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(255,0,0));
                  interior.show();
                }
                break;
              case REACHED_GOAL:
                for( int i=0; i<autonomy.numPixels(); i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(0,255,0));
                  autonomy.show();
                  speaker.setPixelColor(i, speaker.Color(0,255,0));
                  speaker.show();
                  underglow.setPixelColor(i, underglow.Color(0,255,0));
                  underglow.show();
                }
                for( int i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(0,255,0));
                  interior.show();
                }
                break;
            }
          break;
      }
  }
}