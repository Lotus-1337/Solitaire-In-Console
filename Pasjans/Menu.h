#pragma once

#include <string>
#include <array>

class Solitaire;

class Menu
{

private:

	static int cursorPositionY;

public:

	static void menu(bool isGamePaused, Solitaire& S1);

	static void drawTile(std::wstring tileText, int tileWidth, int tileHeight, bool didDrawCursor);

	static void menuAction(int actionID, bool isGamePaused, Solitaire& S1);

	void displayControls();

};
