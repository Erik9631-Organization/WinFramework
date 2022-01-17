#pragma once
class GridSpan
{
private:
	int gridColumnStart = 0;
	int gridColumnEnd = 0;
	int gridRowStart = 0;
	int gridRowEnd = 0;
	GridSpan(int columnStart, int columnEnd, int rowStart, int rowEnd);
public:
	GridSpan();
	static GridSpan CreateColumnSpan(int columnStart, int columnEnd);
	static GridSpan CreateRowSpan(int rowStart, int rowEnd);
	static GridSpan CreateSpan(int columnStart, int columnEnd, int rowStart, int rowEnd);

	bool isSet();
	int GetGridColumnStart();
	int GetGridColumnEnd();
	int GetGridRowStart();
	int GetGridRowEnd();
};

