Overview

The projects in this class will have you work your way up to create a game of Spades. Spades is a simple trick-taking card game. A trick-taking card game is one where whoever plays the highest card, however it is defined, during the "trick" wins the "trick." With Spades, there are four players who play in teams of two. The objective of the game is to have your team win 300 points or have the opposing team lose with -200 points. Points earned or lost are determined by how many tricks the team wins in comparison to how many tricks they predicted they would take during the game session (aka, their bid)
If reading the rules don't help you to understand the game, then play a few games to get a feel for it. Our rules are mostly the same as the rules on this website.
Rules

Players

Four players
Fixed partnerships of two. Partners sit opposite to each other. Deal and play is clockwise.
Example: A list of players is [P0, P1, P2, P3]. Game play is clockwise so it always moves to the right in the array, which in the perspective of a player, it is to their left. P0 and P2 are on Team0 and P1 and P3 are on Team1.
Cards

52 cards
Spades is trump, meaning it has a higher value than a card of another suit regardless of rank.
Rank from highest to lowest: Ace, King, Queen, Jack, 10, 9 ,8 , 7, 6, 5, 4, 3, 2
Suit from highest to lowest: Spades, Hearts, Diamonds, Clubs
Deal

First dealer chosen at random and turn to deal is clockwise.
Cards are shuffled.
Cards dealt singly in clockwise order from starting from player to the left of the dealer.
Example: If I have the Cards in a Pack like this [A, B, C, D, E, F, G, H] and a list of players [P0, P1, P2, P3] with P0 as the dealer, then P1 cards are A, E, P2 cards are [B, F], P3 cards are [C, G] and P0 cards are [D, H].
Each player gets 13 cards at the end of the deal.
Bidding

All four players bid the number of tricks they think they'll win during the game's session.
Bidding starts with player to the left of the dealer and continues clockwise.
Everyone must bid a number from 0 to 13 after looking at their cards.
A bid of zero is known as a nil. The team can get special points if it succeeds and a penalty if it fails.
A blind nil is when the player declares a nil bid before looking at their cards. Again, there are special points if successful and penalty if it fails.
The bid for the team is derived from the adding together the two members' bids.
Example: North bids 2 and Souths bids 3, therefore their team has a bid of 5.
Once the bidding stage is done, no player can change their bid.
Play

Player to the left of the dealer starts the first trick.
The leading player cannot start with a Spade until there are no other cards of another suit. This is different from actual Spade rules, but lets go with this for simplicity.
Game play is clockwise.
Each player must follow suit if able. If not, then the player can play any card.
The winner of the trick leads the next trick.
Winning a Trick
A trick containing a spade is won by the highest spade played.
If no spade is played, then the trick is won by the highest card leading suit, meaning the highest card that played the same suit as the leading card.
Scoring

When a team takes at least or more tricks than they bid, then they receive a score equal to 10 times the bid. Any additional tricks are called bags and are worth an extra one point each.
Example: Team One bid 5 tricks and won 5 tricks, therefore their score is current_score + 50.
Example: Team Two bid 6 tricks and won 8 tricks so their score is current_score + 62.
If a team does not fulfill their bid, then they lose 10 points times the number of tricks they bid.
Example: Team One bid 8 tricks but only won 6 tricks, therefore their score is current_score - 80.
Sandbagging rule: Overtricks are known as bags. If a team accumulates ten or more bags, then 100 will be deducted from their score. Any bags beyond ten will be carried over to the next cycle of ten overtricks.
Example: Team One bids 3 tricks and wins 6 tricks. If the number of bags they've accumulated up until that point was 9 bags, then after the trick, they'll have 12 bags, which means they have to add (33 - 100) to their score. Since they have more then ten bags (12 bags) at that point, the extra two bags carry over to the next game, meaning they start off with two bags.
If a bid of nil is successful by a player, then the team receives 100 points in addition to the points won or lost by the partner of the nil bidder.
Example: Player One of Team One successfully bid nil. Player Two of Team One bid three tricks and won four. Therefore, Team One's total score is current_score + 100 + 31.
Example: Player One of Team One successfully bid nil. Player Two of Team One bid five tricks but lost with four tricks. Therefore, Team One's total score is current_score + 100 - 50.
If a bid of nil is not successful, then the team loses 100 points and the tricks earned by the nil bidder counts as bags for the team.
Example: Player One of Team One lost their nil bid by two tricks. Player Two bid three tricks and won four. Therefore, Team One's total score is current_score - 100 + 33.
Example: Player One of Team One lost their nil bid by two tricks. Player Two bid five tricks but lost by four. Therefore, Team One's total score is current_score - 100 - 50.
Blind nil bids are worth double that of a regular nil bid meaning +/- 200 points.
Once the scoring is finished, if a team ends up with at least 300 points or higher, they win the game. If a team ends up with at least -200 points or lower, they lose the game. If neither team meet these criteria, then we deal cards to the players again and start again, keeping track of the score from previous sessions.
Card class

A Card object is represented by two attributes, a Rank and a Suit. The provided starter file Card.h is pretty self explanatory. Only thing I want to specify is that the comparison operators that we are overloading for the Cards should not be considering the trump suit or lead suit. It is only based on standard card values. Comparison of cards is based on suit first then rank. The card_less function on the other hand does consider trump suit and lead suit. Go back to [[#Winning a Trick]] to read on how this should be determined.
Pack class

Once you finish creating the implementation of the Card class, then you can move onto the Pack class. A Pack object represents a pack of cards. There are different operations that you can act on these pack of card and these are declared in the provided starter file Pack.h.

A input stream used to initialize a Pack would have all 52 Cards in any order using the format [rank] of [suit]\n. Below is an example of such an input stream with only the first three lines.

Two of Hearts
Ace of Spades
Jack of Diamonds
Goal of the Project

The Goal for Project 1 is to create the implementation files for Card.h and Pack.h. Please name these files Card.cpp and Pack.cpp respectively. DO NOT MODIFY THE .h FILES. Since you should only be submitting the .cpp files on Gradescope, there is no need to modify the .h files.
