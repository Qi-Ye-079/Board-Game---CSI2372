#pragma once
#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include <vector>
#include "cardfactory.h"

class DiscardPile {
private:
	std::vector<Card*> d_discardedCards;
public:
	DiscardPile() = default;
	DiscardPile(std::istream&, CardFactory*);

	/**
	*  Put a Card to the pile when the argument is not nullptr.
	*/
	DiscardPile& operator+=(Card*);

	/**
	*  Returns and removes a card from the top of the pile
	*  Use back() to refer to the top of pile for convinience.
	*  Returns a nullptr if no card exists
	*/
	Card* pickup();

	/**
	*  Returns but not removes a card from the top of pile
	*  Use back() to refer to the top of pile for convinience.
	*  Returns a nullptr if no card exists
	*/
	Card* top() const;

	/**
	*  Inserts all the cards in the pile to the ostream
	*/
	void print(std::ostream&);

	/**
	*  Insert only the top card of the pile to the std::ostream
	*/
	friend std::ostream& operator<<(std::ostream&, DiscardPile&);

	// ===================== Belows are self-added functions ===================
	/**
	*  Check if the discard pile is empty
	*/
	bool empty() const;

	/**
	 *  Shuffle the discard pile each time a player sells a chain. 
	 */
	void shuffle();
};

#endif