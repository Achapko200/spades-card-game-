#include "Card.h"
#include <string>
#include <stdexcept>
#include <sstream>

Rank string_to_rank(const std::string& str)
{
    if (str == "Two")
        return Rank::TWO;
    else if (str == "Three")
        return Rank::THREE;
    else if (str == "Four")
        return Rank::FOUR;
    else if (str == "Five")
        return Rank::FIVE;
    else if (str == "Six")
        return Rank::SIX;
    else if (str == "Seven")
        return Rank::SEVEN;
    else if (str == "Eight")
        return Rank::EIGHT;
    else if (str == "Nine")
        return Rank::NINE;
    else if (str == "Ten")
        return Rank::TEN;
    else if (str == "Jack")
        return Rank::JACK;
    else if (str == "Queen")
        return Rank::QUEEN;
    else if (str == "King")
        return Rank::KING;
    else if (str == "Ace")
        return Rank::ACE;
    else
        throw std::invalid_argument("Invalid value for string_to_rank function.");
}

std::ostream& operator<<(std::ostream& os, Rank rank)
{
    switch (rank)
    {
        case Rank::TWO:
            os << "Two";
            break;
        case Rank::THREE:
            os << "Three";
            break;
        case Rank::FOUR:
            os << "Four";
            break;
        case Rank::FIVE:
            os << "Five";
            break;
        case Rank::SIX:
            os << "Six";
            break;
        case Rank::SEVEN:
            os << "Seven";
            break;
        case Rank::EIGHT:
            os << "Eight";
            break;
        case Rank::NINE:
            os << "Nine";
            break;
        case Rank::TEN:
            os << "Ten";
            break;
        case Rank::JACK:
            os << "Jack";
            break;
        case Rank::QUEEN:
            os << "Queen";
            break;
        case Rank::KING:
            os << "King";
            break;
        case Rank::ACE:
            os << "Ace";
            break;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Rank& rank)
{
    std::string input;
    is >> input;

    rank = string_to_rank(input);

    return is;
}

Suit string_to_suit(const std::string& str)
{
    if (str == "Spades")
        return Suit::SPADES;
    else if (str == "Hearts")
        return Suit::HEARTS;
    else if (str == "Clubs")
        return Suit::CLUBS;
    else if (str == "Diamonds")
        return Suit::DIAMONDS;
    else
        throw std::invalid_argument("Invalid value for string_to_suit function.");
}

std::ostream& operator<<(std::ostream& os, Suit suit)
{
    switch (suit)
    {
        case Suit::SPADES:
            os << "Spades";
            break;
        case Suit::HEARTS:
            os << "Hearts";
            break;
        case Suit::CLUBS:
            os << "Clubs";
            break;
        case Suit::DIAMONDS:
            os << "Diamonds";
            break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Suit& suit)
{
    std::string input;
    is >> input;

    suit = string_to_suit(input);

    return is;
}

Card::Card()
{
    rank = Rank::TWO;
    suit = Suit::CLUBS;
}

Card::Card(Rank rank, Suit suit)
{
    this->rank = rank;
    this->suit = suit;
}

Rank Card::get_rank() const
{
    return rank;
}

Suit Card::get_suit() const
{
    return suit;
}

bool Card::is_trump() const
{
    return suit == Suit::SPADES;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

std::istream& operator>>(std::istream& is, Card& card)
{
    std::string rankAndSuitStr;
    std::string rankStr;
    std::string suitStr;
    std::string ignore;

    char c;
    while(is.get(c) && c != '\t' && c != '\n')
    {
        rankAndSuitStr.push_back(c);
    }

    if(rankAndSuitStr.empty())
    {
        throw std::runtime_error("Failed to read card from input");
    }

    std::istringstream iss(rankAndSuitStr);
    iss >> rankStr >> ignore >> suitStr;
    if (rankStr.empty() || suitStr.empty())
    {
        throw std::runtime_error(std::string("failed to read rank or suite from input ") + rankAndSuitStr);
    }

    Rank rank = string_to_rank(rankStr);
    Suit suit = string_to_suit(suitStr);
    card = Card(rank, suit);
    return is;               
}



bool operator<(const Card& lhs, const Card& rhs)
{
    if( lhs.get_suit() < rhs.get_suit())
    {
        return true;
    }
    else if (lhs.get_suit() > rhs.get_suit())
    {
        return false;
    }
    return lhs.get_rank() < rhs.get_rank();
}


bool operator<=(const Card& lhs, const Card& rhs)
{
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Card& lhs, const Card& rhs)
{
    return rhs < lhs;
}

bool operator>=(const Card& lhs, const Card& rhs)
{
    return (lhs> rhs)|| (lhs==rhs);
}

bool operator==(const Card& lhs, const Card& rhs)
{
    return (lhs.get_rank() == rhs.get_rank()) && (lhs.get_suit() == rhs.get_suit());
}

bool operator!=(const Card& lhs, const Card& rhs)
{
    return !(lhs == rhs);
}

bool Card_less(const Card& a, const Card& b, Suit lead)
{
    if (a.get_suit() == Suit::SPADES)
    {
        if (b.get_suit()== Suit::SPADES)
        {
            return a < b;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (b.get_suit() == Suit::SPADES)
        {
            return true;
        }
    }

    if (a.get_suit() == lead)
    {
        if(b.get_suit() == lead)
        {
            return a < b;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (b.get_suit() == lead)
        {
            return true;
        }
        else
        {
            return a < b; // should never happen...
        }
    }
}