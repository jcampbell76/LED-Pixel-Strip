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
// note:  each nop is 62.5 ns in length thus
//        28*62.5 = 1750 ns (1.75 us) 
//         9*62.5 = 562.5 ns
//         3*62.5 = 187.5 ns
{
  int i;
  unsigned long j=0x800000;

  for (i=0;i<24;i++)
  {
    if (data & j)
    {
//        28*62.5 = 1750 ns (1.75 us) 
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
      //   9*62.5 = 562.5 ns
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
     //     3*62.5 = 187.5 ns
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");      
      /*----------------------------*/
    }

    j>>=1;
  }


}

