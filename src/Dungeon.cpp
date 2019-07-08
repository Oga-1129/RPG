#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "rpg.h"

using namespace std;

//6がダンジョン入り口A、7がダンジョン入り口B、8がボス、4が岩、0が枠 1スライム 2ゴブリン 3ドラキー
int setdungeon[20][20] =   
    {{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
	 {6,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
	 {8,0,4,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,8},
	 {8,0,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,8},
	 {8,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4,4,4,8},
	 {8,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,8},
	 {8,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1,8},
	 {8,2,2,2,1,1,1,1,1,1,1,1,1,1,4,1,1,1,1,8},
	 {8,4,4,2,4,1,1,1,1,4,1,1,1,1,4,1,1,1,1,8},
	 {8,2,2,2,4,1,1,1,1,4,1,1,1,1,4,1,1,1,1,8},
	 {8,2,4,4,4,1,1,1,1,4,1,1,1,1,4,1,1,1,1,8},
	 {8,2,2,2,4,1,1,1,1,4,1,1,1,1,4,1,1,1,1,8},
	 {8,4,4,2,4,1,1,1,1,4,1,1,1,1,4,1,1,1,1,8},
	 {8,2,2,2,4,1,1,1,1,4,1,1,1,1,4,1,1,1,1,8},
	 {8,2,4,4,4,1,1,1,1,4,1,1,1,1,1,1,1,1,1,8},
	 {8,2,2,2,4,1,4,4,4,4,4,4,4,4,4,4,4,4,4,8},
	 {8,4,4,2,4,2,2,2,2,2,2,4,2,4,2,4,2,4,2,8},
	 {8,2,4,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,3,7},
	 {8,2,2,2,2,2,2,2,2,2,2,4,2,4,2,4,2,4,2,8},
	 {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}
	};

//コンストラクタ
Dungeon::Dungeon()
{
	 for(int dy = 0; 20 > dy; dy++)
	 {
	 	for(int dx = 0; 20 >dx; dx++)
	 	{
	 		this->dungeon[dy][dx] = setdungeon[dy][dx];
	 		play_dungeon[dy][dx] = this->dungeon[dy][dx];
	 	}
	 }
}

//エンカウントの計算
void Dungeon::encount(Player p[], Game_map game_map, Game_main game_main, int j)
{	
	srand(time(NULL));

	Battle b;

	int ene_count = 0;

	//ボス以外
	if(j != 3){
		int encount = rand()%10;	
		if(encount == 0)
		{
			if(j < 2){
				//最大4体出現
				ene_count = 1 + rand()%4;
			}else if(j == 2){
				//最大2耐出現
				ene_count = 1 + rand()%2;
			}
			b.vs(p, game_map, game_main, ene_count, j);
		}
	}
	else if(j == 3){
		//ボスの座標
		ene_count = 1;
		b.vs(p, game_map, game_main, ene_count, j);
	}
}
//dungeonの表示
void Dungeon::show_dungeon(Player p[])
{
	for(int ry = 0; 20 > ry; ry++)
	{
		for(int rx = 0; 20 > rx; rx++)
		{
			dungeon[ry][rx] = play_dungeon[ry][rx];
		}
	}

	this->dungeon[p[0].x1][p[0].y1] = 5;

	for(int dy = 0; 20 > dy; dy++)
	{
		for(int dx = 0;20 > dx;dx++)
		{
			switch(dungeon[dy][dx])
			{
				case 8: cout << "＋"; break;
				case 0: cout << "　"; break;
				case 1: cout << "　"; break;
				case 2: cout << "　"; break;
				case 3: cout << "　"; break;
				case 4: cout << "岩"; break;
				case 5: cout << "主"; break;
				case 6: cout << "Ａ"; break;
				case 7: cout << "Ｂ"; break;
				
			}		
		}
		cout << endl;
	}	
}
//dungeonの当たり判定
void Dungeon::dungeon_collision(Player p[])
{	
	if(this->dungeon[p[0].x1][p[0].y1] == 8 || this->dungeon[p[0].x1][p[0].y1] == 4)
	{
		output("障害物に当たりました");
		p[0].x1 = p[0].x2;
		p[0].y1 = p[0].y2;
	}
}
//dungeonに入る
void Dungeon::dungeon_main(Player p[], Game_map game_map, Game_main game_main)
{	
	int j;
	//入り口Aから入った時
	if(game_main.judge_dungeon == 1){
		p[0].x1 = 1;
		p[0].y1 = 1;
		p[0].x2 = p[0].x1;
		p[0].y2 = p[0].y1;
	}
	//入り口Bから入った時
	else if(game_main.judge_dungeon == 2){
		p[0].x1 = 17;
		p[0].y1 = 18;
		p[0].x2 = p[0].x1;
		p[0].y2 = p[0].y1;
	}
	//dungeonの表示
	this->show_dungeon(p);

	//ダンジョンに入っている間
	while(game_main.judge_dungeon == 1 || game_main.judge_dungeon == 2)
	{
		//playerの移動
		p[0].move_player(&p);
		//dungeon内の当たり判定
		this->dungeon_collision(p);

		p[0].x2 = p[0].x1;
		p[0].y2 = p[0].y1;
		j = dungeon[p[0].x1][p[0].y1];//

		//エンカウント判定
		this->encount(p,game_map,game_main,j);

		this->show_dungeon(p);
		//ダンジョン入り口Aから出る場合
		if(this->play_dungeon[p[0].x1][p[0].y1] == 6)
		{
			p[0].x1 = 7;
			p[0].y1 = 11;
			p[0].x2 = p[0].x1;
			p[0].y2 = p[0].y1;
			game_main.judge_dungeon = 0;
		}
		//ダンジョン入り口Bから出る場合
		else if(this->play_dungeon[p[0].x1][p[0].y1] == 7)
		{
			p[0].x1 = 12;
			p[0].y1 = 18;
			p[0].x2 = p[0].x1;
			p[0].y2 = p[0].y1;
			game_main.judge_dungeon = 0;
		}
	}
}