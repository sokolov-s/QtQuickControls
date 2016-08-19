#include "cell.h"
#include "model_exeptions.h"

using namespace model;

Cell::Cell()
{    
}

void Cell::SetState(const Cell::eState state)
{
    if(eState::kZ == state_) {
        state_ = state;
    } else {
        throw EBadOperation("Can't change cell state");
    }
}

Cell::eState Cell::GetState() const
{
    return state_;
}
