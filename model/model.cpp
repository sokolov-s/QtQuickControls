#include "model.h"

using namespace model;

Model::Model(ViewModel *cntrl)
    : controller_(cntrl)
{    
}

void Model::CreateField(const size_t size)
{
    field_.reset(new Field(size));
}

void Model::ClearField()
{
    field_->Clear();
}

void Model::SetPlayer(Model::ePlayer player)
{
    curPlayer_ = player;
}

Model::ePlayer Model::GetCurrentPlayer() const
{
    return curPlayer_;
}

void Model::SwitchPlayer()
{
    curPlayer_ =  (ePlayer::kX == curPlayer_) ? ePlayer::kO : ePlayer::kX;
}

Field *Model::GetField()
{
    return field_.get();
}

