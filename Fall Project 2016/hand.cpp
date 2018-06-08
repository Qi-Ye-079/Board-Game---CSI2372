#include "hand.h"

Hand::Hand(std::istream& is, CardFactory* _cFactory)
{
	std::string line;  std::getline(is, line);  // Get this line
	std::istringstream handLine(line);  handLine >> line;
	char ch;
	while (handLine.get(ch)) {
		if (ch != ' ')  d_cardsOnHand.push(_cFactory->getCard(ch));
	}
}

Hand& Hand::operator+=(Card* _card)
{
	// If _card is not null, push it in hand
	if (_card != nullptr) d_cardsOnHand.push(_card);
	return *this;
}

Card* Hand::play()
{
	if (d_cardsOnHand.empty()) return nullptr;
	else {
		Card* playedCard = d_cardsOnHand.front();
		d_cardsOnHand.pop();
		return playedCard;
	}
}

Card* Hand::top() const
{
	if (d_cardsOnHand.empty()) return nullptr;
	else return d_cardsOnHand.front();
}

Card* Hand::operator[](int index)
{
	// First bound checking
	if ((size_t)index >= d_cardsOnHand.size()) throw IndexOutOfBounds();

	// Create a vector that will hold all cards from queue in Hand temperarily
	std::vector<Card*> tempContainer;

	// Transfer all cards to vector
	while(!d_cardsOnHand.empty()) {
		tempContainer.emplace_back(std::move(d_cardsOnHand.front()));
		d_cardsOnHand.pop();
	}

	auto iter = tempContainer.begin() + index;
	Card* discardedCard = *iter; // Stores the card to be discarded
	tempContainer.erase(iter); // Removes the card from vector

	// Finally transfer all cards back to queue
	for (auto c : tempContainer) d_cardsOnHand.push(c);

	return discardedCard;
}

std::ostream& operator<<(std::ostream& os, Hand& _hand) {
	// Store all elements in the queue to a temporary vector
	std::vector<Card*> tempVec;
	while (!_hand.d_cardsOnHand.empty()) {
		tempVec.emplace_back(std::move(_hand.d_cardsOnHand.front()));
		_hand.d_cardsOnHand.pop();
	}

	for (auto c : tempVec) {
		c->print(os);
		_hand.d_cardsOnHand.push(c);
	}
	return os;
}

std::string IndexOutOfBounds::showMessage()
{
	return "The index is INVALID because it's out of bound!!";
}
