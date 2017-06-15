/* BASIC RAINBOW EXAMPLE FOR PIXIE LIBRARY */

#include <Pixie.h>

#define LS_PIN 4				// arduino pin attached to the strip
#define LED_COUNT 50		// number of leds in the strip

#define WAVES_COUNT 2		// rainbow waves count

/* create Pixie object referenced as "p" */
Pixie p (LS_PIN, LED_COUNT); 

void setup ()
{
		/* draw a rainbow */
	  p.rainbow (0, LED_COUNT, WAVES_COUNT);
}

void loop ()
{
		p.shiftUp();	// move up pixels by cyclic shifting 
		p.show();		// write output to actual led strip
	  delay(50);
}
