#include <Pixie.h>

/* pin: 8, led count: 50 */
Pixie p (8, 50); 

void setup ()
{
	
}

void loop ()
{
	static float t = 0;
	
  p.clear();
  p.rainbow (0, 12 * ((sin(t+=PI/8.0)+1)/2));   
  p.show();
  delay(50);
}
