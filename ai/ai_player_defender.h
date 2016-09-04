#ifndef AIPLAYERDEFENDER_H
#define AIPLAYERDEFENDER_H

#include "ai_player_random.h"

namespace ai {

/**
 * @brief The AIPlayerDefender class
 * Create an AI-player with a middle defensive strategy. At first AI analyses field for his own victory.
 * If there are no turns to have a victory by the one turn, AI analyzes field for opponent victory by one turn.
 * If opponent does not have a victory turns, AI makes random turn
 */
class AIPlayerDefender : public AIPlayerRandom
{
public:
    AIPlayerDefender(model::Model::ePlayer playerType);
    ~AIPlayerDefender();
    void CalculateTurn(unsigned int *x, unsigned int *y) const override;
protected:
    bool FindLastCell2Win(model::Cell::eState state, unsigned int *x, unsigned int *y) const;
    bool FindLastCell2Win(const model::Field &fiedl, model::Cell::eState state, unsigned int *x, unsigned int *y) const;
};

} //namespace ai
#endif // AIPLAYERDEFENDER_H
