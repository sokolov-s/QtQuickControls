#ifndef FIELD_H
#define FIELD_H

#include <stdio.h>
#include <vector>
#include "cell.h"

namespace model {

class Field
{
public:
    Field(const size_t size);
    void Clear();
    const Cell & GetCell(size_t x, size_t y) const;
    Cell *GetCellPtr(size_t x, size_t y);
    size_t GetSize() const noexcept;
    void SetCellState(size_t x, size_t y, const Cell::eState state);
    Cell::eState GetCellState(size_t x, size_t y) const noexcept;
    size_t GetEmptyCellsCount() const noexcept;
private:
    void GenerateGrid();
    size_t size_ = 0;
    typedef std::vector<std::vector<Cell>> Grid;
    Grid grid_;
    size_t emptyCellsCnt_ = 0;
};
} //namespace model
#endif // FIELD_H
