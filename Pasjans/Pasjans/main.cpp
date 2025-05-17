#include <fcntl.h>
#include <io.h>
#include <windows.h>
#include <iostream>

#include "solitaire.h"

int main()
{
	
	_setmode(_fileno(stdout), _O_U16TEXT);
	SetConsoleOutputCP(CP_UTF8);

	Solitaire Test;

	Test.randomizeDeck();

	Test.drawDeck();

}