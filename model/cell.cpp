#include "cell.h"
#include "model_exeptions.h"

using namespace model;

size_t Cell::globalX_ = 0;
size_t Cell::globalY_ = 0;

Cell::Cell(size_t fieldSize)
    : position_(globalX_, globalY_)
{
    if(globalX_ < fieldSize) {
        ++globalX_;
    } else {
        globalX_ = 0;
        ++globalY_;
    }
}

void Cell::SetState(const Cell::eState state)
{
    if(eState::kEmpty == state_) {
        state_ = state;
    } else {
        throw EBadOperation("Can't change cell state");
    }
}

Cell::eState Cell::GetState() const
{
    return state_;
}

const Cell::Position &Cell::GetPosition() const
{
    return position_;
}

size_t Cell::GetX() const
{
    return position_.x;
}

size_t Cell::GetY() const
{
    return position_.y;
}
