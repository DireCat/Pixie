#ifndef PIXIELAYER2D_H
#define PIXIELAYER2D


#include "PixieLayerBase.h"

// Last update
// Wed 21/12/2016 from laptop

class PixieLayer2D : public PixieLayerBase
{
	public:
		PixieLayer2D (uint8_t width, uint8_t height, uint8_t offset_x = 0, uint8_t offset_y = 0, pixel_t * buff = NULL);
		~PixieLayer2D();

		// Pixel selector
		//void setPixelColor (uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
		virtual pixel_t * getPixel (uint8_t x, uint8_t y);

		// Drawing functions
		void stroke (uint32_t color);
		void fill (uint32_t color);
		void noFill(boolean no_fill = true);
		void noStroke(boolean no_stroke = true);
		
		void drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
		void drawRect (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
		void drawCircle (uint8_t x_center, uint8_t y_center, uint8_t radius);
		void drawPoly (uint8_t * x, uint8_t * y, uint8_t points);
	
		void point (uint8_t x, uint8_t y);
		void pointBg (uint8_t x, uint8_t y);

		void moveTo (int8_t x, int8_t y);
		void move (int8_t x, int8_t y);

		uint8_t width, height;
		int8_t offset_x, offset_y;

		boolean no_fill, no_stroke;
		pixel_t brush, background;

		pixel_t * buff;

};


#endif