#include "ai_player_aggressive.h"
#include "wincheck.h"

using namespace ai;

AIPlayerAggressive::AIPlayerAggressive(model::Model::ePlayer playerType)
    : AIPlayerDefender(playerType)
{
}

AIPlayerAggressive::~AIPlayerAggressive()
{
}

void AIPlayerAggressive::CalculateTurn(unsigned int *x, unsigned int *y) const
{
    try {
        if(FindLastCell2Win(GetPlayerCellsType(), x, y))
            return;
        if(FindLastCell2Win(GetOpponentCellsType(), x, y))
            return;
        size_t turnNumber = GetField()->GetSize() * GetField()->GetSize() - GetField()->GetEmptyCellsCount();
        if(turnNumber <= 1 &&
                GetField()->GetCell(GetField()->GetSize() / 2, GetField()->GetSize() / 2).GetState() == model::Cell::eState::kEmpty) {
            *x = *y = GetField()->GetSize() / 2;
            return;
        }
        if(turnNumber == 1 && GetField()->GetCell(GetField()->GetSize() / 2, GetField()->GetSize() / 2).GetState() != model::Cell::eState::kEmpty) {
            GetFirstFreeCorner(x, y);
            return;
        }
        if(turnNumber == 2 && GetField()->GetCell(GetField()->GetSize() / 2, GetField()->GetSize() / 2).GetState() == GetPlayerCellsType()) {
            FindDangerCorner(GetPlayerCellsType(), x, y);
            return;
        }
        if(FindFork(GetPlayerCellsType(), x, y))
            return;
        if(FindDanger(GetPlayerCellsType(), x, y)) {
            model::Field tmpField(*GetField());
            tmpField.SetCellState(*x , *y, GetPlayerCellsType());
            size_t winX, winY;
            FindLastCell2Win(tmpField, GetPlayerCellsType(), &winX, &winY);
            size_t opponentX, opponentY;
            if (FindFork(GetOpponentCellsType(), &opponentX, &opponentY)
                    && opponentX == winX && opponentY == winY) {
                *x = opponentX;
                *y = opponentY;
            }
            return;
        }
        if(FindFork(GetOpponentCellsType(), x, y)) {
            return;
        }
        AIPlayerRandom::CalculateTurn(x, y);
    } catch (const std::invalid_argument &) {
        // Generate throw in main thread
        *x = *y = GetField()->GetSize();
    }
}

bool AIPlayerAggressive::GetFirstFreeCorner(const model::Field &field, unsigned int *x, unsigned int *y) const
{
    if(field.GetCell(0, 0).GetState() == model::Cell::eState::kEmpty) {
        *x = *y = 0;
        return true;
    }
    if(field.GetCell(0, field.GetSize() - 1).GetState() == model::Cell::eState::kEmpty) {
        *x = 0;
        *y = field.GetSize() - 1;
        return true;
    }
    if(field.GetCell(field.GetSize() - 1, 0).GetState() == model::Cell::eState::kEmpty) {
        *x = field.GetSize() - 1;
        *y = 0;
        return true;
    }
    if(field.GetCell(field.GetSize() - 1, field.GetSize() - 1).GetState() == model::Cell::eState::kEmpty) {
        *x = *y = field.GetSize() - 1;
        return true;
    }
    return false;
}

bool AIPlayerAggressive::GetFirstFreeCorner(unsigned int *x, unsigned int *y) const
{
    return GetFirstFreeCorner(*GetField(), x, y);
}

bool AIPlayerAggressive::FindFork(model::Cell::eState state, unsigned int *x, unsigned int *y) const
{
    return FindFork(*GetField(), state, x, y);
}

bool AIPlayerAggressive::FindFork(const model::Field &field, model::Cell::eState state, unsigned int *x, unsigned int *y) const
{
    for(size_t i = 0; i < field.GetSize(); ++i) {
        for(size_t j = 0; j < field.GetSize(); ++j) {
            model::Field fieldTmp = field;
            size_t fieldSize = fieldTmp.GetSize();
            if(fieldTmp.GetCell(j, i).GetState() == model::Cell::eState::kEmpty) {
                fieldTmp.GetCellPtr(j, i)->SetState(state);
                size_t winCnt = 0;
                if(CheckDiagonal(fieldTmp, state, model::Cell::Position(0, 0),
                                 GetWinSize(), eTrend::kX2PositiveY2Positive) == 1) {
                    ++winCnt;
                }
                if(CheckDiagonal(fieldTmp, state, model::Cell::Position(fieldSize - 1, 0), GetWinSize(),
                                         eTrend::kX2NegativeY2Positive) == 1) {
                    ++winCnt;
                }
                if(CheckVertical(fieldTmp, state, model::Cell::Position(j, 0), GetWinSize()) == 1) {
                    ++winCnt;
                }
                if(CheckHorizontal(fieldTmp, state, model::Cell::Position(0, i), GetWinSize()) == 1) {
                    ++winCnt;
                }
                if(winCnt >= 2) {
                    *x = j;
                    *y = i;
                    return true;
                }
            }
        }
    }
    return false;
}

bool AIPlayerAggressive::FindDanger(model::Cell::eState state, unsigned int *x, unsigned int *y) const
{
    return FindDanger(*GetField(), state, x, y);
}

bool AIPlayerAggressive::FindDanger(const model::Field &field, model::Cell::eState state, unsigned int *x, unsigned int *y) const
{
    for(size_t i = 0; i < field.GetSize(); ++i) {
        for(size_t j = 0; j < field.GetSize(); ++j) {
            model::Field fieldTmp = field;
            if(fieldTmp.GetCell(j, i).GetState() == model::Cell::eState::kEmpty) {
                fieldTmp.GetCellPtr(j, i)->SetState(state);
                if(FindLastCell2Win(fieldTmp, state, x, y)) {
                    *x = j;
                    *y = i;
                    return true;
                }
            }
        }
    }
    return false;
}

bool AIPlayerAggressive::FindDangerCorner(model::Cell::eState state, unsigned int *x, unsigned int *y) const
{
    if(CheckCell4Danger(0, 0, state)) {
        *x = *y = 0;
        return true;
    }
    if(CheckCell4Danger(0, GetField()->GetSize() - 1, state)) {
        *x = 0;
        *y = GetField()->GetSize() - 1;
        return true;
    }
    if(CheckCell4Danger(GetField()->GetSize() - 1, 0, state)) {
        *x = GetField()->GetSize() - 1;
        *y = 0;
        return true;
    }
    if(CheckCell4Danger(GetField()->GetSize() - 1, GetField()->GetSize() - 1, state)) {
        *x = *y = GetField()->GetSize() - 1;
        return true;
    }
    return false;
}

bool AIPlayerAggressive::CheckCell4Danger(unsigned int cellX, unsigned int cellY, model::Cell::eState state) const
{
    model::Field fieldTmp = *GetField();
    if(fieldTmp.GetCell(cellX, cellY).GetState() != model::Cell::eState::kEmpty)
        return false;
    fieldTmp.GetCellPtr(cellX, cellY)->SetState(state);
    unsigned int x,y;
    if(FindLastCell2Win(fieldTmp, state, &x, &y)) {
        return true;
    }
    return false;
}
