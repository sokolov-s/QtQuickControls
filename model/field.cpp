#include "field.h"
#include "model_exeptions.h"

using namespace model;

Field::Field(const size_t size)
    : size_(size)
    , grid_(size, std::vector<Cell>(size, size))
    , emptyCellsCnt_(size * size)
{    
}

void Field::Clear()
{
    grid_ = std::move(Grid(size_, std::vector<Cell>(size_, size_)));
}

const Cell &Field::GetCell(size_t x, size_t y) const
{
    if(x >= size_ || y >= size_)
        throw EWrongParameter("X or Y is wrong");
    return grid_[x][y];
}

Cell *Field::GetCellPtr(size_t x, size_t y)
{
    // I understand that const_cast is bad. But in future we can change
    // model of field and then we will need to change both functions
    // In this case const_cast is safely
    return &const_cast<Cell&>(GetCell(x,y));
}

size_t Field::GetSize() const noexcept
{
    return size_;
}

void Field::SetCellState(size_t x, size_t y, const Cell::eState state)
{
    GetCellPtr(x,y)->SetState(state);
    --emptyCellsCnt_;
}

size_t Field::GetEmptyCellsCount() const noexcept
{
    return emptyCellsCnt_;
}
