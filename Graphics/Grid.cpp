#include "Grid.h"

void Grid::AddRow()
{
	std::vector<GridCell*>* row = new std::vector<GridCell*>();
	gridArray.push_back(row);


	int lastRow = 0;
	if (gridArray.size() > 1)
		lastRow = gridArray.size() - 1;

	for (int i = 0; i < columnWidths.size(); i++)
	{
		GridCell* cell = new GridCell(*this);
		cell->SetPosition(i, lastRow);
		cell->SetSize(GetGridColumnSize(i), GetGridRowSize(lastRow));
		row->push_back(cell);
	}

}

int Grid::GetGridColumnSize(int index)
{
	if (columnWidths.size() == 0)
		return defaultColumnSize;

	if (index >= columnWidths.size() || index < 0)
		return defaultColumnSize;
	return columnWidths.at(index);
}

int Grid::GetGridRowSize(int index)
{
	if (rowHeights.size() == 0)
		return defaultRowSize;

	if (index >= rowHeights.size() || index < 0)
		return defaultRowSize;
	return rowHeights.at(index);
}

Grid::Grid() : Grid(0, 0, 0, 0)
{
}

Grid::Grid(int x, int y, int width, int height) : Grid(x, y, width, height, "")
{
}

Grid::Grid(int x, int y, int width, int height, std::string name) : Panel(x, y, width, height, name)
{
}

int Grid::GetDefaultColumnSize()
{
	return defaultColumnSize;
}

int Grid::GetDefaultRowSize()
{
	return defaultRowSize;
}

void Grid::SetDefaultColumnSize(int defaultColumnSize)
{
	this->defaultColumnSize = defaultColumnSize;
}

void Grid::SetDefaultRowSize(int defaultRowSize)
{
	this->defaultRowSize = defaultRowSize;
}

GridCell* Grid::GetGridCell(int x, int y)
{
	if (y > gridArray.size() || y < 0)
		return nullptr;
	if (x > gridArray.at(y)->size() || x < 0)
		return nullptr;

	return gridArray.at(y)->at(x);
}

void Grid::SetGridColumns(std::initializer_list<int> columns)
{
	columnWidths.assign(columns);
}

void Grid::SetGridRows(std::initializer_list<int> rows)
{
	rowHeights.assign(rows);
}

void Grid::Add(Component& component)
{
	Panel::Add(component); //Super
	//First check if there is a row that can contain a component

	int lastRow = 0;
	if (gridArray.size() > 1)
		lastRow = gridArray.size() - 1;
	if (lastRow < gridArray.size())
		for (GridCell* cell : *gridArray.at(lastRow))
			if (cell->GetControlledAdjustable() == nullptr)
			{
				cell->ControlAdjustable(&static_cast<Adjustable&>(component));
				return; //Successfully added
			}

	//Failed to find a row, add a new row and insert the component
	AddRow();

	if (gridArray.size() > 1)
		lastRow = gridArray.size() - 1;

	gridArray.at(lastRow)->at(0)->ControlAdjustable(&static_cast<Adjustable&>(component));
}
