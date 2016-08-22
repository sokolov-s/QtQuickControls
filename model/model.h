#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <memory>
#include "field.h"

class ViewModel;

namespace model {

class Model
{
public:
    enum  ePlayer {
        kX,
        kO
    };

    Model(ViewModel *cntrl);
    void CreateField(const size_t size);
    void ClearField();
    void SetPlayer(ePlayer player);
    ePlayer GetCurrentPlayer() const;
    void SwitchPlayer();
    Field *GetField();
private:
    std::unique_ptr<Field> field_;
    ViewModel *controller_ = nullptr;
    ePlayer curPlayer_ = ePlayer::kX;
};

} //namespace model

#endif // MODEL_H
