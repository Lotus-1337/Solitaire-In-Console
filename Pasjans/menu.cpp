#include "Menu.h"
#include "solitaire.h"

#define verticalCursor L'\u2192'

int Menu::cursorPositionY = 0;

void Menu::menu(bool isGamePaused, Solitaire& S1)
{

	int menuWidth = 50;

	int tileHeight = 5;

	int cursorPosition = Menu::cursorPositionY;

	int lastCursorPosition = cursorPosition;

	bool didDrawCursor = false;

	std::wstring gameTitle = L"SOLIRAIRE IN CMD";

	std::array<std::wstring, 4> TileTexts = { L"Play", L"Controls", L"Author", L"Exit" };

	// replacing texts and later funcionality of different tiles in pause menu

	if (isGamePaused)
	{

		TileTexts[0] = L"Resume";
		TileTexts[1] = L"Restart Game";

	}

	// drawing indentation

	for (int i = 0; i < (menuWidth  - gameTitle.length()) / 2 + 11; i++)
	{

		std::wcout << L' ';

	}

	std::wcout << gameTitle << L'\n';

	// drawing cursor

	for (int i = 0; i < TileTexts.size(); i++)
	{
		if (i == cursorPosition)
		{
			std::wcout << verticalCursor;

			didDrawCursor = true;

		}
		else
		{
			didDrawCursor = false;
		}

		drawTile(TileTexts[i], menuWidth, tileHeight, didDrawCursor);

		std::wcout << L'\n';

	}

	// inputs

	while (true)
	{

		if (GetKeyState(VK_UP) & 0x8000 || GetKeyState('W') & 0x8000)
		{

			Menu::cursorPositionY--;
			break;
			
		}
		else if (GetKeyState(VK_DOWN) & 0x8000 || GetKeyState('S') & 0x8000)
		{

			Menu::cursorPositionY++;
			break;
			
		}
		else if (GetKeyState(VK_RETURN) & 0x8000 || GetKeyState(VK_SPACE) & 0x8000)
		{

			Sleep(50); // sleeping to prevent missinput
			system("cls");

			Menu::menuAction(cursorPosition, isGamePaused, S1);

		}

	}

	system("cls");

}

void Menu::drawTile(std::wstring tileText, int tileWidth, int tileHeight, bool didDrawCursor)
{

	#define horizontalLines L'\u2550'
	#define	verticalLines L'\u2551'

	#define leftDownCorner L'\u255A'
	#define rightDownCorner L'\u255D'

	#define leftTopCorner L'\u2554'
	#define rightTopCorner L'\u2557'

	int indentationSize = 10;

	for (int i = 0; i < tileHeight; i++)
	{

		for (int j = 0; j < indentationSize; j++)
		{

			if (i == 0 && j == indentationSize - didDrawCursor)
			{
				continue;
			}
			std::wcout << L' ';
		
		}

		if (i == 0)
		{

			std::wcout << leftTopCorner;

			for (int j = 0; j < tileWidth; j++)
			{

				std::wcout << horizontalLines;

			}

			std::wcout << rightTopCorner;

		}
		else if (i == tileHeight - 1)
		{

			std::wcout << leftDownCorner;

			for (int j = 0; j < tileWidth; j++)
			{

				std::wcout << horizontalLines;

			}

			std::wcout << rightDownCorner;

		}
		else if (i == tileHeight / 2)
		{

			std::wcout << verticalLines;

			for (int i = 0; i < (tileWidth - tileText.length()) / 2; i++)
			{
				std::wcout << L' ';
			}

			std::wcout << tileText;

			for (int i = 0; i < (tileWidth - tileText.length()) / 2; i++)
			{
				std::wcout << L' ';
			}

			std::wcout << verticalLines;


		}


		else
		{

			std::wcout << verticalLines;

			for (int j = 0; j < tileWidth; j++)
			{

				std::wcout << L' ';

			}

			std::wcout << verticalLines;

		}

		std::wcout << L"\n";
	}


}

void Menu::menuAction(int actionID, bool isGamePaused, Solitaire& S1)
{

	switch (actionID)
	{

	case 0:

		if (!isGamePaused)
		{
			S1.randomizeDeck();
		}

		S1.gameLoop();

		break;

	case 1:

		if (isGamePaused)
		{
			S1.gameLoop();
		}
		
		else
		{

			Menu menu;

			menu.displayControls();

		}

		break;

	case 2:

		drawTile(L"Author: Albert Ptaœnik. ", 50, 5, false);

		break;

	case 3:

		exit(0);
		break;

	}

	std::wcout << "Press ESC to go back. ";

	while (true)
	{

		if (GetKeyState(VK_ESCAPE) & 0x8000)
		{

			system("cls");
			Menu::menu(isGamePaused, S1);

		}

	}

}

void Menu::displayControls()
{

	std::wstring controlsText = L"Controls";

	std::wcout << leftTopCorner;

	for (int i = 0; i < controlsText.length(); i++)
	{
		std::wcout << horizontalLines;
	}
	
	std::wcout << rightTopCorner << L'\n';

	std::wcout << verticalLines << controlsText << verticalLines << L'\n';

	std::wcout << leftDownCorner;

	for (int i = 0; i < controlsText.length(); i++)
	{
		std::wcout << horizontalLines;
	}

	std::wcout << rightDownCorner << L'\n\n';

	std::wcout << L"A / Left Arrow - change cursor's X position ( go left ) \n";
	std::wcout << L"D / Right Arrow - change cursor's X position ( go right ) \n";
	std::wcout << L"W / Up Arrow - change cursor's Y position ( go up ) \n";
	std::wcout << L"S / Down Arrow - change cursor's Y position ( go down ) \n";

	std::wcout << L"Enter - confirm change ( moving a card or something in the menu ) \n";
	std::wcout << L"Escape - pause the game \n\n";


}