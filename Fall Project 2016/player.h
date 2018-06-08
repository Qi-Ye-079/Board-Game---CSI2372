#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <array>
#include "hand.h"
#include "chain.h"

class Player {
	/**
	 *  The player's name
	 */
	std::string name;

	/**
	 *  The player's current coins
	 */
	int currentCoins = 0;

	/**
	 *  The player's hand
	 */
	Hand* hand;

	/**
	 *  The players' chains (maximum 3)
	 */
	std::array<Chain_Base*, 3> chains{ { new Chain_Base(), new Chain_Base(), new Chain_Base() } };

	/**
	 *  Indicating if the player has unlocked the 3rd chain
	 */
	bool unlock = false;
public:
	/**
	 *  Constructor to create a player with name, and giving 3 empty chains to begin with.
	 */
	Player(const std::string _name) : name(_name) {
		hand = new Hand();
	}

	/**
	 *  Constructor that takes an input stream and pointer to card factory as arguments.
	 *  Used for reconstruct the player when loading a saved game.
	 */
	Player(std::istream&, CardFactory*);

	/**
	 *  Responsible for deleting dynamically allocated chains
	 */
	~Player();

	/**
	 *  Get the player's name
	 */
	std::string getName() const;

	/**
	 *  Get the player's current number of coins
	 */
	int getNumCoins() const;

	/**
	 *  Add a number of coins to the player
	 */
	Player& operator+=(int);

	/**
	 *  Returns the max number of chains for this player.
	 *  Returns either 2 or 3.
	 */
	int getMaxNumChains() const;

	/**
	 *  Return the number of non-zero chains
	 */
	int getNumChains() const;

	/**
	 *  Returns the reference to the chain at position i.
	 *  May throw EmptyChain exception if the specified chain is empty,
	 *      because when a chain is empty(nullptr), no reference can be returned.
	 */
	Chain_Base& operator[](int i);

	/**
	 *  Adds a third chain to the player for 3 coins.
	 *  If the player has less than 3 coins, throw NotEnoughCoins
	 */
	void buyThirdChain();

	/**
	 *  Prints the top card of player's hand(false), or
	 *  prints all the cards of player's hand(true)
	 */
	void printHand(std::ostream&, bool);

	/**
	*  Print the player's name, number of coins and chains are printed
	*/
	friend std::ostream& operator<<(std::ostream&, Player&);

	//========= Belows are self-added functions============
	/**
	*  Start a new chain at the given position i, whose type is provided by a char in argument
	*/
	void startNewChain(int, const char&);

	/**
	 *  Returns a pointer to the hand of the player.
	 */
	Hand* getHand();
};

/**
 *  Exception: thrown when the player doesn't have enough coin to buy 
 *             the third chain
 */
class NotEnoughCoins : private std::exception {
public:
	std::string showMessage();
};

#endif