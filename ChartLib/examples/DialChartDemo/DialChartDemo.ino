/*
* Program: DialChartDemo
* Author: Stephen J. Heilman
* Date: 10/27/2025
*
* Program demonstrates the use of the DrawDial
* the ChartLib Class on the 1.8 TFT module It 
* is important that the in initDial() function be called prior 
* using DrawDial(). This initializes all varibles to default values.
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

TFT tft = TFT(cs, dc, rst);

ChartLib myCharts(tft); // Create an instance of your library class

void setup() {
  tft.begin();
}

void loop() {
  int data;
  int i;

  myCharts.setNumFormat(2, 0);
  myCharts.setOrientation(45);  // landscape mode, don't understand why 45
  myCharts.clear();

  tft.background(YELLOW);
  myCharts.initDial(tft);
  myCharts.DrawDial();

// sweep the dial
  for(i = 0; i<=100; i+=5)
  {
    myCharts.updateDrawDial(i);
  }
  
  for(i = 100; i>=0; i-=5)
  {
    myCharts.updateDrawDial(i);
  }

  delay(1000);
  tft.background(YELLOW);
  myCharts.initDial(tft);
  myCharts.setDialColor(WHITE, RED);   // for testing
  myCharts.setLimits(0, 150);
  myCharts.setIncrement(30);
  myCharts.setLabel("TEST");
  myCharts.DrawDial();

// sweep the dial
  for(i = 0; i<=150; i+=5)
  {
    myCharts.updateDrawDial(i);
  }
  
  for(i = 150; i>=0; i-=5)
  {
    myCharts.updateDrawDial(i);
  }
  delay(1000);
}

