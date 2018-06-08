#include "player.h"

Player::Player(std::istream& is, CardFactory* _cFactory)
{
	std::string line;    std::getline(is, line);
	// First set player's name 
	// Note that, player's name may contain white spaces.
	std::istringstream record(line);
	int nameLength = 0;
	while (record.get() != ':') ++nameLength;  // Get length of player's name
	record.seekg(0);
	std::string tempName(nameLength, '\0');
	record.read(&tempName[0], nameLength + 1);  // Read player's name(including white space)
	name = tempName;   

	// Then get the players number of coins 
	std::string coinStr;  record >> coinStr;
	currentCoins = std::stoi(coinStr);

	// Set 3 chains the players has
	for (int i = 0; i < 3; ++i) {
		char ch;
		for (int i = 0; i < 2; ++i) is.get(ch);   // Get the 2nd character of this line
		if (ch != '(') {
			switch (ch) {
			case 'Q': 
				chains[i] = new Chain<Quartz>(is, _cFactory);  break;
			case 'H': 
				chains[i] = new Chain<Hematite>(is, _cFactory);  break;
			case 'O': 
				chains[i] = new Chain<Obsidian>(is, _cFactory);  break;
			case 'M': 
				chains[i] = new Chain<Malachite>(is, _cFactory);  break;
			case 'T': 
				chains[i] = new Chain<Turquoise>(is, _cFactory);  break;
			case 'R': 
				chains[i] = new Chain<Ruby>(is, _cFactory);  break;
			case 'A': 
				chains[i] = new Chain<Amethyst>(is, _cFactory);  break;
			case 'E': 
				chains[i] = new Chain<Emerald>(is, _cFactory);  break;
			}
			if (i == 2) unlock = true;
		}
		else {  // if this chain is empty
			chains[i] = new Chain_Base();
			if (is.get() == 'e') {  // If this chain shows "-(empty chain)"
				if (i == 2) unlock = true;
				else unlock = false;
			}
			else {   // if this chain shows "-(3rd chain not available)"
				unlock = false;
			}
			std::getline(is, line);  // Go to next line
		}
	}

	// Finally, get the hand of player
	hand = new Hand(is, _cFactory);
}

std::string Player::getName() const
{
	return name;
}

int Player::getNumCoins() const
{
	return currentCoins;
}

Player& Player::operator+=(int coins)
{
	currentCoins += coins;
	return *this;
}

int Player::getMaxNumChains() const {
	if (unlock) return 3;
	else return 2;
}

int Player::getNumChains() const
{
	int size = 0;
	for (auto &c : chains) {
		if (!c->empty()) ++size;
	}
	return size;
}

Chain_Base& Player::operator[](int i)
{
	// If index is equal or larger than the number of non-empty chains, throw IndexOutOfBounds exception
	if (i >= getMaxNumChains()) throw IndexOutOfBounds();
	else return *(chains[i]);	
}

void Player::buyThirdChain()
{
	if (currentCoins < 3) throw NotEnoughCoins();

	currentCoins -= 3;
	unlock = true;
}

void Player::printHand(std::ostream& os, bool all)
{
	if (hand->top() == nullptr) {
		os << "Oops?? You have no cards in your hand right now!!\n\n";
	}
	// If the player has cards in hand
	else {
		// If boolean is false, only print the top of Hand
		if (!all)  os << hand->top()->getName();
		else os << *hand;
	}
}

void Player::startNewChain(int i, const char& ch)
{
	delete chains[i];
	switch (ch) {
	case 'Q': 
		chains[i] = new Chain<Quartz>();  break;
	case 'H': 
		chains[i] = new Chain<Hematite>();  break;
	case 'O': 
		chains[i] = new Chain<Obsidian>();  break;
	case 'M': 
		chains[i] = new Chain<Malachite>();  break;
	case 'T': 
		chains[i] = new Chain<Turquoise>();  break;
	case 'R': 
		chains[i] = new Chain<Ruby>();  break;
	case 'A': 
		chains[i] = new Chain<Amethyst>();  break;
	case 'E': 
		chains[i] = new Chain<Emerald>();  break;
	default: 
		chains[i] = new Chain_Base();
	}
}

Hand* Player::getHand()
{
	return hand;
}

Player::~Player()
{
	// delete all dynamic allocated Chain
	for (auto& chainPtr : chains) 	delete chainPtr;
	// delete hand
	delete hand;
}

std::ostream& operator<<(std::ostream& os, Player& _player)
{
	os << _player.name << ":    " << _player.currentCoins << " coins" << std::endl;
	for (int i = 0; i < 3; ++i) {
		if (i==2 && !_player.unlock) {
			os << "-(3rd chain: unavailable)" << std::endl;			
		}
		else {
			os << "-" << *(_player.chains[i]) << std::endl;
		}
	}
	return os;
}

std::string NotEnoughCoins::showMessage()
{
	return "You don't have enough coins to buy the third chain!!";
}
