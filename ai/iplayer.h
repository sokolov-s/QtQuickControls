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

namespace ai {

class IPlayer {
public:
    typedef std::shared_ptr<model::Field> Field;
    IPlayer();

    virtual ~IPlayer();

    void SetField(Field field) {field_ = field;}
    void SetPlayerCellsType(model::Cell::eState cellState) {palyerCells_ = cellState;}
    void SetOpponentCellsType(model::Cell::eState cellState) {opponentCells_ = cellState;}
    void MakeTurn(std::function<void(unsigned int , unsigned int)> callBack);
    void MakeTurn(Field field, model::Cell::eState playerState, std::function<void(unsigned int , unsigned int)> callBack);
    virtual bool IsHuman() const = 0;
    void Abort();
    void Wait4Results();
    void SetWinRowsCount(size_t cnt) noexcept;

protected:
    const Field GetField() const noexcept;
    model::Cell::eState GetPlayerCellsType() const noexcept;
    model::Cell::eState GetOpponentCellsType() const noexcept;
    bool IsInterrupted() noexcept;
    size_t GetWinSize() const noexcept;
    virtual void CalculateTurn(unsigned int *x, unsigned int *y) const = 0;
private:
    void RunCalculation();
    void FinishTurn(unsigned int x, unsigned int y);
private:
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
