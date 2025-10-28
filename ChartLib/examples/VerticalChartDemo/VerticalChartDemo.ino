/*
* Program: VerticalChartDemo
* Author: Stephen J. Heilman
* Date: 10/27/2025
*
* Program demonstrates the use of the sqMeter in the ChartLib Class on the 1.8 
* TFT module It is important that the in initsqMeter() function be called prior 
* using sqMeter(). This initializes all varibles to default values.
* After calling initsqMeter(), any custom values can be set such as:
*  myCharts.setOrientation(45);  // landscape mode, don't understand why 45
*  myCharts.setLabel("DEMO");
*  myCharts.setSize(20, 75);
* An instance of the TFT library is required and passed to ChartLib class
*/

#include <ChartLib.h> // Use angle brackets for installed libraries

/* prededefined in ChartLib
#define WHITE         0xFFFF
#define BLACK         0x0000

#define RED           0x001F
#define GREEN         0x07E0
#define BLUE			    0xF800

#define LTRED         0x087F
#define LTGREEN       0x1FF1
#define LTBLUE    	  0xF686

#define DKRED         0x0018
#define DKBLUE        0x3100
#define DKGREEN       0x00E0

#define YELLOW        0x07FF
#define CYAN          0xFFE0
#define MAGENTA       0xF81F

#define LTYELLOW      0x4FFF
#define LTCYAN        0xFFE4
#define LTMAGENTA     0xF9FF

#define DKYELLOW        0x0410
#define DKCYAN          0x8400
#define DKMAGENTA       0x8010

#define ORANGE          0x031F
#define LTORANGE        0x131F
*/


#define cs 10
#define dc 9
#define rst 8

TFT tft = TFT(cs, dc, rst);

ChartLib myCharts(tft); // Create an instance of your library class

void setup() {
  tft.begin();
  tft.background(YELLOW);
  myCharts.setOrientation(45);  // landscape mode, don't understand why 45
  myCharts.setLabel("DEMO");
}

void loop() {
  int data;
  int i;

  myCharts.initVertical(tft); // Call library methods as needed

  myCharts.setSize(20, 75);
  myCharts.DrawBarChartV();

// sweep up
  for(data =0; data <= 100; data +=5)
  {
    myCharts.updateChart(data);
  }

// sweep down
  for(data = 100; data >= 0; data -=5)
  {
    myCharts.updateChart(data);
  }
  delay(1000);

  myCharts.setSize(50, 75);
  myCharts.setColors(RED, BLUE, BLACK, BLACK, YELLOW);
  myCharts.setLabel("TEST");
  myCharts.DrawBarChartV();

// sweep up
  for(data =0; data <= 100; data +=5)
  {
    myCharts.updateChart(data);
  }

// sweep down
  for(data = 100; data >= 0; data -=5)
  {
    myCharts.updateChart(data);
  }
  delay(1000);
  // erase the screen
  tft.background(YELLOW);
}

