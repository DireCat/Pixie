#include "Pixie.h"


Pixie::Pixie (const uint8_t pin, const p_int leds) : Adafruit_NeoPixel (leds, pin, NEOPIXEL_MODE), PixieLayer (leds, 0, (pixel_t *) getPixels())
{
	begin();
	mapping_table = (p_int *) malloc (leds * sizeof(p_int));
	// linear mapping order by default
	for (p_int i=0; i < leds; i++)
		mapping_table[i] = i;
	layers = (PixieLayer **) malloc (PIXIE_MAX_LAYERS * sizeof(PixieLayer *));
	layer_count = 0;
	addLayer (this);
}

void Pixie::setMappingFunction(p_int (*mapping_func)(p_int input))
{
	for (p_int i=0; i < length; i++)
		mapping_table[i] = mapping_func (i);
}

void Pixie::remap(p_int log, p_int phy)
{
	mapping_table[log] = phy;
}

pixel_t * Pixie::getPixel (p_int n)
{
	return &buff[mapping_table[n]];
}

void Pixie::setPixel (p_int n, pixel_t p)
{
	*getPixel(n) = p;
}

uint8_t Pixie::addLayer (PixieLayer * layer)
{
	if (layer_count >= PIXIE_MAX_LAYERS)
		return 0;

	layers [layer_count++] = layer;
	return layer_count;
}

void Pixie::removeLayer (uint8_t id)
{
	layer_count = 1;
} 

void Pixie::show()
{
	if (alpha < 255)
		for (uint8_t i=0; i < length; i++)
			getPixel(i) -> multiply (alpha);

	// switch to layered mode
	if (layer_count > 1)
	{
		memset (buff, 0, length);	// clear
		for (uint8_t i=1; i < layer_count; i++)
		{
			// blend every layer into the main buffer
			PixieLayer * layer = layers[i]; 
			p_int lsize = layer -> getLedCount();
			p_int offset = layer->offset % length;
			for (uint8_t p=0; p < lsize; p++)
			{
				if (!layer->overflow && p + offset >= length)
					break;
				getPixel((p + offset) % length)->add (*layer->getPixel(p), layer->alpha);	// mix into the main layer
				// setPixel((p + offset) % length, *layer->getPixel(p));	// simply overlap
			}
			// handle overflow
			if (overflow_handler != NULL)
			{
				uint16_t mod_offset = (layer->offset < 0 ? layer->offset * -1 : layer->offset);
				if (mod_offset >= length)
				{
					layer->offset = 0; // return layer to offset 0(do I really need it?)
					overflow_handler(layer);
				}
			}
		}
	}

	Adafruit_NeoPixel::show();
}


void Pixie::setOverflowEvent (void (*layer_ovf_handler)(PixieLayer *))
{
	overflow_handler = layer_ovf_handler;
}


/*
uint32_t Pixie::randomColor (uint8_t div)
{
		return hsvToRgb ((float) random(div+1)/div, 1, 1);
}
*/

/*
float Pixie::hueFilter (float h)
{
		return h - 0.1*sin(h*PI);
}
*/

/*

uint8_t Pixie::interpolate (const uint8_t *arr, uint8_t size, uint8_t idx, uint8_t scale)
{
	float coef = (float) idx * (size-1) / scale;
	uint8_t i = floor (coef);
	uint8_t rest = round ((coef - i) * 100);
	return rest * (arr[i+1] - arr[i])/100 + arr[i];
}




*/
