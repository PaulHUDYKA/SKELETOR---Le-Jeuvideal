#pragma once

#include <stdint.h>

typedef struct MENUITEM
{
	char* Name;

	int16_t x;

	int16_t y;

	void(*Action)(void);

}MENUITEM;

typedef struct MENU
{
	char* Name;

	uint8_t SelectedItem;

	uint8_t ItemCount;

	MENUITEM** Items;

} MENU;

void MenuItem_TitleScreen_Resume(void);

void MenuItem_TitleScreen_StartNew(void);

void MenuItem_TitleScreen_Options(void);

void MenuItem_TitleScreen_Exit(void);

MENUITEM gMI_ResumeGame = { "Reprendre la partie", (GAME_RES_WIDTH / 2) - ((19 * 6) / 2), 100, MenuItem_TitleScreen_Resume };

MENUITEM gMI_StartNewGame = { "Nouvelle Partie", (GAME_RES_WIDTH / 2) - ((15 * 6) / 2), 120, MenuItem_TitleScreen_StartNew };

MENUITEM gMI_Options = { "Options", (GAME_RES_WIDTH / 2) - ((7 * 6) / 2), 140, MenuItem_TitleScreen_Options };

MENUITEM gMI_Exit = { "Exit", (GAME_RES_WIDTH / 2) - ((4 * 6) / 2), 160, MenuItem_TitleScreen_Exit };

MENUITEM* gMI_TileScreenItems[] = { &gMI_ResumeGame, &gMI_StartNewGame, &gMI_Options, &gMI_Exit };

MENU gMI_TitleScreen = { "Title Screen Menu", 0, _countof(gMI_TileScreenItems), gMI_TileScreenItems };
