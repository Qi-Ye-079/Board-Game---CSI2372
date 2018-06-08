#pragma once
#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <array>
#include <random>
#include <algorithm>
#include <chrono>
#include "deck.h"
#include "gemstones.h"

class CardFactory {
private:
	CardFactory();

	/**
	 *  Make copy constructor and assignment operator private to prevent being copied
	 */ 
	CardFactory(const CardFactory&);
	CardFactory& operator=(const CardFactory&);

	/**
	*  Responsible for the deletion of all cards.
	*/
	~CardFactory();

	/**
	 *  An array indicating if a certain card in the deck is returned once by getCard() function. 
	 *  Used to ensure that each card generated will be returned ONLY ONCE by the function
	 *  getCard() when loading a saved game.
	 */
	std::array<bool, 104> cardReturned;

	/**
	 *  A deck to store the generated 104 cards. 
	 */
	Deck deck;
public:
	/**
	 *  Return a shuffled deck.
	 */
	Deck getDeck();

	/**
	 *  Return an instance of cardFactory.
	 *  It also ensures only 1 instance of cardfactory can be instantiated.
	 */
	static CardFactory* getCardFactory();

	//================ Self-added function =====================
	/**
	 *  The public function that creates gemstone cards, whose type
	 *  is specified by the argument. 
	 *  This function is the ONLY entry in this program(except CardFactory itself) to produce cards.
	 */
	Card* getCard(const char&);
};

#endif