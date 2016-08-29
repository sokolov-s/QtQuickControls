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

    void SetField(Field field) {field_.swap(field);}
    void SetPlayerState(model::Cell::eState playerState) {state_ = playerState;}
    void MakeTurn(std::function<void(unsigned int , unsigned int)> callBack);
    void MakeTurn(Field field, model::Cell::eState playerState, std::function<void(unsigned int , unsigned int)> callBack);
    virtual bool IsHuman() const = 0;
    void Abort();
    void Wait4Results();

protected:
    const Field GetField() const;
    model::Cell::eState GetPlayerState() const;
    bool IsInterrupted();
private:
    virtual void CalculateTurn(unsigned int *x, unsigned int *y) const = 0;
    void RunCalculation();
    void FinishTurn(unsigned int x, unsigned int y);
private:
    std::shared_ptr<model::Field> field_;
    model::Cell::eState state_ = model::Cell::eState::kEmpty;
    std::function<void(unsigned int, unsigned int)> cb_;
    std::atomic_bool calculatingFlag_;
    std::atomic_bool interruptFlag_;
    std::condition_variable cv_;
    std::mutex mtx_;
};

} //namespace ai
#endif // IPLAYER_H
