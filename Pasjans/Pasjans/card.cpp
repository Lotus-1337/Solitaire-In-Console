
#include "solitaire.h"


#define heart L'\u2665'		// defining shortcuts for all the card suits
#define spade L'\u2660'
#define club L'\u2663'
#define diamond L'\u2666'

#define leftTopCorner L'\u2554'		// defining unicode chars for all the card parts 
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


Card::Card(int cardsWidth, int cardsHeight)
{

	isUncovered = false;
	isHidden = true;
	isOnTopOfStack = false;
	whichPartOfCard = 0;

	cardWidth = cardsWidth;
	cardHeight = cardsHeight;

}

void Card::drawCard()
{

	wchar_t valueSymbol;
	wchar_t suitSymbol = L' ';

	wchar_t spaces = L' ';

	if (whichPartOfCard <= 3)
	{
		if (!isHidden)
		{

			valueSymbol = getValueSymbol();

			if (int(valueSymbol) == 10)
			{
				spaces = 0;
			}
		}
	}

	suitSymbol = getSuitSymbol();

	if (!isHidden)
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

				if (valueSymbol != 10)
				{
					spaces = horizontalLines; // an existing variable becomes horizontal lines
				}

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

		suitSymbol = diamond;
		break;

	case 2:

		suitSymbol = spade;
		break;

	case 3:

		suitSymbol = club;
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
