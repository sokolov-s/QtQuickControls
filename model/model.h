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

    /**
     * @brief CreateField - generate field with empty cells of the specified size
     * @param size - the length of the field side
     */
    void CreateField(const size_t size);

    /**
     * @brief ClearField - mark all cells in the field as empty
     */
    void ClearField();

    /**
     * @brief SetPlayer - Change current player
     * @param player - player
     */
    void SetPlayer(ePlayer player);

    /**
     * @brief GetCurrentPlayer - return current player
     * @return - player
     */
    ePlayer GetCurrentPlayer() const noexcept;

    /**
     * @brief GetCurrentPlayerNumber - return current player number. It can be from 1 to 2
     * @return - player number
     */
    size_t GetCurrentPlayerNumber() const noexcept;

    /**
     * @brief SwitchPlayer - switch player
     * @return  - number of new player
     */
    size_t SwitchPlayer() noexcept;

    std::shared_ptr<Field> GetField();
    Cell::eState GetCellState4Player() const noexcept;
    Cell::eState GetCellState4Player(const ePlayer player) const noexcept;
    bool IsFieldFull() const noexcept;
private:
    std::shared_ptr<Field> field_;
    ePlayer curPlayer_ = ePlayer::kX;
};

} //namespace model

#endif // MODEL_H
