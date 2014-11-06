
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

const int32_t kPIXEL2POS = 1000;  /** Multiplier to convert pixels to a position */  

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

  uint32_t* _displayBuff; /** display buffer */
  uint32_t _numPixels;  /** number of pixels defined at object creation */
private:

 
  /**
   * Write a 24 pulse to LED strip
   *                  
   * @todo modify to only send reference to display buffer
   * @todo see if pwm generator on arduio would work vs bit bang
   * @param the display buffer
   */

  void _sendPixel(uint32_t);
};

/** Effect to set all the pixels in a strip to one color.
 *  Good effect to use to set the base or background color
 */
class FXSetAll{
  public:
  /**
   *  Default Constructor
   */ 
  FXSetAll(){}  //default constructor
  /**
   *  Constructor that ties the effect to a display 
   */ 
  FXSetAll(LEDDisp* disp){_disp = disp; _numPixels = disp->_numPixels;}

  /**
   *  Given a color, set the associated display's buffer all to that color
   */ 
  void setColor(uint32_t);
  private:
  LEDDisp* _disp;
  uint32_t _numPixels;
};


/** 
 * Chase Effects Class - chasing pixels
 *
 * Given an initial position and velocity 
 * provide a chase pattern that updates by calling
 * the propagate function
 */
class FXChase 
{
public:
  /**
   *  Default Constructor
   */
  FXChase(){}
  /**
   *  Initialize FX Chase object given a pointer to a display object,
   *  the initial Pixel to start on, initial velocity, and initial color
   *  
   *  To avoid using floating point operations, the _pos (position) member
   *  is scaled up by kPIXEL2POS and velocity is in 'units' of position/t 
   *  vs. pixel/t
   */
  FXChase(LEDDisp *disp, int32_t initPixel, int32_t initVel, uint32_t initColor) 
  { 
    _disp = disp;
    _dispSize = disp->_numPixels * kPIXEL2POS;    
    _pos = initPixel * kPIXEL2POS;
    _vel = initVel;
    _color = initColor;
  }
  void propogateAndSet(uint32_t time_now);
  void setVel(int32_t vel); /** set velocity */
  int32_t getVel();         /** get velocity */
  void setPos(int32_t pos); /** set position */
  int32_t getPos();         /** get position */
  void setColor(uint32_t color); /**set color */
  uint32_t getColor();  /** get color */

private:
  LEDDisp* _disp;
  uint32_t _dispSize; /** size of the display = number of pixels * kPIXEL2POS */
  int32_t _pos;  /** position of the object _pos/kPIXEL2POS = Pixel position */
  int32_t _vel;  /** speed and direction of chase */
  uint32_t _color; 
  int _time_past; 

};

/** 
 * Scan Effects Class - Scanning pixels
 *
 * Given an initial position and velocity 
 * provide a scan pattern (think Kit from Knight Rider) that updates by calling
 * the propagate function
 * 
 * inherited from the FXChase class - propogateAndSet is overloaded
 */
class FXScan : public FXChase
{
public:
  /**
   *  Default Constructor
   */
  FXScan(){}
  FXScan(LEDDisp *disp, int32_t initPixel, int32_t initVel, uint32_t initColor) : FXChase(disp, initPixel, initVel, initColor){}
  void propogateAndSet(uint32_t time_now); //overload the propogate

private:

};

#endif
