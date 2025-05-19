#pragma once

#include <vector>
#include <array>
#include <Windows.h>

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

		void drawCard();

		wchar_t getSuitSymbol();
		wchar_t getValueSymbol();

		
		
	public:

		Card(int cardsWidth, int cardsHeight);

		//void placeCard(int previousStack, int nextStack);


};

class Solitaire
{

	friend class Card;

	private: 
		
		bool didPlayerPickUpCard;

		int columns;
		int rows;
		int totalDeckLength;

		int howManyCardsInTotal;

		int cardWidth;
		int cardHeight;

		int cursorPositionX;
		int cursorPositionY;

		int howManyDifferentSuits;

		std::vector<class Card> CardsOrder;

		std::array<int, 4> HowManyCardsOfSuit = { 13, 13, 13, 13 };

		std::vector<std::vector<class Card>> Stacks;

		std::vector<std::vector<class Card>> FundationStack;

		std::vector<class Card> PickedUpCards;

	public:

		Solitaire(int cardsWidth, int cardsHeight);

		void randomizeDeck();

		bool checkOrder();
		
		void drawDeck();

		bool getInput();

		void moveCursor(int directionX, int directionY);
		void drawCursor();
		bool isCursorPosValid(int cursorPosX, int cursorPosY);

		void pickCard(int previousStack);
		void moveCard(int nextStack);


};
