#include "PixieLayer2D.h"


PixieLayer2D::PixieLayer2D (uint8_t width, uint8_t height, uint8_t offset_x, uint8_t offset_y, pixel_t * buff)
{
	this -> width = width;
	this -> height = height;
	this -> offset_x = offset_x;
	this -> offset_y = offset_y;
	length = width * height;

	overflow = true;
	alpha = 255;
	no_stroke = false;
	no_fill = true;

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


PixieLayer2D::~PixieLayer2D ()
{
	if (!shared_buff)
		free(buff);
}

void PixieLayer2D::stroke (uint32_t color)
{
	brush.setRgb(color);
}

void PixieLayer2D::fill (uint32_t color)
{
	for (p_int i; i < length; i++)
		buff[i].setRgb(color);
	//background.setRgb(color);
}


pixel_t * PixieLayer2D::getPixel (uint8_t x, uint8_t y)
{	
	if (x < width && y < height)
		return &buff[x + width * y]; // default mapping is horizontal linear
	else if (overflow)
		return &buff[(x % width) + width * (y % height)];
	return &null_pixel;
}



void PixieLayer2D::drawCircle (uint8_t x_center, uint8_t y_center, uint8_t radius)
{
	// Using Bresenham's midpoint circle algorithm
	uint8_t x = radius;
    uint8_t y = 0;
    int err = 0;
    while (x >= y)
    {
        point(x_center + x, y_center + y);
        point(x_center + y, y_center + x);
        point(x_center - y, y_center + x);
        point(x_center - x, y_center + y);
        point(x_center - x, y_center - y);
        point(x_center - y, y_center - x);
        point(x_center + y, y_center - x);
        point(x_center + x, y_center - y);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}

void PixieLayer2D::drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	/*
	uint8_t xmin = ((x0 > x1) ? x1 : x0);
	uint8_t xmax = ((x0 > x1) ? x0 : x1);
	uint8_t ymin = ((y0 > y1) ? y1 : y0);
	uint8_t ymax = ((y0 > y1) ? y0 : y1);
	
	// Vertical line
	if (x0 == x1) 
	{	
		for (uint8_t y = ymin; y <= ymax; y++)
			point(x0, y);
	}

	// Horizontal line
	else if (y0 == y1) 
	{
		for (uint8_t x = xmin; x <= xmax; x++)
			point (x, y0);
	}
	*/

	// Diagonal lines:  Using Bresenham's Line drawing algorithm
	if (true)
	{
		int8_t	x, y;
		int8_t	dx, dy;
		int8_t	incx, incy;
		int8_t	balance;

		if (x1 >= x0)
		{
			dx = x1 - x0;
			incx = 1;
		}
		else
		{
			dx = x0 - x1;
			incx = -1;
		}

		if (y1 >= y0)
		{
			dy = y1 - y0;
			incy = 1;
		}
		else
		{
			dy = y0 - y1;
			incy = -1;
		}

		x = x0;
		y = y0;

		if (dx >= dy)
		{
			dy <<= 1;
			balance = dy - dx;
			dx <<= 1;

			while (x != x1)
			{
				point (x, y);
				if (balance >= 0)
				{
					y += incy;
					balance -= dx;
				}
				balance += dy;
				x += incx;
			} point (x, y);
		}
		else
		{
			dx <<= 1;
			balance = dx - dy;
			dy <<= 1;

			while (y != y1)
			{
				point (x, y);
				if (balance >= 0)
				{
					x += incx;
					balance -= dy;
				}
				balance += dx;
				y += incy;
			} point (x, y);
		}
	}
}

void PixieLayer2D::drawRect (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	drawLine (x0, y0, x0, y1);
	drawLine (x0, y0, x1, y0);
	drawLine (x0, y1, x1, y1);
	drawLine (x1, y1, x1, y0);
}

void PixieLayer2D::point (uint8_t x, uint8_t y)
{
	if (brush.getRgb() == 0)	// workaround
		getPixel (x, y) -> set (brush);
	else
		getPixel (x, y) -> add (brush, 255);
}

void PixieLayer2D::pointBg (uint8_t x, uint8_t y)
{
	getPixel(x, y) -> set (background);
}

void PixieLayer2D::move (int8_t x, int8_t y)
{

}

void PixieLayer2D::moveTo (int8_t x, int8_t y)
{

}