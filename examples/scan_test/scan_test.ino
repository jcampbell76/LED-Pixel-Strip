/** 
 *  Example Code
 */


#include <avr/pgmspace.h>
#include <led_pixel_strip.h>

const uint16_t kPIXELCNT = 30;
LEDDisp display1(kPIXELCNT);
FXSetAll fxSetAll(&display1);
FXChase fxChase1(&display1, 0, 300, 0x000000);
FXChase fxChase2(&display1, 8, 300, 0x000000);
FXChase fxChase3(&display1, 16, 300, 0x000000);
FXChase fxChase4(&display1, 24, 300, 0x000000);
FXScan fxScan1(&display1, 2, 100, 0x0000FF);
FXScan fxScan2(&display1, 1, 100, 0x000060);
FXScan fxScan3(&display1, 0, 100, 0x000010);

FXScan fxScan4(&display1, 0, 100, 0x000000);
FXScan fxScan5(&display1, 10, 150, 0x000000);
FXScan fxScan6(&display1, 20, 200, 0x000000);


void setup() {                

  STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use

  reset_strip();

}

uint16_t time_cnt = 1;
void loop() 
{
  
  fxSetAll.setColor(0xFFFFFF);
//  fxChase1.propogateAndSet(time_cnt);
//  fxChase2.propogateAndSet(time_cnt);
//  fxChase3.propogateAndSet(time_cnt);
//  fxChase4.propogateAndSet(time_cnt);
  //fxScan1.propogateAndSet(time_cnt);
  //fxScan2.propogateAndSet(time_cnt);
  //fxScan3.propogateAndSet(time_cnt);
  fxScan4.propogateAndSet(time_cnt);
  fxScan5.propogateAndSet(time_cnt);
  fxScan6.propogateAndSet(time_cnt);

  display1.dispWrite();
  reset_strip();
  delay(10);
  time_cnt++;
}


void	reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}

