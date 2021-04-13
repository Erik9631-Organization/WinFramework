#pragma once
#include "Panel.h"
#include <string>
#include <vector>
#include "GridCell.h"
#include "GridSpan.h"

class Grid : public Panel
{
private:
	std::vector< std::vector<GridCell*>* > gridArray;
	std::vector<int> columnWidths;
	std::vector<int> rowHeights;
	std::vector<GridSpan> spans;
	int currentRowIndex = 0;

	int defaultColumnSize = 50;
	int defaultRowSize = 50;
	int rowGap = 0;
	int columnGap = 0;
	void AddRow();
	void AddRows(int count);

	
	void CreateSpan(GridSpan span);

public:
	Grid();
	Grid(int x, int y, int width, int height);
	Grid(int x, int y, int width, int height, std::string name);
	void SetRowGap(int rowGap);
	void SetColumnGap(int columnGap);
	int GetColumnGap();
	int GetRowGap();
	bool AreSpansColliding(GridSpan a, GridSpan b);


	void AddColumnSpan(int columnStart, int columnEnd);
	void AddRowSpan(int rowStart, int rowEnd);
	void AddSpan(int columnStart, int columnEnd, int rowStart, int rowEnd);
	void AddColumnSpan(int columnStart, int columnEnd, int row);
	void AddRowSpan(int rowStart, int rowEnd, int column);
	bool CheckSpanCollision(GridSpan span);

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

