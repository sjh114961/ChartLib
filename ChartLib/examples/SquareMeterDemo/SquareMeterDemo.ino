/*
* Program: SquareMeterDemo
* Author: Stephen J. Heilman
* Date: 10/27/2025
*
* Program demonstrates the use of the sqMeter in the ChartLib Class on the 1.8 
* TFT module It is important that the in initsqMeter() function be called prior 
* using sqMeter(). This initializes all varibles to default values.
* After calling initsqMeter(), any custom values can be set such as:
*  myCharts.setDialColor(BLUE, RED);
*  myCharts.setLabel("Amps");
*  myCharts.setIncrement(2);
*  myCharts.setLimits(0, 10);
* An instance of the TFT library is required and passed to ChartLib class
*/

#include <ChartLib.h>

#define cs 10
#define dc 9
#define rst 8

TFT tft = TFT(cs, dc, rst);   // create a TFT object to use with ClassLib

ChartLib myCharts(tft); // Create an instance of your library class

void setup() {
  tft.begin();
}

void loop() {
  int data;
  int i;

  tft.background(YELLOW);
  myCharts.initsqMeter(tft);  // initialize sqMeter
  myCharts.sqMeter();         // Start sqMeter
  delay(1000);

  // sweep up
  for(i = 0; i <= 5; i++)
  {
    myCharts.updateSqMeter(i);
  }

  // sweep down
  for(i = 5; i >= 0; i--)
  {
    myCharts.updateSqMeter(i);
  }

  // lets now change the colors, label, tick increments and limits 
  myCharts.setDialColor(BLUE, RED);
  myCharts.setLabel("Amps");
  myCharts.setIncrement(2);
  myCharts.setLimits(0, 10);
  myCharts.sqMeter();

  // sweep up
  for(i = 0; i <= 10; i++)
  {
    myCharts.updateSqMeter(i);
  }

  //sweep down
  for(i = 10; i >= 0; i--)
  {
    myCharts.updateSqMeter(i);
  }

  delay(1000);
}

