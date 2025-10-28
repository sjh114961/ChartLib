#include <ChartLib.h>

#define cs 10
#define dc 9
#define rst 8

TFT tft = TFT(cs, dc, rst);

ChartLib myCharts(tft); // Create an instance of your library class

void setup() {
  tft.begin();
  myCharts.initVertical(tft); // Call library methods as needed
}

void loop() {
  int data;
  int i;

  myCharts.initVertical(tft);

// display vertical bar chart
//  myCharts.setLocation(10, 100);  // for testing
//  myCharts.setColors(GREEN, BLUE, BLACK, WHITE, RED);
/*  for testing
  myCharts.setLimits(20, 150);
  myCharts.setIncrement(30);
  myCharts.setNumFormat(2, 0);
*/

  myCharts.setOrientation(45);  // landscape mode, don't understand why 45
  myCharts.clear();
  
  myCharts.DrawBarChartV();
//  delay(500); // for testing
// sweep up
  for(i= 0; i <2; i++)
  {
    for(data =0; data <= 100; data +=5)
    {
      myCharts.updateChart(data);
    }
  }
  
/* testing only 
  myCharts.setLabel("FUN");  // run DrawBarChartV() because it is the only one that writes label
  myCharts.DrawBarChartV();
*/

// sweep down
  for(i= 0; i <2; i++)
  {
    for(data = 100; data >= 0; data -=5)
    {
      myCharts.updateChart(data);
    }
  }
  
  myCharts.initHorizonal(tft);
  myCharts.clear();
  myCharts.DrawBarChartH();

  for(i= 0; i <2; i++)
  {
    for(data = 0; data <= 10; data +=1)
    {
      myCharts.updateChartH(data);
    }
  }
  delay(500);

  for(i= 2; i > 0; i--)
  {
    for(data = 10; data >0 ; data -=1)
    {
      myCharts.updateChartH(data);
    }
  }

  tft.background(YELLOW);
  myCharts.initDial(tft);
//  myCharts.setDialColor(WHITE, RED);   // for testing
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

  tft.background(YELLOW);
  myCharts.initsqMeter(tft);
  myCharts.sqMeter();
  delay(1000);

  for(i = 0; i <= 5; i++)
  {
    myCharts.updateSqMeter(i);
  }

  for(i = 5; i >= 0; i--)
  {
    myCharts.updateSqMeter(i);
  }

  delay(1000);
}

