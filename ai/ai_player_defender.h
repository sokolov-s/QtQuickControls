#ifndef AIPLAYERDEFENDER_H
#define AIPLAYERDEFENDER_H

#include "ai_player_random.h"

namespace ai {

class AIPlayerDefender : public AIPlayerRandom
{
public:
    AIPlayerDefender();
    ~AIPlayerDefender();
    void CalculateTurn(unsigned int *x, unsigned int *y) const override;
private:
    bool FindLastCell2Win(model::Cell::eState state, unsigned int *x, unsigned int *y) const;
};

} //namespace ai
#endif // AIPLAYERDEFENDER_H
