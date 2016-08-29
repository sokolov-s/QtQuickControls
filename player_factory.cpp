#include "player_factory.h"
#include <stdexcept>
#include "ai/human_player.h"
#include "ai/ai_player_random.h"
#include "ai/ai_player_defender.h"

using namespace factory;

factory::PlayerFactory &factory::PlayerFactory::Instance()
{
    static PlayerFactory factory;
    return factory;
}

PlayerFactory::Player PlayerFactory::CreatePlayer(PlayerFactory::ePlayer player)
{
    switch(player) {
    case ePlayer::kHuman : return std::move(Player(new ai::HumanPlayer));
    case ePlayer::kAiLevel1: return std::move(Player(new ai::AIPlayerRandom));
    case ePlayer::kAiLevel2: return std::move(Player(new ai::AIPlayerDefender));
    default: throw std::invalid_argument("Unknown player type");
    }
}
