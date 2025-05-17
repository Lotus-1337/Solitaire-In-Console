#pragma once

#include <vector>
#include <array>

class Solitaire;

enum Suit
		{

			Heart,
			Spade,
			Club,
			Diamond

		};

class Card
{

	friend class Solitaire;

	protected:

		bool isHidden;
		bool isOnTopOfStack;
		bool isUncovered;

		int cardValue;
		int whichPartOfCard;

		int cardHeight;
		int cardWidth;
		
		Suit CardsSuit;

		void drawCard(bool isInFundationPile);

		wchar_t getSuitSymbol();
		wchar_t getValueSymbol();

		
		
	public:

		Card(int cardsWidth, int cardsHeight);

		void placeCard();


};

class Solitaire
{

	friend class Card;

	private: 

		int columns;
		int rows;
		int totalDeckLength;

		int cardWidth;
		int cardHeight;

		std::vector<class Card> CardsOrder;

		std::array<int, 4> HowManyCardsOfSuit = { 13, 13, 13, 13 };

		std::vector<std::vector<class Card>> Stacks;

	public:

		Solitaire(int cardsWidth, int cardsHeight);

		void randomizeDeck();

		bool checkOrder(Card &Card1);
		
		void drawDeck();

};
