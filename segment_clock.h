#ifndef segment_clock_h
#define segment_clock_h

#include "ledstrip.h"
#include "udplogger.h"


class SegmentClock{
    public:
        SegmentClock(LEDStrip *ledstrip, UDPLogger *logger);
        void setTime(uint8_t hour, uint8_t minute);
        void setTimeColor(uint32_t color);
        void setTimeBrightness(uint8_t brightness);
        void setBackgroundColor(uint32_t color);
        void setBackgroundBrightness(uint8_t brightness);
        uint8_t getBrightnessTime();
        uint8_t getBrightnessBackground();
        void randomizeBackground();

    private:
        LEDStrip *ledstrip;
        UDPLogger *logger;

        /*
        Definition of led ids per segment. Left to right.
        Each segment has 7 LEDs which are places like this: 
         --0--
        |     |
        5     1
        |     |
         --6--
        |     |
        4     2
        |     |
         --3--
        */

        uint8_t ids_of_first_segment[7] = {84, 81, 80, 88, 90, 91, 86};
        uint8_t ids_of_second_segment[7] = {60, 54, 53, 64, 70, 71, 62};
        uint8_t ids_of_third_segment[7] = {28, 22, 21, 32, 38, 39, 30};
        uint8_t ids_of_fourth_segment[7] = {4, 2, 1, 8, 11, 12, 6};
        uint8_t ids_of_points[2] = {45, 47};
        uint8_t ids_of_background[LED_COUNT- 30];

        uint32_t color_background = LEDStrip::Color24bit(0, 0, 0);
        uint32_t color_time = LEDStrip::Color24bit(255, 255, 255);
        uint8_t brightness_time = 255;
        uint8_t brightness_background = 255;

        void calcBackgroundIds();
        void setSegment(uint8_t *segment_ids, uint8_t digit, uint32_t color_time, uint32_t color_background);
        void setBackground(uint32_t color_background);
        uint32_t scaleColor(uint32_t color, uint8_t brightness);
};

#endif