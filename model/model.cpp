#include "model.h"

using namespace model;

Model::Model()
{    
}

void Model::CreateField(const size_t size)
{
    field_ = std::make_shared<Field>(size);
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

size_t Model::GetCurrentPlayerNumber() const noexcept
{
    return (ePlayer::kX == GetCurrentPlayer()) ? 1 : 2;
}

size_t Model::SwitchPlayer() noexcept
{
    curPlayer_ =  (ePlayer::kX == GetCurrentPlayer()) ? ePlayer::kO : ePlayer::kX;
    return GetCurrentPlayerNumber();
}

std::shared_ptr<Field> Model::GetField()
{
    return field_;
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

