#include <string>
#include <iostream>
#include <fstream>
#include "Table.h"
#include "CardFactory.h"

using std::cout;
using std::cin;
using std::endl;
using std::ifstream; 
using std::ofstream;

// ====================  Global functions  ===========================
// Global functions. See comments after main() function.
// ===================================================================
std::string getAnswer(bool);
int getIndex();
void setPlayersName(std::string&, std::string&);
void sellAndStartNewChain(Player*, Card*, DiscardPile*);


int main() {
	// First choose if starting a new game or load a paused game
	cout << "Hello there, player!! welcome to the game!!\n";
	cout << "Would you like to start a new game ? Choosing 'no' will load a saved game.\n";
	cout << "Please enter 'yes' or 'no':  ";
	std::string answer = getAnswer(false);

	std::string playerName1, playerName2;
	Table table(playerName1, playerName2);  // Initialze an empty table first

	// If starting a new game:
	if (answer == "yes") {
		new_game:
		cout << "===================================================================================" << endl;
		// First input the names of 2 players and avoid 2 players having the same name)
		cout << "A new game will start! Please enter the names for 2 players." << std::endl;
		setPlayersName(playerName1, playerName2);

		// Reconstructs a table (and deck on it), and draw 5 cards for Hand of each player
		table.~Table();
		new (&table) Table(playerName1, playerName2);
		for (auto i = 0; i < 5; ++i) {
			for (auto& p : table.getPlayers()) {
				*(p->getHand()) += (table.getDeck()->draw());
			}
		}
		cout << "\nEach player has drawn 5 cards. Game will start whenever you're ready!!\n";
		system("pause");  // Press any key to continue.
	}
	// if load a saved game
	else {
		ifstream ldfile("SavedData.txt");
		if (ldfile) {
			// Reconstruct the table from input file stream(SavedData.txt)
			table.~Table();
			new (&table) Table(ldfile, CardFactory::getCardFactory());
			cout << "> Saved data has been successfully loaded.\n\n";
		}  else {
			// If no saved file exists, simply start a new game
			cout << "> No saved data was found! Starting a new game... \n\n";
			goto new_game;
		}
	}

	std::string winner;  // Winner of this game
	auto& t_players = table.getPlayers();  // players on this table
	TradeArea* t_tradeArea = table.getTradeArea();  // trade area on this table
	DiscardPile* t_discardPile = table.getDiscardPile();  // discard pile on this table
	Deck* t_deck = table.getDeck();   // Deck on this table

	while (!table.win(winner)) {
		// if pause, save game to file and exist
		cout << "\n\n===================== A new turn starts!!! =========================\n";
		cout << "Pause the game? Choosing 'yes' will save the game and exist.\n";
		cout << "Please enter 'yes' or 'no':  ";
		answer = getAnswer(false);
		if (answer == "yes") {
			// save game and exist
			ofstream sdfile("SavedData.txt");
			cout << "> Saving now..." << endl;
			table.print(sdfile);
			cout << "> You have successfully saved the game. Quitting..." << endl;
			return 0;
		}

		// for each player:
		for (auto& p : t_players) {
			// Display table
			cout << table << endl;
			cout << "> Player: " << p->getName() << " is now taking this turn.\n\n";

			// If player has 2 chains available, ask if player wants to buy a third chain
			if (p->getMaxNumChains() == 2) {
				cout << "Purchase a third chain? Please enter 'yes' or 'no':  ";
				answer = getAnswer(false);

				// if wants to buy a third chain:
				if (answer == "yes") {
					try {
						p->buyThirdChain();   // May throw NotEnoughCoin exception
						cout << "> You have purchased the third chain with the cost of 3 coins!!\n";
					}
					catch (NotEnoughCoins& e) {
						cout << "> Error: " << e.showMessage() << endl;
						cout << "> Proceeding the game as usual.\n";
					}
				}
			}

			// Player draw top card from deck
			*(p->getHand()) += (t_deck->draw());
			cout << "\n" << "> You have drawn a card from the deck. \n\n";

			// if trade area is not empty
			if (t_tradeArea->numCards()) {
				// Add gemstone cards from tradeArea to chains or discard them
				cout << "Chain the cards from trade area? Choosing 'no' will discard all of them.\n";
				cout << "Also, the cards that can't be chained will be discarded as well.\n";
				cout << "Please enter 'yes' or 'no':  ";
				answer = getAnswer(false);

				std::vector<std::string> tradingCards;
				for (auto& c : t_tradeArea->getTradeCards()) {
					tradingCards.push_back(c->getName());
				}
				if (answer == "yes") {
					for (std::string& tc : tradingCards) {
						Card* tradeCard = t_tradeArea->trade(tc);
						// check if the played card can be tied to any of the chain
						bool chainFlag = false;
						for (auto i = 0; i < p->getMaxNumChains(); ++i) {
							if ((*p)[i].empty()) 	p->startNewChain(i, tc[0]);
							try {
								(*p)[i] += tradeCard;
								chainFlag = true;  break;
							}
							catch (IllegalType) {
								// If the card type doesn't match the chain type, do nothing;
								// continue checking the next available chain
							}
						}
						if (chainFlag) {
							cout << "> The card: " << tc << " has been successfully chained!!\n\n";
						}
						else {
							cout << "> This card: " << tc << " matches none of your chains, ";
							cout << "and it will be discarded.\n\n";
							(*t_discardPile) += tradeCard;
						}
					}
					cout << "> Now you have the following chains: \n";
					for (int i = 0; i < p->getMaxNumChains(); ++i) {
						cout << "  [" << i << "]" << (*p)[i] << endl;
					}
					cout << endl;
				}
				// if answer is "no"
				else {
					// Discard all cards from trade area to the discard pile
					for (auto& tc : tradingCards) {
						(*t_discardPile) += t_tradeArea->trade(tc);
					}
					cout << "> All the cards from trade area have been discarded.\n\n";
				}			
			}

			// Let player play the topmost card from Hand, and ask if wanting to repeat once
			bool repeat;  int numRepeat = 1;
			do {
				cout << "> Now you're about to play your topmost card: "; 
				p->printHand(cout, false); cout << " from your hand...\n";
				// Play top-most card from hand; could be nullptr/
				if (p->getHand()->top()) {
					Card* playedCard = p->getHand()->play();
					// check if the played card can be tied to any of the chain
					bool chainFlag = false;
					for (int i = 0; i < p->getMaxNumChains(); ++i) {
						if ((*p)[i].empty()) 	p->startNewChain(i, playedCard->getName()[0]);
						try {
							(*p)[i] += playedCard;
							chainFlag = true;  break;
						}
						catch (IllegalType) {
							// If the card type doesn't match the chain type, do nothing;
							// continue checking the next available chain
						}
					}
					// if no chains has the same name as the played card:
					if (!chainFlag) {
						cout << "> Oops. None of your chains matches your topmost card!\n";
						cout << "Select the chain you want to sell by entering the index of chain:  ";
						// let the player choose the chain he wants to sell:
						sellAndStartNewChain(p, playedCard, t_discardPile);
						cout << "> And you have successfully played your topmost card: " << playedCard->getName() << " on the new chain!!\n";
					}  else  cout << "> You have successfully chained the card: " << playedCard->getName() << "! \n";
				}  else cout << "> Oops?? Seems you got no cards in hand!!\n";
				// Print out the chains the player currently owns, and the topmost card on his hand
				cout << "> Now you have the following chains: \n";
				for (int i = 0; i < p->getMaxNumChains(); ++i) {
					cout << "  [" << i << "]" << (*p)[i] << endl;
				}
				cout << "> Now the top-most card on your hand: "; p->printHand(cout, false); cout << "\n\n";

				//Ask if player wants to repeat
				repeat = false;
				if (numRepeat) {
					cout << "Do you want to play your topmost card again? ";
					cout << "Please enter 'yes' or 'no':  ";
					answer = getAnswer(false);
					if (answer == "yes") {
						repeat = true;  --numRepeat;
					}
				}
			} while (repeat);

			// Ask if the player decides to show his full hand and select an arbitrary card
			cout << "Show your full hand and discard an arbitrary card? ";
			cout << "Please enter 'yes' or 'no':  ";
			answer = getAnswer(false);
			// If yes, show player's full hand and let player choose the arbitrary card he/she wants to discard
			if (answer == "yes") {
				cout << "------ The Cards on player: " << p->getName() << "'s hand ------" << endl;
				p->printHand(cout, true);
				cout << "\n------------- End of player's hand -------------" << endl;

				Card* discarded = nullptr;
				cout << "Select a card you'd like to discard by entering corresponding index:  ";			
			    input_valid_index:
				// Make sure an integer is entered by player as index
				int index = getIndex();
				// Removes the selected card from the player's hand
				try {
					discarded = (*(p->getHand()))[index];  // May throw IndexOutOfBound exception
				}
				catch (IndexOutOfBounds& e) {
					// If exception caught, do the loop again
					cout << "> Error: " << e.showMessage() << endl;
					cout << "> Please re-enter an index within bound:  ";
					goto input_valid_index;
				}

				// Then place the card on the discard pile
				(*t_discardPile) += discarded;
				cout << "> You have discarded: " << discarded->getName() << ". \n";
			}

			// Draw 3 cards from deck and place them in the trade area
			for (int i = 0; i < 3; ++i)  (*t_tradeArea) += (t_deck->draw());
			cout << "\n" << "> 3 cards have been drawn and placed into the trade area.\n\n";

			// While top card of discard pile matches an existing card on the trade area
			while (t_tradeArea->legal(t_discardPile->top())) {
				// Removes the top card from pile and push it into the trade area
				Card* topDiscarded = t_discardPile->pickup();
				(*t_tradeArea) += topDiscarded;
				cout << "> The top card of discard pile: " << topDiscarded->getName();
				cout << " has been added to the trade area.\n\n";
			}

			// For all cards in the trade area(if non-empty), ask the player if he/she wants to chain the card
			if (t_tradeArea->numCards()) {
				cout << "> You're about to decide which card to chain from the trade area." << endl;
				cout << "> If none of your chains matches this card, you have to sell one of your chains." << endl;
				cout << "> NOTE: entering 'no' will stop chaining from trade area and proceed." << endl;
				do {
					cout << "\n> Now the trade area has the following cards: " << *t_tradeArea;
					cout << "\n> Please enter the character(upper case) of which card you'd like to chain OR 'no': ";
					input_answer:
					answer = getAnswer(true);
					if (answer == "no") break;
					else {  // If choose one of cards to chain
						Card* toChain = nullptr;
						switch (answer[0]) {
						case'Q':  
							toChain = t_tradeArea->trade("Quartz"); break;
						case'H':  
							toChain = t_tradeArea->trade("Hematite"); break;
						case'O':  
							toChain = t_tradeArea->trade("Obsidian"); break;
						case'M':  
							toChain = t_tradeArea->trade("Malachite"); break;
						case'T':  
							toChain = t_tradeArea->trade("Turquoise"); break;
						case'R':  
							toChain = t_tradeArea->trade("Ruby"); break;
						case'A':  
							toChain = t_tradeArea->trade("Amethyst"); break;
						case'E':  
							toChain = t_tradeArea->trade("Emerald"); break;
						}
						if (!toChain) {
							cout << "Invalid input! Please enter your choice again: ";
							goto input_answer;
						}
						else {
							// check if the chosen card can be tied to any of the chain
							bool chainFlag = false;
							for (int i = 0; i < p->getMaxNumChains(); ++i) {
								if ((*p)[i].empty()) 	p->startNewChain(i, toChain->getName()[0]);
								try {
									(*p)[i] += toChain;
									chainFlag = true;  break;
								}
								catch (IllegalType) {
									// If the card type doesn't match the chain type, do nothing;
									// continue checking the next available chain
								}
							}
							// if no chains has the same name as the played card:
							if (!chainFlag) {
								cout << "> Oops. None of your chains matches this card!\n";
								cout << "Select the chain you want to sell by entering the index of chain:  ";
								// let the player choose the chain he wants to sell:
								sellAndStartNewChain(p, toChain, t_discardPile);
								cout << "> And you have successfully played your topmost card: " << toChain->getName() << " on the new chain!!\n";
							}
							else {
								cout << "> You have successfully chained the card: " << toChain->getName() << "! \n";
								cout << "> Now you have the following chains: " << endl;
							}
							for (int i = 0; i < p->getMaxNumChains(); ++i) {
								cout << "  [" << i << "]" << (*p)[i] << endl;
							}
						}
					}
				} while (t_tradeArea->numCards());
				cout << "> Ended chaining from trade area.\n\n";
			}

			// Player draws 2 cards from deck
			for (int i=0;i<2;++i)  *(p->getHand()) += (t_deck->draw());
			cout << "> 2 more cards drawn, and the player have finished this turn.\n\n";

			// Prompt player to input a key to proceed to next player
			cout << "> To proceed to the next player: ";  system("pause");
		} // A player's turn ends
	}  // main while loop ends

	cout << "\n\n==================== The game is OVER!! =============================" << endl;
	if (winner == "No one") {  // If 2 players have same number of coins
		cout << "Ooh, 2 players have the same number of coins thus no one wins!" << endl;
	} else {
		cout << "The player: " << winner << " wins!! Congratulations!!" << endl;
	}
	return 0;
}

/**
 *  A global function to prompt user input answer.
 *  Loops until a valid answer is read.
 *  freeType: if true, any entered text is valid answer.
 *            if false, only "yes" and "no" are valid answers.
 */
std::string getAnswer(bool freeType)
{
	std::string answer;
	do {
		cin.clear();
		std::getline(cin, answer);
		if (freeType) break;
		else if (!(answer == "yes" || answer == "no")) {
			cout << "Invalid answer! Please enter 'yes' or 'no':  ";
		}
	} while (!(answer == "yes" || answer == "no"));
	return answer;
}

/**
 *  Global function to prompt player to input an index(integer).
 *  Loops until the player enters an integer.
 *  This function makes sure to return an integer whenever an index is needed.
 */
int getIndex() {
	std::string indexStr;  int index;
    loop:
	std::getline(cin, indexStr);
	try {
		index = std::stoi(indexStr);  // May throw invalid_argument exception
	}
	catch (std::exception&) {
		cout << "Invalid input! Please enter a valid index:  ";
		goto loop;
	}
	return index;
}

/**
 *  Global function to prompt user to enter and set the 2 players' names.
 *  This function also prevents 2 players' names being the same.
 *  Also allows players' names have white spaces.
 *  The names to be set are returned by reference.
 */
void setPlayersName(std::string& _playerName1, std::string& _playerName2) {
	cout << "Player 1: ";
	std::getline(cin, _playerName1);
	do {
		cin.clear();
		cout << "Player 2: ";
		std::getline(cin, _playerName2);
		if (_playerName2 == _playerName1) {
			cout << "ERROR: 2 players can't have the same name!! ";
			cout << "Please re-enter the name for player2." << endl;
		}
	} while (_playerName2 == _playerName1);
}

/**
 *  This global function lets player to sell one of their chain, and start a new chain
 *  with the card passed by pointer.
 *  Also, the sold chain will discard all its cards into discard pile
 */
void sellAndStartNewChain(Player* _player, Card* _card, DiscardPile* _discardPile) {
    valid_input:
	// Make sure an integer is entered by player as index
	int index = getIndex();
	try {
		int earnedCoin = (*_player)[index].sell(); // may throw IndexOutOfBound exception
		// Put all cards in chain into discard pile and shuffle discard pile
		while (!(*_player)[index].empty()) {
			(*_discardPile) += (*_player)[index].discard();
		}
		_discardPile->shuffle();
		// Start a new chain with the given card type
		_player->startNewChain(index, _card->getName()[0]);  
		(*_player)[index] += _card;
		// Add to the earned coins
		(*_player) += earnedCoin;    
		cout << "> You have successfully sold your chain at position " << index << ", ";
		cout << "and earned " << earnedCoin << " coins!\n";
	}
	catch (IndexOutOfBounds& e) {
		cout << "> Error: " << e.showMessage() << endl;
		cout << "> Please re-enter a valid index:  ";
		goto valid_input;
	}
}