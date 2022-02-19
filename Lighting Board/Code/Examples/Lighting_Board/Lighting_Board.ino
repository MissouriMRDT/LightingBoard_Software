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

  pinMode(AUTONOMY_PANEL,OUTPUT);

  autonomy.begin();
  autonomy.setBrightness(255);
  autonomy.clear();
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
  uint32_t red = 0x00FF0000;
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
          Serial.println(displayState[0]);
          switch (displayState[0])
            {
              case TELEOP:
                Serial.println("Ya mum");
                autonomy.setPixelColor(1, 0, 255, 255);
                autonomy.show();
                autonomy.fill(red,0,AUTONOMY_COUNT);
                autonomy.show();
                Serial.println("Ya mum2");
                Serial.println(autonomy.canShow());
                for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
                {
                  autonomy.setPixelColor(i, red);
                  autonomy.show();
                  speaker.setPixelColor(i, speaker.Color(0,0,255));
                  speaker.show();
                  underglow.setPixelColor(i, underglow.Color(0,0,255));
                  underglow.show();
                }
                Serial.println("Ya mum3");
                for( uint16_t i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(0,0,255));
                  interior.show();
                }
                Serial.println("Ya mum4");
                break;
              case AUTONOMY:
                for( uint16_t i=0; i<autonomy.numPixels(); i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(255,0,0));
                  autonomy.show();
                  speaker.setPixelColor(i, speaker.Color(255,0,0));
                  speaker.show();
                  underglow.setPixelColor(i, underglow.Color(255,0,0));
                  underglow.show();
                }
                for( uint16_t i=0; i<interior.numPixels(); i++)
                {
                  interior.setPixelColor(i, interior.Color(255,0,0));
                  interior.show();
                }
                break;
              case REACHED_GOAL:
                for( uint16_t i=0; i<autonomy.numPixels(); i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(0,255,0));
                  autonomy.show();
                  speaker.setPixelColor(i, speaker.Color(0,255,0));
                  speaker.show();
                  underglow.setPixelColor(i, underglow.Color(0,255,0));
                  underglow.show();
                }
                for( uint16_t i=0; i<interior.numPixels(); i++)
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