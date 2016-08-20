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
private:
    size_t size_;
    typedef std::vector<std::vector<Cell>> Grid;
    Grid grid_;
};
} //namespace model
#endif // FIELD_H
