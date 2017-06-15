/* BASIC GRADIENT EXAMPLE FOR PIXIE LIBRARY */

#include <Pixie.h>

#define LS_PIN 4				// arduino pin attached to the strip
#define LED_COUNT 50		// number of leds in the strip

/* colors are stored as 24-bit hex rgb value (0xRRGGBB) */ 
#define PINK		0xff00ae
#define ORANGE		0xff4000

Pixie p (LS_PIN, LED_COUNT); 

void setup ()
{
	/* draw three color gradient on the entire strip */
	p.gradient (PINK, ORANGE, PINK);
}

void loop ()
{
	p.shiftUp();	// move up pixels by cyclic shifting 
	p.show();			// write output to actual led strip
	delay(20);
}
