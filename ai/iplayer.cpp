#include "iplayer.h"

using namespace ai;

IPlayer::IPlayer()
    : calculatingFlag_(false)
    , interruptFlag_(false)
{
}

IPlayer::~IPlayer()
{
    Abort();
}

void IPlayer::MakeTurn(std::function<void (unsigned int, unsigned int)> callBack)
{
    Wait4Results();
    std::swap(cb_, callBack);
    std::thread(std::bind(&IPlayer::RunCalculation, this)).detach();
}

void IPlayer::MakeTurn(Field field, model::Cell::eState playerState, std::function<void (unsigned int, unsigned int)> callBack)
{
    Wait4Results();
    SetField(field);
    SetPlayerState(playerState);
    MakeTurn(callBack);
}

void IPlayer::Abort()
{
    interruptFlag_.store(true);
    Wait4Results();
    interruptFlag_.store(false);
}

const IPlayer::Field IPlayer::GetField() const
{
    return field_;
}

model::Cell::eState IPlayer::GetPlayerState() const
{
    return state_;
}

bool IPlayer::IsInterrupted()
{
    return interruptFlag_.load();
}

void IPlayer::Wait4Results()
{
    std::unique_lock<std::mutex> locker(mtx_);
    cv_.wait(locker, [this]{return !calculatingFlag_.load();});
}

void IPlayer::RunCalculation()
{
    calculatingFlag_.store(true);
    unsigned int x, y;
    x = y = 0;
    CalculateTurn(&x, &y);
    if (! IsInterrupted()) {
        FinishTurn(x, y);
    }
    calculatingFlag_.store(false);
    cv_.notify_one();
}

void IPlayer::FinishTurn(unsigned int x, unsigned int y)
{
    std::thread(std::bind(cb_, x, y)).detach();
}
