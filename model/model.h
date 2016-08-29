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

    Model();
    void CreateField(const size_t size);
    void ClearField();
    void SetPlayer(ePlayer player);
    ePlayer GetCurrentPlayer() const noexcept;
    size_t GetCurrentPlayerNumber() const noexcept;
    /**
     * @brief SwitchPlayer - switch player
     * @return  - number of new player
     */
    size_t SwitchPlayer() noexcept;
    std::shared_ptr<Field> GetField();
    Cell::eState GetState4Player(const ePlayer player) const noexcept;
    bool IsFieldFull() const noexcept;
private:
    std::shared_ptr<Field> field_;
    ePlayer curPlayer_ = ePlayer::kX;
};

} //namespace model

#endif // MODEL_H
