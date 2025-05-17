#include <fcntl.h>
#include <io.h>
#include <windows.h>

#include "solitaire.h"

int main()
{

	const int cardWidth = 5;
	const int cardHeight = 5;
	
	_setmode(_fileno(stdout), _O_U16TEXT);
	SetConsoleOutputCP(CP_UTF8);

	Solitaire Test(cardWidth, cardHeight);

	Test.randomizeDeck();

	Test.drawDeck();

}
