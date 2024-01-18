#include "Pack.h"
#include <algorithm>
#include <stdexcept>

Pack::Pack()
{
    // Create cards in ascending order of rank and suit
    int cardIndex = 0;
    for (int suit = 0; suit <= static_cast<int>(Suit::SPADES) ; ++suit)
    {
        for (int rank = 0; rank <= static_cast<int>(Rank::ACE); ++rank)
        {
            cards[cardIndex++] = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));
        }
    }

    // Reset the index
    reset();
}

Pack::Pack(std::istream& pack_input)
{
    // Read cards from the input stream
    for (int i = 0; i < PACK_SIZE; ++i)
    {
        Card card;
        if (!(pack_input >> card))
        {
            throw std::runtime_error("Failed to read cards from the input stream.");
        }
        cards[i] = card;
    }

    // Reset the index
    reset();
}

Card Pack::deal_one()
{
    if (empty())
    {
        throw std::range_error("No more cards in the pack to deal.");
    }

    Card card = cards[next];
    ++next;
    return card;
}


void Pack::reset()
{
    next = 0;
}

void Pack::shuffle()
{
    for (int i = 0; i < 15; i++)
    {
        int mid = PACK_SIZE / 2;
        int index1 = 0;
        int index2 = mid;

        std::array<Card, PACK_SIZE>temp;
        for(int index3 = 0; index3 < PACK_SIZE;)
        while (index2 < PACK_SIZE)
        {
            temp[index3] = cards[index2];
            temp[index3 + 1] = cards[index1];
            index1++;
            index2++;
            index3 +=2;
        }
        cards = temp;
    }

    reset();
}


bool Pack::empty() const
{
    return next >= PACK_SIZE;
}
