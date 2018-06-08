#include "gemstones.h"
#include <utility>

std::ostream& operator<<(std::ostream &os, Card& gemCard)
{
	gemCard.print(os);
	return os;
}

Quartz::Quartz()
{
	m_cardMap = {
		std::make_pair(1,4),    // 1 coin needs 4 cards
		std::make_pair(2,6),    // 2 coins needs 6 cards
		std::make_pair(3,8),    // 3 coins needs 8 cards
		std::make_pair(4,10)    // 4 coins needs 10 cards
	};
}

int Quartz::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 0) return 0;

	/**
	 * if the argument is greater than 0,
	 * including when coins > 4, we have to decide how many cards are needed according to the noCardsPerCoin map
	 */
	int result = 0;  
	result += (coins / 4) * m_cardMap[4];
	coins %= 4;
	if (coins) result += m_cardMap[coins];
	return result;
}

std::string Quartz::getName() const
{
	return "Quartz";
}

void Quartz::print(std::ostream& out)
{
	out << "Q  ";
}

Hematite::Hematite()
{
	m_cardMap = {
		std::make_pair(1,3),
		std::make_pair(2,6),
		std::make_pair(3,8),
		std::make_pair(4,9)
	};
}

int Hematite::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 0) return 0;

	/**
	* if the argument is greater than 0,
	* including when coins > 4, we have to decide how many cards are needed according to the noCardsPerCoin map
	*/
	int result = 0;
	result += (coins / 4) * m_cardMap[4];
	coins %= 4;
	if (coins) result += m_cardMap[coins];
	return result;
}

std::string Hematite::getName() const
{
	return "Hematite";
}

void Hematite::print(std::ostream& out)
{
	out << "H  ";
}

Obsidian::Obsidian()
{
	m_cardMap = {
		std::make_pair(1,3),
		std::make_pair(2,5),
		std::make_pair(3,7),
		std::make_pair(4,8),
	};
}

int Obsidian::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 0) return 0;

	/**
	* if the argument is greater than 0,
	* including when coins > 4, we have to decide how many cards are needed according to the noCardsPerCoin map
	*/
	int result = 0;
	result += (coins / 4) * m_cardMap[4];
	coins %= 4;
	if (coins) result += m_cardMap[coins];
	return result;
}

std::string Obsidian::getName() const
{
	return "Obsidian";
}

void Obsidian::print(std::ostream& out)
{
	out << "O  ";
}

Malachite::Malachite()
{
	m_cardMap = {
		std::make_pair(1,3),
		std::make_pair(2,5),
		std::make_pair(3,6),
		std::make_pair(4,7),
	};
}

int Malachite::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 0) return 0;

	/**
	* if the argument is greater than 0,
	* including when coins > 4, we have to decide how many cards are needed according to the noCardsPerCoin map
	*/
	int result = 0;
	result += (coins / 4) * m_cardMap[4];
	coins %= 4;
	if (coins) result += m_cardMap[coins];
	return result;
}

std::string Malachite::getName() const
{
	return "Malachite";
}

void Malachite::print(std::ostream & out)
{
	out << "M  ";
}

Turquoise::Turquoise()
{
	m_cardMap = {
		std::make_pair(1,2),
		std::make_pair(2,4),
		std::make_pair(3,6),
		std::make_pair(4,7),
	};
}

int Turquoise::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 0) return 0;

	/**
	* if the argument is greater than 0,
	* including when coins > 4, we have to decide how many cards are needed according to the noCardsPerCoin map
	*/
	int result = 0;
	result += (coins / 4) * m_cardMap[4];
	coins %= 4;
	if (coins) result += m_cardMap[coins];
	return result;
}

std::string Turquoise::getName() const
{
	return "Turquoise";
}

void Turquoise::print(std::ostream& out)
{
	out << "T  ";
}

Ruby::Ruby()
{
	m_cardMap = {
		std::make_pair(1,2),
		std::make_pair(2,4),
		std::make_pair(3,5),
		std::make_pair(4,6),
	};
}

int Ruby::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 0) return 0;

	/**
	* if the argument is greater than 0,
	* including when coins > 4, we have to decide how many cards are needed according to the noCardsPerCoin map
	*/
	int result = 0;
	result += (coins / 4) * m_cardMap[4];
	coins %= 4;
	if (coins) result += m_cardMap[coins];
	return result;
}

std::string Ruby::getName() const
{
	return "Ruby";
}

void Ruby::print(std::ostream & out)
{
	out << "R  ";
}

Amethyst::Amethyst()
{
	m_cardMap = {
		std::make_pair(1,2),
		std::make_pair(2,3),
		std::make_pair(3,4),
		std::make_pair(4,5),
	};
}

int Amethyst::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 0) return 0;

	/**
	* if the argument is greater than 0,
	* including when coins > 4, we have to decide how many cards are needed according to the noCardsPerCoin map
	*/
	int result = 0;
	result += (coins / 4) * m_cardMap[4];
	coins %= 4;
	if (coins) result += m_cardMap[coins];
	return result;
}

std::string Amethyst::getName() const
{
	return "Amethyst";
}

void Amethyst::print(std::ostream& out)
{
	out << "A  ";
}

Emerald::Emerald()
{
	m_cardMap = {
		std::make_pair(2,2),
		std::make_pair(3,3),
	};
}

int Emerald::getCardsPerCoin(int coins)
{
	// If the argument passed in is less than 0, just return 0
	if (coins <= 1) return 0;

	/**
	* if the argument is greater than 0,
	* including when coins > 3, we have to decide how many cards are needed according to the noCardsPerCoin map
	* NOTE:
	*    The implementation for Emerald is slightly different from others, because it can only earn 2 types of coins
	*/
	int result = 0;
	result += (coins / 3) * m_cardMap[3];
	coins %= 3;
	if (coins) result += m_cardMap[2];
	return result;
}

std::string Emerald::getName() const
{
	return "Emerald";
}

void Emerald::print(std::ostream& out)
{
	out << "E  ";
}

std::string IllegalType::showMessage()
{
	return "This gemstone card cannot be placed on this chain due to difference in type!!";
}
