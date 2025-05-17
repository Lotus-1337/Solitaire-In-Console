#include <random>
#include <iostream>

#include "solitaire.h"

#define heart L'\u2665'
#define spade L'\u2660'
#define club L'\u2663'
#define diamond L'\u2666'

#define leftTopCorner L'\u2554'
#define rightTopCorner L'\u2557'

#define horizontalLines L'\u2550'
#define verticalLines L'\u2551'

#define leftDownCorner L'\u255A'
#define rightDownCorner L'\u255D'

#define coveredCardLeftTopCorner L'\u250C'
#define coveredCardRightTopCorner L'\u2510'

#define coveredCardVertLine L'\u2502'
#define coveredCardHorLine L'\u2500'

#define coveredCardLeftDownCorner L'\u2514'
#define coveredCardRightDownCorner L'\u2518'

#define currentCard Stacks[column][currentCardIndex]

float absoluteValue(float number);


Solitaire::Solitaire(int cardsWidth, int cardsHeight)
{

	cardWidth = cardsWidth;
	cardHeight = cardsHeight;

	columns = 7;
	rows = cardHeight + columns;

	totalDeckLength = columns * cardWidth;
}


void Solitaire::randomizeDeck()
{
	int howManyCardsInTotal = 52;
	int howManyDifferentSuits = 4;

	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, howManyCardsInTotal - 1);

	int placeholderValue = 100;

	for (int i = 0; i < howManyCardsInTotal; i++)
	{

		Card Card1(cardWidth, cardHeight);
		Card1.cardValue = placeholderValue; 
		Card1.isHidden = true;

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

	Card HiddenCard(cardWidth, cardHeight);
	HiddenCard.isHidden = true;

	Card FundationPileCard(cardWidth, cardHeight);
	std::vector<class Card> FundationCards;

	std::vector<bool> ShouldCardBeDrawn = { 1, 1, 1, 1, 1, 1, 1 };

	for (int i = 0; i < howManyDifferentSuits; i++)
	{
		FundationPileCard.isHidden = false;
		FundationPileCard.isOnTopOfStack = true;

		FundationPileCard.CardsSuit = Suit(i);
		FundationCards.push_back(FundationPileCard);

	}

	for (int i = 0; i < cardHeight ; i++)                                 // printing the drawing stack and the foundation pile
	{

		Stacks.back().back().isHidden = false;

		Stacks.back().back().drawCard(false);

		Stacks.back().back().whichPartOfCard++;

		std::wcout << L' ';

		HiddenCard.drawCard(false);
		HiddenCard.whichPartOfCard++;

		for (int j = 0; j < totalDeckLength; j++)
		{
			std::wcout << L' ';
		}

		for (int j = 0; j < 4; j++)
		{
			FundationCards[j].drawCard(true);
			FundationCards[j].whichPartOfCard++;
		}


		std::wcout << L'\n';

	}
	
	std::wcout << L"\n\n";


	for (int row = 0; row < rows; row++)
	{
		

		for (int i = 0; i < cardWidth * 2 + 1; i++)
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
				
				currentCard.drawCard(false);

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

	}
	
}

void Solitaire::drawCursor(int x)
{
	
	for (int i = 0; i < x * (cardWidth - 1); i++)
	{
		std::wcout << L' ';
	}


}

void Card::drawCard(bool isInFundationPile)
{

	wchar_t valueSymbol;
	wchar_t suitSymbol = L' ';
	
	wchar_t spaces = L' ';

	if (whichPartOfCard <= 3)
	{
		if (!isHidden || !isInFundationPile)
		{

			valueSymbol = getValueSymbol();

			if (int(valueSymbol) == 10)
			{
				spaces = 0;
			}
		}
		if  (isInFundationPile)
		{
			valueSymbol = L' ';
		}
	}

	if (!isHidden)
	{
		suitSymbol = getSuitSymbol();
	}
	else
	{
		suitSymbol = L' ';
	}

	if (!isHidden && !isInFundationPile)
	{
		if (isOnTopOfStack)
		{

			switch (whichPartOfCard)
			{

			case 0:
				std::wcout << leftTopCorner << horizontalLines << horizontalLines << horizontalLines << rightTopCorner;
				break;

			case 1:

				if (valueSymbol != L'A' && valueSymbol != L'J' && valueSymbol != L'Q' && valueSymbol != L'K')
				{
					std::wcout << verticalLines << static_cast<int>(valueSymbol) << L' ' << spaces << verticalLines;
				}
				else
				{
					std::wcout << verticalLines << valueSymbol << L' ' << spaces << verticalLines;
				}

				break;

			case 2:
				std::wcout << verticalLines << L' ' << suitSymbol << L' ' << verticalLines;
				break;

			case 3:
				if (valueSymbol != L'A' && valueSymbol != L'J' && valueSymbol != L'Q' && valueSymbol != L'K')
				{
					std::wcout << verticalLines << L' ' << spaces << static_cast<int>(valueSymbol) << verticalLines;
				}
				else
				{
					std::wcout << verticalLines << L' ' << spaces << valueSymbol << verticalLines;
				}

				break;

			case 4:
				std::wcout << leftDownCorner << horizontalLines << horizontalLines << horizontalLines << rightDownCorner;
				break;

			default:
				for (int i = 0; i < cardWidth; i++)
				{
					std::wcout << L' ';
				}

				break;

			}
		}
		else {
			switch (whichPartOfCard)
			{
			case 0:

				if (valueSymbol != L'A' && valueSymbol != L'J' && valueSymbol != L'Q' && valueSymbol != L'K')
				{
					std::wcout << leftTopCorner << static_cast<int>(valueSymbol) << suitSymbol << spaces << rightTopCorner;
				}
				else
				{
					std::wcout << leftTopCorner << valueSymbol << suitSymbol << spaces << rightTopCorner;
				}

				break;
			}
		}
	}
	else 
	{

		switch (whichPartOfCard)
		{

		case 0:
			std::wcout << coveredCardLeftTopCorner << coveredCardHorLine << coveredCardHorLine << coveredCardHorLine << coveredCardRightTopCorner;
			break;

		case 1: case 3:
			std::wcout << coveredCardVertLine << L"   " << coveredCardVertLine;
			break;

		case 2:
			std::wcout << coveredCardVertLine << L' ' << suitSymbol << L' ' << coveredCardVertLine;
			break;

		case 4:
			std::wcout << coveredCardLeftDownCorner << coveredCardHorLine << coveredCardHorLine << coveredCardHorLine << coveredCardRightDownCorner;
			break;
		}
	}
}

wchar_t Card::getSuitSymbol()
{

	wchar_t suitSymbol;

	switch (CardsSuit)
	{

	case 0:
		suitSymbol = heart;
		break;

	case 1:
		suitSymbol = spade;
		break;

	case 2:
		suitSymbol = club;
		break;

	case 3:
		suitSymbol = diamond;
		break;

	default:
		suitSymbol = L' ';
		break;
	}

	return suitSymbol;

}

wchar_t Card::getValueSymbol()
{

	wchar_t valueSymbol;

	switch (cardValue)
	{

	case 0:
		valueSymbol = L'A';
		break;

	case 11:
		valueSymbol = L'J';
		break;

	case 12:
		valueSymbol = L'Q';
		break;

	case 13:
		valueSymbol = L'K';
		break;

	default:
		valueSymbol = cardValue;

	}

	return valueSymbol;

}

Card::Card(int cardsWidth, int cardsHeight)
{
	
	isUncovered = false;
	isHidden = true;
	isOnTopOfStack = false;
	whichPartOfCard = 0;

	cardWidth = cardsWidth;
	cardHeight = cardsHeight;

}

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

