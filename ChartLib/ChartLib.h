#ifndef CHARTLIB_H
#define CHARTLIB_H

#include <Arduino.h>
#include <TFT.h>
#include <SPI.h>

/*
These are the predefined colors to ease use.
Colors are in BGR format (blue, green, red).
0 0 0 0  0|0 0 0  0 0 0|0  0 0 0 0|
  BLUE        GREEN         RED
*/
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

/* These are not yet defined
#define LTTEAL    0xBF5F
#define LTORANGE        0xFE73
#define LTPINK          0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY          0xE71C
#define TEAL    0x0438
#define PINK          0xF81F
#define PURPLE    0x801F
#define GREY        0xC618

#define DKTEAL    0x020C
#define DKORANGE        0x8200
#define DKPINK          0x9009
#define DKPURPLE      0x4010
#define DKGREY        0x4A49
*/

class ChartLib {
private:
    TFT &tft;     // The TFT object to be used
    double x;     // initial x postion, depends on graph type
    double y;     // initial y postion, depends on graph type
    double w;     // width of chart
    double h;     // height if chart
    double loval; // lowest value in chart
    double hival; // highest value in chart 
    double inc;   // increment of the tick marks 
    double curval;// current value of chart 
    double preval;// previous value of chart, internal use only
    int dig;      // number of digits to display not counting decimal
    int dec;      // nuber of decimal digits to display
    unsigned int barcolor;  // active bar color
    unsigned int voidcolor; // inactive bar color
    unsigned int bordercolor;   //chart bordercolor
    unsigned int textcolor; // text color
    unsigned int backcolor; // background color of chart
    unsigned int needlecolor; // color to applt to needle of dial and square chart
    unsigned int dialcolor;   // color of the dial or square chart
    String label; // Label for chart
    int r;        // radius foe dial chart and square chart
    double sa;    // sweep angle, how of the dial or square chart to sweep

    // following are interally used and calculated
    double tx, ty, px, py, pix, piy, plx, ply, prx, pry;

public:
    ChartLib(TFT &tftInstance);
    void initHorizonal(TFT &theScreen);
    void initVertical(TFT &theScreen);
    void DrawBarChartV();
    void updateChart(int value);
    void updateChartH(int value);
    void DrawBarChartH();
    void clear();
    String Format(double val, int dec, int dig );
    void initDial(TFT &theScreen);
    void setDial(double value);
    void DrawDial();
    void updateDrawDial(double value);
    void initsqMeter(TFT &theScreen);
    void sqMeter();
    void updateSqMeter(double value);
    void setLocation(int myx, int myy);
    void setLimits(int low, int high);
    void setIncrement(int value);
    void setNumFormat(int digits, int decimalDigits);
    void setColors(unsigned int actColor, unsigned int inactColor, unsigned int border, unsigned int txtcolor, unsigned int background);
    void setDialColor(unsigned int needle, unsigned int dial);
  	void setOrientation(int angle);
   	void setLabel(String name);
	void setSize(int width, int height);


};

#endif


