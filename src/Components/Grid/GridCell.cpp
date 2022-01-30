#include "GridCell.h"
#include "Grid.h"
#include "EventTypes/EventUpdateInfo.h"

Vector2Int GridCell::CalculatePixelPosition()
{
    int posX = 0;
    int posY = 0;

    if(parentGrid.GetGridCell(indexPos.GetX() - 1, indexPos.GetY()) != nullptr)
        posX = parentGrid.GetGridCell(indexPos.GetX() - 1, indexPos.GetY())->GetPixelX() +
                parentGrid.GetGridCell(indexPos.GetX() - 1, indexPos.GetY())->GetWidth() + parentGrid.GetColumnGap();

    if (parentGrid.GetGridCell(indexPos.GetX(), indexPos.GetY() - 1) != nullptr)
        posY = parentGrid.GetGridCell(indexPos.GetX(), indexPos.GetY() - 1)->GetPixelY() +
                parentGrid.GetGridCell(indexPos.GetX(), indexPos.GetY() - 1)->GetHeight() + parentGrid.GetRowGap();
    return {posX, posY};
}

Vector2Int GridCell::GetSpanSize()
{
    Vector2Int spanSize;

    if (GetSpanParent() == nullptr)
        return spanSize;
    if (GetSpanCorner() == nullptr)
        return spanSize;

    int spanX = GetSpanCorner()->GetPixelPosition().GetX();
    int spanParentX = GetSpanParent()->GetPixelPosition().GetY();

    GridCell* cornerCell = GetSpanCorner();
    GridCell* parentCell = GetSpanParent();

    int columnGapSum = (span.GetGridColumnEnd() - span.GetGridColumnStart()) * parentGrid.GetColumnGap();
    int rowGapSum = (span.GetGridRowEnd() - span.GetGridRowStart()) * parentGrid.GetRowGap();

    spanSize.SetX(cornerCell->GetPixelPosition().GetX() - parentCell->GetPixelPosition().GetY() + cornerCell->GetSize().GetX() + columnGapSum);
    spanSize.SetY(cornerCell->GetPixelPosition().GetY() - parentCell->GetPixelPosition().GetY() + cornerCell->GetSize().GetY() + rowGapSum);
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

    if (position.GetX() == span.GetGridColumnStart() && position.GetY() == span.GetGridRowStart())
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

Vector2 GridCell::GetSize()
{
    return cellSize;
}

float GridCell::GetWidth()
{
    return cellSize.GetX();
}

float GridCell::GetHeight()
{
    return cellSize.GetY();
}

void GridCell::SetSize(Vector2 size)
{
    cellSize = size;
    if (GetControlledAdjustable() == nullptr)
        return;

    if (span.isSet())
        GetControlledAdjustable()->SetSize(GetSpanSize());
    else
        GetControlledAdjustable()->SetSize(size);
}

void GridCell::SetSize(float width, float height)
{
    SetSize({width, height});
}

void GridCell::SetWidth(float width)
{
    SetSize(width, cellSize.GetY());
}

void GridCell::SetHeight(float height)
{
    SetSize(cellSize.GetX(), height);
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

Vector2 GridCell::GetPosition()
{
    return indexPos;
}

float GridCell::GetX()
{
    return indexPos.GetX();
}

float GridCell::GetY()
{
    return indexPos.GetY();
}

float GridCell::GetAbsoluteX()
{
    return indexPos.GetX() + parentGrid.GetAbsoluteX();
}

float GridCell::GetAbsoluteY()
{
    return indexPos.GetY() + parentGrid.GetAbsoluteY();
}

Vector2 GridCell::GetAbsolutePosition()
{
    return {indexPos.GetX() + parentGrid.GetAbsoluteX(), indexPos.GetY() + parentGrid.GetAbsoluteY()};
}

void GridCell::SetPosition(Vector2 position)
{
    this->indexPos = position;
    this->position = CalculatePixelPosition();
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetPosition(this->position);
}

void GridCell::SetPosition(float x, float y)
{
    SetPosition({x, y});
}

void GridCell::SetX(float x)
{
    SetPosition(x, indexPos.GetY());
}

void GridCell::SetY(float y)
{
    SetPosition(indexPos.GetX(), y);
}

void GridCell::SetTranslate(Vector2 offset)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetTranslate(offset);
}

void GridCell::SetTranslateX(float x)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetTranslateX(x);
}

void GridCell::SetTranslateY(float y)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetTranslateY(y);
}

Vector2 GridCell::GetTranslate()
{
    if (associatedAdjustable == nullptr)
        return {0, 0};

    return associatedAdjustable->GetTranslate();
}

float GridCell::GetTranslateX()
{
    if (associatedAdjustable == nullptr)
        return 0;
    return associatedAdjustable->GetTranslateX();
}

float GridCell::GetTranslateY()
{
    if (associatedAdjustable == nullptr)
        return 0;
    return associatedAdjustable->GetTranslateY();
}

void GridCell::OnUpdate(EventUpdateInfo e)
{
    if (e.HasFlag(EventUpdateFlags::Move))
    {
        Vector2Int pixelPos = CalculatePixelPosition(); //Update
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
    return position.GetX();
}

int GridCell::GetPixelY()
{
    return position.GetY();
}

Vector2 GridCell::GetPixelPosition()
{
    return position;
}
