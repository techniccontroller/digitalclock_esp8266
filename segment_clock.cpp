#include "segment_clock.h"


/**
 * @brief Construct a new Segment Clock:: Segment Clock object
 * 
 * @param ledstrip pointer to the LEDStrip object
 * @param logger pointer to the UDPLogger object
 */
SegmentClock::SegmentClock(LEDStrip *ledstrip, UDPLogger *logger)
{
    this->ledstrip = ledstrip;
    this->logger = logger;
    calcBackgroundIds();
}

/**
 * @brief Show the time on the clock
 * 
 * @param hour hour to show
 * @param minute minute to show
 */
void SegmentClock::setTime(uint8_t hour, uint8_t minute)
{
    clearTempBackground();
    uint32_t scaled_color_time = scaleColor(color_time, brightness_time);
    
    // set time
    if(hour < 10)
    {
        setSegment(ids_of_first_segment, NO_DIGIT, scaled_color_time);
    }
    else
    {
        setSegment(ids_of_first_segment, hour/10, scaled_color_time);
    }
    setSegment(ids_of_second_segment, hour%10, scaled_color_time);
    setSegment(ids_of_third_segment, minute/10, scaled_color_time);
    setSegment(ids_of_fourth_segment, minute%10, scaled_color_time);

    // set points
    ledstrip->setPixel(ids_of_points[0], scaled_color_time);
    ledstrip->setPixel(ids_of_points[1], scaled_color_time);
}

/**
 * @brief Set the color of the time
 */
void SegmentClock::setTimeColor(uint32_t color)
{
    this->color_time = color;
}

/**
 * @brief Set the brightness of the time
 */
void SegmentClock::setTimeBrightness(uint8_t brightness)
{
    this->brightness_time = brightness;
}

/**
 * @brief Set the background color of the clock
 */
void SegmentClock::setBackgroundColor(uint32_t color)
{
    this->color_background = color;
}

/**
 * @brief Set the brightness of the background of the clock
 */
void SegmentClock::setBackgroundBrightness(uint8_t brightness)
{
    this->brightness_background = brightness;
}

/**
 * @brief Get the brightness of the time
 */
uint8_t SegmentClock::getBrightnessTime()
{
    return brightness_time;
}

/**
 * @brief Get the brightness of the background
 */
uint8_t SegmentClock::getBrightnessBackground()
{
    return brightness_background;
}

/**
 * @brief Randomize the background of the clock
 */
void SegmentClock::randomizeBackground()
{
    for(int i = 0; i < LED_COUNT - 30; i++)
    {
        uint8_t brightness = (random(255) / 255.0) * brightness_background;
        uint32_t color = scaleColor(color_background, brightness);
        ledstrip->setPixel(ids_of_background[i], color);    
    }

    for(int i = 0; i < num_temp_background_leds; i++)
    {
        uint8_t brightness = (random(255) / 255.0) * brightness_background;
        uint32_t color = scaleColor(color_background, brightness);
        ledstrip->setPixel(ids_of_background_temp[i], color);
    }
}

/**
 * @brief Calculate the ids of the background LEDs
 */
void SegmentClock::calcBackgroundIds()
{
    int id = 0;
    for(int led = 0; led < LED_COUNT; led++)
    {
        bool is_background = true;
        for(int k = 0; k < 7; k++)
        {
            if(ids_of_first_segment[k] == led){
                is_background = false;
                break;
            }
            if(ids_of_second_segment[k] == led){
                is_background = false;
                break;
            }
            if(ids_of_third_segment[k] == led){
                is_background = false;
                break;
            }
            if(ids_of_fourth_segment[k] == led){
                is_background = false;
                break;
            }
        }
        if(ids_of_points[0] == led){
            is_background = false;
        }
        if(ids_of_points[1] == led){
            is_background = false;
        }
        if(is_background){
            ids_of_background[id] = led;
            id++;
        }
    }
}

/**
 * @brief Draw a digit to a segment of the clock
 * 
 * @param segment_ids ids of the segment leds
 * @param digit digit to show
 * @param color_time color of the segment
 * @param color_background color of the background
 */
void SegmentClock::setSegment(const uint8_t *segment_ids, uint8_t digit, uint32_t color_time)
{
    switch (digit)
    {
    case 0:
        ledstrip->setPixel(segment_ids[0], color_time);
        ledstrip->setPixel(segment_ids[1], color_time);
        ledstrip->setPixel(segment_ids[2], color_time);
        ledstrip->setPixel(segment_ids[3], color_time);
        ledstrip->setPixel(segment_ids[4], color_time);
        ledstrip->setPixel(segment_ids[5], color_time);
        addTempBackground(segment_ids[6]);
        break;

    case 1:
        addTempBackground(segment_ids[0]);
        ledstrip->setPixel(segment_ids[1], color_time);
        ledstrip->setPixel(segment_ids[2], color_time);
        addTempBackground(segment_ids[3]);
        addTempBackground(segment_ids[4]);
        addTempBackground(segment_ids[5]);
        addTempBackground(segment_ids[6]);
        break;
    
    case 2:
        ledstrip->setPixel(segment_ids[0], color_time);
        ledstrip->setPixel(segment_ids[1], color_time);
        addTempBackground(segment_ids[2]);
        ledstrip->setPixel(segment_ids[3], color_time);
        ledstrip->setPixel(segment_ids[4], color_time);
        addTempBackground(segment_ids[5]);
        ledstrip->setPixel(segment_ids[6], color_time);
        break;

    case 3:
        ledstrip->setPixel(segment_ids[0], color_time);
        ledstrip->setPixel(segment_ids[1], color_time);
        ledstrip->setPixel(segment_ids[2], color_time);
        ledstrip->setPixel(segment_ids[3], color_time);
        addTempBackground(segment_ids[4]);
        addTempBackground(segment_ids[5]);
        ledstrip->setPixel(segment_ids[6], color_time);
        break;
    
    case 4:
        addTempBackground(segment_ids[0]);
        ledstrip->setPixel(segment_ids[1], color_time);
        ledstrip->setPixel(segment_ids[2], color_time);
        addTempBackground(segment_ids[3]);
        addTempBackground(segment_ids[4]);
        ledstrip->setPixel(segment_ids[5], color_time);
        ledstrip->setPixel(segment_ids[6], color_time);
        break;
    
    case 5:
        ledstrip->setPixel(segment_ids[0], color_time);
        addTempBackground(segment_ids[1]);
        ledstrip->setPixel(segment_ids[2], color_time);
        ledstrip->setPixel(segment_ids[3], color_time);
        addTempBackground(segment_ids[4]);
        ledstrip->setPixel(segment_ids[5], color_time);
        ledstrip->setPixel(segment_ids[6], color_time);
        break;
    
    case 6:
        ledstrip->setPixel(segment_ids[0], color_time);
        addTempBackground(segment_ids[1]);
        ledstrip->setPixel(segment_ids[2], color_time);
        ledstrip->setPixel(segment_ids[3], color_time);
        ledstrip->setPixel(segment_ids[4], color_time);
        ledstrip->setPixel(segment_ids[5], color_time);
        ledstrip->setPixel(segment_ids[6], color_time);
        break;
    
    case 7:
        ledstrip->setPixel(segment_ids[0], color_time);
        ledstrip->setPixel(segment_ids[1], color_time);
        ledstrip->setPixel(segment_ids[2], color_time);
        addTempBackground(segment_ids[3]);
        addTempBackground(segment_ids[4]);
        addTempBackground(segment_ids[5]);
        addTempBackground(segment_ids[6]);
        break;

    case 8:
        ledstrip->setPixel(segment_ids[0], color_time);
        ledstrip->setPixel(segment_ids[1], color_time);
        ledstrip->setPixel(segment_ids[2], color_time);
        ledstrip->setPixel(segment_ids[3], color_time);
        ledstrip->setPixel(segment_ids[4], color_time);
        ledstrip->setPixel(segment_ids[5], color_time);
        ledstrip->setPixel(segment_ids[6], color_time);
        break;
    
    case 9:
        ledstrip->setPixel(segment_ids[0], color_time);
        ledstrip->setPixel(segment_ids[1], color_time);
        ledstrip->setPixel(segment_ids[2], color_time);
        ledstrip->setPixel(segment_ids[3], color_time);
        addTempBackground(segment_ids[4]);
        ledstrip->setPixel(segment_ids[5], color_time);
        ledstrip->setPixel(segment_ids[6], color_time);
        break;
    
    case NO_DIGIT:
        addTempBackground(segment_ids[0]);
        addTempBackground(segment_ids[1]);
        addTempBackground(segment_ids[2]);
        addTempBackground(segment_ids[3]);
        addTempBackground(segment_ids[4]);
        addTempBackground(segment_ids[5]);
        addTempBackground(segment_ids[6]);
        break;
    
    default:
        break;
    }
}

/**
 * @brief Set the background pixels of the clock
 */
void SegmentClock::setBackground(uint32_t color_background)
{
    for(int i = 0; i < LED_COUNT - 30; i++)
    {
        ledstrip->setPixel(ids_of_background[i], color_background);
    }
}

/**
 * @brief Scale a color with a brightness value
 * 
 * @param color color to scale
 * @param brightness brightness value
 * 
 * @return scaled color
 */
uint32_t SegmentClock::scaleColor(uint32_t color, uint8_t brightness)
{
    uint8_t red = color >> 16 & 0xff;
    uint8_t green = color >> 8 & 0xff;
    uint8_t blue = color & 0xff;

    red = red * brightness / 255;
    green = green * brightness / 255;
    blue = blue * brightness / 255;

    return LEDStrip::Color24bit(red, green, blue);
}

void SegmentClock::clearTempBackground()
{
    num_temp_background_leds = 0;
}

void SegmentClock::addTempBackground(uint8_t id)
{
    ids_of_background_temp[num_temp_background_leds] = id;
    num_temp_background_leds++;
}
