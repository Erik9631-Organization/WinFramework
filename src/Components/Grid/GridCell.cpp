#include "GridCell.h"
#include "Grid.h"
#include "EventUpdateInfo.h"

glm::ivec2 GridCell::CalculatePixelPosition()
{
    int posX = 0;
    int posY = 0;

    if(parentGrid.GetGridCell(indexPos.x - 1, indexPos.y) != nullptr)
        posX = parentGrid.GetGridCell(indexPos.x - 1, indexPos.y)->GetPixelX() +
                parentGrid.GetGridCell(indexPos.x - 1, indexPos.y)->GetWidth() + parentGrid.GetColumnGap();

    if (parentGrid.GetGridCell(indexPos.x, indexPos.y - 1) != nullptr)
        posY = parentGrid.GetGridCell(indexPos.x, indexPos.y - 1)->GetPixelY() +
                parentGrid.GetGridCell(indexPos.x, indexPos.y - 1)->GetHeight() + parentGrid.GetRowGap();
    return {posX, posY};
}

glm::ivec2 GridCell::GetSpanSize()
{
    glm::ivec2 spanSize;

    if (GetSpanParent() == nullptr)
        return spanSize;
    if (GetSpanCorner() == nullptr)
        return spanSize;

    int spanX = GetSpanCorner()->GetPixelPosition().x;
    int spanParentX = GetSpanParent()->GetPixelPosition().y;

    GridCell* cornerCell = GetSpanCorner();
    GridCell* parentCell = GetSpanParent();

    int columnGapSum = (span.GetGridColumnEnd() - span.GetGridColumnStart()) * parentGrid.GetColumnGap();
    int rowGapSum = (span.GetGridRowEnd() - span.GetGridRowStart()) * parentGrid.GetRowGap();

    spanSize.x = cornerCell->GetPixelPosition().x - parentCell->GetPixelPosition().x + cornerCell->GetSize().x + columnGapSum;
    spanSize.y = cornerCell->GetPixelPosition().y - parentCell->GetPixelPosition().y + cornerCell->GetSize().y + rowGapSum;
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

    if (position.x == span.GetGridColumnStart() && position.y == span.GetGridRowStart())
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

const glm::vec4 & GridCell::GetSize()
{
    return {cellSize.x, cellSize.y, 0, 1};
}

float GridCell::GetWidth()
{
    return cellSize.x;
}

float GridCell::GetHeight()
{
    return cellSize.y;
}

void GridCell::SetSize(const glm::vec4 &size, bool emit)
{
    cellSize = size;
    if (GetControlledAdjustable() == nullptr)
        return;

    if (span.isSet())
        GetControlledAdjustable()->SetSize({GetSpanSize().x, GetSpanSize().y, 0, 1}, emit);
    else
        GetControlledAdjustable()->SetSize(size, emit);
}

void GridCell::SetSize(float width, float height, bool emit)
{
    SetSize({width, height, 0, 1}, emit);
}

void GridCell::SetWidth(float width, bool emit)
{
    SetSize(width, cellSize.y, emit);
}

void GridCell::SetHeight(float height, bool emit)
{
    SetSize(cellSize.x, height, emit);
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

void GridCell::NotifyOnMoveSubscribers(const EventMoveInfo &event)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->NotifyOnMoveSubscribers(event);
}

const glm::vec4 & GridCell::GetPosition() const
{
    return indexPos;
}

//TODO fix absolute position
const glm::vec4 & GridCell::GetAbsolutePosition() const
{
    return {indexPos.x + parentGrid.GetAbsolutePosition().x, indexPos.y + parentGrid.GetAbsolutePosition().y, 0, 1};
}

void GridCell::SetPosition(const glm::vec4 &position, bool emit)
{
    this->indexPos.x = position.x;
    this->indexPos.y = position.y;
    this->position = {CalculatePixelPosition().x, CalculatePixelPosition().y};
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetPosition({this->position.x, this->position.y, 0, 1}, emit);
}

void GridCell::SetTranslate(const glm::vec4 &offset, bool emit)
{
    if (associatedAdjustable == nullptr)
        return;
    associatedAdjustable->SetTranslate(offset, true);
}

const glm::vec4 & GridCell::GetTranslate() const
{
    if (associatedAdjustable == nullptr)
        return {0, 0, 0, 1};

    return associatedAdjustable->GetTranslate();
}


void GridCell::OnUpdate(EventUpdateInfo e)
{
    if (e.HasFlag(EventUpdateFlags::Move))
    {
        glm::ivec2 pixelPos = CalculatePixelPosition(); //Update
        if(associatedAdjustable != nullptr)
        {
            auto pixelPos = CalculatePixelPosition();
            associatedAdjustable->SetPosition({pixelPos.x, pixelPos.y, 0, 1}, false);
        }
        this->position = glm::vec2(pixelPos.x, pixelPos.y);
    }

    if (e.HasFlag(EventUpdateFlags::Resize))
        SetSize({cellSize.x, cellSize.y, 0, 1}, false);

    if (e.HasFlag(EventUpdateFlags::Redraw))
    {
        if(associatedAdjustable != nullptr)
            associatedAdjustable->OnUpdate(e);
    }

}

int GridCell::GetPixelX()
{
    return position.x;
}

int GridCell::GetPixelY()
{
    return position.y;
}

glm::vec2 GridCell::GetPixelPosition()
{
    return position;
}


void GridCell::SetSize(glm::vec4 size)
{
    SetSize(size, true);
}

void GridCell::SetSize(float width, float height)
{
    SetSize(width, height, true);
}

void GridCell::SetWidth(float width)
{
    SetWidth(width, true);
}

void GridCell::SetHeight(float height)
{
    SetHeight(height, true);
}