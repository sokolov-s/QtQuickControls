#include "viewmodel.h"
#include <QQmlEngine>
#include <QQmlComponent>
#include <random>
#include "model/field.h"
#include"model/model_exeptions.h"
#include "ai/wincheck.h"
#include "player_factory.h"
#include <functional>

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{
    qmlRegisterType<ViewModel>("com.TicTacToe.ViewModel", 1, 0, "viewmodel");
}

void ViewModel::NewGame(int player, unsigned int filedSize)
{
    model_.reset(new model::Model());
    model_->CreateField(filedSize);
    emit generateFieldInQml(filedSize);
    model_->SetPlayer(model::Model::ePlayer::kX);
    emit playerCanged(GetPlayerString(model_->GetCurrentPlayer()));
    players_.clear();
    players_.emplace_back(factory::PlayerFactory::Instance().CreatePlayer(factory::PlayerFactory::ePlayer::kHuman));
    players_.emplace_back(factory::PlayerFactory::Instance().CreatePlayer(static_cast<factory::PlayerFactory::ePlayer>(player)));
    gameEnd_ = false;
}

void ViewModel::OnCellClicked(unsigned int x, unsigned int y, bool force)
{
    if (gameEnd_) return;
    if(!(*GetCurrentPlayer())->IsHuman() && !force) return;
    try {
        auto state = (model_->GetCurrentPlayer() == model::Model::ePlayer::kO) ? model::Cell::eState::kO : model::Cell::eState::kX;
        model_->GetField()->SetCellState(x, y, state);
        emit changeCellState(x, y, GetStateString(state));
        if(ai::IsWin(*model_->GetField(), model_->GetState4Player(model_->GetCurrentPlayer()), model_->GetField()->GetSize())) {
            gameEnd_ = true;
            emit playerWin(GetPlayerString(model_->GetCurrentPlayer()));
        } else if (model_->IsFieldFull()) {
            gameEnd_ = true;
            emit standoff();
        } else {
            model_->SwitchPlayer();
            emit playerCanged(GetPlayerString(model_->GetCurrentPlayer()));
            if(!(*GetCurrentPlayer())->IsHuman()) {
                using namespace std::placeholders;
                (*GetCurrentPlayer())->MakeTurn(std::bind(&ViewModel::OnCellClicked, this, _1, _2, true));
            }
        }
    } catch (const model::EBadOperation &/*err*/) {
        // in this context we do nothing
    }
}

QString ViewModel::GetStateString(const model::Cell::eState state)
{
    switch(state) {
    case model::Cell::eState::kX : return std::move(QString("X"));

    case model::Cell::eState::kO : return std::move(QString("O"));

    case model::Cell::eState::kEmpty :
    default:
        return std::move(QString("empty"));
    }
}

QString ViewModel::GetPlayerString(const model::Model::ePlayer player)
{
    switch(player) {
    case model::Model::ePlayer::kX : return std::move(QString("Player 1"));
    case model::Model::ePlayer::kO : return std::move(QString("Player 2"));
    default: return std::move(QString("Player Unknown"));
    }
}

std::vector<ViewModel::Player>::iterator ViewModel::GetCurrentPlayer()
{
    return players_.begin() + (model_->GetCurrentPlayerNumber() - 1);
}

