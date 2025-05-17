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
		
		Suit CardsSuit;

		void drawCard(int whichPartOfCard, bool isInFundationPile);

		wchar_t getSuitSymbol();
		wchar_t getValueSymbol();

		
		
	public:

		void placeCard();

		Card();

};

class Solitaire
{

	public: 

		void randomizeDeck();

		bool checkOrder(Card &Card1);

		std::vector<class Card> CardsOrder;

		std::array<int, 4> HowManyCardsOfSuit = { 13, 13, 13, 13 };

		void drawDeck();

		int totalDeckLength;

		std::vector<std::vector<class Card>> Stacks;

};
