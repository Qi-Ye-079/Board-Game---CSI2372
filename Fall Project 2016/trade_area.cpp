#include "trade_area.h"

std::ostream& operator<<(std::ostream& os, TradeArea& _tradeArea)
{
	for (auto& c : _tradeArea.d_tradeCards) {
		c->print(os);
	}
	return os;
}

TradeArea::TradeArea(std::istream& is, CardFactory* _cFactory)
{
	std::string line;  std::getline(is, line);
	std::istringstream record(line);
	char ch;
	while (record.get(ch)) {
		if (ch != ' ') 	d_tradeCards.push_back(_cFactory->getCard(ch));
	}
}

TradeArea& TradeArea::operator+=(Card* _card)
{
	if (_card != nullptr) d_tradeCards.push_back(_card);
	return *this;
}

bool TradeArea::legal(Card* _card)
{
	// If a null pointer is passed in:
	if (_card == nullptr) return false;

	bool hasSame = false;
	for (auto& c : d_tradeCards) {
		if ((c->getName()) == (_card->getName())) hasSame = true;
	}
	return hasSame;
}

Card* TradeArea::trade(std::string _name)
{
	Card* card = nullptr;
	for (auto iter = d_tradeCards.begin(); iter != d_tradeCards.end(); ++iter) {
		if ((*iter)->getName() == _name) {
			card = *iter;
			d_tradeCards.erase(iter);
			break;
		}
	}
	return card;
}

int TradeArea::numCards() const
{
	return d_tradeCards.size();
}

std::list<Card*>& TradeArea::getTradeCards()
{
	return d_tradeCards;
}