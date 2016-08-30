#include "ai_player_defender.h"
#include "wincheck.h"

using namespace ai;

AIPlayerDefender::AIPlayerDefender(model::Model::ePlayer playerType)
    : AIPlayerRandom(playerType)
{

}

AIPlayerDefender::~AIPlayerDefender()
{

}

void ai::AIPlayerDefender::CalculateTurn(unsigned int *x, unsigned int *y) const
{
    try {
        if(FindLastCell2Win(GetPlayerCellsType(), x, y)) return;
        if(FindLastCell2Win(GetOpponentCellsType(), x, y)) return;
        AIPlayerRandom::CalculateTurn(x, y);
    } catch (const std::invalid_argument &) {
        // Generate throw in main thread
        *x = *y = GetField()->GetSize();
    }
}

bool AIPlayerDefender::FindLastCell2Win(model::Cell::eState state, unsigned int *x, unsigned int *y) const
{
    size_t fieldSize = GetField()->GetSize();
    try {
        if(CheckDiagonal(*GetField(), state, model::Cell::Position(0, 0),
                         GetWinSize(), eTrend::kX2PositiveY2Positive) == 1) {
            for(size_t j = 0; j < fieldSize; ++j) {
                if(GetField()->GetCellState(j, j) == model::Cell::eState::kEmpty) {
                    *x = j;
                    *y = j;
                    return true;
                }
            }
        }
        if(CheckDiagonal(*GetField(), state, model::Cell::Position(fieldSize - 1, 0), GetWinSize(),
                         eTrend::kX2NegativeY2Positive) == 1) {
            for(size_t j = 1; j <= fieldSize; ++j) {
                if(GetField()->GetCellState(j - 1, fieldSize - j) == model::Cell::eState::kEmpty) {
                    *x = j - 1;
                    *y = fieldSize - j;
                    return true;
                }
            }
        }
        for(size_t i = 0; i < fieldSize; ++ i) {
            if(IsInterrupted()) return false;
            if(CheckVertical(*GetField(), state, model::Cell::Position(i, 0), GetWinSize()) == 1) {
                for(size_t j = 0; j < fieldSize; ++j) {
                    if(GetField()->GetCellState(i, j) == model::Cell::eState::kEmpty) {
                        *x = i;
                        *y = j;
                        return true;
                    }
                }
            }
            if(CheckHorizontal(*GetField(), state, model::Cell::Position(0, i), GetWinSize()) == 1) {
                for(size_t j = 0; j < fieldSize; ++j) {
                    if(GetField()->GetCellState(j, i) == model::Cell::eState::kEmpty) {
                        *x = j;
                        *y = i;
                        return true;
                    }
                }
            }
        }
    } catch (const std::invalid_argument &) {
        throw;
    }

    return false;
}
