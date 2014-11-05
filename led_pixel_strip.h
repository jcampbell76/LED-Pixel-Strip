
/** @file led_pixel_strip.h
 *  @brief Set of Classes to Build LED Pixel Strip light effects. 
 * 
 *   
 *   
 *  @details   This class is used to demonstrate a number of section commands.
 *  @author    Jacob Campbell 
 *  @version   1.0 
 *  @date      2014 
 *  @copyright GNU Public License.
 */


#ifndef LED_PIXEL_STRIP
#define LED_PIXEL_STRIP

#include<Arduino.h>

#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO


const uint32_t kRED = 0x0000FF;
const uint32_t kGREEN = 0xFF0000;
const uint32_t kBLUE = 0x00FF00;

/** Handles modifications to the display buffer and sends display buffer to LED pixel strip.
 *
 */
class LEDDisp{
public:

  /** Default Constructor */
  LEDDisp(){
  }
  /** 
   *  Initializes LED Display object 
   *  
   *  @param Number of pixels in LED light strip
   */ 
  LEDDisp(int numPixelsToCreate)
  {
    _displayBuff = new uint32_t[numPixelsToCreate];
    _numPixels = numPixelsToCreate;
  }
  /**
   *  Delete the internal display buffer 
   */ 
  ~LEDDisp(){
    delete [] _displayBuff;
  }
  
  /**  
   * Write the display buffer to the LED pixel strip.
   *       
   */
  void dispWrite();

  /**
   * Add FX overlay to current display buffer 
   *
   */
  void addOverlay();
 
  /**
   *  Set display buffer background color
   */ 
  void setBackColor(uint32_t);

private:

  uint32_t* _displayBuff; /** display buffer */
  uint16_t _numPixels;  /** number of pixels defined at object creation */
 
  /**
   * Write a 24 pulse to LED strip
   *                  
   * @todo modify to only send reference to display buffer
   * @todo see if pwm generator on arduio would work vs bit bang
   * @param the display buffer
   */

  void _sendPixel(uint32_t);
};

/** 
 * Chase Effects Class - chasing pixels
 *
 * Given an initial position and velocity 
 * provide a chase pattern that updates by calling
 * the propagate function
************************************************/
class FXChase
{
public:

private:

};

#endif
