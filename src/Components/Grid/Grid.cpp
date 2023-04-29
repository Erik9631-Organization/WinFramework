#include "Grid.h"
using namespace std;

void Grid::AddRow()
{
	//Add new row only if over the capacity

	std::vector<GridCell*>* row = new std::vector<GridCell*>();
	gridArray.push_back(row);


	int lastRowIndex = 0;
	if (gridArray.size() > 1)
		lastRowIndex = gridArray.size() - 1;

	for (int i = 0; i < columnWidths.size(); i++) //CreateElement new row
	{
		GridCell* cell = new GridCell(*this);
		//Check if current index is spanning and capture the index of the span

		//If == -1 then cell.SetSpan(spanVector[returnVal])
		//Get spans Y find the different between current row and preemtivly add rows till the last span, use recursion
		//CreateElement last assigned row variable which keeps track of which row was the last gridCell assigned to.
		row->push_back(cell);
        cell->SetSize({GetGridColumnSize(i), GetGridRowSize(lastRowIndex), 0, 1}, false); // First viewPortSize
        cell->SetPosition({i, lastRowIndex, 0}, false); // Then viewPortPosition since viewPortSize is dependent on viewPortPosition
	}
	if (autoExtend == false)
		return;

	if (gridArray.size() == 0)
		return;

	if (gridArray.at(gridArray.size()-1)->at(0) == nullptr)
		return;
	//If autoextend enabled check if grid extention required
	
	int lastY = gridArray.at(gridArray.size()-1)->at(0)->GetPixelY();
	int lastHeight = gridArray.at(gridArray.size() - 1)->at(0)->GetSize().y;

	if (lastY + lastHeight > GetSize().y)
        SetSize({GetSize().x,lastY + lastHeight, GetSize().z, GetSize().w}, false);

}

void Grid::AddRows(int count)
{
	for (; count > 0; count--)
		AddRow();
}


bool Grid::AreSpansColliding(GridSpan a, GridSpan b)
{

	if (a.GetGridColumnStart() <= b.GetGridColumnStart() && a.GetGridColumnEnd() >= b.GetGridColumnStart() ||
		a.GetGridColumnStart() <= b.GetGridColumnEnd() && a.GetGridColumnEnd() >= b.GetGridColumnEnd())
		if (a.GetGridRowStart() <= b.GetGridRowStart() && a.GetGridRowEnd() >= b.GetGridRowStart() || 
			a.GetGridRowStart() <= b.GetGridRowEnd() && a.GetGridRowEnd() >= b.GetGridRowEnd())
			return true;
	return false;
}

void Grid::CreateSpan(GridSpan span)
{
	//Check if rows need to be added

	int currentRows = gridArray.size();
	int requiredRows = (span.GetGridRowEnd() + 1) - currentRows;
	AddRows(requiredRows);


	for (int iy = span.GetGridRowStart(); iy <= span.GetGridRowEnd(); iy++)
		for (int ix = span.GetGridColumnStart(); ix <= span.GetGridColumnEnd(); ix++)
			gridArray.at(iy)->at(ix)->SetSpan(span);
}

int Grid::GetGridColumnSize(int index)
{
	if (columnWidths.size() == 0)
		return defaultColumnSize;

	if (index >= columnWidths.size() || index < 0)
		return defaultColumnSize;
	return columnWidths.at(index);
}

void Grid::SetAutoExtend(bool state)
{
	autoExtend = state;
}

bool Grid::IsAutoextending()
{
	return autoExtend;
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

void Grid::SetRowGap(int rowGap)
{
	this->rowGap = rowGap;
}

void Grid::SetColumnGap(int columnGap)
{
	this->columnGap = columnGap;
}

int Grid::GetColumnGap()
{
	return columnGap;
}

int Grid::GetRowGap()
{
	return rowGap;
}


void Grid::AddColumnSpan(int columnStart, int columnEnd)
{
	GridSpan span  = GridSpan::CreateColumnSpan(columnStart, columnEnd);
	CreateSpan(span);
	spans.push_back(GridSpan::CreateColumnSpan(columnStart, columnEnd));
}

void Grid::AddRowSpan(int rowStart, int rowEnd)
{
	GridSpan span = GridSpan::CreateRowSpan(rowStart, rowEnd);
	CreateSpan(span);
	spans.push_back(span);
}

void Grid::AddSpan(int columnStart, int columnEnd, int rowStart, int rowEnd)
{
	GridSpan span = GridSpan::CreateSpan(columnStart, columnEnd, rowStart, rowEnd);
	CreateSpan(span);
	spans.push_back(span);
}

void Grid::AddColumnSpan(int columnStart, int columnEnd, int row)
{
	AddSpan(columnStart, columnEnd, row, row);
}

void Grid::AddRowSpan(int rowStart, int rowEnd, int column)
{
	AddSpan(column, column, rowStart, rowEnd);
}

bool Grid::CheckSpanCollision(GridSpan span)
{
	return false;
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
	if ( y >= gridArray.size() || y < 0)
		return nullptr;
	if (x >= gridArray.at(y)->size() || x < 0)
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

UiElement & Grid::Add(unique_ptr<UiElement> component)
{
    UiElement& componentRef = *component;
	Panel::Add(std::move(component)); //Super
	//First check if there is a row that can contain a component

	//int lastRow = 0;

		for (int i = currentRowIndex; i < gridArray.size(); i++)
		{
			for (GridCell* cell : *gridArray.at(i))
			{
				if (cell->GetControlledAdjustable() == nullptr)
				{
					cell->ControlAdjustable(&static_cast<Adjustable&>(componentRef));
					return componentRef; //Successfully added
				}
			}
		}



	//Failed to find a row, add a new row and insert the component
	AddRow();
	if (gridArray.size() > 1)
		currentRowIndex++;
	if(gridArray.at(currentRowIndex)->size() == 0)
	    return componentRef;
	gridArray.at(currentRowIndex)->at(0)->ControlAdjustable(&static_cast<Adjustable&>(componentRef));
}
