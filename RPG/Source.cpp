#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <windows.h>
#include "Player.h"
#include "Enemies.h"
using namespace std;

//creates the player as a global variable
Player* player = new Player();

int combatChance = 0;	//sets the chance of a combat encounter 

//-----------------------------------------------------------------------------
//
//							COMBAT
//
//-----------------------------------------------------------------------------

void drawCombatScreen(EnemyTemplate* enemy)
{
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "                                                      " << enemy->name << endl;
	cout << "                                                      Health: " << enemy->health << endl;
	cout << endl << endl << endl;
	cout << "           Health: " << player->Health << endl;
	cout << "           Attack: " << player->Attack << endl;
	cout << "           Armor: " << player->Armor << endl;
	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
}

void drawCombatItem(EnemyTemplate* enemy)
{
	vector<string> menu;
	int redo = 1;
	while (redo)
	{
		system("cls");
		drawCombatScreen(enemy);
		int count = 1;
		int choice;
		for (int i = 0; i < player->inventory.size(); i++)
		{
			if (player->inventory[i].first > 0)
			{
				cout << count << ") " << player->inventory[i].second << endl;
				menu.push_back(player->inventory[i].second);
				count++;
			}
		}
		cout << count << ") Back" << endl;
		menu.push_back("Back");
		char key = ' ';
		key = _getch();
		if (key == '1')
		{
			choice = 0;
		}
		else if (key == '2')
		{
			choice = 1;
		}
		else if (key == '3')
		{
			choice = 2;
		}
		else
			choice = -1;

		if (menu[choice] == "Back")
		{
			redo = 0;
		}
		//TODO make it so that items actually do something
	}
}

void drawCombatAbility(EnemyTemplate* enemy)
{
	int redo = 1;
	while (redo)
	{
		system("cls");
		drawCombatScreen(enemy);
		cout << "Ability" << endl << "1) back" << endl;
		char key = ' ';
		key = _getch();
		if (key == '1')
		{
			redo = 0;
		}

		//TODO make it so player can choose an ability
	}
}

int combat(EnemyTemplate* enemy)
{
	int choice;
	system("cls");
	cout << "You encountered a " << enemy->name << "!" << endl;
	system("pause");

	while (enemy->health > 0)
	{
		system("cls");
		drawCombatScreen(enemy);
		cout << "1) Attack" << endl << "2) Item" << endl << "3) Ability" << endl;
		char key = ' ';
		key = _getch();
		if (key == '1')
		{
			//TODO make attacks work
		}
		if (key == '2')
		{
			drawCombatItem(enemy);
		}
		if (key == '3')
		{
			drawCombatAbility(enemy);
		}

		//TODO make the enemy fight back
	}
	
	system("pause");
	return 0;
}

//-----------------------------------------------------------------------------
//
//							Map
//
//-----------------------------------------------------------------------------

void printMap(vector<vector<char>> map, int& posX, int& posY)
{
	int const mapStartX = posX - 40;
	int const mapStartY = posY - 10;
	
	cout << "            L: Legend      I: Inventory      J: Journal      H: Help" << endl;
	for (int y = mapStartY; y < mapStartY + 20; y++)
	{
		for (int x = mapStartX; x < mapStartX + 80; x++)
		{
			if (y < 0 || x < 0)
				cout << '-';
			else if (x >= map.size() || y >= map.size())
				cout << '-';
			else if (y == mapStartY + 10 && x == mapStartX + 40)
				cout << 'X';
			else
				cout << map[y][x];
		}
		cout << endl;
	}
	cout << "________________________________________________________________________________" << endl;
}

void mapHelpScreen()
{
	system("cls");
	cout << "help Screen" << endl;
	system("pause");
}

void mapInventoryScreen()
{
	system("cls");
	cout << "Inventory Screen" << endl;
	system("pause");
}

void mapJournalScreen()
{
	system("cls");
	cout << "Journal Screen" << endl;
	system("pause");
}

void mapLegendScreen()
{
	system("cls");
	cout << "Legend Screen" << endl;
	system("pause");
}

void mapControl(vector<vector<char>> &map, int posX, int posY)
{
	while (true)
	{
		system("cls");
		printMap(map, posX, posY);

		//Get input from player
		char key = ' ';
		key = _getch();
		int moved = 0;
		if (key == 'a')
		{
			if (posX != 1)
			{
				posX--;
				moved = 1;
			}
		}
		else if (key == 'w')
		{
			if (posY != 1)
			{
				posY--;
				moved = 1;
			}
		}
		else if (key == 's')
		{
			if (posY != map.size()-2)
			{
				posY++;
				moved = 1;
			}
		}
		else if (key == 'd')
		{
			if (posX != map.size() - 2)
			{
				posX++;
				moved = 1;
			}
		}
		else if (key == 'l')
		{
			mapLegendScreen();
		}
		else if (key == 'i')
		{
			mapInventoryScreen();
		}
		else if (key == 'h')
		{
			mapHelpScreen();
		}
		else if (key == 'j')
		{
			mapJournalScreen();
		}

		//Determine combat encounter
		if (moved)
		{
			int const isCombat = rand() % combatChance;
			if (isCombat == 1)
			{
				BasicEnemy* enemy = new BasicEnemy();

				combat(enemy);
				delete(enemy);
			}
		}
	}
}

//-----------------------------------------------------------------------------
//
//							Main
//
//-----------------------------------------------------------------------------

int main()
{
	pair<int, string> test(1, "Potion");
	player->inventory.push_back(test);
	test.second = "Mana Potion";
	player->inventory.push_back(test);
	
	//modify console text
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	//set up overworld map
	int testmapX = 5;
	int testmapY = 5;
	vector<vector<char>> testMap(10, vector<char>(10));
	for (int i = 0; i < 10; i++)
	{
		for (int x = 0; x < 10; x++)
		{
			testMap[i][x] = ' ';
		}
	}

	//set the borders for the map
	for (int i = 0; i < 10; i++)
	{
		testMap[i][0] = '|';
	}
	for (int i = 0; i < 10; i++)
	{
		testMap[i][9] = '|';
	}
	for (int i = 0; i < 10; i++)
	{
		testMap[0][i] = '_';
	}
	for (int i = 0; i < 10; i++)
	{
		testMap[9][i] = '_';
	}
	testMap[9][0] = '|';
	testMap[9][9] = '|';

	mapControl(testMap, testmapX, testmapY);




	int OverWorldPosX = 50;
	int OverWorldPosY = 50;

	//set up overworld map
	vector<vector<char>> OverWorldMap(1000, vector<char>(1000));
	for (int i = 0; i < 1000; i++)
	{
		for (int x = 0; x < 1000; x++)
		{
			OverWorldMap[i][x] = ' ';
		}
	}

	//set the borders for the map
	for (int i = 0; i < 1000; i++)
	{
		OverWorldMap[i][0] = '|';
	}
	for (int i = 0; i < 1000; i++)
	{
		OverWorldMap[i][999] = '|';
	}
	for (int i = 0; i < 1000; i++)
	{
		OverWorldMap[0][i] = '_';
	}
	for (int i = 0; i < 1000; i++)
	{
		OverWorldMap[999][i] = '_';
	}
	OverWorldMap[999][0] = '|';
	OverWorldMap[999][999] = '|';


	mapControl(OverWorldMap, OverWorldPosX, OverWorldPosY);
	

	cout << "End of Program" << endl;	
	system("pause");
	return 0;
}