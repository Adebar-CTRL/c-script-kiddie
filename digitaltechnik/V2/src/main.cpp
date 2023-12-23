#define DEMO 1         //Demomodus AUS bei 0
#define BPM_IN_MS 484  //Quotient aus 60.000ms und BPM

#include <Arduino.h>
#include "RgbwSpotlight8Ch.h"
#include "MiniMovingHead14Ch.h"

#if DEMO == 0
RgbwSpotlight8Ch spotlights[2] = {
        {RgbwSpotlight8Ch(2)},
        {RgbwSpotlight8Ch(4)}
};
MiniMovingHead14Ch movingHeads[2] = {
        {MiniMovingHead14Ch(3)},
        {MiniMovingHead14Ch(5)}
};

#else
#include "RgbwSpotlight8ChDemo.h"
#include "MiniMovingHead14ChDemo.h"

RgbwSpotlight8ChDemo spotlights[2] = {
        {RgbwSpotlight8ChDemo(2)},
        {RgbwSpotlight8ChDemo(4)}
};
MiniMovingHead14ChDemo movingHeads[2] = {
        {MiniMovingHead14ChDemo(3)},
        {MiniMovingHead14ChDemo(5)}
};
#endif

unsigned int previousMillis = 0;
unsigned int loopStartMillis = 0;

unsigned int beatIntervals[1][2] = {
        {4770, 14480},
};

void BeatDetector(unsigned int currentMillis) {
    if ((currentMillis - previousMillis) >= BPM_IN_MS) {
        previousMillis = currentMillis;
        //Serial.println(currentMillis);
        for (auto const &interval : beatIntervals) {
            if (interval[0] <= currentMillis && currentMillis <= interval[1]) {
                //Serial.println(currentMillis);
                //Serial.print(interval[0]); Serial.print(" > "); Serial.println(currentMillis);
                //Serial.print(interval[1]); Serial.print(" < "); Serial.println(currentMillis);

                for (auto &spotlight: spotlights) {
                    spotlight.StartBlink(currentMillis);
                }
                break;
            }
        }
    }
}

void setup() {
#if DEMO == 0
    DmxSimpleClass::usePin(3);
    DmxSimpleClass::maxChannel(44);
#endif

    Serial.begin(115200);
    Serial.println(3);
    delay(800);
    Serial.println(2);
    delay(800);
    Serial.println(1);
    delay(800);
    Serial.println("GO");
    delay(100);

    loopStartMillis = millis();
    //Serial.println(loopStartMillis);
}

void loop() {
    unsigned int currentMillis = millis() - loopStartMillis;
    BeatDetector(currentMillis);

    for (auto &spotlight: spotlights) {
        spotlight.CleanUp(currentMillis);
        spotlight.RunTick(currentMillis);
    }
    for (auto &movingHead: movingHeads) {
        movingHead.CleanUp(currentMillis);
        movingHead.RunTick(currentMillis);
    }
}