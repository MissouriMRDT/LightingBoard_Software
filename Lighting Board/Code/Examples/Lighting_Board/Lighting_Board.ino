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
  pinMode(HEADLIGHT_TOGGLE, OUTPUT);
  digitalWrite(HEADLIGHT_TOGGLE, LOW);
}

void loop()
{
  packet = RoveComm.read();
  if (packet.data_id != 0)
  {
    switch (packet.data_id)
      {
        case RC_MULTIMEDIABOARD_HEADLIGHTINTENSITY_DATA_ID:
          uint8_t* headlightEnable = (uint8_t*)packet.data;
          if (headlightEnable > 0)
            digitalWrite(HEADLIGHT_TOGGLE, HIGH);
          else
            digitalWrite(HEADLIGHT_TOGGLE, LOW);
          break;
        case RC_MULTIMEDIABOARD_LEDRGB_DATA_ID:
          uint8_t* LEDRGB = (uint8_t*)packet.data;
          for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
          {
            autonomy.setPixelColor(i, LEDRGB[0], LEDRGB[1], LEDRGB[2]);
          }
          autonomy.show();
          break;
        case RC_MULTIMEDIABOARD_LEDPATTERNS_DATA_ID:
          uint8_t* LEDPattern = (uint8_t*)packet.data;
          break;
        case RC_MULTIMEDIABOARD_STATEDISPLAY_DATA_ID:
          uint8_t* displayState = (uint8_t*)packet.data;
          switch (displayState[0])
            {
              case TELEOP:
                for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(0,0,255));
                }
                autonomy.show();
                break;
              case AUTONOMY:
                for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(255,0,0));
                }
                autonomy.show();
                break;
              case REACHED_GOAL:
                for( uint16_t i=0; i<AUTONOMY_COUNT; i++)
                {
                  autonomy.setPixelColor(i, autonomy.Color(0,255,0));
                }
                autonomy.show();
                break;
            }
          break;
        case RC_MULTIMEDIABOARD_BRIGHTNESS_DATA_ID;
          uint8_t* brightness = (uint8_t*)packet.data;
          autonomy.setBrightness(brightness[0]);
          break;
      }
  }
}

//mrdt logo, belgum, merica, minecraft blocks, dota logo, mcdonalds, windows logo,