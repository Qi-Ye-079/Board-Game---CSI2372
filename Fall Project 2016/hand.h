#pragma once
#ifndef HAND_H
#define HAND_H

#include <vector>
#include <list>
#include <queue>
#include <memory>
#include <exception>
#include "cardfactory.h"

class Hand {
	std::queue<Card*> d_cardsOnHand;
public:
	Hand() = default;	
	Hand(std::istream&, CardFactory*);

	/**
	 *  Adds a card to the rear of the hand if it's not nullptr
	 */
	Hand& operator+=(Card*);

	/**
	 *  Returns and removes the top card from this player's hand
	 *  If empty, returns a nullptr
	 */
	Card* play();

	/**
	 *  Returns but not removes the top card from the player's hand
	 *  If empty, returns a nullptr
	 */
	Card* top() const;

	/**
	 *  Returns and removes the card at the given index from player's hand
	 *  May throw IndexOutOfBound exception
	 */
	Card* operator[](int);

	/**
	 *  Prints all cards on Hand in order
	 */
	friend std::ostream& operator<<(std::ostream&, Hand&);
};

/**
 *  A self-added exception class: thrown when an index
 *  to access a card is out of range(bound checking exception)
 */
class IndexOutOfBounds : private std::exception {
public:
	std::string showMessage();
};

#endif