#include "deck.h"
#include "cardfactory.h"

Deck::Deck(std::istream& is, CardFactory* _cFactory)
{
	Deck temp;
	std::string line;	std::getline(is, line);
	std::istringstream record(line);
	char ch;
	while (record.get(ch)) {
		if (ch != ' ') 	temp.push_back(_cFactory->getCard(ch));
	}
	new (&(*this)) Deck(temp);  // Re-construct itself using default copy constructor(shallow copy)
}

Card* Deck::draw()
{
	if (empty()) return nullptr;
	else {
		Card* card = back();
		pop_back();
		return card;
	}
}

std::ostream& operator<<(std::ostream& os, Deck& _deck)
{
	for (auto& c : _deck) {
		os << *c;
	}
	return os;
}