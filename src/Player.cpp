#include <iostream>
#include <string>
#include "rpg.h"

using namespace std;

Player::Player(string name, int hp, int mp, int ap, int dp, int dead, int hit, int x1 , int y1)
{
	NAME = name;
	HP = hp;
	MP = mp;
	MAX_HP = HP;
	MAX_MP = MP;
	AP = ap;
	DP = dp;
	DEAD = dead;
	HIT = hit;
	x2 = x1;
	y2 = y1;
	gold = 800;
	item[0] = 0;
	item[1] = 0;
}

void Player::move_player(Player* p[])
{
	int w;
	cout << "移動します。（4左 6右 8上 2下)：" ;
	cin >> w;
	switch(w)
	{
		case 4: this->y1 -= 1; break; //左に
		case 6: this->y1 += 1; break; //右に
		case 8: this->x1 -= 1; break; //上に
		case 2: this->x1 += 1; break; //下に
	}
	cout << endl;
}
