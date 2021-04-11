#pragma once
#include "Panel.h"
#include <string>
#include <vector>
#include "GridCell.h"

class Grid : public Panel
{
private:
	std::vector< std::vector<GridCell*>* > gridArray;
	std::vector<int> columnWidths;
	std::vector<int> rowHeights;
	int defaultColumnSize = 50;
	int defaultRowSize = 50;

	void AddRow();
public:
	Grid();
	Grid(int x, int y, int width, int height);
	Grid(int x, int y, int width, int height, std::string name);
	int GetDefaultColumnSize();
	int GetDefaultRowSize();
	void SetDefaultColumnSize(int defaultColumnSize);
	void SetDefaultRowSize(int defaultRowSize);
	GridCell* GetGridCell(int x, int y);
	void SetGridColumns(std::initializer_list<int> columns);
	void SetGridRows(std::initializer_list<int> rows);
	int GetGridRowSize(int index);
	int GetGridColumnSize(int index);

	virtual void Add(Component& component) override;
};

