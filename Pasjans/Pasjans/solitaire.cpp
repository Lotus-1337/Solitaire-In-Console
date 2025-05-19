#include <random>
#include <iostream>

#include "solitaire.h"

#define currentCard Stacks[column][currentCardIndex]

#define cursorPointer L'\u2191'
#define cursorLeftSide L'\u207D'
#define cursorRightSide L'\u207E'

#define verticalCursor L'\u2192'

float absoluteValue(float number);


Solitaire::Solitaire(int cardsWidth, int cardsHeight)
{

	cardWidth = cardsWidth;
	cardHeight = cardsHeight;

	columns = 7;
	rows = cardHeight + columns;

	totalDeckLength = columns * cardWidth;

	howManyCardsInTotal = 52;

	didPlayerPickUpCard = false;

	cursorPositionX = (columns - 1) / 2;

	howManyDifferentSuits = 4;


}


void Solitaire::randomizeDeck()
{

	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, howManyCardsInTotal - 1);

	int placeholderValue = 100;

	for (int i = 0; i < howManyCardsInTotal; i++)
	{

		Card Card1(cardWidth, cardHeight);
		Card1.cardValue = placeholderValue; 

		CardsOrder.push_back(Card1);

	}

	CardsOrder.shrink_to_fit();

	for (int i = 0; i < howManyCardsInTotal; i++)
	{

		int randomNumber = dist(rd);

		while (CardsOrder[randomNumber].cardValue != placeholderValue)
		{
			randomNumber = dist(rd);
			//std::wcout << L"Skibidi \n" << randomNumber << L'\n';
		}

		CardsOrder[i].cardValue = randomNumber % 13;
		CardsOrder[i].CardsSuit = static_cast<Suit>(randomNumber % howManyDifferentSuits);
		
	}

	std::vector<class Card> Stack1;

	int cardsInStack = 0;

	for (int i = 0; i < columns; i++)
	{

		for (int j = 0; j <= i; j++)
		{
			Stack1.push_back(CardsOrder[cardsInStack]);
			cardsInStack++;
			
		}

		Stacks.push_back(Stack1);

		Stack1.clear();
	}

	Stack1.shrink_to_fit();
	Stacks.shrink_to_fit();


	for (int i = cardsInStack; i < howManyCardsInTotal - 1; i++)
	{
		Stack1.push_back(CardsOrder[i]);
	}


	Stacks.push_back(Stack1);

	Stacks.shrink_to_fit();

	for (int i = 0; i < Stacks.size(); i++)
	{
		Stacks[i].back().isOnTopOfStack = true;
		Stacks[i].back().isUncovered = true;
		Stacks[i].back().isHidden = false;
	}
	
	/*
	std::vector<int> ValueCount = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
	std::vector<int> SuitCount = { 0, 0, 0, 0 };

	for (int i = 0; i < Stacks.size(); i++)
	{

		for (int j = 0; j < Stacks[i].size(); j++)
		{
			std::wcout << Stacks[i][j].cardValue << L' ';

			ValueCount[Stacks[i][j].cardValue]++;
			SuitCount[Stacks[i][i].CardsSuit]++;
		}

		std::wcout << L'\n';

	}

	std::wcout << L"Values count: \n";
	for (int i = 0; i < ValueCount.size(); i++)
	{
		std::wcout << ValueCount[i] << L' ';
	}

	std::wcout << L"\n Suit count: \n";
	for (int i = 0; i < SuitCount.size(); i++)
	{
		std::wcout << SuitCount[i] << L' ';
	}

	*/  // TO FIX 

}

void Solitaire::drawDeck()
{

	int howManyDifferentSuits = 4;

	int totalLengthOfIndentationInSpaces;

	Card HiddenCard(cardWidth, cardHeight);
	HiddenCard.isHidden = true;

	Card FundationPileCard(cardWidth, cardHeight);
	std::vector<class Card> FundationCards;

	std::vector<bool> ShouldCardBeDrawn = { 1, 1, 1, 1, 1, 1, 1 };

	for (int i = 0; i < howManyDifferentSuits; i++)
	{
		FundationPileCard.isHidden = true;
		FundationPileCard.isOnTopOfStack = true;
		FundationPileCard.whichPartOfCard = 0;

		FundationPileCard.CardsSuit = Suit(i);
		FundationCards.push_back(FundationPileCard);

		FundationStack.push_back(FundationCards);

	}

	for (int i = 0; i < cardHeight ; i++)                                 // printing the drawing stack and the foundation pile
	{

		Stacks.back().back().isHidden = false;

		Stacks.back().back().drawCard();

		Stacks.back().back().whichPartOfCard++;

		std::wcout << L' ';

		HiddenCard.drawCard();
		HiddenCard.whichPartOfCard++;

		for (int j = 0; j < totalDeckLength; j++)
		{
			std::wcout << L' ';
		}

		for (int j = 0; j < howManyDifferentSuits; j++)
		{
			FundationStack[j].back().drawCard();
			FundationStack[j].back().whichPartOfCard++;
		}
		


		std::wcout << L'\n';

	}

	Stacks.back().back().whichPartOfCard = 0;
	
	for (int i = 0; i < Stacks.size(); i++)
	{
		Stacks[i].back().whichPartOfCard = 0;
	}

	for (int i = 0; i < FundationStack.size(); i++)
	{
		FundationStack[i].back().whichPartOfCard = 0;
	}

	std::wcout << L"\n\n";


	for (int row = 0; row < rows; row++)
	{

		bool hasVerticalCursBeenDrawn = false;

		if (cursorPositionY == rows - row)
		{
			std::wcout << verticalCursor;
			hasVerticalCursBeenDrawn = true;
		}
		
		totalLengthOfIndentationInSpaces = cardWidth * 2 + 1 - hasVerticalCursBeenDrawn;

		for (int i = 0; i < totalLengthOfIndentationInSpaces; i++)
		{
			std::wcout << L' ';
		}

		int cardPart = 0;
		

		for (int column = 0; column < columns; column++)
		{

			int currentCardIndex = 0;

			if (Stacks[column].size() > currentCardIndex)
			{

				cardPart = currentCard.whichPartOfCard; // line 29 "#define currentCard Stacks[column][currentCardIndex]"

				currentCardIndex = row - cardPart;

				currentCardIndex = absoluteValue(currentCardIndex);
				
				if (currentCardIndex > Stacks[column].size() - 1)
				{
					currentCardIndex = Stacks[column].size() - 1;

				}
				
				currentCard.drawCard();

				if (currentCard.isOnTopOfStack && row < currentCardIndex + cardHeight)
				{
					currentCard.whichPartOfCard++;
				}

			}

			if (columns - column <= 1)
			{
				std::wcout << L'\n';
			}

		}

		if (row == rows - 1)
		{
			if (didPlayerPickUpCard)
			{
				for (int i = 0; i < PickedUpCards.size(); i++)
				{
					PickedUpCards[i].drawCard();
				}
				
			}
			else
			{
				for (int i = 0; i < cardWidth; i++)
				{
					std::wcout << L' ';
				}
			}

			drawCursor();
			break;
		}

	}

	
}

bool Solitaire::getInput()			// returning whether the input has been received
{

	int movingDirectionX = 0;
	int movingDirectionY = 0;

	int pickOrMoveCard = 0;

	
	
	if (GetKeyState(VK_RIGHT) & 0x8000 || GetKeyState('D') & 0x8000) 
	{
		movingDirectionX = 1;
	}
	else if (GetKeyState(VK_LEFT) & 0x8000 || GetKeyState('A') & 0x8000)
	{
		movingDirectionX = -1;
	}
	if (GetKeyState(VK_UP) & 0x8000 || GetKeyState('W') & 0x8000)
	{
		movingDirectionY = 1;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000 || GetKeyState('S') & 0x8000)
	{
		movingDirectionY = -1;
	}

	else if (GetKeyState(VK_RETURN) & 0x8000 || GetKeyState(VK_SPACE) & 0x8000)
	{
		if (pickOrMoveCard % 2 == 0)
		{

			pickCard(cursorPositionX);
			didPlayerPickUpCard = true;
		}
		else
		{
			didPlayerPickUpCard = false;
			moveCard(cursorPositionX);
		}

		return true; 
		
	}

	moveCursor(movingDirectionX, movingDirectionY);

	if (movingDirectionX != 0 && movingDirectionY != 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Solitaire::moveCursor(int directionX, int directionY)
{

	if (isCursorPosValid(cursorPositionX + directionX, cursorPositionY + directionY))
	{
		cursorPositionX += directionX;
		cursorPositionY += directionY;
	}

	std::wcout << cursorPositionX;

}

void Solitaire::pickCard(int previousStack)
{

	if (cursorPositionX <= 0 && Stacks.back().size() > 0)
	{
		for (int i = cursorPositionY; i > 0; i--)
		{
			int reserveStackSize = Stacks.back().size();
			PickedUpCards.push_back(Stacks.back()[reserveStackSize - i]);
		}
		
		Stacks.back().pop_back();

	}
	else if (cursorPositionX >= columns && FundationStack[cursorPositionX - columns].size() > 0)
	{
		
		//int fundationStackSize = FundationStack[cursorPositionX - columns].size();

		//for (int i = cursorPositionY)
		PickedUpCards.push_back(FundationStack[cursorPositionX - columns].back());
		FundationStack[cursorPositionX - columns].pop_back();
	}

	else if (cursorPositionX > 0 && cursorPositionX < columns)
	{

		previousStack -= 1; // if position is 3, then picked card is from the 3rd stack (its index is 2)

		int StacksSize = Stacks[previousStack].size();

		if (StacksSize > 0)
		{
			
			for (int i = StacksSize; i > 0; i--)
			{
				PickedUpCards.push_back(Stacks[previousStack][StacksSize - i]);
			}
			
			Stacks[previousStack].pop_back();
		}
	}
	
	for (int i = 0; i < PickedUpCards.size(); i++)
	{
		PickedUpCards[i].whichPartOfCard = 0;
	}
	
}

void Solitaire::moveCard(int nextStack)
{

	for (int i = 0; i < PickedUpCards.size(); i++)
	{
		Stacks[nextStack].push_back(PickedUpCards[i]);
	}
	
	Stacks[nextStack].shrink_to_fit();


}

void Solitaire::drawCursor()
{


	for (int i = 0; i < cursorPositionX * (cardWidth - didPlayerPickUpCard); i++)	// if player did pick it up, 
	{																				// it will be showed in the bottom left corner, so the amount of 
		std::wcout << L' ';															// needed spaces is cardWidth less
	}

	std::wcout << cursorLeftSide << L' ' << cursorPointer << L' ' << cursorRightSide << L'\n';


}

bool Solitaire::isCursorPosValid(int cursorPosX, int cursorPosY)
{

	int smallestValidPosX = 0 + didPlayerPickUpCard;
	int biggestValidPosX = (2 - didPlayerPickUpCard) + columns + howManyDifferentSuits;

	int smallestValidPosY = 0;
	int biggestValidPosY = columns - 1;

	if (cursorPosX >= smallestValidPosX && cursorPosX <= biggestValidPosX || 
		cursorPosY >= smallestValidPosY && cursorPosY <= biggestValidPosY)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//bool Solitaire::checkOrder()
//{
//
//}


float absoluteValue(float number)
{
	if (number > 0.0)
	{
		return number;
	}
	else
	{
		return -number;
	}
}

