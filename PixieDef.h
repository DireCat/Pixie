#include <Arduino.h>

#ifndef PIXIEDEF_H
#define PIXIEDEF_H

// Last update
// Mon 12/12/2016 from laptop

#ifndef p_int
	#define p_int uint16_t
#endif

#ifndef NEOPIXEL_MODE
	#define NEOPIXEL_MODE NEO_GRB + NEO_KHZ800
#endif

 #define PIXIE_MAX_LAYERS 16



struct pixel_t
{
	 uint8_t g,r,b;
	 void setRgb (uint8_t r, uint8_t g, uint8_t b)
	 {
			this -> g = g;
			this -> r = r;
			this -> b = b;
	 }

	 void setRgb (uint32_t color)
	 {
			r = (color & 0xff0000) >> 16;
			g = (color & 0xff00) >> 8;
			b = color & 0xff;
	 }

	 void setHsv (uint8_t h, uint8_t s, uint8_t v)
	 {
		uint8_t region, p, q, t;
		uint16_t remainder;
		if (s == 0)
		{
			r = v;
			g = v;
			b = v;
			return;
		}
		region = h / 43;
		remainder = (h - (region * 43)) * 6; 

		p = (v * (255 - s)) >> 8;
		q = (v * (255 - ((s * remainder) >> 8))) >> 8;
		t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

		switch (region)
		{
			case 0: r = v; g = t; b = p; break;
			case 1: r = q; g = v; b = p; break;
			case 2: r = p; g = v; b = t; break;
			case 3: r = p; g = q; b = v; break;
			case 4: r = t; g = p; b = v; break;
			default: r = v; g = p; b = q; break;
		};
	}

	uint32_t getRgb()
	{
		return 0L | r*256*256L + g*256L + b;
	}

	void set (pixel_t copy)
	{
		*this = copy;
	}

	void multiply (uint8_t a)
	{
		r = r * a >> 8;
		g = g * a >> 8;
		b = b * a >> 8;
	}

	inline uint8_t blend (uint8_t base, uint8_t mix, uint8_t alpha)
	{
		return (mix * alpha >> 8) + (base * (255 - alpha) >> 8);
	}

	void add (pixel_t p, uint8_t opacity = 255)
	{
		r = blend (r, p.r, opacity);
		g = blend (g, p.g, opacity);
		b = blend (b, p.b, opacity);
	}
};


uint32_t hsvToRgb (uint8_t h, uint8_t s, uint8_t v);
p_int periodic (int16_t num, p_int nmax);

#endif