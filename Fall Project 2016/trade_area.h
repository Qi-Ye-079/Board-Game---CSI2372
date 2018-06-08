#pragma once
#ifndef TRADE_AREA_H
#define TRADE_AREA_H

#include <list>
#include "cardfactory.h"

class TradeArea {
	std::list<Card*> d_tradeCards;
public:
	TradeArea() = default;

	TradeArea(std::istream&, CardFactory*);

	/**
	*  Adds a card to the trade area without checking if it's legal
	*/
	TradeArea& operator+=(Card*);

	/**
	*  Returns true if a card is legal to place in the trade area,
	*  e.g. a card of gemstone already exists in the trade area
	*  Will return false in case of nullptr.
	*/
	bool legal(Card*);

	/**
	*  Removes a gemstone card with the name provided in the argument from the trade area.
	*  Returns a nullptr if no such card exist.
	*/
	Card* trade(std::string);

	/**
	* Returns the number of cards currently in the trade area
	*/
	int numCards() const;

	/**
	* Inserts all cards to the object of std::ostream
	*/
	friend std::ostream& operator<<(std::ostream&, TradeArea&);

	//======== Below are self-added functions=======
	/**
	*  Get the cards in the trade area
	*/
	std::list<Card*>& getTradeCards();
};
#endif // !_TRADE_AREA_H_
