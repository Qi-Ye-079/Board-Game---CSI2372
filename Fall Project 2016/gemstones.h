#pragma once
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <map>
#include <exception>

class Card {
protected:
	/**
	 *  The map to associate the certain number of coins earned with the number of cards needed
	 *  first int:
	 *     the number of coins
	 *  second int:
	 *     the number of gemstone cards needed to earn the associated number of coins
	 */
	std::map<int, int> m_cardMap;
public:
	Card() = default;
	virtual ~Card() = default;
	Card(const Card&) = delete;
	Card& operator=(const Card&) = delete;

	virtual int getCardsPerCoin(int coins) = 0;

	virtual std::string getName() const = 0;

	virtual void print(std::ostream& out) = 0;

	friend std::ostream& operator<<(std::ostream& os, Card& gemCard);
};

class Quartz : public Card {
	friend class CardFactory;
private:
	Quartz();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class Hematite : public Card {
	friend class CardFactory;
private:
	Hematite();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class Obsidian : public Card {
	friend class CardFactory;
private:
	Obsidian();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class Malachite : public Card {
	friend class CardFactory;
private:
	Malachite();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class Turquoise : public Card {
	friend class CardFactory;
private:
	Turquoise();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class Ruby : public Card {
	friend class CardFactory;
private:
	Ruby();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class Amethyst : public Card {
	friend class CardFactory;
private:
	Amethyst();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class Emerald : public Card {
	friend class CardFactory;
private:
	Emerald();
public:
	int getCardsPerCoin(int coins) override;

	std::string getName() const override;

	void print(std::ostream& out) override;
};

class IllegalType : private std::exception {
public:
	std::string showMessage();
};
#endif