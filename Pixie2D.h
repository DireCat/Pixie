#ifndef PIXIE2D_H
#define PIXIE2D_H

#include "PixieLayer2D.h"
#include <Adafruit_NeoPixel.h>
//#include <PixieDriver.h>


// Last update
// Sab 17/12/2016 from desktop

#define	LS_HORIZONTAL 	0x00	// strips are placed as rows (default)
#define LS_VERTICAL  	0x01	// strips are placed as columns

#define 	LS_LEFT 	0x00	// scan order is from LEFT to RIGHT (default)
#define 	LS_RIGHT 	0x02	// scan order is from RIGHT to LEFT
#define 	LS_TOP 		0x00	// from TOP to BOTTOM (default)
#define 	LS_BOTTOM 	0x04	// from BOTTOM to TOP

#define 	LS_ZIGZAG 	0x08
#define 	LS_LINEAR 	0x00	// keep the same order withing each line/row


class Pixie2D : public Adafruit_NeoPixel, public PixieLayer2D
{
	public:
		Pixie2D (const uint8_t pin, uint8_t width, uint8_t height);
		
		void addLayer (PixieLayer2D * layer);
		
		void setOrder (uint8_t order);
		void debug();
		uint8_t getWidth();
		uint8_t getHeight();
		pixel_t * getPixel (uint8_t x, uint8_t y);

		void show();

		// base paint functions

	private:
		PixieLayer2D ** layers;
		p_int * mapping_table;
		void (*overflow_handler)(PixieLayer2D *);
		uint8_t layer_count;

		uint8_t width, height;
		p_int map2d (uint8_t x, uint8_t y, uint8_t order); // default mapping function

	protected:
		pixel_t brush, background;
};





#endif