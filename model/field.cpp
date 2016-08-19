#include "field.h"

using namespace model;

Field::Field(const size_t size)
    : size_(size)
    , grid_(size, std::vector<Cell>(size))
{    
}

void Field::Clear()
{
    
}
