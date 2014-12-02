
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

FXScan fxScan4(&display1, 0, 100, kDARKORANGE);
FXScan fxScan5(&display1, 10, 150, kGREEN);
FXScan fxScan6(&display1, 20, 200, kBLACK);

FXSparkle fxSparkle1(&display1, 50, 10, kWHITE);
void setup() {                

  STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use

  reset_strip();

}

uint32_t time_now = 1;
uint32_t time_past = 0;
uint32_t time_step = 1;
uint32_t dt;
void loop() 
{
  dt = time_now - time_past;
  if(time_now < time_past){
     time_now = 0;
  } 
  time_past = time_now;
  time_now += time_step;
  
  fxSetAll.setColor(kOLIVE);
//  fxChase1.propogateAndSet(dt);
//  fxChase2.propogateAndSet(dt);
//  fxChase3.propogateAndSet(dt);
//  fxChase4.propogateAndSet(dt);
  //fxScan1.propogateAndSet(dtdt);
  //fxScan2.propogateAndSet(dt);
  //fxScan3.propogateAndSet(dt);
//  fxScan4.propogateAndSet(dt);
//  fxScan5.propogateAndSet(dt);
//  fxScan6.propogateAndSet(dt);
 fxSparkle1.sparkle(dt);
 
  display1.dispWrite();
  reset_strip();
  delay(10);
  
}


void	reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}

