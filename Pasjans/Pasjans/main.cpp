#include <fcntl.h>
#include <io.h>

#include "solitaire.h"

int main()
{

	const int cardWidth = 5;
	const int cardHeight = 5;
	
	_setmode(_fileno(stdout), _O_U16TEXT);  // setting the console character coding to utf-8 
	SetConsoleOutputCP(CP_UTF8);			// to make drawing cards possible
											// which in turn will make me have to use std::wcout everywhere 
	Solitaire * Test = new Solitaire(cardWidth, cardHeight);

	Test->randomizeDeck();

	Test->drawDeck(); // drawing for the first time

	while (true)
	{
		Sleep(1000);
		
		if (Test->getInput())  // redrawing if input is received
		{
			system("cls");
			Test->drawDeck();  
			Sleep(50);
		}
		else
		{
			while (!Test->getInput())
			{
				break;
			}
		}

	}

}
