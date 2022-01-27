#pragma once
#include "Components/Panel.h"
#include <string>
#include <vector>
#include "GridCell.h"
#include "GridSpan.h"
/**
 * A layout manager which automatically controls the sizing and positioning of the components within its containment hierarchy.
 */
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

	bool autoExtend = false;

public:
	Grid();
	/**
	 * \param x the X position of the grid.
	 * \param y the Y position of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 */
	Grid(int x, int y, int width, int height);

	/**
	 * \param x the X position of the grid.
	 * \param y the Y position of the grid
	 * \param width the width of the grid
	 * \param height the height of the grid.
	 * \param name the identification name of the grid. This is not a display value.
	 */
	Grid(int x, int y, int width, int height, std::string name);

	/**
	 * \param rowGap sets the gaps between individual rows.
	 */
	void SetRowGap(int rowGap);

	/**
	 * \param rowGap sets the gaps between individual columns.
	 */
	void SetColumnGap(int columnGap);

	/**
	 * \return returns the gaps between individual columns.
	 */
	int GetColumnGap();

	/**
	 * \return returns the rows between individual columns.
	 */
	int GetRowGap();

	/**
	 * \param a The first span to compare.
	 * \param b the second span to compare
	 * \return returns whether there is a collision between the inputs spans.
	 */
	bool AreSpansColliding(GridSpan a, GridSpan b);

	/**
	 * Adds span between specified columns on all rows.
	 * \param columnStart the start of the column
	 * \param columnEnd the end of the column
	 */
	void AddColumnSpan(int columnStart, int columnEnd);

	/**
	 * Adds spanning on all columns between the defined rows.
	 * \param rowStart The index of the start row
	 * \param rowEnd The index of the end row.
	 */
	void AddRowSpan(int rowStart, int rowEnd);

	/**
	 * Adds spanning between specified columns and rows. The span is a rectangle.
	 * \param rowStart The index of the start row
	 * \param rowEnd The index of the end row.
	 */
	void AddSpan(int columnStart, int columnEnd, int rowStart, int rowEnd);

	/**
	 * Adds span between specified columns on specified row
	 * \param columnStart the start of the span
	 * \param columnEnd the end of the span
	 * \param row the row of the span
	 */
	void AddColumnSpan(int columnStart, int columnEnd, int row);


	/**
	 * Adds span between specified rows on specified column
	 * \param rowStart the start of the span
	 * \param rowEnd the end of the span
	 * \param column the column of the span
	 */
	void AddRowSpan(int rowStart, int rowEnd, int column);

	/**
	 * Checks whether within the grid, there is a collision with the defined span.
	 * \param span the span it should follow.
	 */
	bool CheckSpanCollision(GridSpan span);

	/**
	 * \return returns the default column size.
	 */
	int GetDefaultColumnSize();

	/**
	 * \return returns the default row size.
	 */
	int GetDefaultRowSize();

	/**
	 * \param defaultColumnSize sets the default size for columns if they expand beyound the defined Grid::SetGridColumns
	 */
	void SetDefaultColumnSize(int defaultColumnSize);

	/**
	 * \param defaultRowSize sets the default size for row if they expand beyound the defined Grid::SetDefaultRowSize
	 */
	void SetDefaultRowSize(int defaultRowSize);

	/**
	 * Gets the grid cell at the specified index
	 * \param x the x index of the cell
	 * \param y the y index of the cell.
	 */
	GridCell* GetGridCell(int x, int y);

	/**
	 * \param columns a list of column sizes which are explicitely defined. If the columns expand beyound the defined size, the default column size is used.
	 */
	void SetGridColumns(std::initializer_list<int> columns);

	/**
	 * \param columns a list of row sizes which are explicitely defined. If the columns expand beyound the defined size, the default row size is used.
	 */
	void SetGridRows(std::initializer_list<int> rows);

	/**
	 * \param index the index at which to check.
	 * \return returns the row height at the specified index.
	 */
	int GetGridRowSize(int index);
	
	/**
	 * \param index the index at which to check.
	 * \return returns the row height at the specified index.
	 */
	int GetGridColumnSize(int index);

	/**
	 * Automatically extends the size of the grid based on the number of rows and columns
	 * \param state Auto extention state.
	 */
	void SetAutoExtend(bool state);

	/**
	 * \return returns the auto extention state.
	 */
	bool IsAutoextending();
	void Add(UiElement& component) override;
};

