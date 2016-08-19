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
private:
    size_t size_;
    std::vector<std::vector<Cell>> grid_;
};
} //namespace model
#endif // FIELD_H
