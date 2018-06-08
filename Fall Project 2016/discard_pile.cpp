#include "discard_pile.h"
#include <time.h>

std::ostream& operator<<(std::ostream& os, DiscardPile& _discardPile)
{
	// First check if the vector is empty to avoid vector iterator out-of-bound
	if (!_discardPile.d_discardedCards.empty()) {
		auto cardPtr = _discardPile.d_discardedCards.back();
		// Then check if it's null pointer to avoid null pointer exception
		if (cardPtr != nullptr) {
			os << *cardPtr;
		}
	}
	return os;
}

DiscardPile::DiscardPile(std::istream& is, CardFactory* _cFactory)
{
	std::string line;  std::getline(is, line);
	std::istringstream record(line);
	char ch;
	while (record.get(ch)) {
		if (ch!=' ') 	d_discardedCards.push_back(_cFactory->getCard(ch));
	}
}

DiscardPile& DiscardPile::operator+=(Card* _card)
{
	if (_card != nullptr)	d_discardedCards.push_back(_card);
	return *this;
}

Card* DiscardPile::pickup()
{
	// Check if discard pile is empty
	if (d_discardedCards.empty()) return nullptr;
	else {
		Card* pickedCard = d_discardedCards.back();
		d_discardedCards.pop_back();
		return pickedCard;
	}
}

Card* DiscardPile::top() const
{
	// Check if discard pile is empty
	if (d_discardedCards.empty()) return nullptr;
	else return d_discardedCards.back();
}

void DiscardPile::print(std::ostream& os)
{
	for (auto& c : d_discardedCards) {
		os << c->getName().at(0) << "  ";
	}
}

bool DiscardPile::empty() const
{
	return d_discardedCards.empty();
}

void DiscardPile::shuffle()
{
	std::mt19937 g(time(0));
	std::shuffle(d_discardedCards.begin(), d_discardedCards.end(), g);
}
