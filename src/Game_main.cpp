#include <iostream>
#include <string>
#include "rpg.h"

using namespace std;

Game_main::Game_main()
{
	dead_end = 0;
	judge_goal = 0;
	judge_city = 0;
	judge_dungeon = 0;
}

void Game_main::start_up(Player p[], Enemy e[], Game_main game_main)
{
	Game_map game_map;
	//ゴールしていない時
	while(game_main.judge_goal == 0)
	{
		game_map.show_map(p);
		game_map.map_main(p,game_map, game_main);
	}
}