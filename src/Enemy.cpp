#include <iostream>
#include <string>
#include "rpg.h"

using namespace std;

Enemy::Enemy(string e_name, int e_hp, int e_mp, int e_ap, int e_dp, int e_dead, int e_hit, int Gold, int dp)
{
	NAME = e_name;
	HP = e_hp;
	MP = e_mp;
	MAX_HP = e_hp;
	MAX_MP = e_mp;
	AP = e_ap;
	DP = e_dp;
	DEAD = e_dead;
	HIT = e_hit;
	drop_gold = Gold;
	drop_probability = dp;
};