/** @file led_pixel_strip.cpp
 *  @brief functions for classes defined in led_pixel_strip.h 
 * 
 *   
 *  @author    Jacob Campbell 
 *  @version   1.0 
 *  @date      2014 
 *  @copyright GNU Public License.
 */

#include<Arduino.h>
#include<led_pixel_strip.h>

void FXSparkle::sparkle(uint32_t dt)
{
  if(_fgPixelOn == false){
    _offTime += dt;
    if(_offTime > _offPeriod){  //if true turn on pixel
      _fgPixelOn = true;
      _offTime = 0;
      _pixelPos = random(_disp->_numPixels);
    }
  }

  if(_fgPixelOn == true){
    _onTime += dt;
    if(_onTime > _onPeriod){ //if true turn off pixel
      _fgPixelOn = false;
      _onTime = 0;
      _offPeriod = random(_aveRate * 2);
    } else {
      _disp->_displayBuff[_pixelPos] = _color;
    }
      
  }
}

void FXScan::propogateAndSet(uint32_t dt)
{
  _pos = _pos + (dt * _vel);
  _disp->_displayBuff[_pos/kPIXEL2POS] = _color; 
  if(_pos > int32_t(_dispSize)-1){ //if at the end of the string start over
    _vel *= -1;
  }
  if(_pos <= 0){  //if at the start of the string start over (negative velocities)
    _vel *= -1;
  }
}

void FXChase::propogateAndSet(uint32_t dt)
{
  _pos = _pos + (dt * _vel);
 if(_pos >= int32_t(_dispSize)){ //if at the end of the string start over
   _pos = 0;
 }
 if(_pos < 0){  //if at the start of the string start over (negative velocities)
   _pos = _dispSize ;
 }
 _disp->_displayBuff[_pos/kPIXEL2POS] = _color; 


}

void FXSetAll::setColor(uint32_t color)
{
  int ii;
  for(ii=0; ii< _numPixels; ii++){
    _disp->_displayBuff[ii] = color;
  }
}

void LEDDisp::addOverlay()
{
  int ii;
  for(ii=0;ii<_numPixels;ii++){
    _displayBuff[ii] = 0x000000;
  } 
}

void LEDDisp::setBackColor(uint32_t backColor)
{
  int32_t ii;
  for(ii=0;ii<_numPixels;ii++){
    _displayBuff[ii] = backColor;
  } 
}


void LEDDisp::dispWrite()
{
  int32_t ii;

  noInterrupts();
  for (ii=0;ii<_numPixels;ii++)
  {
    _sendPixel(_displayBuff[ii]);
  }
  interrupts();
} 



void LEDDisp::_sendPixel(uint32_t data)
// note:  each nop is 62.5 ns in length thus
//        28*62.5 = 1750 ns (1.75 us) 
//         9*62.5 = 562.5 ns
//         3*62.5 = 187.5 ns
{
  int16_t i;
  uint32_t j=0x800000;

  for (i=0;i<24;i++)
  {
    if (data & j)
    {
//        28*62.5 = 1750 ns (1.75 us) 

      PORTC |= _outBit;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");

      /*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");  
      __asm__("nop\n\t");        
      /*----------------------------*/
      //DATA_0;
      PORTC &= !_outBit;
    }
    else
    {
      //   9*62.5 = 562.5 ns
      //DATA_1;
      PORTC |= _outBit;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      //DATA_0;
      PORTC &= !_outBit;
      /*----------------------------*/
     //     3*62.5 = 187.5 ns
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");      
      /*----------------------------*/
    }

    j>>=1;
  }


}

