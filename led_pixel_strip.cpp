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



void LEDDisp::addOverlay()
{
  int ii;
  for(ii=0;ii<_numPixels;ii++){
    _displayBuff[ii] = kGREEN;
  } 
}

void LEDDisp::setBackColor(uint32_t backColor)
{
  int ii;
  for(ii=0;ii<_numPixels;ii++){
    _displayBuff[ii] = backColor;
  } 
}


void LEDDisp::dispWrite()
{
  int ii;

  noInterrupts();
  for (ii=0;ii<_numPixels;ii++)
  {
    _sendPixel(_displayBuff[ii]);
  }
  interrupts();
} 



void LEDDisp::_sendPixel(uint32_t data)
{
  int i;
  unsigned long j=0x800000;

  for (i=0;i<24;i++)
  {
    if (data & j)
    {
      DATA_1;
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
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      DATA_0;
      /*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");      
      /*----------------------------*/
    }

    j>>=1;
  }


}

