#ifndef IPLAYER_H
#define IPLAYER_H

#include "../model/field.h"
#include "../model/cell.h"
#include <functional>
#include <thread>
#include <memory>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "../model/model.h"

namespace ai {
/**
 * @brief The IPlayer class. Base abstract class for all players.
 */
class IPlayer {
public:
    typedef std::shared_ptr<model::Field> Field;
    IPlayer(model::Model::ePlayer playerType);
    virtual ~IPlayer();

    model::Model::ePlayer GetType() const noexcept { return type_;}
    void SetField(Field field) {field_ = field;}
    void SetPlayerCellsType(model::Cell::eState cellState) noexcept {palyerCells_ = cellState;}
    void SetOpponentCellsType(model::Cell::eState cellState) noexcept {opponentCells_ = cellState;}

    /**
     * @brief MakeTurn - Function runs async process to calculate player turn. When calculations will be finished
     * callback function will be called.
     * @param callBack - callback function. The first argument is an x and the second - is an y coordinats of calculated position
     */
    void MakeTurn(std::function<void(unsigned int , unsigned int)> callBack);
    void MakeTurn(Field field, model::Cell::eState playerState, std::function<void(unsigned int , unsigned int)> callBack);
    virtual bool IsHuman() const = 0;

    /**
     * @brief Abort - Abort all previous calculations. Set abort flag to true. Processes which make calculations
     * need to check this flag by calling IsInterrupted() function to abort job immediately
     * The calling thread will stopped
     */
    void Abort();

    /**
     * @brief Wait4Results - Function waits for the end of previous calculations. The calling thread will stopped
     */
    void Wait4Results();

    /**
     * @brief SetWinRowsCount - Set count of the same cells to victory
     * @param cnt - count of cells
     */
    void SetWinRowsCount(size_t cnt) noexcept;

protected:
    const Field GetField() const noexcept;
    model::Cell::eState GetPlayerCellsType() const noexcept;
    model::Cell::eState GetOpponentCellsType() const noexcept;
    bool IsInterrupted() const noexcept;
    size_t GetWinSize() const noexcept;
    virtual void CalculateTurn(unsigned int *x, unsigned int *y) const = 0;
private:
    void RunCalculation();
    void FinishTurn(unsigned int x, unsigned int y);
private:
    model::Model::ePlayer type_;
    std::shared_ptr<model::Field> field_;
    model::Cell::eState palyerCells_ = model::Cell::eState::kEmpty;
    model::Cell::eState opponentCells_ = model::Cell::eState::kEmpty;
    std::function<void(unsigned int, unsigned int)> cb_;
    std::atomic_bool calculatingFlag_;
    std::atomic_bool interruptFlag_;
    std::condition_variable cv_;
    std::mutex mtx_;
    size_t cnt2Win_ = 0;
};

} //namespace ai
#endif // IPLAYER_H
