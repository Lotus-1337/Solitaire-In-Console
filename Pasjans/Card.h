#pragma once

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