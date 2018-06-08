#pragma once
#ifndef CHAIN_H
#define CHAIN_H

#include <vector>
#include "cardfactory.h"

/**
 *  An common base class for any type of Chain
 */
class Chain_Base {
protected:
	/**
	*  For printing the contents of any subclass Chain<T> in the friend function.
	*/
	virtual void printChain(std::ostream& os) const { os << "(empty chain)"; }
public:
	Chain_Base() = default;
	virtual ~Chain_Base() = default;

	/**
	 *  For Chain_Base: do nothing; simply provides an entry to derived classes.
	 */
	virtual Chain_Base& operator+=(Card*) { return *this; }

	/**
	 *  A Chain_Base is always of no value.
	 */
	virtual int sell() { return 0; }

	/**
	 *  A Chain_Base class is always empty
	 */
	virtual bool empty() const { return true; }

	/**
	 *  Discard top card of this chain
	 */
	virtual Card* discard() { return nullptr; }

	/**
	 *  For Chain_Base class: simply prints "-".
	 */
	friend std::ostream& operator<<(std::ostream& os, const Chain_Base& _cBase) {
		_cBase.printChain(os);
		return os;
	}
};

template<typename T>
class Chain: public Chain_Base {
	/**
	*  The vector that holds all the cards in this chain
	*/
	std::vector<T*> d_cardsChain;
protected:
	/**
	*  Print all the cards of this chain, starting with full name of cards.
	*  Only when type is card will it print; only used in insertion operator.
	*/
	virtual void printChain(std::ostream& os) const override;
public:
	Chain() = default;
	Chain(std::istream&, CardFactory*);

	/**
	*  Adds a card to the chain.
	*  Exception:
	*      IllegalType - if the Type of Card doesn't match the template type
	*/
	Chain_Base& operator+=(Card*) override;

	/**
	*  Counts the number of cards in the chain and return the number of coins
	*  according to the function Card::getCardsPerCoin()
	*/
	int sell() override;

	/**
	*  Print the chain
	*/
    friend std::ostream& operator<<(std::ostream& os, Chain<T>& chain)
	{
		chain.printChain(os);
		return os;
	}

	//======= Below are self-added functions ========
	/**
	*  Check if the chain is empty.
	*/
	bool empty() const override { return d_cardsChain.empty(); }

	/**
	*  Discard the top card of this chain when this chain is sold.
	*  No empty checking. Empty checking will be performed by the caller.
	*  Used in a loop to discard all cards of this chain.
	*/
	Card* discard() override;
};

template<typename T>
void Chain<T>::printChain(std::ostream& os) const
{
	Card* frontCard = dynamic_cast<Card*>(d_cardsChain.front());
	os << frontCard->getName() << "   ";
	for (auto c : d_cardsChain) {
		c->print(os);
	}
}

template<typename T>
Chain<T>::Chain(std::istream& is, CardFactory* _cFactory)
{
	std::string line;   std::getline(is, line);  // Get this line and move indicator to next line
	std::istringstream chainLine(line);
	char ch;
	while (chainLine.get(ch)) {
		T* card = dynamic_cast<T*>(_cFactory->getCard(ch));
		if (card && ch != ' ')  d_cardsChain.push_back(card);
	}
}

template<typename T>
Chain_Base& Chain<T>::operator+=(Card* _card)
{
	T* gemCard = dynamic_cast<T*>(_card);
	if (gemCard) d_cardsChain.push_back(gemCard);
    else throw IllegalType();
	return *this;
}

template<typename T>
int Chain<T>::sell()
{
	int noCards = d_cardsChain.size();

	// If chain is empty, simply return 0 
	if (!noCards) return 0;
	else {
		int coins;
		if (d_cardsChain.front()->getName() == "Emerald") coins = 2;
		else coins = 1;

		Card* gemCard = dynamic_cast<Card*>(d_cardsChain.front());
		if (gemCard) {
			if (noCards < gemCard->getCardsPerCoin(coins)) return 0;
			while (noCards > gemCard->getCardsPerCoin(coins)) {
				if (noCards >= gemCard->getCardsPerCoin(coins + 1)) ++coins;
				else break;
			}
		}
		return coins;
	}
}

template<typename T>
Card* Chain<T>::discard()
{
	Card* retCard = d_cardsChain.back();
	d_cardsChain.pop_back();
	return retCard;
}

#endif