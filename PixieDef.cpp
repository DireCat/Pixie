#include "PixieDef.h"

uint32_t hsvToRgb (uint8_t h, uint8_t s, uint8_t v)
{
	pixel_t p;
	p.setHsv(h,s,v);
	return p.getRgb();
}

p_int periodic (int16_t num, p_int nmax)
{
	return (num < 0) ? nmax + num : num - nmax * floor(num/nmax);
}