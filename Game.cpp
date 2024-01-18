#include "Game.h"

Game::Game(PlayerComponents player0, PlayerComponents player1,
	PlayerComponents player2, PlayerComponents player3, Pack pack)
{
	teams.push_back(Team(player0, player2));
	teams.push_back(Team(player1, player3));
	this->pack = pack;
	dealer = 0;
}

void Game::run()
{
	deal();
	bid();
	play();
	score();
}

void Game::deal()
{
	pack.shuffle();
	int player = dealer;
	for (int i = 0; i < 52; ++i)
	{
		teams[get_team(player)].add_card(get_pos_in_team(player), pack.deal_one());
		player = next_player(player);
	}
}

void Game::bid()
{
	int startPlayer = next_player(dealer);

	for (int i = 0; i < 4; ++i)
	{
		int currentPlayer = next_player(startPlayer);
		teams[get_team(currentPlayer)].set_bid(get_pos_in_team(currentPlayer));
		startPlayer = currentPlayer;
	}
}

void Game::play()
{
	int startPlayer = next_player(dealer);

	for (int i = 0; i < 52; ++i)
	{
		int currentPlayer = next_player(startPlayer);
		Card leadCard = teams[get_team(currentPlayer)].lead_card(get_pos_in_team(currentPlayer), false);
		Suit ledSuit = leadCard.get_suit();
		Card winningCard = leadCard;
		int winningPlayer = currentPlayer;

		for (int j = 0; j < 3; ++j)
		{
			currentPlayer = next_player(currentPlayer);
			Card playedCard = teams[get_team(currentPlayer)].play_card(get_pos_in_team(currentPlayer), ledSuit);

			if (playedCard > winningCard)
			{
				winningCard = playedCard;
				winningPlayer = currentPlayer;
			}
		}

		for (int j = 0; j < 4; ++j)
		{
			if (j == winningPlayer)
			{
				teams[get_team(j)].add_trick(get_pos_in_team(j));
			}
		}

		startPlayer = winningPlayer;
	}
}

bool Game::score()
{
	Score scoreTeam1 = teams[0].get_score();
	Score scoreTeam2 = teams[1].get_score();

	std::cout << "Team 1 Score:\n" << scoreTeam1;
	std::cout << "Team 2 Score:\n" << scoreTeam2;

	if (scoreTeam1.game_score >= WINNING_POINTS && scoreTeam2.game_score >= WINNING_POINTS)
	{
		std::cout << "The game is a draw!\n";
		return true;
	}
	else if (scoreTeam1.game_score >= WINNING_POINTS)
	{
		std::cout << "Team 1 wins the game!\n";
		return true;
	}
	else if (scoreTeam2.game_score >= WINNING_POINTS)
	{
		std::cout << "Team 2 wins the game!\n";
		return true;
	}

	if (scoreTeam1.game_score <= LOSING_POINTS && scoreTeam2.game_score <= LOSING_POINTS)
	{
		std::cout << "The game is a draw!\n";
		return true;
	}
	else if (scoreTeam1.game_score <= LOSING_POINTS)
	{
		std::cout << "Team 2 wins the game!\n";
		return true;
	}
	else if (scoreTeam2.game_score <= LOSING_POINTS)
	{
		std::cout << "Team 1 wins thegame!\n";
		return true;
	}

	return false;
}

int Game::next_player(int player) const
{
	return (player + 1) % 4;
}

int Game::get_team(int player) const
{
	return player % 2;
}

int Game::get_pos_in_team(int player) const
{
	return player / 2;
}
