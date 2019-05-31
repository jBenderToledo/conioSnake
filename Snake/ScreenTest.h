#pragma once
#include "Screen.h"

using namespace Screen;

namespace ScreenTest
{
	const char BLACK = 0x20;
	const char WHITE = 0xB2;

	void checkerBoard(short x0, short y0)
	{

		Coordinate c = { 0,0 };
		short &x = c.x, &y = c.y;

		for (y = y0; y < y0 + 8; y++)
			for (x = x0; x < x0 + 8; x++)
				writeAtXY(c, ((x + y - x0 - y0) % 2 == 0) ? BLACK : WHITE);
	}

	char hexValOf(int i)
	{
		if (0x61 <= i && i <= 0x66)
			return (i & ~0x60) + 0x9;
		else if (0x41 <= i && i <= 0x46)
			return (i & ~0x40) + 0x9;
		else if (0x30 <= i && i <= 0x39)
			return (i & ~0x30);
		else
			return -1; // The sign being on means that an error has occurred.
	}

	char getHexValueFromUser()
	{
		int input;
		do
		{
			input = hexValOf(_getch());
		} while (input & 0x80);

		return input;
	}

	void putStr(const char* cstring, Coordinate position)
	{
		gotoXY(position);
		while (*cstring != 0)
		{
			_putch(*cstring);
			cstring++;
		}
	}

	typedef Coordinate basicCoord;

	void putHexValue(basicCoord c, int ch)
	{
		if (0 <= ch && ch <= 9)
			writeAtXY(c, ch + 0x30);
		else if (10 <= ch && ch < 16)
			writeAtXY(c, ch + 0x41 - 10);
	}

	void printBoardsIndefinitely()
	{
		const char* prompt = "Input a hex coordinate (0->F) to print a checker board!";
		const char* continuePrompt = "Press a key to continue!";
		const char* eraseContinuePrompt = "                        ";
		Coordinate  inputCoord;
		short promptHeight = 17 + 8 + 1;

		const Coordinate
			CURR_X_LOCATION = { (short)strlen(prompt) + 1, promptHeight },
			CURR_Y_LOCATION = { CURR_X_LOCATION.x + 2, promptHeight },
			PREV_X_LOCATION = { CURR_Y_LOCATION.x + 5, promptHeight },
			PREV_Y_LOCATION = { PREV_X_LOCATION.x + 2, promptHeight };

		short &x = inputCoord.x, &y = inputCoord.y;
		turnOffCursor();

		putStr(prompt, { 0, promptHeight });
		do
		{
			x = getHexValueFromUser();
			putHexValue(CURR_X_LOCATION, x);

			y = getHexValueFromUser();
			writeAtXY({ CURR_X_LOCATION.x + 1, CURR_X_LOCATION.y }, ',');
			putHexValue(CURR_Y_LOCATION, y);

			putStr(continuePrompt, { 0, promptHeight + 2 });
			writeAtXY(inputCoord, 'X');
			_getch();
			putStr(eraseContinuePrompt, { 0, promptHeight + 2 });

			checkerBoard(x, y);

			for (short x0 = 0; x0 < 3; x0++)
			{
				writeAtXY({ CURR_X_LOCATION.x + x0, CURR_X_LOCATION.y }, ' ');
			}

			putHexValue(PREV_X_LOCATION, x);
			putHexValue(PREV_Y_LOCATION, y);

			writeSeries(
				new Coordinate[3]{ {PREV_X_LOCATION.x - 1, PREV_X_LOCATION.y},
				  {PREV_Y_LOCATION.x - 1, PREV_Y_LOCATION.y},
				  {PREV_Y_LOCATION.x + 1, PREV_Y_LOCATION.y} },
				new char[3]{
					'(', ',', ')'
				},
				3
			);
		} while (true);
	}
};