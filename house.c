#include <stdio.h>

int main()
{
	float g = 100;		// gong ji jin unit : 10000
	float s;			// shang dai
	float f = 100;		// fang jia
	float x;			// shou fu
	float scale = 0.3;	//
	
	int i = 0;
	for(i = 0; i < 200; i++, f += 1)
	{
		x = f * scale;
		s = f - g - x;
		printf("fangjia %f, shoufu %f, shang dai= %f\n", f, x, s);
	}
		


	return 0;
}
