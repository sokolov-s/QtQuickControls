#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <memory>
#include "field.h"
#include "cell.h"

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
    ePlayer GetCurrentPlayer() const noexcept;
    void SwitchPlayer();
    Field *GetField();
    Cell::eState GetState4Player(const ePlayer player) const noexcept;
private:
    std::unique_ptr<Field> field_;
    ViewModel *controller_ = nullptr;
    ePlayer curPlayer_ = ePlayer::kX;
};

} //namespace model

#endif // MODEL_H
