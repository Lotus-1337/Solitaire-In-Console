#include <random>
#include <string>

#include "solitaire.h"
#include "Card.h"
#include "Menu.h"

#define verticalCursor L'\u2192'

float absoluteValue(float number);


Solitaire::Solitaire(int cardsWidth, int cardsHeight)
{

	cardWidth = cardsWidth;
	cardHeight = cardsHeight;

	columns = 7;
	rows = cardHeight + 13;

	totalDeckLength = columns * cardWidth;

	howManyCardsInTotal = 52;

	didPlayerPickUpCard = false;

	cursorPositionX = (columns - 1) / 2;
	cursorPositionY = 0;

	howManyDifferentSuits = 4;

	moves = 0;
	
}

void Solitaire::swapTwoCards(Card &Card1, Card &Card2)
{

	Card TemporaryCard = Card2;

	Card2 = Card1;

	Card1 = TemporaryCard;

}

void Solitaire::randomizeDeck()
{

	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, howManyCardsInTotal - 1);

	std::array<int, 13> howManyCardsOfValue = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::array<int, 4> howManyCardsOfSuit = { 0, 0, 0, 0 };

	Card HiddenCard(cardWidth, cardHeight);
	HiddenCard.isHidden = true;

	for (int i = 0; i < howManyCardsInTotal; i++)
	{

		Card Card1(cardWidth, cardHeight);

		Card1.cardValue = (i + 1) % 13;
		Card1.CardsSuit = static_cast<Suit>((i + 1) % howManyDifferentSuits);

		howManyCardsOfValue[Card1.cardValue]++;
		howManyCardsOfSuit[Card1.CardsSuit]++;

		CardsOrder.push_back(Card1);

	}

	CardsOrder.shrink_to_fit();

	// shuffling the cards

	for (int i = 0; i < howManyCardsInTotal; i++)
	{

		swapTwoCards(CardsOrder[i], CardsOrder[dist(rd)]);
		
	}


	std::vector<class Card> Stack1;

	int cardsInStack = 0;

	// adding the cards to the stacks

	for (int i = 0; i < columns; i++)
	{

		for (int j = 0; j <= i; j++)
		{
			Stack1.push_back(CardsOrder[cardsInStack]);
			cardsInStack++;
			
		}

		Stack1.shrink_to_fit();

		Stacks.push_back(Stack1);

		Stack1.clear();
	}

	Stacks.shrink_to_fit();

	// a hidden card is being added to the very beggining of both of the reserve stacks

	ReserveStack.push_back(HiddenCard);
	Stack1.push_back(HiddenCard);

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

	// DEBUG

	for (int i = 0; i < howManyCardsOfValue.size(); i++)
	{

		std::wcout << howManyCardsOfValue[i] << L' ';

	}
	std::wcout << L'\n';
	for (int i = 0; i < howManyCardsOfSuit.size(); i++)
	{

		std::wcout << howManyCardsOfSuit[i] << L' ';

	}
	std::wcout << L'\n';



}

void Solitaire::drawDeck()
{

	#define currentCard Stacks[column][currentCardIndex]

	int howManyDifferentSuits = 4;

	int totalLengthOfIndentationInSpaces;

	

	Card FundationPileCard(cardWidth, cardHeight);
	std::vector<class Card> FundationCards;

	// setting the values of the first "cards" in the fundation stack

	for (int i = 0; i < howManyDifferentSuits; i++)  
	{

		FundationPileCard.isHidden = true;
		FundationPileCard.isOnTopOfStack = true;
		FundationPileCard.whichPartOfCard = 0;

		FundationPileCard.CardsSuit = Suit(i);
		FundationCards.push_back(FundationPileCard);

		FundationStack.push_back(FundationCards);

	}

	// all the cards except for the ones on top are not on top of the stack anymore

	for (int i = 0; i < Stacks.size(); i++)   
	{

		for (int j = 0; j < Stacks[i].size(); j++)
		{

			Stacks[i][j].isOnTopOfStack = false;

		}

		Stacks[i].back().isHidden = false;
		Stacks[i].back().isOnTopOfStack = true;
		Stacks[i].back().whichPartOfCard = 0;

	}
	
	// printing the drawing stack and the foundation pile

	for (int i = 0; i < cardHeight ; i++)                                 
	{

		if (Stacks.back().size() == 1)
		{
			
			Stacks.back().back().isHidden = true;

		}
		else
		{

			Stacks.back().back().isHidden = false;

		}

		Stacks.back().back().drawCard();

		Stacks.back().back().whichPartOfCard++;

		std::wcout << L' ';

		ReserveStack.back().drawCard();
		ReserveStack.back().whichPartOfCard++;

		std::wstring howManyMoves = L"Moves: " + std::to_wstring(moves);

		std::wcout << L' ';

		int spaces = (totalDeckLength - howManyMoves.length()) / 2;

		if (i == cardHeight / 2)
		{

			for (int j = 0; j < spaces; j++)
			{
				std::wcout << L' ';
			}

			std::wcout << howManyMoves;

			for (int j = 0; j < spaces; j++)
			{
				std::wcout << L' ';
			}

		}
		else
		{
			for (int j = 0; j < totalDeckLength; j++)
			{
				std::wcout << L' ';
			}
		}
		
		for (int j = 0; j < howManyDifferentSuits; j++)
		{

			FundationStack[j].back().drawCard();
			FundationStack[j].back().whichPartOfCard++;
		}
		


		std::wcout << L'\n';

	}

	Stacks.back().back().whichPartOfCard = 0; 
	ReserveStack.back().whichPartOfCard = 0;

	for (int i = 0; i < FundationStack.size(); i++)
	{
		FundationStack[i].back().whichPartOfCard = 0;
	}

	std::wcout << L"\n\n";

	// printing the main stacks and cursors

	for (int row = 0; row < rows; row++)
	{

		bool hasVerticalCursBeenDrawn = false;

		int cursPosX = cursorPositionX - 2;

		if (cursorPositionY == rows - row)
		{
			std::wcout << verticalCursor;
			hasVerticalCursBeenDrawn = true;
		}
		
		totalLengthOfIndentationInSpaces = cardWidth * 2 + 1 - hasVerticalCursBeenDrawn;   // subtracting 0 (when cursor was not drawn) or 1 (when it was drawn)
																						   // from the amount of spaces needed to indent the cards

		for (int i = 0; i < totalLengthOfIndentationInSpaces; i++)
		{
			std::wcout << L' ';
		}

		int cardPart = 0;
		

		for (int column = 0; column < columns; column++)
		{

			int currentCardIndex = 0;

			cardPart = currentCard.whichPartOfCard; // line 147 "#define currentCard Stacks[column][currentCardIndex]"

			currentCardIndex = row - cardPart;		// current card index is sort of a shortcut 

			currentCardIndex = absoluteValue(currentCardIndex);

			if (currentCardIndex > Stacks[column].size() - 1)
			{
				currentCardIndex = Stacks[column].size() - 1;

			}

			currentCard.drawCard();

			if (currentCard.isOnTopOfStack)//&& row < currentCardIndex + cardHeight)
			{
				currentCard.whichPartOfCard++;
			}
	
			if (columns - column <= 1)
			{
				std::wcout << L'\n';
			}

		}

		if (row == rows - 1)
		{

			drawCursor();

			
			if (PickedUpCards.size() == 0)
			{

				drawIndentation();
			
			}
			else
			{

				for (int i = 0; i < PickedUpCards.size(); i++)
				{
					PickedUpCards[i].drawCard();
					std::wcout << L'\n';
				}

			}

			
			break;
		}

	}
							

	
	// PURE DEBUGGING
	// DELETE AFTER THE CODE WORKS FINE

	// PLEASE WORK
	
}

bool Solitaire::getInput()			// returning whether the input has been received
{

	int movingDirectionX = 0;
	int movingDirectionY = 0;
	
	if (GetKeyState(VK_RIGHT) & 0x8000 || GetKeyState('D') & 0x8000) 
	{
		movingDirectionX = 1;
		movingDirectionY = - 1;
	}
	else if (GetKeyState(VK_LEFT) & 0x8000 || GetKeyState('A') & 0x8000)
	{
		movingDirectionX = - 1;
		movingDirectionY =  1;
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
		if (PickedUpCards.size() == 0)
		{
			pickCard(cursorPositionX);
			didPlayerPickUpCard = true;
		}
		else
		{
			moveCard(cursorPositionX);
			didPlayerPickUpCard = false;
		}

		return true; 
		
	}

	else if (GetKeyState(VK_ESCAPE) & 0x8000)
	{

		system("cls");

		while (true)
		{
			Menu::menu(true, *this);
		}

		
		

	}

	moveCursor(movingDirectionX, movingDirectionY);

	if (movingDirectionX != 0 || movingDirectionY != 0)
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

	if (isHorizontalCursorPosValid(cursorPositionX + directionX))
	{

		cursorPositionX += directionX;
	}

	if (isVerticalCursorPosValid(cursorPositionY + directionY))
	{

		cursorPositionY += directionY;

	}

}

void Solitaire::pickCard(int previousStack)
{
	previousStack -= 2; // if position is 2, then picked card is from the 2nd stack
						// - 2 because the cursor position can range from being under the reserve stack to the fundation stack, 
						// reserve stack is 2 cards

						// also the stack of index 0 is at 2 cursorPositionX
						// variable only used when picking up a card from a stack which is not a reserve one nor a fundation one

	int numberOfPickedCards = (rows + 1) - cursorPositionY;


	if (cursorPositionX == 0)
	{
		if (Stacks.back().size() > 1)
		{

			ReserveStack.push_back(Stacks.back().back());
	
			Stacks.back().pop_back();

		}

		else
		{

			// all the cards are going back to the stack where you cant pick them up

			for (int i = 0; i < ReserveStack.size(); i++)  
			{

				Stacks.back().push_back(ReserveStack.back());

				ReserveStack.pop_back();

			}

		}
		

	}

	else if (cursorPositionX == 1 && ReserveStack.size() > 1) // if size is 0, it means the only card in the reserve stack is the invisible temp card
	{

		PickedUpCards.push_back(ReserveStack.back());

		ReserveStack.pop_back();

	}

	else if (previousStack >= columns && FundationStack[previousStack - columns].size() > 0) //picking up a card from a fundation stack
	{

		PickedUpCards.push_back(FundationStack[cursorPositionX - columns].back());
		FundationStack[previousStack - columns].pop_back();
	
	}

	else if (previousStack > 0 && previousStack < columns) // picking up a card from one of the main stacks
	{

		int StacksSize = Stacks[previousStack].size();

		if (StacksSize > 0 && StacksSize >= numberOfPickedCards)
		{
			
			int column = cursorPositionX - 2;

			for (int i = numberOfPickedCards; i > 0; i--)
			{

				if (!Stacks[previousStack][StacksSize - i].isHidden)
				{

					PickedUpCards.push_back(Stacks[previousStack][StacksSize - i]);

					Stacks[previousStack].pop_back();
				
				}
				
			}
			Stacks[previousStack].back().isHidden = false;
			
		}
	}
	
	for (int i = 0; i < PickedUpCards.size(); i++)
	{
		PickedUpCards[i].whichPartOfCard = 0;
		PickedUpCards[i].isHidden = false;
		PickedUpCards[i].isOnTopOfStack = false;
	}
	
}

void Solitaire::moveCard(int nextStack)
{
	
	nextStack -= 2;

	if (nextStack < columns)
	{
		for (int i = 0; i < PickedUpCards.size(); i++)
		{

			if (canPlaceCardInStack())
			{

				Stacks[nextStack].push_back(PickedUpCards[i]);

				PickedUpCards.clear();



			}
			
	
		}

		moves++;
		
	}
	else
	{

		if (canPlaceCardInFundationStack())
		{

			int fundationStackID = nextStack - columns;

			FundationStack[fundationStackID].push_back(PickedUpCards[0]);

			PickedUpCards.clear();
			
			moves++;

		}

	}
	
	Stacks[nextStack].shrink_to_fit();

	

}

void Solitaire::drawCursor()
{

	#define cursorPointer L'\u2191'		// defining unicode chars for all the cursor parts 
	#define cursorLeftSide L'\u207D'	// doing that for better code readability
	#define cursorRightSide L'\u207E'

	for (int i = 0; i < (cursorPositionX * cardWidth) + 1; i++)	// if player did pick it up, 
	{																				// the card will be showed in the bottom left corner, so the amount of 
		std::wcout << L' ';															// needed spaces is cardWidth less
	}

	std::wcout << cursorLeftSide << L' ' << cursorPointer << L' ' << cursorRightSide << L'\n';


}

bool Solitaire::isHorizontalCursorPosValid(int cursorPosX)
{

	int smallestValidPosX = 0 + didPlayerPickUpCard;
	int biggestValidPosX = (2 - didPlayerPickUpCard) + columns + howManyDifferentSuits;


	if (cursorPosX >= smallestValidPosX && cursorPosX <= biggestValidPosX)
	{

		return true;
	}

	else
	{

		return false;
	}


}

bool Solitaire::isVerticalCursorPosValid(int cursorPosY)
{

	int smallestValidPosY = 0;
	int biggestValidPosY = rows;

	if (cursorPosY >= smallestValidPosY && cursorPosY <= biggestValidPosY)
	{

		return true;

	}
	else
	{

		return false;

	}

}

void Solitaire::drawIndentation()
{
	for (int i = 0; i < cardWidth; i++)
	{
		std::wcout << L' ';
	}

}

bool Solitaire::canPlaceCardInFundationStack()
{

	if (PickedUpCards.size() == 1)
	{

		int fundationStackID = cursorPositionX - columns;

		if (PickedUpCards.back().CardsSuit == fundationStackID &&
			PickedUpCards.back().cardValue - FundationStack[fundationStackID].back().cardValue == 1)
		{

			return true;
		
		}
		else if (PickedUpCards.back().CardsSuit == fundationStackID &&
				FundationStack[fundationStackID].size() == 0 && PickedUpCards.back().cardValue == 0)
		{
			return true;
		}

	}

	return false;

}

bool Solitaire::canPlaceCardInStack()
{

	int StackToPlaceCard = cursorPositionX - 2;

	if (Stacks[StackToPlaceCard].size() > 0)
	{

		int cardSuitColor = 0;
		int lastCardInStackColor = 0;

		if (PickedUpCards[0].CardsSuit < 2)
		{
			cardSuitColor = 1;
		}

		if (Stacks[StackToPlaceCard].back().CardsSuit < 2)
		{
			lastCardInStackColor = 1;
		}
		
		int pickedCardValue = PickedUpCards[0].cardValue;
		
		int lastCardInStackValue = Stacks[StackToPlaceCard].back().cardValue;

		if (cardSuitColor != lastCardInStackColor)				// if cards color (red or black) is != color of the last card 
		{

			if (lastCardInStackValue - pickedCardValue == 1)
			{

				return true;

			}

		}
	}

	else
	{

		int valueOfKingCard = 12;

		if (PickedUpCards[0].cardValue == valueOfKingCard)
		{

			return true;

		}

	}

	return false;

}

bool Solitaire::hasGameBeenWon()
{

	for (int i = 0; i < howManyDifferentSuits; i++)
	{

		if (FundationStack[i].size() != 13)
		{

			return false;

		}

	}

	return true;

}

void Solitaire::gameLoop()
{

	cursorPositionY = rows; // preparing the cursor for the game loop

	int winningScreenHeight = 11;
	int winningScreenWitdh = 51;

	drawDeck();  // drawing deck for the first time

	while (!hasGameBeenWon())
	{

		if (getInput())
		{
			system("cls");

			drawDeck();

			Sleep(50);  // sleeping for 50 ms to reduce the chance of missinputs from the player


		}

	}

	std::wstring winningMessage = L"Congrats, you won in " + std::to_wstring(moves) + L" moves!";

	Menu::drawTile(winningMessage, winningScreenWitdh, winningScreenHeight, false);

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

