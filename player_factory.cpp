#include "player_factory.h"
#include <stdexcept>
#include "ai/human_player.h"
#include "ai/ai_player_random.h"
#include "ai/ai_player_defender.h"
#include "ai/ai_player_aggressive.h"

using namespace factory;

factory::PlayerFactory &factory::PlayerFactory::Instance()
{
    static PlayerFactory factory;
    return factory;
}

PlayerFactory::Player PlayerFactory::CreatePlayer(PlayerFactory::ePlayer player, model::Model::ePlayer playerType)
{
    switch(player) {
    case ePlayer::kHuman : return std::move(Player(new ai::HumanPlayer(playerType)));
    case ePlayer::kAiLevel1: return std::move(Player(new ai::AIPlayerRandom(playerType)));
    case ePlayer::kAiLevel2: return std::move(Player(new ai::AIPlayerDefender(playerType)));
    case ePlayer::kAiLevel3: return std::move(Player(new ai::AIPlayerAggressive(playerType)));
    default: throw std::invalid_argument("Unknown player type");
    }
}
