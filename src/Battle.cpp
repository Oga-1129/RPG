#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "rpg.h"

using namespace std;

void Magic_cheack(Player p[], string str ,int x ,int& i, int m_num)
{
	cout << i;
	if(p[m_num].magic_name[x] == str)
	{
		output(str);
		i++;
	}else{
		output("");
		i++;
	}
}

void player_behavior(Player p[], Enemy e[], Game_main game_main, Battle b, int encount, int& clear, int group , int i, int j, int ene_hp[], int ene_dead[]);

//攻撃計算
void attackcheack(Player p[], Enemy e[],  int choice, int clear, int j, int group, int ene_hp[], int ene_dead[])
{
	int damage = 0;
	switch(group)
	{
		case 1:
		{
			output(p[clear].NAME + "の攻撃");
			int hit = rand() % 101;
			if(p[clear].HIT < hit)
			{
				//ダメージ計算
				damage = (p[clear].AP + p[clear].weapon_performance[0]) - e[j].DP;
				if(damage > 0){
					ene_hp[choice] -= damage; 
				}else{
					damage = 0;
				}
				cout << e[j].NAME << choice << "に" << damage << "のダメージ" << endl;

				cout << ene_hp[choice] << endl;

				//敵が倒れたかの判定
				if(ene_hp[choice] <= 0)
				{
					ene_hp[choice] = 0;
					output(e[j].NAME + "が倒れた");
					ene_dead[choice]= 0;
				}else{
					
				}
			}else{
				output("攻撃が外れた");
			}
		}
		break;

		case 2:
		{
			if(ene_dead[j] == 1){
				//攻撃先が倒れていた場合
				bool e_at;
				int t;
				output(e[j].NAME + "の攻撃");//敵
				while(e_at == false){
					t = rand() % 4;
					if(p[t].DEAD == 1){
						e_at = true;
					}
				}
				int hit = rand() % 101;
				if(e[clear].HIT < hit)
				{
					p[t].HP -= e[clear].AP - (p[t].DP + p[t].armor_performance[0]);
					cout << p[t].NAME << "に" << e[clear].AP - (p[t].DP + p[t].armor_performance[0]) << "ダメージ" << endl;
					//味方が倒れたかの判定
					if(p[t].HP <= 0)
					{
					  	p[t].DEAD = 0;
					  	output(p[t].NAME + "が倒れた");
					}
				}else{
					output("攻撃が外れた");
				}
			}
		}
		break;
	}
}

//魔法ダメージ計算
void magiccheack(Player p[], Enemy e[], int  j, int encount ,int clear, int choice, int m_choice, int ene_hp[], int ene_dead[])
{

	switch(m_choice)
	{
		case 1:
		{
			output(p[clear].NAME + "のメラ");
			ene_hp[choice] -= 8;
			cout << e[choice].NAME << choice << "に8ダメージ" << endl;
			p[clear].MP -= 8;
			cout << ene_hp[choice] << endl;
			cout << p[clear].MP << "/" << p[clear].MAX_MP << endl;
			if(ene_hp[choice] <= 0)
			{
				ene_dead[choice] = 0;
				cout << e[j].NAME << choice << "が倒れた" << endl;
			}
		}
		break;

		case 2:
		{
			output("黒魔道士のイオ");
			p[clear].MP -= 8;
			int m_num = 0;

			cout << p[clear].MP << "/" << p[clear].MAX_MP << endl;
			while(m_num < encount)
			{
				if(ene_dead[m_num] == 1)
				{
					ene_hp[m_num] -= 4;
					cout << e[j].NAME << m_num << "に4ダメージ" << endl;
					if(ene_hp[m_num] <= 0)
					{
						cout << e[j].NAME << m_num << "が倒れた" << endl;
						ene_dead[m_num]= 0;
					}
				}
				m_num++;
			}
		}
		break;
	}
}

void Battle::heal_caluculation(Player p[] , Game_main game_main,int cheack, int battle_choice, int& clear)
{
	switch(cheack)//1が薬草 2がエーテル　3がケアル 4がレイズ
	{
		case 1: output("薬草を使用した");
				output(p[battle_choice - 1].NAME + "のHPが30回復した");
				p[battle_choice - 1].HP += 30;
				if(p[battle_choice - 1].HP > p[battle_choice - 1].MAX_HP)
				{
					p[battle_choice - 1].HP = p[battle_choice - 1].MAX_HP;
				}
				p[0].item[0] -= 1;
				break;

		case 2: output("エーテルを使用した");
				output(p[battle_choice - 1].NAME + "のMPが20回復した");
				p[battle_choice-1].MP += 20;
				if(p[battle_choice-1].MP > p[battle_choice-1].MAX_MP)
				{
					p[battle_choice-1].MP = p[battle_choice-1].MAX_MP;
				}
				p[0].item[1] -= 1;
				break;

		case 3: output("ケアルを使用した");
				output(p[battle_choice-1].NAME + "のHPが30%回復した");
				p[battle_choice-1].HP += p[battle_choice-1].HP * 0.3;
				if(p[battle_choice-1].HP > p[battle_choice-1].MAX_HP)
				{
					p[battle_choice-1].HP = p[battle_choice-1].MAX_HP;
				}
				break;

		case 4: output("レイズを使用した");
				output(p[battle_choice-1].NAME + "が蘇生した");
				p[battle_choice-1].HP += p[battle_choice-1].MAX_HP;
				p[battle_choice-1].DEAD = 1;
		        break;
	}
}

void Battle::Attack(Player p[], Enemy e[], Game_main game_main, Battle b, int encount, int clear, int group, int j ,int ene_hp[], int ene_dead[])
{
	srand(time(NULL));
	int battle_choice;

	// 1が味方　2が敵
	switch(group)
	{
		case 1:
		{
			bool attack_tg_e;
			while(attack_tg_e == false){
				output("攻撃対象を選択してください");//味方
				for(int i = 0; encount > i; i++)
				{
					cout << i << " ";
					if(ene_dead[i] != 0){
					   	output(e[j].NAME);
					}else{
						output("");
					}
				}
				cin >> battle_choice;
				if(battle_choice >= 0 && battle_choice < encount)
				{
					if(ene_dead[battle_choice] == 1){
						attack_tg_e = true;
						attackcheack(p, e, battle_choice, clear, j, group , ene_hp, ene_dead);
					}else{
						attack_tg_e = false;
						output("すでに倒れています。");
					}
				}else{
					output("敵がいません。");
				}
			}
		}
		break;

		case 2:
		{
			battle_choice = 0;
			attackcheack(p, e, battle_choice, clear, j, group,  ene_hp, ene_dead);		
		}
		break;
	}
}

void Battle::Magic(Player p[], Enemy e[], Game_main game_main, Battle b, int encount, int clear, int group,int j, int ene_hp[], int ene_dead[])
{
	if(p[0].NAME == p[clear].NAME || p[1].NAME == p[clear].NAME)
	{
		cout << p[clear].NAME << "は魔法を唱えられません" << endl;
		b.player_behavior(p, e,  game_main,  b,  encount,  clear,  group,  j, ene_hp, ene_dead);
	}
	int m_num;
	int battle_choice;
	string str;
	int x;
	if(p[2].NAME == p[clear].NAME)
	{
		if(clear == 2){
			m_num = 2;
			int i = 1;
			output("使用する魔法を選択してください");
			str = "メラ";
			x = 0;
			Magic_cheack(p, str , x, i, m_num);
			str = "イオ";
			x = 1;
			Magic_cheack(p, str , x, i, m_num);
			cout << i << "戻る" << endl;
			int m_choice;
			cin >> m_choice;
			if(p[2].MP > 8){
				switch(m_choice)
				{
					case 1:
						output("攻撃対象を選択してください");
						for(int i = 0; encount > i; i++)
						{
						   	cout << i ;
						   	if(ene_dead[j] == 1)
						   	{
								output(e[j].NAME);
							}else{
								output("");
							}
						}
						cin >> battle_choice;
						if(battle_choice < encount){
							magiccheack(p, e, j, encount ,clear, battle_choice, m_choice, ene_hp, ene_dead);
						}else{
							output("正しい値を入力してください");
						}
						break;

					case 2:
						magiccheack(p, e, j, encount ,clear, battle_choice, m_choice, ene_hp, ene_dead);
						break;

					case 3:
						player_behavior(p,  e, game_main , b, encount, clear, group,  j,  ene_hp,  ene_dead);
						break;

					default:
						output("正しい値を入力してください");
						Magic(p, e, game_main, b, encount, clear, group, j, ene_hp, ene_dead);
						break;
				}
			}else{
				output("MPが足りません");
				player_behavior(p,  e, game_main , b, encount, clear, group,  j,  ene_hp,  ene_dead);
			}
		}
	}

	if(p[3].NAME == p[clear].NAME)
	{
		output("使用する魔法を選択してください");
		int cheack = 3;
		m_num = 3;
		str = "ケアル";
		x = 0;
		int i = 1;
		Magic_cheack(p, str , x, i, m_num);
		str = "レイズ";
		x = 1;
		Magic_cheack(p, str , x, i, m_num);
		cout << i << "戻る" << endl;
		cin >> battle_choice;

		switch(battle_choice)
		{
			case 1:
			{
				output("対象を選択してください");
				int t = 1;
				for(int h = 0; h < 4; h++)
				{
					cout << t;
					if(p[h].DEAD == 1)
					{							
						cout << p[h].NAME;					
					}
					t++;
					cout << endl;
				}
					
				cin >> battle_choice;

				switch(battle_choice)
				{
					case 1:
					{ 
						this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
						break; 
					}
					case 2: 
					{
						this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
						break;
					}
					case 3: 
					{
						this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
						break;
					}
					case 4:
					{
						this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
						break;
					}
				}
			}break;

			case 2:
			{ 
				output("対象を選択してください");
				int o = 1;
				cheack += 1;
				for(int h = 0; h < 3; h++)
				{
					cout << o;
					if(p[h].DEAD == 0)
					{							
						cout << p[h].NAME;					
					}
					o++;
					cout << endl;
				}
					
				cin >> battle_choice;

				switch(battle_choice)
				{
					case 1:
						this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
						break;

					case 2:
						this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
						break;

					case 3:
						this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
						break;
				}
			}break;

			case 3:
				player_behavior(p,  e, game_main , b, encount, clear, group,  j,  ene_hp,  ene_dead);
				break;
		}
	}		
}

void Battle::Item(Player p[] , Enemy e[], Game_main game_main, Battle b, int encount, int clear,  int group,  int j, int ene_hp[], int ene_dead[])
{
	int battle_choice;
	cout << "1 薬草 	 " << p[0].item[0] << endl;
	cout << "2 エーテル 	" << p[0].item[1] << endl;
	output( "3 戻る");
	cin >> battle_choice;
	int cheack = 1;
	switch(battle_choice)
	{
		case 1: 
			if(p[0].item[0] == 0){
				output("持ってません");
				cout << clear << endl;
				player_behavior(p,  e, game_main , b, encount, clear, group,  j,  ene_hp,  ene_dead);
				break;
			}
			for(int i = 0; i < 4; i++)
			{
				cout << i + 1 << " " << p[i].NAME << "	HP" << p[i].HP << "/" << p[i].HP << endl;
			}
			output("5 戻る");

			cin >> battle_choice;

			switch(battle_choice)
			{
				case 1:
					this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
					break;

				case 2:
					this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
					break;

				case 3:
					this->heal_caluculation(p, game_main, cheack, battle_choice, clear); 
					break;

				case 4:
					this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
					break;

				case 5:
					Item(p, e, game_main, b, encount, clear, group,j , ene_hp, ene_dead);
					break;
			}
			break;

		case 2: 
			cheack = 2; 
			if(p[0].item[1] == 0){
				output("持ってません");
				cout << clear << endl;
				b.player_behavior(p, e, game_main, b, clear, encount, group,j, ene_hp, ene_dead);//Player全員行動
				break;
			}
			for(int i = 0; i < 4; i++)
			{
				cout << i + 1 << p[i].NAME << "	MP" << p[i].MP << "/" << p[i].MP << endl;
			}
			output("5	戻る");

			cin >> battle_choice;

			switch(battle_choice)
			{
				case 1: 
					this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
					break;

				case 2: 
					this->heal_caluculation(p, game_main, cheack, battle_choice, clear);
					break;

				case 3:
					this->heal_caluculation(p, game_main,cheack, battle_choice, clear);
					break;

				case 4:
					this->heal_caluculation(p, game_main,cheack, battle_choice, clear);
					break;

				case 5:
					Item(p, e, game_main, b, encount, clear, group, j, ene_hp, ene_dead);
					break;
			}
			break;
		case 3:
			player_behavior(p,  e, game_main , b, encount, clear, group,  j,  ene_hp,  ene_dead);
			break;
	}
}

void Battle::player_behavior(Player p[], Enemy e[], Game_main game_main , Battle b, int encount, int clear, int group, int j, int ene_hp[], int ene_dead[])
{
	while(clear < 4){
		if(p[clear].DEAD == 1){
			cout << "HP" << p[clear].HP << endl;
			cout << p[clear].NAME << "の行動選択" << endl;
			output("1 攻撃");
			output("2 魔法");
			output("3 アイテム");

			cin >> battle_choice;

			switch(battle_choice)
			{
				case 1: 
					Attack(p, e, game_main, b, encount, clear, group,j ,ene_hp, ene_dead); 
					clear +=1;
					break;
				case 2:  
					Magic(p, e, game_main, b, encount, clear, group,j, ene_hp, ene_dead);
					clear +=1;
					break;
				case 3:   
					Item(p, e, game_main, b, encount, clear, group,j, ene_hp, ene_dead); 
					clear +=1;
					break;
			}	
					
		}
		else{
			clear +=1;
		}
		if(ene_dead[0] == 0 && ene_dead[1] == 0 && ene_dead[2] == 0 && ene_dead[3] == 0){
			clear = 4;
		}
	}
}

void Battle::enemy_behavior( Player p[], Enemy e[], Game_main game_main , Battle b, int encount, int group, int j, int ene_hp[], int ene_dead[])
{
	int clear = 0;
	for(int i = 0; i < encount; i++)
	{
		if(ene_dead[i] == 1)
		{
			Attack(p, e, game_main, b, encount, clear, group, j, ene_hp, ene_dead);
		}
		if(p[0].DEAD == 0 && p[1].DEAD == 0 && p[2].DEAD == 0 && p[3].DEAD == 0){
			i = encount;
		}
	}
}

void Battle::result(Player p[] , Enemy e[], int encount, int j , int result)
{
	if(result == 0){
		if(encount == 1){
			output("魔物を倒した。");
		}else{
			output("魔物の群れを倒した。");
		}
		p[0].gold += e[j].drop_gold*encount;
		cout << e[j].drop_gold*encount << "G手に入れた"<< endl;
	}else{
		output("全滅した");
		p[0].gold /= 2;
	}

}

void Battle::vs(Player p[], Game_map game_map, Game_main game_main, int encount, int j)
{
	srand(time(NULL));
	Battle b;
	int result = 0;
	int ene_hp[encount];
	int ene_ap[encount];
	int ene_dp[encount];
	int ene_dead[encount];
	Enemy e[4] = {Enemy("スライム", 15, 0, 20, 1, 1, 60, 50, 1),
				  Enemy("ゴブリン", 18, 0, 30, 3, 1, 65, 70, 15),
				  Enemy("ドラキー", 21, 0, 40, 5, 1, 70, 150, 25),
				  Enemy("ミニドラゴン", 300, 0, 50, 7, 1, 75, 0, 0)
				};

	cout << e[j].NAME << "が" << encount << "体現れた" << endl;

	cout << "バトルの開始" << endl;

	int i = 0;
	while(encount > i)
	{
		ene_hp[i] = e[j].HP;
		ene_ap[i] = e[j].AP;
		ene_dp[i] = e[j].DP;
		ene_dead[i] = e[j].DEAD; 
		i++;  
	}
	while(i < 4){
		ene_dead[i] = 0; 
		i++;
	}
	int group = 0;
	//全滅していない時
	while(game_main.dead_end == 0)
	{
		group = 1;
		int clear = 0;
		//Player全員行動
		b.player_behavior(p, e, game_main, b, encount, clear, group, j, ene_hp, ene_dead);
		if(ene_dead[0] == 0 && ene_dead[1] == 0 && ene_dead[2] == 0 && ene_dead[3] == 0){
			//敵の全滅
			game_main.dead_end = 1;
			b.result(p, e, encount, j, result);
		}
		group += 1;
		//Enemy全員行動
		b.enemy_behavior(p, e, game_main, b, encount, group, j, ene_hp, ene_dead);
		if(p[0].DEAD == 0 && p[1].DEAD == 0 && p[2].DEAD == 0 && p[3].DEAD == 0){
			p[0].x1 = 4;
			p[0].y1 = 4;
			result = 1;
			b.result(p, e, encount, j, result);
			game_main.judge_dungeon = 0; 
			for(int i = 0; i < 4; i++)
			{
				p[i].HP = p[i].MAX_HP;
				p[i].DEAD = 1;
			}
			game_main.start_up(p, e,game_main);
		}
	}
}