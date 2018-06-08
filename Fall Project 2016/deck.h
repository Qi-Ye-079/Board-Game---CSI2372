#pragma once
#ifndef DECK_H
#define DECK_H

#include <vector>
#include <sstream>
#include <iostream>
#include "gemstones.h"

class Deck : public std::vector<Card*> {
public:
	Deck() = default;

	/**
	*  A constructor that accepts the istream,
	*  and can be reconstructed from file
	*/
	Deck(std::istream&, class CardFactory*);

	/**
	*  Draw a Card from the top of the Deck
	*  Returns a nullptr if deck is empty
	*/
	Card* draw();

	friend std::ostream& operator<<(std::ostream&, Deck&);
};

#endif // ! _DECK_H_
