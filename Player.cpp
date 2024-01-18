#include "Player.h"

#include <iostream>
#include <algorithm>
#include <sstream>

class Human : public Player
{
private:
    std::string name;
    int bid;
    int tricks;
    std::vector<Card> hand;

public:
    Human(const std::string &playerName)
        : name(playerName), bid(0), tricks(0)
    {
    }

    const std::string &get_name() const override
    {
        return name;
    }

    void set_bid() override
    {
        std::ostringstream oss;
        oss << "Does Player " << name << " want to bid blind nil? [y/n]\n";
        std::cout << oss.str();

        std::string response;
        std::cin >> response;

        while (response != "y" && response != "n")
        {
            std::cout << "Please answer using only `y` for yes or `n` for no." << std::endl;
            std::cin >> response;
        }

        if (response == "y")
        {
            bid = -1;
        }
        else
        {
            std::sort(hand.begin(), hand.end()); // Sort the hand in ascending order
            for (int i = 0; i < hand.size(); i++)
            {
                std::cout << "[" << (i + 1) << "] " << hand[i] << std::endl;
            }

            int maxBid = hand.size();
            std::cout << "How much would you like to bid (0 to " << maxBid << " inclusive)?\n";

            int chosenBid;
            std::cin >> chosenBid;

            while (chosenBid < 0 || chosenBid > maxBid)
            {
                std::cout << "Please answer with values from 0 to " << maxBid << " inclusive." << std::endl;
                std::cin >> chosenBid;
            }

            bid = chosenBid;
        }
    }

    int get_bid() const override
    {
        return bid <= 0 ? 0 : bid;
    }

    bool add_trick() override
    {
        if (tricks < MAX_HAND_SIZE)
        {
            tricks++;
            return true;
        }
        return false;
    }

    int get_trick() const override
    {
        return tricks;
    }

    bool nil_bid() const override
    {
        return (bid == 0);
    }

    bool blind_nil_bid() const override
    {
        return (bid == -1);
    }

    bool add_card(const Card &c) override
    {
        if (hand.size() < MAX_HAND_SIZE)
        {
            hand.push_back(c);
            // Sort the hand in ascending order after adding the card
            std::sort(hand.begin(), hand.end());
            return true;
        }
        return false;
    }

    Card lead_card(bool broken_spade) override
    {
        // Step 1: Check if the hand is empty
        if (hand.empty())
        {
            throw std::out_of_range("Player has no more cards to play with.");
        }

        // Step 2: Figure out the playable cards
        std::vector<Card> playable_hand;
        for (const Card &card : hand)
        {
            if (!broken_spade && card.get_suit() != Suit::SPADES)
            {
                playable_hand.push_back(card);
            }
            else if (broken_spade)
            {
                playable_hand.push_back(card);
            }
        }
        if (playable_hand.empty())
            playable_hand = hand;

        // Step 3: Print out the playable cards
        for (int i = 0; i < playable_hand.size(); ++i)
        {
            std::cout << "[" << (i + 1) << "] " << playable_hand[i] << std::endl;
        }

        // Step 4: Ask the user for a valid card choice
        int choice;
        std::cout << "Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n";
        std::cin >> choice;

        while (choice < 1 || choice > playable_hand.size())
        {
            std::cout << "Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n";
            std::cin >> choice;
        }

        // Step 5: Select the card, remove it from the player's hand, and return the card
        Card selectedCard = playable_hand[choice - 1];
        hand.erase(hand.begin() + (choice - 1));
        return selectedCard;
    }

      Card play_card(Suit led_suit) override
    {
        // Step 1: Check if the hand is empty
        if (hand.empty())
        {
            throw std::out_of_range("Player has no more cards to play with.");
        }

        // Step 2: Figure out the playable cards based on the led suit
        std::vector<Card> playable_hand;
        for (const Card &card : hand)
        {
            if (card.get_suit() == led_suit)
            {
                playable_hand.push_back(card);
            }
        }
        if (playable_hand.empty())
        {
            // No cards of the leading suit, so any card can be played
            playable_hand = hand;
        }

        // Step 3: Print out the playable cards
        for (int i = 0; i < playable_hand.size(); ++i)
        {
            std::cout << "[" << (i + 1) << "] " << playable_hand[i] << std::endl;
        }

        // Step 4: Ask the user for a valid card choice
        int choice;
        std::cout << "Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n";
        std::cin >> choice;

        while (choice < 1 || choice > playable_hand.size())
        {
            std::cout << "Please enter a number between 1 and " << playable_hand.size() << " inclusive:\n";
            std::cin >> choice;
        }

        // Step 5: Select the card, remove it from the player's hand, and return the card
        Card selectedCard = playable_hand[choice - 1];
        auto it = std::find(hand.begin(),hand.end(),selectedCard);
        hand.erase(it);
        return selectedCard;
    }



    void reset() override
    {
        bid = 0;
        tricks = 0;
        hand.clear();
    }
};

Player *Player_factory(const std::string &name, const std::string &type)
{
    if (type == "Human")
    {
        return new Human(name);
    }
    // Add more player types as needed
    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << p.get_name();
    return os;
}
