#include "model.h"

using namespace model;

Model::Model(Controller *cntrl)
    : controller_(cntrl)
{    
}

void Model::CreateField(const size_t size)
{
    field_.reset(new Field(size));
}

void Model::ClearField()
{
    field_->Clear();
}

