#ifndef segment_clock_h
#define segment_clock_h

#include "ledstrip.h"
#include "udplogger.h"

#define NO_DIGIT 10

class SegmentClock{
    public:
        SegmentClock(LEDStrip *ledstrip, UDPLogger *logger);
        void setTime(uint8_t hour, uint8_t minute);
        void setTimeColor(uint32_t color);
        void setTimeBrightness(uint8_t brightness);
        void setBackgroundColor(uint32_t color);
        void setBackgroundBrightness(uint8_t brightness);
        void setBackgroundAnimationSpeed(float speed);
        uint8_t getBrightnessTime();
        uint8_t getBrightnessBackground();
        float getBackgroundAnimationSpeed();
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

        const uint8_t ids_of_first_segment[7] = {84, 81, 80, 88, 90, 91, 86};
        const uint8_t ids_of_second_segment[7] = {60, 54, 53, 64, 70, 71, 62};
        const uint8_t ids_of_third_segment[7] = {28, 22, 21, 32, 38, 39, 30};
        const uint8_t ids_of_fourth_segment[7] = {4, 2, 1, 8, 11, 12, 6};
        const uint8_t ids_of_points[2] = {45, 47};
        const static uint8_t num_segment_leds = 30;
        const static uint8_t num_background_leds = LED_COUNT - num_segment_leds;
        uint8_t num_temp_background_leds = 0; // number of segment leds that are temporarly are part of the background
        uint8_t ids_of_background[num_background_leds];
        uint8_t ids_of_background_temp[num_segment_leds];

        // Animation state for smooth brightness changes
        float* speeds;     // Array of speed factors for each LED
        float* phases;     // Array of phase offsets for each LED
        float background_time = 0;    // Global time for background animation in seconds (updated every 20ms)
        float animation_speed = 1.0;  // Default speed multiplier (1.0 = normal speed)

        uint32_t color_background = LEDStrip::Color24bit(0, 0, 0);
        uint32_t color_time = LEDStrip::Color24bit(255, 255, 255);
        uint8_t brightness_time = 255;
        uint8_t brightness_background = 255;

        void calcBackgroundIds();
        void setSegment(const uint8_t *segment_ids, uint8_t digit, uint32_t color_time);
        void setBackground(uint32_t color_background);
        uint32_t scaleColor(uint32_t color, uint8_t brightness);
        void clearTempBackground();
        void addTempBackground(uint8_t id);
};

#endif