#ifndef AIPLAYERAGGRESSIVE_H
#define AIPLAYERAGGRESSIVE_H

#include "ai_player_defender.h"

namespace ai {

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
