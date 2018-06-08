#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <array>
#include "player.h"
#include "discard_pile.h"
#include "trade_area.h"

class Table {
	/**
	 *  2 players on the table
	 */
	std::array<Player*, 2> players;

	/**
	 *  The deck
	 */
	Deck* d_deck;

	/**
	 *  The discard pile
	 */
	DiscardPile* d_discardPile;

	/**
	 *  The trade Area
	 */
	TradeArea* d_tradeArea;
public:
	/**
	 *  Constructor takes 2 string as arguments, to initialize the 2 players' names.
	 *  Also, this table constructor is responsible for creating a Card Factory (only one can exist).
	 */
	Table(std::string, std::string);
	Table(std::istream&, CardFactory*);
	~Table();

	/**
	 *  Returns true when a player wins. Name of player returned by reference.
	 *  Wining condition: all cards from deck have been picked and the player with most coins wins.
	 */
	bool win(std::string&) const;

	/**
	*  Prints the complete table with all content. Intented for serialization to file
	*/
	void print(std::ostream&);

	/**
	*  Top-level print 2 players' names, discard pile and trading area.
	*  Complete output for the pause and save functionality uses a seperate function - print() above.
	*/
	friend std::ostream& operator<<(std::ostream&, Table&);

	//============ Belows are self-added functions =========================
	/**
	 *  Returns a reference to the 2 players on this table
	 */
	std::array<Player*, 2>& getPlayers();

	/**
	 *  Return a pointer to the deck on this table;
	 */
    Deck* getDeck();

	/**
	 *  Return a pointer to the trade area of the table
	 */
	TradeArea* getTradeArea();

	/**
	*  Return a pointer to the discard pile of the table
	*/
	DiscardPile* getDiscardPile();
};

#endif