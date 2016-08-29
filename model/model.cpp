#include "model.h"

using namespace model;

Model::Model()
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

Model::ePlayer Model::GetCurrentPlayer() const noexcept
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

Cell::eState Model::GetState4Player(const Model::ePlayer player) const noexcept
{
    switch(player) {
    case ePlayer::kX: return Cell::eState::kX;
    case ePlayer::kO: return Cell::eState::kO;
    default: return Cell::eState::kEmpty;
    }
}

bool Model::IsFieldFull() const noexcept
{
    return (field_->GetEmptyCellsCount() == 0);
}

