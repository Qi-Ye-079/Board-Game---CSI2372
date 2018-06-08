#include "table.h"

Table::Table(std::string d_playerName1, std::string d_playerName2)
{
	players[0] = new Player(d_playerName1);
	players[1] = new Player(d_playerName2);
	d_deck = new Deck(CardFactory::getCardFactory()->getDeck());
	d_tradeArea = new TradeArea();
	d_discardPile = new DiscardPile();
}

Table::Table(std::istream& is, CardFactory* _cFactory)
{
	std::string line;
	for (int i = 0; i < 2; ++i) {
		players[i] = new Player(is, _cFactory);
	}
	std::getline(is, line);   // Go to next line
	d_deck = new Deck(is, _cFactory);
	std::getline(is, line);  // Go to next line
	d_tradeArea = new TradeArea(is, _cFactory);
	std::getline(is, line);   // Go to next line
	d_discardPile = new DiscardPile(is, _cFactory);
}

bool Table::win(std::string& winner) const
{
	if (d_deck->empty()) {
		if (players[0]->getNumCoins() > players[1]->getNumCoins()) {
			winner = players[0]->getName();
		} else if (players[0]->getNumCoins() < players[1]->getNumCoins()) {
			winner = players[1]->getName();
		} else {  // if 2 players have same number of coins, no winner
			winner = "No one";
		}
		return true;
	} else {  // If deck still has cards
		return false;
	}
}

std::array<Player*,2>& Table::getPlayers()
{
	return players;
}

Deck* Table::getDeck()
{
	return d_deck;
}

TradeArea* Table::getTradeArea()
{
	return d_tradeArea;
}

DiscardPile* Table::getDiscardPile()
{
	return d_discardPile;
}

void Table::print(std::ostream& os)
{
	os << *players[0] << "Hand: ";  players[0]->printHand(os, true);  os << std::endl;
	os << *players[1] << "Hand: ";  players[1]->printHand(os, true);  os << std::endl;
	os << "Deck:" << std::endl << *d_deck << std::endl;
	os << "Trade Area:" << std::endl << *d_tradeArea << std::endl;
	os << "Discard Pile:" << std::endl;  d_discardPile->print(os);   // Print all the cards in discard pile
}

std::ostream& operator<<(std::ostream& os, Table& _table)
{
	os << "\n------------------------------------------ table ------------------------------------------\n";
	os << *(_table.players[0]) << std::endl << *(_table.players[1]) << std::endl;
	os << "Trade area: " << *(_table.d_tradeArea) << std::endl;
	os << "Discard Pile: " << *(_table.d_discardPile) << std::endl;  // Only top card of discard pile is printed
	os << "\n---------------------------------------- End table ----------------------------------------\n";
	return os;
}

Table::~Table() {
	for (auto& p : players)  delete p;
	delete d_deck;
	delete d_tradeArea;
	delete d_discardPile;
}

