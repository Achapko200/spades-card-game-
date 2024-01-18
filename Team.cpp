#include "Team.h"

Team::Team(const PlayerComponents &player1, const PlayerComponents &player2)
{
    // Create player instances and add them to the team vector
    team.push_back(Player_factory(player1.name, player1.strategy));
    team.push_back(Player_factory(player2.name, player2.strategy));

    total_bags = 0;
    game_score = 0;
}

std::string Team::get_name(int player) const
{
    if (valid_player(player))
    {
        return team[player]->get_name();
    }
    throw std::out_of_range("Invalid player index");
}

void Team::set_bid(int player)
{
    if (valid_player(player))
    {
        team[player]->set_bid();
        return;
    }
    throw std::out_of_range("Invalid player index");
}

bool Team::add_trick(int player)
{
    if (valid_player(player))
    {
        return team[player]->add_trick();
    }
    throw std::out_of_range("Invalid player index");
}

bool Team::add_card(int player, const Card &card)
{
    if (valid_player(player))
    {
        return team[player]->add_card(card);
    }
    throw std::out_of_range("Invalid player index");
}

Card Team::lead_card(int player, bool broken_spade)
{
    if (valid_player(player))
    {
        return team[player]->lead_card(broken_spade);
    }
    throw std::out_of_range("Invalid player index");
}

Card Team::play_card(int player, Suit led_suit)
{
    if (valid_player(player))
    {
        return team[player]->play_card(led_suit);
    }
    throw std::out_of_range("Invalid player index");
}

void Team::reset()
{
    team[0]->reset();
    team[1]->reset();
    //total_bags = 0;
    //game_score = 0;
}

Score Team::get_score()
{
    Score score;
    int possible_bags = 0;
    int non_nil_tricks = 0;
    score.tricks = team[0]->get_trick() + team[1]->get_trick();
    score.nil_score = calculate_nil_score(score.tricks, non_nil_tricks, score.bid, possible_bags);
    score.bid_score = calculate_bid_score(non_nil_tricks, score.bid, score.bags, possible_bags);
    score.total_bags = update_total_bags(score.bags, score.bag_penalty);
    score.hand_score = calculate_hand_score(score.bid_score, score.nil_score, score.bag_penalty);
    score.game_score = update_game_score(score.hand_score);

    return score;
}

Team::~Team()
{
    for (Player *player : team)
    {
        delete player;
    }
}

std::ostream &operator<<(std::ostream &os, const Team &team)
{
    os << "Team ";

    std::string sep = "";
    for (int i = 0; i < team.team.size(); ++i)
    {
        os << sep << team.get_name(i);
        sep = "/";
    }

    return os;
}

bool Team::valid_player(int player) const
{
    return (player >= 0 && player < 2);
}

int Team::calculate_nil_score(int &tricks, int &non_nil_tricks, int &bid, int &possible_bags)
{
    int nil_score = 0;
    if (team[0]->blind_nil_bid())
    {
        if (team[0]->get_trick() > 0)
        {
            nil_score -= 200;
            possible_bags += team[0]->get_trick();
        }
        else if (team[0]->get_trick() == 0)
        {
            nil_score += 200;
        }
    }
    else if (team[0]->nil_bid())
    {
        if (team[0]->get_trick() > 0)
        {
            nil_score -= 100;
            possible_bags += team[0]->get_trick();
        }
        else if (team[0]->get_trick() == 0)
        {
            nil_score += 100;
        }
    }
    else
    {
        non_nil_tricks += team[0]->get_trick();
        bid += team[0]->get_bid();
    }

    if (team[1]->blind_nil_bid())
    {
        if (team[1]->get_trick() > 0)
        {
            nil_score -= 200;
            possible_bags += team[1]->get_trick();
        }
        else if (team[1]->get_trick() == 0)
        {
            nil_score += 200;
        }
    }
    else if (team[1]->nil_bid())
    {
        if (team[1]->get_trick() > 0)
        {
            nil_score -= 100;
            possible_bags += team[1]->get_trick();
        }
        else if (team[1]->get_trick() == 0)
        {
            nil_score += 100;
        }
    }
    else
    {
        non_nil_tricks += team[1]->get_trick();
        bid += team[1]->get_bid();
    }

    return nil_score;
}

int Team::calculate_bid_score(int non_nil_tricks, int bid, int &bags, int possible_bags)
{
    if (non_nil_tricks > 0 && non_nil_tricks >= bid)
    {
        bags += (possible_bags + non_nil_tricks - bid);
        return bid * 10 + bags;
    }
    return bid * -10;
}

int Team::update_total_bags(int bags, int &bag_penalty)
{
    total_bags += bags;
    bag_penalty = total_bags / 10 * -100;
    return total_bags % 10;
}

int Team::calculate_hand_score(int bid_score, int nil_score, int bag_penalty)
{
    return bid_score + nil_score + bag_penalty;
}

int Team::update_game_score(int hand_score)
{
    game_score += hand_score;
    return game_score;
}

std::ostream &operator<<(std::ostream &os, const Score &score)
{
    os << "Bid: " << score.bid << "\n";
    os << "Tricks: " << score.tricks << "\n";
    os << "Bags: " << score.bags << "\n";
    os << "Bid Score: " << score.bid_score << "\n";
    os << "Nil Score: " << score.nil_score << "\n";
    os << "Bag Penalty: " << score.bag_penalty << "\n";
    os << "Hand Score: " << score.hand_score << "\n";
    os << "Total Bags: " << score.total_bags << "\n";
    os << "Game Score: " << score.game_score << "\n";

    return os;
}
