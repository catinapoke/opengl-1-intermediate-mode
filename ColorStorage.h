#include "Color.h"
#include <exception>
#include <cstdio>
class ColorStorage
{
private:
	Color* colors;
	int colorCount;
	int currentColor;
public:
	ColorStorage(Color _colors[], int arraySize);
	void SetNextColor();
	Color GetCurrentColor() const;
	Color GetNextColor() const;
};