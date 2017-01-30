#include "Pixie2D.h"



Pixie2D::Pixie2D (const uint8_t pin, uint8_t width, uint8_t height) : Adafruit_NeoPixel (width*height, pin, NEOPIXEL_MODE), PixieLayer2D (width, height, 0, 0, (pixel_t *) getPixels())
{
	begin();
	this -> width = width;
	this -> height = height;
	mapping_table = (p_int*) malloc (length * sizeof(p_int));	// problems?
	setOrder (LS_HORIZONTAL | LS_LINEAR | LS_TOP | LS_LEFT);
	brush.setRgb(0xffffff);
	background.setRgb(0);
}

uint8_t Pixie2D::getWidth()
{
	return width;
}

uint8_t Pixie2D::getHeight()
{
	return height;
}

void Pixie2D::setOrder (uint8_t order)
{
	for (uint8_t x = 0; x < width; x++)
		for (uint8_t y = 0; y < height; y++)
			mapping_table[x + width * y] = map2d (x, y, order);
}

p_int Pixie2D::map2d (uint8_t x, uint8_t y, uint8_t order)
{
	boolean to_left = ((order & LS_RIGHT) == 0);
	boolean to_top = ((order & LS_BOTTOM) == 0);
	boolean zigzag = ((order & LS_ZIGZAG) != 0);
	boolean vertical = ((order & LS_VERTICAL) != 0);

	uint8_t xl = (to_left ? x : width-x-1);
	uint8_t yl = (to_top ? y : height-y-1);

	if (vertical)
		return ((zigzag && x%2!=0) ? xl * height + (height - yl - 1) : xl * height + yl);
	return ((zigzag && y%2!=0) ? yl * width + (width - xl - 1) : yl * width + xl);
}

pixel_t * Pixie2D::getPixel (uint8_t x, uint8_t y)
{
	if (x < width && y < height)
		return &buff [mapping_table[x + width * y]];
	return &null_pixel;
	return &buff [mapping_table[(x % width) + width * (y % height)]];
}

void Pixie2D::show ()
{
	
	if (alpha < 255)
		for (uint8_t i=0; i < length; i++)
			buff[i].multiply (alpha);

	if (layer_count > 1)
	{
		// clear buffer and blend layers
	}
	
	Adafruit_NeoPixel::show();
}


/* Debug stuff */

/*

void Pixie2D::debug()
{
	struct dbg_func
	{
		char decode (uint32_t val)
		{
			char c;
			switch (val)
			{
				case 0xff0000:
					return 'R';
				case 0xffff00:
					return 'Y';
				case 0x00ff00:
					return 'G';
				case 0x00ffff:
					return 'C';
				case 0x0000ff:
					return 'B';
				case 0xff00ff:
					return 'M';
				case 0xffffff:
					return 'W';
			}
			return '0';
		}
	} dbg;
	Serial << "Original matrix: " << width << "x" << height << "\r\n";
	for (uint8_t y=0 ; y < height; y++)
	{
		for (uint8_t x=0; x < width; x++)
		{
			Serial << dbg.decode (getPixel (x, height-y-1) -> getRgb()) << "\t   \t";
		}
		Serial << "\r\n";
	}

	Serial << "\r\nStrip mapping: ";
	for (uint8_t i=0; i < width*height; i++)
	{
		Serial << dbg.decode(buff[i].getRgb()) << ", ";
	}
	Serial << "\r\n";
}
*/