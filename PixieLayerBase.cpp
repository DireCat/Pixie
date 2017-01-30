#include "PixieLayerBase.h"

void PixieLayerBase::setOverflow (boolean val)
{
	overflow = val;
}

boolean PixieLayerBase::isOverflow()
{
	return overflow;
}

void PixieLayerBase::setAlpha (uint8_t val)
{
	alpha = val;
}

uint8_t PixieLayerBase::getAlpha ()
{
	return alpha;
}

p_int PixieLayerBase::getLedCount()
{
	return length;
}


void PixieLayerBase::replaceColor (uint32_t from, uint32_t to)
{
	pixel_t color;
	color.setRgb(from);
	for (p_int i=0; i < length; i++)
		if (memcmp (&buff[i], &color, sizeof(pixel_t)) == 0)
			getPixel(i)->setRgb (to);
}

void PixieLayerBase::fill (uint32_t color)
{
	for (p_int i=0; i < length; i++)
		getPixel(i)->setRgb(color);
}

pixel_t * PixieLayerBase::getPixel (p_int n)
{
	return &buff[n];
}

void PixieLayerBase::setPixel (p_int n, pixel_t val)
{
	buff[n] = val;
}