//rpgのヘッダファイル(関数宣言)
#include <iostream>
#include <string>


using namespace std;

void output( string str);

//playerクラスのメンバ関数の宣言
class Character
{	
	public:
		string NAME; 
		int MAX_HP;
		int MAX_MP;
		int HP;
		int AP;
		int DP;
		int MP;
		int DEAD;
		int HIT;
};

//Player4人分のステータスと武器・防具・魔法のステータスを持つクラス
class Player : public Character
{
	public:
		Player(string name, int hp, int mp, int ap, int dp, int dead, int hit, int x1, int y1);
		string weapon_name[4];
		string armor_name[4];
		string magic_name[4];
		int gold;
	    int item[2];
		int weapon_performance[4];
		int armor_performance[4];
		int x1;
		int y1;
		int x2;
		int y2;
		void move_player(Player* p[]);
};

class Enemy : public Character
{
	public:
		int drop_items;
		int drop_gold;
		string shape;
		int drop_probability;
		Enemy(string e_name, int e_hp, int e_mp, int e_ap, int e_dp,  int e_dead, int e_hit, int Gold, int dp);
};

class Dungeon;

class Battle;

class Game_main;

class Game_map
{
	public:
		int map[20][30];
		int play_map[20][30];
		int player_coordinate[2];
		Game_map();
		//mapを表示させる
		void show_map(Player p[]);
		//mapの当たり判定
		void map_collision(Player p[]);
		void map_main(Player p[], Game_map game_map, Game_main game_main);
};

class Game_main
{
	public:
		int dead_end;
		int judge_goal;
		int judge_city;
		int judge_dungeon;
		Game_main();
		void start_up(Player p[], Enemy e[], Game_main game_main);
};


class Dungeon
{
	public:
		int dungeon[20][20];
		int play_dungeon[20][20];
		int player_coordinate[2][2];
		int enemy_count;
		Dungeon();
		//エンカウントの判定
		void encount(Player p[], Game_map game_map,Game_main game_main, int j);
		//dungeonの表示
		void show_dungeon(Player p[]);
		//dungeonの当たり判定
		void dungeon_collision(Player p[]);
		//dungeonに入る
		void dungeon_main(Player p[], Game_map game_map,Game_main game_main);
};



class City
{
	public:
		int choice;
		void shop(Player p[],Game_main* game_main);
		void inn(Player p[], Game_main* game_main);
		void church(Player p[], Game_main* game_main);
		void out_city(Player p[], Game_main* game_main);
		void city_main(Player p[], Game_main* game_main);
};

class Battle
{
	public:
		int damage;
		int battle_choice;
		int result_herbs;
		int result_gold;
		int heal;
		void damage_calculation();
		void accuracy_caluculation();
		void Attack(Player p[] , Enemy e[], Game_main game_main, Battle b, int encount, int clear,  int group, int j, int ene_hp[], int ene_dead[]);
		void Magic(Player p[] , Enemy e[], Game_main game_main, Battle b, int encount, int clear,  int group, int j, int ene_hp[], int ene_dead[]);
		void Item(Player p[] , Enemy e[], Game_main game_main, Battle b, int encount, int clear,  int group, int j , int ene_hp[], int ene_dead[]);
		void player_behavior(Player p[], Enemy e[], Game_main game_main , Battle b, int encount, int clear, int group, int j, int ene_hp[], int ene_dead[]);
		void enemy_behavior(Player p[], Enemy e[], Game_main game_main ,  Battle b, int encount, int j, int c, int ene_hp[], int ene_dead[]);
		void vs(Player p[], Game_map game_map, Game_main game_main, int encount, int j);
		void result(Player p[] , Enemy e[], int encount, int j, int result);
		void heal_caluculation(Player p[], Game_main game_main,int cheack, int battle_choice, int& clear);
		void drop();
};




//playerの移動
void move_player(Player* p[]);

//ドロップの確率
void drop_probability();

//Game_mapクラスのメンバ関数の宣言
//playerの座標を得る
int get_Coordinate(int mx, int my);
//mapを表示させる
void show_map(Player p[]);
//mapの当たり判定
void map_collision(Player p);
void map_main(Player p[], Enemy e[], Game_map game_map,Game_main* game_main);


//Game_mainクラスのメンバ関数
void start_up(Player p[], Game_map game_map, Dungeon dungeon, Game_main game_main, Battle battle);


//Dungeonクラスのメンバ関数の宣言
//playerの座標を得る
int get_Coordinate();
//エンカウントの計算
void encount(Player p[],Game_main, int j);
//dungeonの表示
void show_dungeon(Player p[]);
//dungeonの当たり判定
void dungeon_collision(Player p[]);
//dungeonに入る
void dungeon_main(Player p[],Game_map game_map,Game_main game_main);


//Cityクラスのメンバ関数の宣言
//よろず屋
void shop(Player p[], Game_main game_main);
//宿屋
void inn(Player p[],Game_main game_main);
//教会
void church(Player p[],Game_main game_main);
//街を出る
void out_city(Player p[], Game_main game_main);
//街に入る
void city_main(Player p[], Game_main game_main);

//Battleクラスのメンバ関数の宣言
//ダメージ計算
void damage_calculation();
//命中処理
void accuracy_caluculation();

void Attack(Player p[] , Enemy e[], Game_main game_main, Battle b, int encount, int clear,  int group, int j, int ene_hp[], int ene_dead[]);
void Magic(Player p[] , Enemy e[], Game_main game_main, Battle b, int encount, int clear,  int group, int j, int ene_hp[], int ene_dead[]);
void Item(Player p[] , Enemy e[], Game_main game_main, Battle b, int encount, int clear,  int group, int j, int ene_hp[], int ene_dead[]);

//playerの行動
void player_behavior(Player p[], Enemy e[]);
//enemyの行動
void enemy_behavior(Enemy e[], Player p[], int encount, int j);
//戦闘の流れ
void vs(Player p[], Game_map game_map, Game_main game_main, int encount, int j);
//リザルト
void result(int encount);
//回復計算
void heal_caluculation();
//ドロップ計算
void drop();
