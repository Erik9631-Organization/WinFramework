#include "GridCell.h"
#include "Grid.h"
#include "EventTypes/EventUpdateInfo.h"

Gdiplus::Point GridCell::CalculatePixelPosition()
{
    int posX = 0;
    int posY = 0;

    if(parentGrid.GetGridCell(indexPos.X - 1, indexPos.Y) != nullptr)
        posX = parentGrid.GetGridCell(indexPos.X - 1, indexPos.Y)->GetPixelX() + parentGrid.GetGridCell(indexPos.X - 1, indexPos.Y)->GetWidth() + parentGrid.GetColumnGap();

    if (parentGrid.GetGridCell(indexPos.X, indexPos.Y - 1) != nullptr)
        posY = parentGrid.GetGridCell(indexPos.X, indexPos.Y - 1)->GetPixelY() + parentGrid.GetGridCell(indexPos.X, indexPos.Y - 1)->GetHeight() + parentGrid.GetRowGap();
    return Gdiplus::Point(posX, posY);
}

Gdiplus::Size GridCell::GetSpanSize()
{
    Gdiplus::Size spanSize;

    if (GetSpanParent() == nullptr)
        return spanSize;
    if (GetSpanCorner() == nullptr)
        return spanSize;

    int spanX = GetSpanCorner()->GetPixelPosition().X;
    int spanParentX = GetSpanParent()->GetPixelPosition().X;

    GridCell* cornerCell = GetSpanCorner();
    GridCell* parentCell = GetSpanParent();

    int columnGapSum = (span.GetGridColumnEnd() - span.GetGridColumnStart()) * parentGrid.GetColumnGap();
    int rowGapSum = (span.GetGridRowEnd() - span.GetGridRowStart()) * parentGrid.GetRowGap();

    spanSize.Width = cornerCell->GetPixelPosition().X - parentCell->GetPixelPosition().X + cornerCell->GetSize().Width + columnGapSum;
    spanSize.Height = cornerCell->GetPixelPosition().Y - parentCell->GetPixelPosition().Y + cornerCell->GetSize().Height + rowGapSum;
    return spanSize;
}

void GridCell::ControlAdjustable(Adjustable* associatedAdjustable)
{
    if (span.isSet())
    {
        if (this != GetSpanParent()) //Use IsSpanParent
            GetSpanParent()->ControlAdjustable(associatedAdjustable);
        else
            this->associatedAdjustable = associatedAdjustable;
    }

    else
        this->associatedAdjustable = associatedAdjustable;

    OnUpdate(EventUpdateInfo(EventUpdateFlags::Move | EventUpdateFlags::Resize));
}

Adjustable* GridCell::GetControlledAdjustable()
{
    if (span.isSet()) //If spanning is set, then only one component can exist and it is contained within the parent
    {
        if (GetSpanParent() == this) //Use IsSpanParent
            return associatedAdjustable;
        if(GetSpanParent() != nullptr)
            return GetSpanParent()->GetControlledAdjustable();  
        return nullptr;
    }

    return associatedAdjustable;
}

GridCell::GridCell(Grid& parentGrid) : parentGrid(parentGrid)
{
    associatedAdjustable = nullptr;
}

GridCell* GridCell::GetSpanParent()
{
    if (!span.isSet())
        return nullptr;

    return parentGrid.GetGridCell(span.GetGridColumnStart(), span.GetGridRowStart());
}

GridCell* GridCell::GetSpanCorner()
{
    if (!span.isSet())
        return nullptr;

    return parentGrid.GetGridCell(span.GetGridColumnEnd(), span.GetGridRowEnd());
}

void GridCell::SetSpan(GridSpan span)
{
    this->span = span;
}

GridSpan GridCell::GetSpan()
{
    return span;
}

bool GridCell::IsSpanParent()
{
    if (!span.isSet())
        return false;

    if (position.X == span.GetGridColumnStart() && position.Y == span.GetGridRowStart())
        return true;

}

void GridCell::NotifyOnResizeSubscribers(EventResizeInfo event)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->NotifyOnResizeSubscribers(event);
}

void GridCell::AddOnResizeSubscriber(ResizeSubscriber& subscriber)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->AddOnResizeSubscriber(subscriber);
}

void GridCell::RemoveOnResizeSubscriber(ResizeSubscriber& subscriber)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->RemoveOnResizeSubscriber(subscriber);
}

Gdiplus::Size GridCell::GetSize()
{
    return cellSize;
}

int GridCell::GetWidth()
{
    return cellSize.Width;
}

int GridCell::GetHeight()
{
    return cellSize.Height;
}

void GridCell::SetSize(Gdiplus::Size size)
{
    cellSize = size;
    if (GetControlledAdjustable() == nullptr)
        return;

    if (span.isSet())
        GetControlledAdjustable()->SetSize(GetSpanSize());
    else
        GetControlledAdjustable()->SetSize(size);
}

void GridCell::SetSize(int width, int height)
{
    SetSize(Gdiplus::Size(width, height));
}

void GridCell::SetWidth(int width)
{
    SetSize(cellSize.Height, width);
}

void GridCell::SetHeight(int height)
{
    SetSize(height, cellSize.Width);
}

void GridCell::AddOnMoveSubscriber(MoveSubscriber& subscriber)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->AddOnMoveSubscriber(subscriber);
}

void GridCell::RemoveOnMoveSubscriber(MoveSubscriber& subscriber)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->RemoveOnMoveSubscriber(subscriber);
}

void GridCell::NotifyOnMoveSubscribers(EventMoveInfo event)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->NotifyOnMoveSubscribers(event);
}

Gdiplus::Point GridCell::GetPosition()
{
    return indexPos;
}

int GridCell::GetX()
{
    return indexPos.X;
}

int GridCell::GetY()
{
    return indexPos.Y;
}

int GridCell::GetAbsoluteX()
{
    return indexPos.X + parentGrid.GetAbsoluteX();
}

int GridCell::GetAbsoluteY()
{
    return indexPos.Y + parentGrid.GetAbsoluteY();
}

Gdiplus::Point GridCell::GetAbsolutePosition()
{
    return Gdiplus::Point(indexPos.X + parentGrid.GetAbsoluteX(), indexPos.Y + parentGrid.GetAbsoluteY());
}

void GridCell::SetPosition(Gdiplus::Point position)
{
    this->indexPos = position;
    this->position = CalculatePixelPosition();
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetPosition(this->position);
}

void GridCell::SetPosition(int x, int y)
{
    SetPosition(Gdiplus::Point(x, y));
}

void GridCell::SetX(int x)
{
    SetPosition(x, indexPos.Y);
}

void GridCell::SetY(int y)
{
    SetPosition(indexPos.X, y);
}

void GridCell::SetElementOffset(Gdiplus::Point offset)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetElementOffset(offset);
}

void GridCell::SetElementXOffset(int x)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetElementXOffset(x);
}

void GridCell::SetElementYOffset(int y)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetElementYOffset(y);
}

Gdiplus::Point GridCell::GetElementOffset()
{
    if (associatedAdjustable == nullptr)
        return Gdiplus::Point(0, 0);

    return associatedAdjustable->GetElementOffset();
}

int GridCell::GetElementXOffset()
{
    if (associatedAdjustable == nullptr)
        return 0;
    return associatedAdjustable->GetElementXOffset();
}

int GridCell::GetElementYOffset()
{
    if (associatedAdjustable == nullptr)
        return 0;
    return associatedAdjustable->GetElementYOffset();
}

void GridCell::OnUpdate(EventUpdateInfo e)
{
    if (e.HasFlag(EventUpdateFlags::Move))
    {
        Gdiplus::Point pixelPos = CalculatePixelPosition(); //Update
        if(associatedAdjustable != nullptr)
            associatedAdjustable->SetPosition(CalculatePixelPosition());
        this->position = pixelPos;
    }

    if (e.HasFlag(EventUpdateFlags::Resize))
        SetSize(cellSize);

    if (e.HasFlag(EventUpdateFlags::Redraw))
    {
        if(associatedAdjustable != nullptr)
            associatedAdjustable->OnUpdate(e);
    }

}

int GridCell::GetPixelX()
{
    return position.X;
}

int GridCell::GetPixelY()
{
    return position.Y;
}

Gdiplus::Point GridCell::GetPixelPosition()
{
    return position;
}
