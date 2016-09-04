#ifndef AIPLAYERAGGRESSIVE_H
#define AIPLAYERAGGRESSIVE_H

#include "ai_player_defender.h"

namespace ai {

/**
 * @brief The AIPlayerAggressive class
 * Create an AI-player with a perfect strategy. At first AI analyses field for his own victory.
 * If there are no turns to have a victory by the one turn, AI analyzes field for opponent victory by one turn.
 * If opponent does not have a victory turns, AI try to find a cell wich make a "fork" from both side.
 * If AI or opponent do not have a "fork", AI find first cell with next wictory line
 */
class AIPlayerAggressive : public AIPlayerDefender
{
public:
    AIPlayerAggressive(model::Model::ePlayer playerType);
    ~AIPlayerAggressive();
    void CalculateTurn(unsigned int *x, unsigned int *y) const override;
protected:
    bool GetFirstFreeCorner(const model::Field &field, unsigned int *x, unsigned int *y) const;
    bool GetFirstFreeCorner(unsigned int *x, unsigned int *y) const;
    bool FindFork(model::Cell::eState state, unsigned int *x, unsigned int *y) const;
    bool FindFork(const model::Field &field, model::Cell::eState state, unsigned int *x, unsigned int *y) const;
    bool FindDanger(model::Cell::eState state, unsigned int *x, unsigned int *y) const;
    bool FindDanger(const model::Field &field, model::Cell::eState state, unsigned int *x, unsigned int *y) const;
    bool FindDangerCorner(model::Cell::eState state, unsigned int *x, unsigned int *y) const;
    bool CheckCell4Danger(unsigned int cellX, unsigned int cellY, model::Cell::eState state) const;
};

} //namespace ai
#endif // AIPLAYERAGGRESSIVE_H
