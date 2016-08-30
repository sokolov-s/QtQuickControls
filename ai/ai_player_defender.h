#ifndef AIPLAYERDEFENDER_H
#define AIPLAYERDEFENDER_H

#include "ai_player_random.h"

namespace ai {

/**
 * @brief The AIPlayerDefender class
 * Create a bot with small ai. At first bot analyses field for his own victory.
 * If there are no turns to have a victory by the one turn, bot analyzes field for opponent victory by one turn.
 * If opponent does not have a victory turn, bot makes random turn
 */
class AIPlayerDefender : public AIPlayerRandom
{
public:
    AIPlayerDefender(model::Model::ePlayer playerType);
    ~AIPlayerDefender();
    void CalculateTurn(unsigned int *x, unsigned int *y) const override;
private:
    bool FindLastCell2Win(model::Cell::eState state, unsigned int *x, unsigned int *y) const;
};

} //namespace ai
#endif // AIPLAYERDEFENDER_H
