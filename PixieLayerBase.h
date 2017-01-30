#ifndef PIXIELAYERBASE_H
#define PIXIELAYERBASE_H

// Last update
// Thu 08/12/2016 from desktop

#include "PixieDef.h"

class PixieLayerBase
{
	public:

		void setOverflow (boolean val);
		boolean isOverflow ();
		void setAlpha (uint8_t val);
		uint8_t getAlpha ();
		p_int getLedCount();	


		void setPixel (p_int n, pixel_t val);
		pixel_t * getPixel (p_int n);


		void fill (uint32_t color);
		void replaceColor (uint32_t from, uint32_t to);

		boolean overflow;
		
		uint8_t alpha;

		p_int length;
		pixel_t * buff;

		pixel_t null_pixel;

		boolean shared_buff;
};


#endif