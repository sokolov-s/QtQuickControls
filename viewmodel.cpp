#include "viewmodel.h"
#include <QQmlEngine>
#include <QQmlComponent>
#include <random>
#include "model/field.h"
#include"model/model_exeptions.h"
#include "ai/wincheck.h"
#include <functional>

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{
    qmlRegisterType<ViewModel>("com.TicTacToe.ViewModel", 1, 0, "viewmodel");
}

void ViewModel::NewGame(int player, unsigned int fieldSize)
{
    static bool needSwitch = false;
    model_.reset(new model::Model());
    model_->CreateField(fieldSize);
    emit generateFieldInQml(fieldSize);
    model_->SetPlayer(model::Model::ePlayer::kX);
    players_.clear();

    AddPlayer(factory::PlayerFactory::ePlayer::kHuman, model_->GetCurrentPlayer(), fieldSize);
    model_->SwitchPlayer();
    AddPlayer(static_cast<factory::PlayerFactory::ePlayer>(player), model_->GetCurrentPlayer(), fieldSize);

    if(needSwitch) {
        model_->SwitchPlayer();
    }
    needSwitch = !needSwitch;

    emit playerCanged(GetPlayerString(model_->GetCurrentPlayer()));

    gameEnd_ = false;

    MakeTurn();
}

void ViewModel::OnCellClicked(unsigned int x, unsigned int y, bool force)
{
    if (gameEnd_) return;
    if(!(*GetCurrentPlayer())->IsHuman() && !force) return;
    try {
        auto state = model_->GetCellState4Player();
        model_->GetField()->SetCellState(x, y, state);
        emit changeCellState(x, y, GetStateString(state));
        if(ai::IsWin(*model_->GetField(), state, model_->GetField()->GetSize())) {
            gameEnd_ = true;
            emit playerWin(GetPlayerString(model_->GetCurrentPlayer()));
        } else if (model_->IsFieldFull()) {
            gameEnd_ = true;
            emit standoff();
        } else {
            model_->SwitchPlayer();
            emit playerCanged(GetPlayerString(model_->GetCurrentPlayer()));
            MakeTurn();
        }
    } catch (const model::EBadOperation &/*err*/) {
        // in this context we do nothing
    }
}

QString ViewModel::GetStateString(model::Cell::eState state)
{
    switch(state) {
    case model::Cell::eState::kX : return std::move(QString("X"));

    case model::Cell::eState::kO : return std::move(QString("O"));

    case model::Cell::eState::kEmpty :
    default:
        return std::move(QString("empty"));
    }
}

QString ViewModel::GetPlayerString(model::Model::ePlayer player)
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

void ViewModel::AddPlayer(factory::PlayerFactory::ePlayer player, model::Model::ePlayer playerType,
                          unsigned int fieldSize)
{
    players_.emplace_back(factory::PlayerFactory::Instance().CreatePlayer(player, playerType));
    players_.back()->SetWinRowsCount(fieldSize);
    players_.back()->SetField(model_->GetField());
    players_.back()->SetPlayerCellsType(model_->GetCellState4Player(playerType));
    if(players_.size() > 1) {
        auto &prevPlayer = players_.at(players_.size() - 2);
        players_.back()->SetOpponentCellsType(model_->GetCellState4Player(prevPlayer->GetType()));
        prevPlayer->SetOpponentCellsType(model_->GetCellState4Player(playerType));
    }
}

void ViewModel::MakeTurn()
{
    if(!(*GetCurrentPlayer())->IsHuman()) {
        using namespace std::placeholders;
        (*GetCurrentPlayer())->MakeTurn(std::bind(&ViewModel::OnCellClicked, this, _1, _2, true));
    }
}

