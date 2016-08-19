#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <memory>
#include "field.h"

class Controller;

namespace model {

class Model
{
public:
    Model(Controller *cntrl);
    void CreateField(const size_t size);
    void ClearField();
    
private:
    std::unique_ptr<Field> field_;
    Controller *controller_ = nullptr;
};

} //namespace model

#endif // MODEL_H
