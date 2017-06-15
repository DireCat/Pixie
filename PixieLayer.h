#ifndef PIXIELAYER_H
#define PIXIELAYER_H


// Last update
// Thu 08/12/2016 from desktop

#include "PixieLayerBase.h"

class PixieLayer : public PixieLayerBase
{
	public:
		PixieLayer (p_int length, p_int offset = 0, pixel_t * buff = NULL);
		~PixieLayer ();

		// possibly add blend function directly to layer itself

		// Position and display transformations:
		void shiftUp ();
		void shiftDown ();
		void moveUp();
		void moveDown();
		void moveTo (uint8_t offset);

		// Draw Settings
	
		void rainbow (p_int start, p_int end, uint8_t waves);
		void rainbow (p_int start, p_int end);
		void rainbow (uint8_t waves);
		void splash (p_int center, p_int radius, uint32_t color);
		void line (p_int start, p_int end, uint32_t color);
		void gradient (uint32_t color1, uint32_t color2);
		// (deprecated) void gradient (p_int start, p_int end, uint32_t color1, uint32_t color2);
		void gradient (uint32_t color1, uint32_t color2, uint32_t color3);
		void copy (p_int start, p_int end, p_int dest);
		void mirror (p_int start, p_int end); 
		p_int cycle (p_int p);

		uint16_t offset;

};


#endif
