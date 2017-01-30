# Pixie for WS2812
Easy and small graphics library for drawing on WS2812 led strips and arrays

## Features
- Basic drawing and transformation functions for 1D and 2D arrays
- Supports 24-bit HSV color format
- Multiple layers with individual bitmap, transformations, alpha and blend order
- Easy strip mapping in 2D mode: vertical/horizontal, linear/zigzag
- Accepts custom mapping function for 1D and 2D


## Dependencies
Adafruit NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel

## Under development
The library is working however some functional is not implemented yet:
- Pixie2D Multiple layers
- Some drawing functions
- More documentation and examples
There is no "master" yet because of the need to create an interface for this library in order to get this working on various type of displays rather than NeoPixel. This can result in structural changes which may result in breaking the code using this library in the future.

