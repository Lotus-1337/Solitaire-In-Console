#pragma once

#include <vector>
#include <array>
#include <Windows.h>
#include <iostream>

#include "Card.h"
#include "Menu.h"

class Solitaire
{

	friend class Menu;

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

		int moves;

		std::vector<class Card> CardsOrder;

		std::vector<std::vector<class Card>> Stacks;

		std::vector<std::vector<class Card>> FundationStack;

		std::vector<class Card> ReserveStack; // second reserve stack, the one from which you can pick up the cards

		std::vector<class Card> PickedUpCards;

		void swapTwoCards(Card& Card1, Card& Card2);

		void drawIndentation();
		
		void moveCursor(int directionX, int directionY);
		void drawCursor();

		bool isHorizontalCursorPosValid(int cursorPosX);
		bool isVerticalCursorPosValid(int cursorPosY);


		void pickCard(int previousStack);
		void moveCard(int nextStack);

		bool canPlaceCardInFundationStack();
		bool canPlaceCardInStack();

	public:

		Solitaire(int cardsWidth, int cardsHeight);

		void randomizeDeck();
		
		void drawDeck();

		bool getInput();

		bool hasGameBeenWon();

		void gameLoop();


};

