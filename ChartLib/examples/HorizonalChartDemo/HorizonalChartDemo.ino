/*
* Program: HorizonlChartDemo
* Author: Stephen J. Heilman
* Date: 10/27/2025
*
* Program demonstrates the use of the DrawBarChartH
* the ChartLib Class on the 1.8 TFT module It 
* is important that the in initHorizonal() function be called prior 
* using DrawBarChartH(). This initializes all varibles to default values.
* After calling initHorizonal(), any custom values can be set such as:
* myCharts.setSize(140, 50);
* myCharts.setColors(RED, BLUE, BLACK, BLACK, YELLOW);
* myCharts.setLocation(10, 60);
* myCharts.DrawBarChartH();
* An instance of the TFT library is required and passed to ChartLib class
*/

#include <ChartLib.h>

/* preset defined for colors in BGR format
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
}

void loop() {
  int data;
  int i;

  
  myCharts.initHorizonal(tft);


  myCharts.clear();
  myCharts.DrawBarChartH();

  //sweep right
  for(data = 0; data <= 10; data +=1)
  {
    myCharts.updateChartH(data);
  }
  delay(500);

  // sweep left
  for(data = 10; data >= 0; data -=1)
  {
    myCharts.updateChartH(data);
  }
  delay(500);
  
  tft.background(YELLOW);
  myCharts.setSize(140, 50);
  myCharts.setColors(RED, BLUE, BLACK, BLACK, YELLOW);
  myCharts.setLocation(10, 60);
  myCharts.DrawBarChartH();

  for(data = 0; data <= 10; data +=1)
  {
    myCharts.updateChartH(data);
  }

  for(data = 10; data >= 0; data -=1)
  {
    myCharts.updateChartH(data);
  }
 
  delay(1000);
}
