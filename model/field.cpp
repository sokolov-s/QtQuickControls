#include "field.h"

using namespace model;

Field::Field(const size_t size)
    : size_(size)
    , grid_(size, std::vector<Cell>(size, size))
{    
}

void Field::Clear()
{
    grid_ = std::move(Grid(size_, std::vector<Cell>(size_, size_)));
}

const Cell &Field::GetCell(size_t x, size_t y) const
{
    return grid_[x][y];
}

Cell *Field::GetCellPtr(size_t x, size_t y)
{
    return &const_cast<Cell&>(GetCell(x,y));
}
