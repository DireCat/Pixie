#ifndef PIXIE_H
#define PIXIE_H


#include <PixieLayer.h>
#include <Adafruit_NeoPixel.h>
//#include <PixieDriver.h>

// Last update
// Mon 12/12/2016 from laptop

/*  -----------------------
 *  PIXIE LED STRIP LIBRARY
 *	beta
 *  -----------------------
 *  Powerful extension of Adafruit Neopixel WS2812 library
 *  -----------------------
 *  by Denis Tolochenko
 *  -----------------------
*/


class Pixie : public Adafruit_NeoPixel, public PixieLayer
{
	public:
		// Constructor:
		Pixie (const uint8_t pin, const p_int leds);
		
		pixel_t * getPixel (p_int n);
		void setPixel (p_int n, pixel_t p);

		void remap (p_int log, p_int phy);
		void setMappingFunction (p_int (*mapping_func)(p_int input));
		void setOverflowEvent (void (*layer_ovf_handler)(PixieLayer *));

		uint8_t addLayer (PixieLayer * layer);
		void removeLayer (uint8_t id = 0);

		void show();

		Adafruit_NeoPixel * strip;
		p_int getLedCount();

		//uint8_t interpolate (const uint8_t *arr, uint8_t size, uint8_t idx, uint8_t scale);

	private:

		PixieLayer ** layers;
		p_int * mapping_table;
		void (*overflow_handler)(PixieLayer *);
		uint8_t layer_count;
		
};


#endif