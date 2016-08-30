#include "ai_player_random.h"
#include <vector>
#include "../model/cell.h"
#include <random>

using namespace ai;

AIPlayerRandom::AIPlayerRandom(model::Model::ePlayer playerType)
    : IPlayer(playerType)
{

}

AIPlayerRandom::~AIPlayerRandom()
{

}

void AIPlayerRandom::CalculateTurn(unsigned int *x, unsigned int *y) const
{
    std::vector<model::Cell> emptyCells;
    for(size_t i = 0; i < GetField()->GetSize(); ++i) {
        for(size_t j = 0; j < GetField()->GetSize(); ++j) {
            if(GetField()->GetCell(j, i).GetState() == model::Cell::eState::kEmpty) {
                emptyCells.push_back(GetField()->GetCell(j, i));
            }
        }
    }
    if (!emptyCells.empty()) {
        std::random_device rd;
        static std::default_random_engine eng(rd());
        std::uniform_int_distribution<size_t> dis(0, emptyCells.size() - 1);
        size_t res = dis(eng);
        *x = emptyCells[res].GetX();
        *y = emptyCells[res].GetY();
    }
}
