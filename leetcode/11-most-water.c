#include <stdio.h>
#include <math.h>

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
int maxArea_t(int* height, int heightSize){
    int max = 0;
	for(int i = 0; i < heightSize; i++) {
		for(int j = i+1; j < heightSize; j++) {
			int h = MIN(height[i], height[j]);
			max = MAX(max, h*(j - i)); 
		}
	}

	return max;
}

int maxArea(int* height, int heightSize){
	int l = 0, r = heightSize - 1;
	int max = 0;
	while(l < r) {
		int h = MIN(height[l], height[r]);
		max = MAX(max, h * (r-l));
		if(height[l] < height[r])
			l++;
		else
			r--;
	}

	return max;
}

int main()
{
	int a[] = {1,8,6,2,5,4,8,3,7};
	int hs = 9;
	int max = maxArea(a, hs);
	printf("max %d\n", max);	

	return 0;
}
