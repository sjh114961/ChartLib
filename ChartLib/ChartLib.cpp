#include <Arduino.h>
#include <ChartLib.h>

ChartLib::ChartLib(TFT &tftInstance) : tft(tftInstance) 
{}

// initialization for horizonal bar chart
	void ChartLib::initHorizonal(TFT &theScreen) 
		{
			tft = theScreen;	// link to the TFT object that the chart will use
			x = 10;				// x starting postion fom upper left
			y = 80;				// y starting posiion from upper left
			w = 140;			// width of bar chart
			h = 20;				// height of bar chart
			loval = 0;			// lowest value to be used
			hival = 10;			// highest value to be used
			inc = 2;			// increments for tick marks
			curval = 0;			// current or starting value
			dig = 2;			// number of digits not counting decimal point
			dec = 1;			// number if digits after decimal point
			barcolor = GREEN;	// active bar color
			voidcolor = BLUE;	// inactive bar color
			bordercolor = RED;	// border color
			textcolor = BLACK;	// text color
			backcolor = YELLOW;	// background color
			label = "HBAR";		// chart name
			Serial.begin(115200);
		}

// initialization for veritcal bar chart
	void ChartLib::initVertical(TFT &theScreen) 
		{
			tft = theScreen;	// link to the TFT object that the chart will use
			x = 10;				// x starting postion fom upper left
			y = 100;			// y starting posiion from upper left
			w = 20;				// width of bar chart
			h = 75;				// height of bar chart
			loval = 0;			// lowest value to be used
			hival = 100;		// highest value to be used
			inc = 20;			// increments for tick marks
			curval = 5;			// current or starting value
			dig = 2;			// number of digits not counting decimal point
			dec = 0;			// number if digits after decimal point
			barcolor = BLUE;	// active bar color
			voidcolor = GREEN;	// inactive bar color
			bordercolor = RED;	// border color
			textcolor = BLUE;	// text color
			backcolor = YELLOW;	// background color
			label = "VBAR";		// chart name
		}

	void ChartLib::DrawBarChartV()
	  {  
		double stepval, range;
		double my, level;
		double i, data;
		String textString;

	  // draw the border, scale, and label once
	  // avoid doing this on every update to minimize flicker
		tft.drawRect(x - 1, y - h - 1, w + 2, h + 2, bordercolor);

		tft.setTextColor(textcolor, backcolor);
		tft.setTextSize(1);
		tft.setCursor(x , y + 10);
		tft.println(label);

		// step val basically scales the hival and low val to the height
		// deducting a small value to eliminate round off errors
		// this val may need to be adjusted
		stepval = ( inc) * (double (h) / (double (hival - loval))) - .001;
		for (i = 0; i <= h; i += stepval) {
		  my =  y - h + i;

		  //draw tick marks
		  tft.drawFastHLine(x + w + 1, my,  5, textcolor);

		  // draw lables
		  tft.setTextSize(1);
		  tft.setTextColor(textcolor, backcolor);
		  tft.setCursor(x + w + 12, my - 3 );
		  
		  // data is value printed at tick mark;
		  data = hival - ( i * (inc / stepval));
		  tft.println(Format(data, dig, dec));
		}
	  }; // end of DrawBarChartV    

	void ChartLib::updateChart(int value)
		{
		  int level;
		  
		  curval = value;

		  // compute level of bar graph that is scaled to the  height and the hi and low vals
		  // this is needed to accompdate for +/- range
		  level = (h * (((curval - loval) / (hival - loval))));

		  // draw the bar graph
		  // write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
		  tft.fillRect(x, y - h, w, h - level,  voidcolor);
		  tft.fillRect(x, y - level, w,  level, barcolor);
		  // write the current value
		  tft.setTextColor(textcolor, backcolor);
		  tft.setTextSize(2);
		  tft.setCursor(x , y - h - 23);
		  // to erase old data, 
		  // might be better to write old data in backcolor
		  tft.println("        "); 
		  tft.setCursor(x , y - h - 23);
		  tft.println(curval, dec);
		} // end of updateChart

// update the value in the Horizonal chart
	void ChartLib::updateChartH(int value)
		{
			int level;
			int size;
			double stepval;

			curval = value;
			
			// compute level of bar graph that is scaled to the  height and the hi and low vals
			// this is needed to accompdate for +/- range
			level = (h * (((curval - loval) / (hival - loval))));

			// draw the bar graph
			// write a upper and lower bar to minimize flicker cause by blanking out bar and redraw on update
			size = inc * value;

			stepval =  (double (w) / (double (hival - loval))) - .00001;
		
			// draw the text
			// write the current value
			tft.setTextColor(textcolor, backcolor);
			tft.setTextSize(2);
//	tft.setCursor(x , y - h - 15);
//			tft.setCursor(x , y - h - 5);
		tft.setCursor(x , y-35);

//			Serial.println(y-35);
			
			// erase old header value
			// might be better to write old data in backcolor

			tft.println("         ");

			// write new data value
//	tft.setCursor(x , y - h - 15);
			tft.setCursor(x , y-35);
			tft.println(Format(value, dec, dig));

			tft.fillRect(x , y, w, h, voidcolor);
			tft.fillRect(x , y, value * stepval, h, barcolor);
		} // end of updateChartH

	  void ChartLib::DrawBarChartH()
	  {
		double stepval, range;
		double mx, level;
		double i, data, xvalue;

		// draw the border, scale, and label once
		// avoid doing this on every update to minimize flicker
		// draw the border and scale
		tft.drawRect(x , y , w, h, bordercolor);
		tft.setTextColor(textcolor, backcolor);

		tft.setTextSize(1);
		tft.setCursor(x , y - 15);

		tft.println(label);
		  
		// step val basically scales the hival and low val to the width
		stepval =  inc * (double (w) / (double (hival - loval))) - .00001;

		// draw the text
		data = 0;
		for (i = 0; x + (i * stepval) <= w; i += 1) 
		{
			xvalue = x + (i * stepval);
		  tft.drawFastVLine(xvalue , y + h + 1,  5, textcolor);
		  tft.setCursor(x + (i * stepval) -5, y + h + 7);

		  tft.print(Format(data, dig, dec));
/*
			tft.setCursor(20, 20);
			tft.print("X ");
			tft.print(x);
			tft.print(" ");
			tft.print(y-h);
*/

		  data = data + inc;
		}
	  }// end of updateChartH

	// set entire display to background color to clear it
	  void ChartLib::clear()
	  {
		tft.background(backcolor);
	  }

	  String ChartLib::Format(double val, int dec, int dig ) 
	  {
		int addpad = 0;
		char sbuf[20];
		String condata = (dtostrf(val, dec, dig, sbuf));
		return(condata);
	  } // end of Format

		void ChartLib::initDial(TFT &theScreen)
		{
			tft = theScreen;  // Reference to the TFT instance
			x = 75;           // center x
			y = 65;           // center y
			r = 60;           // radius
			loval = 0;        // lowest value
			hival = 100;        // highest value
			inc = 20;          // tick mark increment
			sa = 200;         // total sweep anagle
			curval = 0;       // current data value
			preval = 0;       // previous data value
			dig = 2;          // digits to display not including '.'
			dec = 1;          // number of decimal digits
			needlecolor = RED;  // needle color
			dialcolor = WHITE;  // dial face color
			textcolor = BLACK;  // text color
			label = " PSI";    // dial face label
		} // end of initDial
			

	void ChartLib::setDial(double value)
	{
	  curval = value;
	  DrawDial();
	} // end of setDial

	void ChartLib::DrawDial()
	{
		double ix, iy, ox, oy, lx, rx, ly, ry, i, offset, stepval, data, angle;
		double degtorad = .0174532778;

		tft.fillCircle(x, y, r - 5, dialcolor);
		tft.drawCircle(x, y, r, needlecolor);
		tft.drawCircle(x, y, r - 1, needlecolor);
		tft.setTextColor(textcolor, dialcolor);
		tft.setTextSize(1);
		tft.setCursor(x - 10, y + 10);
		tft.println(label);

		// draw the current value
		tft.setTextSize(2);
		tft.setTextColor(textcolor, dialcolor);
		tft.setCursor(x - 15, y + 20 );
		tft.println(Format(curval, dig, dec));
	  
		// center the scale about the vertical axis--and use this to offset the needle, and scale text
		offset = (270 +  sa / 2) * degtorad;

		// find hte scale step value based on the hival low val and the scale sweep angle
		// deducting a small value to eliminate round off errors
		// this val may need to be adjusted
		stepval = ( inc) * (double (sa) / (double (hival - loval))) + .00;

		// draw the scale and numbers
		// note draw this each time to repaint where the needle was
		for (i = 0; i <= sa; i += stepval) 
		{
			angle = ( i  * degtorad);
			angle = offset - angle ;
			ox =  (r - 2) * cos(angle) + x;
			oy =  (r - 2) * sin(angle) + y;
			ix =  (r - 10) * cos(angle) + x;
			iy =  (r - 10) * sin(angle) + y;
			tx =  (r - 20) * cos(angle) + x;
			ty =  (r - 20) * sin(angle) + y;
			tft.drawLine(ox, oy, ix, iy, textcolor);
			tft.setTextSize(1.5);
			tft.setTextColor(textcolor, dialcolor);
			tft.setCursor(tx - 10, ty );

			data = hival - ( i * (inc / stepval)) ;
			tft.println(Format(data, dig, dec));
		}
	  
		// compute and draw the needle
		angle = (sa * (1 - (((curval - loval) / (hival - loval)))));
		angle = angle * degtorad;
		angle = offset - angle  ;
		ix =  (r - 10) * cos(angle) + x;
		iy =  (r - 10) * sin(angle) + y;
		// draw a triangle for the needle (compute and store 3 vertiticies)
		lx =  5 * cos(angle - 90 * degtorad) + x;
		ly =  5 * sin(angle - 90 * degtorad) + y;
		rx =  5 * cos(angle + 90 * degtorad) + x;
		ry =  5 * sin(angle + 90 * degtorad) + y;
		// first draw the previous needle in dial color to hide it
		// note draw performance for triangle is pretty bad...

		tft.fillTriangle (pix, piy, plx, ply, prx, pry, dialcolor);
		tft.drawTriangle (pix, piy, plx, ply, prx, pry, dialcolor);

		// then draw the old needle in need color to display it
		tft.fillTriangle (ix, iy, lx, ly, rx, ry, needlecolor);
		tft.drawTriangle (ix, iy, lx, ly, rx, ry, textcolor);

		// draw a cute little dial center
		tft.fillCircle(x, y, 8, textcolor);
		//save all current to old so the previous dial can be hidden
		pix = ix;
		piy = iy;
		plx = lx;
		ply = ly;
		prx = rx;
		pry = ry;

	}// end of Drawdial

	void ChartLib::updateDrawDial(double value)
	{
		double ix, iy, ox, oy, lx, rx, ly, ry, i, offset, stepval, data, angle;
		double degtorad = .0174532778;

		curval = value;

		// erase previous data value by writing previous value in dialcolor
		tft.setTextColor(dialcolor);
		tft.setTextSize(2);
		tft.setCursor(x - 15, y + 20 );
		tft.println(Format(preval, dig, dec));

		// print data value
		tft.setTextColor(textcolor);
		tft.setTextSize(2);
		tft.setCursor(x - 15, y + 20 );
		tft.println(Format(curval, dig, dec));

		preval = curval;

		// redo dial digits
		// find hte scale step value based on the hival low val and the scale sweep angle
		// deducting a small value to eliminate round off errors
		// this val may need to be adjusted

		stepval = ( inc) * (double (sa) / (double (hival - loval))) + .00;
		// center the scale about the vertical axis--and use this to offset the needle, and scale text
		offset = (270 +  sa / 2) * degtorad;

		for (i = 0; i <= sa; i += stepval) 
		{
			angle = ( i  * degtorad);
			angle = offset - angle ;
			ox =  (r - 2) * cos(angle) + x;
			oy =  (r - 2) * sin(angle) + y;
			ix =  (r - 10) * cos(angle) + x;
			iy =  (r - 10) * sin(angle) + y;
			tx =  (r - 20) * cos(angle) + x;
			ty =  (r - 20) * sin(angle) + y;
			tft.drawLine(ox, oy, ix, iy, textcolor);
			tft.setTextSize(1.5);
			tft.setTextColor(textcolor, dialcolor);
			tft.setCursor(tx - 10, ty );

			data = hival - ( i * (inc / stepval)) ;
			tft.println(Format(data, dig, dec));
		}

		// compute and draw the needle
		angle = (sa * (1 - (((curval - loval) / (hival - loval)))));
		angle = angle * degtorad;
		angle = offset - angle  ;
		ix =  (r - 10) * cos(angle) + x;
		iy =  (r - 10) * sin(angle) + y;

		// draw a triangle for the needle (compute and store 3 vertiticies)
		lx =  5 * cos(angle - 90 * degtorad) + x;
		ly =  5 * sin(angle - 90 * degtorad) + y;
		rx =  5 * cos(angle + 90 * degtorad) + x;
		ry =  5 * sin(angle + 90 * degtorad) + y;

		// first draw the previous needle in dial color to hide it
		// note draw performance for triangle is pretty bad...
		tft.fillTriangle (pix, piy, plx, ply, prx, pry, dialcolor);
		tft.drawTriangle (pix, piy, plx, ply, prx, pry, dialcolor);

		// then draw the old needle in need color to display it
		tft.fillTriangle (ix, iy, lx, ly, rx, ry, needlecolor);
		tft.drawTriangle (ix, iy, lx, ly, rx, ry, textcolor);

		// draw a cute little dial center
		tft.fillCircle(x, y, 8, textcolor);

		//save all current to old so the previous dial can be hidden
		pix = ix;
		piy = iy;
		plx = lx;
		ply = ly;
		prx = rx;
		pry = ry;

	}  // end of updateDrawDial

	void ChartLib::initsqMeter(TFT &theScreen)
	{
		tft = theScreen;  	// Reference to the TFT instance
		x = 10;    			// x = position of bar graph (lower left of bar)
		y = 10;            	// y = position of bar (lower left of bar)
		w = 140;          	// w = width of bar graph 
		h = 105;           	// h =  height of bar graph (does not need to be the same as the max scale)
		r = 90;           	// radius
		loval = 0;        	// lowest value
		hival = 5;        	// highest value
		inc = 1;          	// tick mark increment
		sa = 100;          	// total sweep anagle
		curval = 0;       	// current data value
		dig = 2;          	// digits to display not including '.'
		dec = 1;          	// number of decimal digits
		needlecolor = RED;  // needle color
		dialcolor = WHITE;  // dial face color
		textcolor = BLACK;  // text color
		label = "Volts";    // dial face label
	} // end of initsqMeter
			

	void ChartLib::sqMeter()
	{
		double ix, iy, ox, oy, lx, rx, ly, ry, i, offset, stepval, data, angle;
		double degtorad = .0174532778;
		int cx, cy;

		// draw the border
		tft.drawRect(x, y, w, h, textcolor);
		tft.fillRect(x, y, w, h, dialcolor);
		
		// set up text for chart name
		tft.setTextColor(textcolor, textcolor);
		tft.setTextSize(2);
		tft.setCursor(x + 82, y+h-20);
		tft.println(label);

		// draw the current value
		tft.setTextSize(2);
		tft.setTextColor(textcolor, dialcolor);
		tft.setCursor(x + 10, y+h-20 );
		tft.println(Format(curval, dig, dec));

		cx = (w/2) + x; 	// center for needle
		cy = h + y -20;  	// center for needle 

		// center the scale about the vertical axis--and use this to offset the needle, and scale text
		offset = (270 +  sa / 2) * degtorad;
		// find hte scale step value based on the hival low val and the scale sweep angle
		// deducting a small value to eliminate round off errors
		// this val may need to be adjusted
		stepval = ( inc) * (double (sa) / (double (hival - loval))) + .00;
		
		// draw the scale and numbers
		// note draw this each time to repaint where the needle was

		for (i = 0; i <= sa; i += stepval) 
		{
			angle = ( i  * degtorad);
			angle = offset - angle ;
			ox =  (r - 2) * cos(angle) + cx;
			oy =  (r - 2) * sin(angle) + cy;
			ix =  (r - 10) * cos(angle) + cx;
			iy =  (r - 10) * sin(angle) + cy;
			tx =  (r - 20) * cos(angle) + cx;
			ty =  (r - 20) * sin(angle) + cy;
			tft.drawLine(ox, oy, ix, iy, textcolor);
			tft.setTextSize(1.5);
			tft.setTextColor(textcolor, dialcolor);
			tft.setCursor(tx - 10, ty );

			data = hival - ( i * (inc / stepval)) ;
			tft.println(Format(data, dig, dec));
		}
	  
		// compute and draw the needle
		angle = (sa * (1 - (((curval - loval) / (hival - loval)))));
		angle = angle * degtorad;
		angle = offset - angle  ;
		ix =  (r - 10) * cos(angle) + cx;
		iy =  (r - 10) * sin(angle) + cy;
		// draw a triangle for the needle (compute and store 3 vertiticies)
		lx =  5 * cos(angle - 90 * degtorad) + cx;
		ly =  5 * sin(angle - 90 * degtorad) + cy;
		rx =  5 * cos(angle + 90 * degtorad) + cx;
		ry =  5 * sin(angle + 90 * degtorad) + cy;

		// first draw the previous needle in dial color to hide it
		// note draw performance for triangle is pretty bad...

		tft.fillTriangle (pix, piy, plx, ply, prx, pry, dialcolor);
		tft.drawTriangle (pix, piy, plx, ply, prx, pry, dialcolor);

		// then draw the old needle in need color to display it
		tft.fillTriangle (ix, iy, lx, ly, rx, ry, needlecolor);
		tft.drawTriangle (ix, iy, lx, ly, rx, ry, textcolor);

		// draw a cute little dial center
		tft.fillCircle(cx, cy, 8, textcolor);
		//save all current to old so the previous dial can be hidden
		pix = ix;
		piy = iy;
		plx = lx;
		ply = ly;
		prx = rx;
		pry = ry;

	}// end of sqMeter

	void ChartLib::updateSqMeter(double value)
	{
	  double ix, iy, ox, oy, lx, rx, ly, ry, i, offset, stepval, data, angle;
	  double degtorad = .0174532778;
	  int cx, cy;

	  curval = value;

	  // draw the previous value (erase)
	  tft.setTextSize(2);
	  tft.setTextColor(dialcolor, dialcolor);
	  tft.setCursor(x + 10, y+h-20 );
	  tft.println(Format(preval, dig, dec));

	  // draw the current value
	  tft.setTextSize(2);
	  tft.setTextColor(textcolor, dialcolor);
	  tft.setCursor(x + 10, y+h-20 );
	  tft.println(Format(curval, dig, dec));

	  preval = curval;

	  cx = (w/2) + x;   // center for needle
	  cy = h + y -20;  // center for needle 

	  // center the scale about the vertical axis--and use this to offset the needle, and scale text
	  offset = (270 +  sa / 2) * degtorad;
	  // find hte scale step value based on the hival low val and the scale sweep angle
	  // deducting a small value to eliminate round off errors
	  // this val may need to be adjusted
	  stepval = ( inc) * (double (sa) / (double (hival - loval))) + .00;
	  // draw the scale and numbers
	  // note draw this each time to repaint where the needle was
	  for (i = 0; i <= sa; i += stepval) 
	  {
		angle = ( i  * degtorad);
		angle = offset - angle ;
		ox =  (r - 2) * cos(angle) + cx;
		oy =  (r - 2) * sin(angle) + cy;
		ix =  (r - 10) * cos(angle) + cx;
		iy =  (r - 10) * sin(angle) + cy;
		tx =  (r - 20) * cos(angle) + cx;
		ty =  (r - 20) * sin(angle) + cy;
		tft.drawLine(ox, oy, ix, iy, textcolor);
		tft.setTextSize(1.5);
		tft.setTextColor(textcolor, dialcolor);
		tft.setCursor(tx - 10, ty );


		data = hival - ( i * (inc / stepval)) ;
		tft.println(Format(data, dig, dec));
	  }
	  
	  // compute and draw the needle
	  angle = (sa * (1 - (((curval - loval) / (hival - loval)))));
	  angle = angle * degtorad;
	  angle = offset - angle  ;
	  ix =  (r - 10) * cos(angle) + cx;
	  iy =  (r - 10) * sin(angle) + cy;
	  // draw a triangle for the needle (compute and store 3 vertiticies)
	  lx =  5 * cos(angle - 90 * degtorad) + cx;
	  ly =  5 * sin(angle - 90 * degtorad) + cy;
	  rx =  5 * cos(angle + 90 * degtorad) + cx;
	  ry =  5 * sin(angle + 90 * degtorad) + cy;
	  // first draw the previous needle in dial color to hide it
	  // note draw performance for triangle is pretty bad...

	  tft.fillTriangle (pix, piy, plx, ply, prx, pry, dialcolor);
	  tft.drawTriangle (pix, piy, plx, ply, prx, pry, dialcolor);

	  // then draw the old needle in need color to display it
	  tft.fillTriangle (ix, iy, lx, ly, rx, ry, needlecolor);
	  tft.drawTriangle (ix, iy, lx, ly, rx, ry, textcolor);


	  // draw a cute little dial center
	  tft.fillCircle(cx, cy, 8, textcolor);
	  //save all current to old so the previous dial can be hidden
	  pix = ix;
	  piy = iy;
	  plx = lx;
	  ply = ly;
	  prx = rx;
	  pry = ry;

	}// end of updateSqMeter

	void ChartLib::setLocation(int myx, int myy)
	{
		x = myx;
		y = myy; 
 	}// setLocation

  void ChartLib::setLimits(int low, int high)
	{
		loval = low;
		hival = high;
	} // end of setLimits

  void ChartLib::setIncrement(int value)
	{
		inc = value;
	}// end of setIncrement

  void ChartLib::setNumFormat(int digits, int decimalDigits)
	{
		dig = digits;
		dec = decimalDigits;
	}// end of setNumFormat


 	void ChartLib::setColors(unsigned int actColor, unsigned int inactColor, \
														unsigned int border, unsigned int txtcolor, unsigned int background)
	{
		barcolor = actColor;
		voidcolor = inactColor;
		bordercolor = border;
		textcolor = txtcolor;
		backcolor = background;
	} // end of setColors

	void ChartLib::setDialColor(unsigned int needle, unsigned int dial)
	{
		needlecolor = needle;
		dialcolor = dial;
	}// end of setDialColor

	void ChartLib::setOrientation(int angle)
	{
		tft.setRotation(angle);
	}

	void ChartLib::setLabel(String name)
	{
		label = name;
	}
	void ChartLib::setSize(int width, int height)
	{	
		w = width;
		h = height;
	}


