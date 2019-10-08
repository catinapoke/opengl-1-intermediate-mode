#include "ColorStorage.h"

ColorStorage::ColorStorage(Color _colors[], int arraySize) :currentColor(0)
{
	colorCount = arraySize;
	try
	{
		if (colorCount == 0)
			throw(std::exception("Size can't be zero\n"));
	}
	catch (std::exception e)
	{
		printf(e.what());
		system("pause");
	}

	colors = new Color[colorCount];
	for (int i = 0; i < colorCount; i++)
	{
		colors[i] = _colors[i];
	}
}

void ColorStorage::SetNextColor()
{
	currentColor++;
	currentColor %= colorCount;
}

Color ColorStorage::GetCurrentColor() const
{
	return colors[currentColor];
}

Color ColorStorage::GetNextColor() const
{
	int num = 1 + currentColor;
	num %= colorCount;
	return colors[num];
}