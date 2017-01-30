#include "PixieLayer.h"


PixieLayer::PixieLayer (p_int length, p_int offset, pixel_t * buff)
{
	alpha = 255;
	overflow = true;
	this -> offset = offset;
	this -> length = length;
	if (buff != NULL) 
	{
		this->buff = buff;
		shared_buff = true;
	}
	else 
	{
		this->buff = (pixel_t *) calloc (length, sizeof (pixel_t));
		shared_buff = false;
	}
}

PixieLayer::~PixieLayer ()
{
	if (!shared_buff)
		free(buff);
}


void PixieLayer::shiftUp ()
{
	pixel_t last = *getPixel(length-1);
	for (p_int i=length-1; i > 0; i--)
		setPixel (i, *getPixel(i-1));
	setPixel(0, last);
}

void PixieLayer::shiftDown ()
{
	pixel_t first = *getPixel(0);
	for (p_int i=1; i < length; i++)
		setPixel(i-1, *getPixel(i));
	setPixel(length-1, first);
}

void PixieLayer::rainbow (p_int start, p_int end, uint8_t waves)
{	/*
	p_int wavelength = (end-start) / waves;
	for (uint8_t w=0; w < waves; w++)
	{
		for (p_int i=0; i < wavelength; i++)
			pixel[start + w*wavelength + i].setHsv ((float)i/wavelength, 1, 1);
	}
	*/
	//p_int len = end - start;
	for (p_int i=start; i < end; i++)
		getPixel(i)->setHsv(((65535L*(i-start))/(end-start)) >> 8, 255, 255);

}

void PixieLayer::rainbow (p_int start, p_int end)
{
	rainbow (start, end, 1);
}
void PixieLayer::rainbow (uint8_t waves)
{
	rainbow (0, length, waves);
}

void PixieLayer::line (p_int start, p_int end, uint32_t color)
{
	for (p_int i=start; i < end; i++)
		getPixel(cycle(i))->setRgb(color);
}



void PixieLayer::mirror (p_int start, p_int end)
{
	pixel_t p;
	for (p_int i=start, j=end-1, c=0; c < (end-start)/2; i++, c++, j--)
	{	// swap values
		p = *getPixel(i);
		setPixel (i, *getPixel(j));
		setPixel (j, p);
	}
}


void PixieLayer::copy(p_int start, p_int end, p_int dest)
{
	/*
	p_int length = end - start;
	if (end > length || length == 0 || dest + length > length)
		return;
	pixel_t * tmp = (pixel_t *) malloc (length * sizeof(pixel_t));
	memcpy (tmp, pixel + start, length * sizeof(pixel_t));
	memcpy (pixel + dest, tmp, length * sizeof(pixel_t));
	free (tmp);
	*/
}

void PixieLayer::splash (p_int center, p_int radius, uint32_t color)
{
	if (center == 0 || center >= length || radius == 0)
		return;
	p_int start = center - radius;
	p_int end = center + radius;
	if (start < 0) start = 0;
	if (end > length) end = length;

	gradient (start, center, 0, color);
	gradient (center, end, color, 0);
}


void PixieLayer::gradient (p_int start, p_int end, uint32_t color1, uint32_t color2)
{
	pixel_t c1, c2;

	p_int length = end - start;

	c1.setRgb(color1);
	c2.setRgb(color2);

	for (p_int i=0; i < length; i++)
	{
		pixel_t * p = getPixel (cycle(start+ i));
		p->r = map (i, 0, length, c1.r, c2.r);
		p->g = map (i, 0, length, c1.g, c2.g);
		p->b = map (i, 0, length, c1.b, c2.b);
	}
}


void PixieLayer::gradient (uint32_t color1, uint32_t color2)
{
	gradient (0, length, color1, color2);
}

void PixieLayer::gradient3 (uint32_t color1, uint32_t color2, uint32_t color3)
{
	p_int start = 0;
	p_int end = length;
	p_int middle = cycle(start + (end - start)/2);
	gradient (start, middle, color1, color2);
	gradient (middle, end, color2, color3);
}

void PixieLayer::moveUp ()
{
	offset++;
}

void PixieLayer::moveDown()
{
	offset--;
}


p_int PixieLayer::cycle(p_int p)
{
	 return (p < 0) ? length + p : p - length * floor(p/length);
}