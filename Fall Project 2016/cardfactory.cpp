#include "cardfactory.h"

CardFactory::CardFactory()
{
	for (size_t noQuartz = 0; noQuartz < 20; ++noQuartz) {
		deck.push_back(new Quartz());
	}
	for (size_t noHematite = 0; noHematite < 18; ++noHematite) {
		deck.push_back(new Hematite());
	}
	for (size_t noObsidian = 0; noObsidian < 16; ++noObsidian) {
		deck.push_back(new Obsidian());
	}
	for (size_t noMalachite = 0; noMalachite < 14; ++noMalachite) {
		deck.push_back(new Malachite());
	}
	for (size_t noTurquoise = 0; noTurquoise < 12; ++noTurquoise) {
		deck.push_back(new Turquoise());
	}
	for (size_t noRuby = 0; noRuby < 10; ++noRuby) {
		deck.push_back(new Ruby());
	}
	for (size_t noAmethyst = 0; noAmethyst < 8; ++noAmethyst) {
		deck.push_back(new Amethyst());
	}
	for (size_t noEmerald = 0; noEmerald < 6; ++noEmerald) {
		deck.push_back(new Emerald());
	}
	deck.shrink_to_fit();

	cardReturned.fill(false);
}

Deck CardFactory::getDeck()
{
	// Shuffle the deck and return it
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 g(seed);
	std::shuffle(deck.begin(), deck.end(), g);
	return deck;
}

Card* CardFactory::getCard(const char& ch)
{
	Card* retCard = nullptr;
	for (int i = 0; i < 104; ++i) {
		// Only return the card that's not been returned before
		if (!cardReturned[i] && deck[i]->getName()[0] == ch) {
			retCard = deck[i];  cardReturned[i] = true;
			break;
		}
	}
	return retCard;
}

CardFactory::~CardFactory() {
	for (auto &c : deck)  delete c;
}

CardFactory* CardFactory::getCardFactory() {
	static CardFactory cFactory;
	return &cFactory;
}
