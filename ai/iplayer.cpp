#include "iplayer.h"

using namespace ai;

IPlayer::IPlayer(model::Model::ePlayer playerType)
    : type_(playerType)
    , calculatingFlag_(false)
    , interruptFlag_(false)
{
}

IPlayer::~IPlayer()
{
    Abort();
}

void IPlayer::MakeTurn(std::function<void (unsigned int, unsigned int)> callBack)
{
    // TODO: use boost thread pool for jobs
    Wait4Results();
    std::swap(cb_, callBack);
    std::thread(std::bind(&IPlayer::RunCalculation, this)).detach();
}

void IPlayer::MakeTurn(Field field, model::Cell::eState playerState, std::function<void (unsigned int, unsigned int)> callBack)
{
    // TODO: use boost thread pool for jobs
    Wait4Results();
    SetField(field);
    SetPlayerCellsType(playerState);
    MakeTurn(callBack);
}

void IPlayer::Abort()
{
    interruptFlag_.store(true);
    Wait4Results();
    interruptFlag_.store(false);
}

const IPlayer::Field IPlayer::GetField() const noexcept
{
    return field_;
}

model::Cell::eState IPlayer::GetPlayerCellsType() const noexcept
{
    return palyerCells_;
}

model::Cell::eState IPlayer::GetOpponentCellsType() const noexcept
{
    return opponentCells_;
}

bool IPlayer::IsInterrupted() const noexcept
{
    return interruptFlag_.load();
}

size_t IPlayer::GetWinSize() const noexcept
{
    return cnt2Win_;
}

void IPlayer::Wait4Results()
{
    std::unique_lock<std::mutex> locker(mtx_);
    cv_.wait(locker, [this]{return !calculatingFlag_.load();});
}

void IPlayer::SetWinRowsCount(size_t cnt) noexcept
{
    cnt2Win_ = cnt;
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
