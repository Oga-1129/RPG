#include <iostream>
#include <string>
#include "rpg.h"

using namespace std;

void output( string str)
{
	cout << str << endl;
}

int main()
{
	Player p[4] = 
		{
		 Player("勇者",100, 0,5,1,1,80,1,1),
		 Player("戦士", 80, 0,7,1,1,70,1,1),
		 Player("黒魔導師", 50,40,2,1,1,70,1,1),
		 Player("白魔導師", 50,60,2,1,1,70,1,1)
		};

	Enemy e[4] = 
		{
		Enemy("スライム",      15, 0, 20, 1, 1, 60, 50,   1),
		Enemy("ゴブリン",      18, 0, 30, 3, 1, 65, 70,  15),
		Enemy("ドラキー",      21, 0, 40, 5, 1, 70, 150, 25),
		Enemy("ミニドラゴン",  300, 0, 50, 7, 1, 75,   0,  0)
	};

	Game_main game_main;

	p[0].x1 = 1;
	p[0].y1 = 1;
	game_main.start_up(p,e, game_main);

	output("ゴールしました");
}