/* BASIC GRADIENT AND HSV EXAMPLE FOR PIXIE LIBRARY */

#include <Pixie.h>

#define LS_PIN 4				// arduino pin attached to the strip
#define LED_COUNT 50			// number of leds in the strip

#define CYCLE_PERIOD_MS		5000		// set full cycle period to 5 sec.

/* create Pixie object referenced as "p" */
Pixie p (LS_PIN, LED_COUNT); 

float hue = 0;	// dynamic hue variable

void setup ()
{ 
}

void loop ()
{
		/* hsvToRgb(hue [0..255], saturation [0..255], vibrance [0..255])
		 *  outputs a 24-bit RGB color 
		 */
		
		uint32_t color1 = hsvToRgb (hue, 255, 255);				// first color
		uint32_t color2 = hsvToRgb (hue + 32, 255, 255);  // second color with shifted hue
		
		p.gradient (color1, color2);		//	draw gradient

		p.show();			// write output to actual led strip

		hue ++;				// rotate hue
		delay (CYCLE_PERIOD_MS / 256);
}
