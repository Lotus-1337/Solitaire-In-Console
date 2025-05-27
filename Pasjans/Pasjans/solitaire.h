#pragma once

#include <vector>
#include <array>
#include <Windows.h>
#include <iostream>

class Solitaire;

enum Suit
		{

			Heart,
			Diamond,
			Spade,
			Club

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

		//std::array<int, 4> HowManyCardsOfSuit = { 13, 13, 13, 13 };

		std::vector<std::vector<class Card>> Stacks;

		std::vector<std::vector<class Card>> FundationStack;

		std::vector<class Card> PickedUpCards;

	public:

		Solitaire(int cardsWidth, int cardsHeight);

		void randomizeDeck();

		bool checkOrder();
		
		void drawDeck();

		void drawIndentation();

		bool getInput();

		void moveCursor(int directionX, int directionY);
		void drawCursor();

		bool isHorizontalCursorPosValid(int cursorPosX);
		bool isVerticalCursorPosValid(int cursorPosY);


		void pickCard(int previousStack);
		void moveCard(int nextStack);

		bool canPlaceCardInFundationStack();
		bool canPlaceCardInStack();


};
