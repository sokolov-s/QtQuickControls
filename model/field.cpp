#include "field.h"
#include "model_exeptions.h"

using namespace model;

Field::Field(const size_t size)
    : size_(size)
    , emptyCellsCnt_(size * size)
{
    GenerateGrid();
}

void Field::Clear()
{
    GenerateGrid();
}

const Cell &Field::GetCell(size_t x, size_t y) const
{
    if(x >= size_ || y >= size_)
        throw EWrongParameter("X or Y is wrong");
    return grid_[y][x];
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

Cell::eState Field::GetCellState(size_t x, size_t y) const noexcept
{
    return GetCell(x,y).GetState();
}

size_t Field::GetEmptyCellsCount() const noexcept
{
    return emptyCellsCnt_;
}

void Field::GenerateGrid()
{
    grid_.clear();
    for(size_t y = 0; y < GetSize(); ++y) {
        std::vector<Cell> row;
        for (size_t x = 0; x < GetSize(); ++x) {
            row.push_back(Cell(GetSize()));
        }
        grid_.push_back(row);
    }
}
