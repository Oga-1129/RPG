#include <iostream>
#include <string>
#include "rpg.h"

using namespace std;

void City::city_main(Player p[], Game_main* game_main)
{
	while(game_main->judge_city == 1){
		output("どこに行きますか？" );
		output("1 よろず屋");
		output("2 宿屋");
		output("3 教会");
		output("4 街を出る");

		cin >> choice;

		switch(choice)
		{
			case 1: shop    (p, game_main); break;
			case 2: inn     (p, game_main); break;
			case 3: church  (p, game_main); break;
			case 4: out_city(p, game_main); break;
		}
	}
}

//よろず屋での行動
void City::shop(Player p[], Game_main* game_main)
{
	output("1 買う");
	output("2 店を出る");

	cin >> choice;

	//買う場合
	if(choice == 1)
	{
		cout << "現在の所持金は" << p[0].gold << "Ｇです" << endl;
		output("1 武器");
		output("2 防具");
		output("3 魔法");
		output("4 アイテム");
		output("5 戻る" );

		cin >> choice;

		switch(choice)
		{
			case 1://武器
				output("1 ひのきの棒     100G" );
				output("2 銅の剣         500G" );
				output("3 ドラゴンの杖    200G");
				output("4 エクスカリバー 2000G");
				output("5 戻る");

				cin >> choice;

				switch(choice)
				{
					case 1 :if(p[0].gold < 100)
							{
								output("お金が足りない・・・");
								shop(p, game_main);
							}break;
					case 2 : if(p[0].gold < 500)
							{
								output("お金が足りない・・・");
								shop(p, game_main);
							}break;
					case 3 : if(p[0].gold < 200)
							{
								output("お金が足りない・・・");
								shop(p, game_main); 
							}break;
					case 4 : if(p[0].gold < 2000)
							{
								output("お金が足りない・・・");
								shop(p, game_main);
							}break;
				}

				if(choice < 5)
				{
					int check;
					output("それを買うかい? 1 はい 2 いいえ");
					cin >> check;
					if(check == 2)
					{
						shop(p, game_main);
					}

				}
				switch(choice)
				{
					//ヒノキの棒
					case 1: output("誰が装備するんだい?");
							output("1" + p[0].NAME); 
							output("2" + p[1].NAME); 
							output("3" + p[2].NAME);
							output("4" + p[3].NAME);
							output("5　やめる");

							cin >> choice;

							switch(choice)
							{
								case 1: p[0].weapon_name[0] = "ひのきの棒";
										p[0].weapon_performance[0] = 3;
										p[0].gold -= 100;
										output("ありがとよ！"); break;

								case 2: p[1].weapon_name[0] = "ひのきの棒";
										p[1].weapon_performance[0] = 3;
										p[0].gold -= 100;
										output("ありがとよ！") ; break;

								case 3: if(p[2].weapon_name[0] == "ドラゴンの杖")
										{
											p[2].MAX_MP -= 10;
										}
										p[2].weapon_name[0] = "ひのきの棒";
										p[2].weapon_performance[0] = 3;
										p[0].gold -= 100;
										output("ありがとよ！") ; break;

								case 4: if(p[3].weapon_name[0] == "ドラゴンの杖")
										{
											p[3].MAX_MP -= 10;
										}
										p[3].weapon_name[0] = "ひのきの棒";
										p[3].weapon_performance[0] = 3;
										p[0].gold -= 100;
										output("ありがとよ！") ; break;

								case 5: output("やめる");
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;

							}
							 break;

					//銅の剣
					case 2: output("誰が装備するんだい?") ;
							output("1" + p[0].NAME) ; 
							output("2" + p[1].NAME) ; 
							output("3　やめる") ;

							cin >> choice;

							switch(choice)
							{
								case 1: p[0].weapon_name[0] = "銅の剣";
										p[0].weapon_performance[0] = 6;
										p[0].gold -= 500;
										output("ありがとよ！") ; break;

								case 2: p[1].weapon_name[0] = "銅の剣";
										p[1].weapon_performance[0] = 6;
										p[0].gold -= 500;
										output("ありがとよ！") ; break;

								case 3: output("やめる");
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;

							}
							break;
					//ドラゴンの杖
					case 3: output("誰が装備するんだい?");
							output("1" + p[2].NAME) ;
							output("2" + p[3].NAME) ;
							output("3　やめる");

							cin >> choice;

							switch(choice)
							{
								case 1: if(p[2].weapon_name[0] == "ドラゴンの杖"){
											p[2].MAX_MP -= 10;
										}
										p[2].weapon_performance[0] = 1;
										p[0].gold -= 200;
										p[2].MAX_MP += 10;
										output("ありがとよ！") ; break;

								case 2: if(p[3].weapon_name[0] == "ドラゴンの杖"){
											p[3].MAX_MP -= 10;
										}
										p[3].weapon_performance[0] = 1;
										p[0].gold -= 200;
										p[3].MAX_MP += 10;
										output("ありがとよ！") ; break;

								case 3: output("やめる");
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;

							}
							break;
					//エクスカリバー
					case 4: output("誰が装備するんだい?");
							output("1" + p[0].NAME) ; 
							output("2" + p[1].NAME) ; 

							cin >> choice;

							switch(choice)
							{
								case 1: p[0].weapon_name[0] = "エクスカリバー";
										p[0].weapon_performance[0] = 20;
										p[0].gold -= 2000;
										output("ありがとよ！") ; break;

								case 2: p[1].weapon_name[0] = "エクスカリバー";
										p[1].weapon_performance[0] = 20;
										p[0].gold -= 2000;
										output("ありがとよ！") ; break;

								case 3: output( "やめる");
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;

							}
							break;
					//戻る
					case 5: shop(p, game_main); break;
				}break;	
			//防具			
			case 2:
				output("1 布の服     　　　60G");
				output("2 銅の鎧         300G");
				output("3 ドラゴンローブ   120G") ;
				output("4　ドラゴンメイル 1200G") ;
				output("5 戻る") ;

				cin >> choice;


				switch(choice)
				{
					case 1 : if(p[0].gold < 60)
							{
								output("お金が足りない・・・") ;
								shop(p, game_main);
							}break;
					case 2 : if(p[0].gold < 300)
							{
								output("お金が足りない・・・") ;
								shop(p, game_main);
							}break;
					case 3 : if(p[0].gold < 120)
							{
								output("お金が足りない・・・") ;
								shop(p, game_main); 
							}break;
					case 4 : if(p[0].gold < 1200)
							{
								output("お金が足りない・・・") ;
								shop(p, game_main);
							}break;
				}

				if(choice < 5)
				{
					int check;
					output("それを買うかい? 1 はい 2 いいえ") ;
					cin >> check;
					if(check == 2)
					{
						shop(p, game_main);
					}

				}
				switch(choice)
				{
					//布の服
					case 1: output("誰が装備するんだい?");
							output("1" + p[0].NAME); 
							output("2" + p[1].NAME); 
							output("3" + p[2].NAME);
							output("4" + p[3].NAME);
							output("5　やめる") ;

							cin >> choice;

							switch(choice)
							{
								case 1: p[0].armor_name[0] = "布の服";
										p[0].armor_performance[0] = 1;
										p[0].gold -= 60;
										output("ありがとよ！") ; break;

								case 2: p[1].armor_name[0] = "布の服";
										p[1].armor_performance[0] = 1;
										p[0].gold -= 60;
										output("ありがとよ！") ; break;

								case 3: if(p[2].armor_name[0] == "ドラゴンのローブ")
										{
											p[2].MAX_MP -= 10;
										}
										p[2].armor_name[0] = "布の服";
										p[2].armor_performance[0] = 1;
										p[0].gold -= 60;
										output("ありがとよ！") ; break;

								case 4: if(p[3].armor_name[0] == "ドラゴンローブ")
										{
											p[3].MAX_MP -= 10;
										}
										p[3].armor_name[0] = "布の服";
										p[3].armor_performance[0] = 1;
										p[0].gold -= 60;
										output("ありがとよ！") ; break;

								case 5: output("やめる") ;
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;

							}
							break;
					//銅の鎧
					case 2: output("誰が装備するんだい?");
							output("1" + p[0].NAME) ; 
							output("2" + p[1].NAME) ; 
							output("3　やめる") ;

							cin >> choice;

							switch(choice)
							{
								case 1: p[0].armor_name[0] = "銅の鎧";
										p[0].armor_performance[0] = 5;
										p[0].gold -= 300;
										output("ありがとよ！") ; break;

								case 2: p[1].armor_name[0] = "銅の鎧";
										p[1].armor_performance[0] = 5;
										p[0].gold -= 300;
										output("ありがとよ！") ; break;

								case 3: output("やめる") ;
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;

							}
							break;
					//ドラゴンローブ
					case 3: output("誰が装備するんだい?") ;
							output("1" + p[2].NAME) ;
							output("2" + p[3].NAME) ;
							output("3　やめる") ;

							cin >> choice;

							switch(choice)
							{
								case 1: if(p[2].armor_name[0] == "ドラゴンローブ"){
											p[2].MAX_MP -= 10;
										}
										p[2].armor_performance[0] = 3;
										p[0].gold -= 120;
										p[2].MAX_MP += 10;
										output("ありがとよ！") ; break;

								case 2: if(p[3].armor_name[0] == "ドラゴンローブ"){
											p[3].MAX_MP -= 10;
										}
										p[3].armor_performance[0] = 3;
										p[0].gold -= 120;
										p[3].MAX_MP += 10;
										output("ありがとよ！") ; break;

								case 3: output("やめる") ;
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;
							}
							break;
					//エクスカリバー
					case 4: output("誰が装備するんだい?") ;
							output("1" + p[0].NAME) ; 
							output("2" + p[1].NAME) ; 

							cin >> choice;

							switch(choice)
							{
								case 1: p[0].armor_name[0] = "ドラゴンメイル";
										p[0].armor_performance[0] = 20;
										p[0].gold -= 2000;
										output("ありがとよ！") ; break;

								case 2: p[1].armor_name[0] = "ドラゴンメイル";
										p[1].armor_performance[0] = 20;
										p[0].gold -= 2000;
										output("ありがとよ！") ; break;

								case 3: output("やめる") ;
									    shop(p, game_main); break;

								default:
										output("正しい値を入力してください。やり直してください");
										shop(p, game_main); break;
							}
					break;
					//戻る
					case 5: shop(p, game_main); break;
				}
				break;
			//魔法
			case 3:
				 output("1 ケアル　 400Ｇ");
				 output("2 レイズ　1000Ｇ");
				 output("3 メラ　　 200Ｇ");
				 output("4 イオ　　 400Ｇ");
				 output("0 戻る");

				 cin >> choice;

				 switch(choice)
				 {
				 	case 1: if(p[0].gold < 400){ 
				 				output("お金が足りない・・・");
				 				shop(p, game_main);
				 			}
				 			if(p[3].magic_name[0] == "ケアル"){
				 				output("すでに覚えています");
				 				shop(p, game_main);
				 			}
							p[3].magic_name[0] = "ケアル";
				 			p[0].gold -= 400;
				 			output("白魔導師はケアルを覚えた！");
				 			output("ありがとよ！"); break;

				 	case 2: if(p[0].gold < 1000){
				 				output("お金が足りない・・・");
				 				shop(p, game_main);
				 			}
				 			if(p[3].magic_name[1] == "レイズ"){
				 				output("すでに覚えています");
				 				shop(p, game_main);
				 			}
							p[3].magic_name[1] = "レイズ";
				 			p[0].gold -= 1000;
				 			output("白魔導師はレイズを覚えた！");
				 			output("ありがとよ！"); break;

				 	case 3: if(p[2].magic_name[0] == "メラ"){
				 				output("すでに覚えています");
				 				shop(p, game_main);
				 			}
							p[2].magic_name[0] = "メラ";
				 			p[0].gold -= 200;
				 			output("黒魔導師はメラを覚えた！");
				 			output("ありがとよ！"); break;

				 	case 4: if(p[2].magic_name[1] == "イオ"){
				 				output("すでに覚えています");
				 				shop(p, game_main);
				 			}
				 			p[2].magic_name[1] = "イオ";
				 			p[0].gold -= 400;
				 			output("黒魔導師はイオを覚えた！");
				 			output("ありがとよ！"); break;
				 }
				 break;
			//アイテム
			case 4:
				  output("1 薬草       80G") ;
				  output("2 エーテル  160G") ;
				  output("3 戻る") ;
				  cin >> choice;
				  switch(choice)
				  {
				  	//薬草
				  	case 1: if(p[0].gold < 80)
				  			{
				  				output("お金が足りない・・・") ;
				  				shop(p, game_main);
				  			}
				  			output("薬草を買いますか?1 はい 2いいえ") ;
				  			cin >> choice;

				  			switch(choice)
				  			{
				  				case 1: p[0].gold -= 80;
				  						p[0].item[0] += 1;
				  						output("ありがとよ！") ; 
				  						cout << "現在の薬草の数は"<< p[0].item[0] << "個です。"<< endl;
				  						break; 
				  			}
				  			break;
				  	//エーテル
				  	case 2: if(p[0].gold < 160)
				  			{
				  				output("お金が足りない・・・") ;
				  				shop(p, game_main);
				  			}
				  			output("エーテルを買いますか?1 はい 2いいえ") ;
				  			cin >> choice;
				  			switch(choice)
				  			{
				  				case 1: p[0].gold -= 160;
				  						p[0].item[1] += 1;
				  						output("ありがとよ！") ; 
										cout << "現在のエーテルの数は"<< p[0].item[1] << "個です。"<< endl;
										break; 
				  			}
				  			break;

				  	default:
							output("正しい値を入力してください。やり直してください");
							shop(p, game_main); break;
				  }
			case 5: shop(p, game_main); break;
		}
	}
	//店を出る場合
	else if(choice == 2){
		city_main(p, game_main);
	}
}

//宿屋での行動
void City::inn(Player p[], Game_main* game_main)
{
	output("いらっしゃいませ") ;
	cout << p[0].gold << endl;
	output("1 休む　50Ｇ") ;
	output("2 宿屋を出る") ;

	cin >> choice;

	if(choice == 1)
	{
		if(p[0].gold >= 50)
		{
			p[0].gold -= 50;
			for(int i = 0; i < 4; i++){
				if(p[i].DEAD == 1)
				{
					p[i].HP = p[i].MAX_HP;
					p[i].MP = p[i].MAX_MP;
				}
			}
			output( "HPとMPが回復しました。");
			output("昨晩はよくお休みになりました?") ;
			output("それでは行ってらっしゃいませ！") ;
			city_main(p, game_main);
		}else{
			output("お金が足りない・・・") ; 
		}
	}else if(choice == 2)
	{
		city_main(p, game_main);
	}else{
		output("正しい値を入力してください。");
	}
}

//教会での行動
void City::church(Player p[], Game_main* game_main)
{
	output("ようこそおいでくださいました") ;
	//誰か死んでいる場合
	if(p[0].DEAD == 0 || p[1].DEAD == 0 || p[2].DEAD == 0 || p[3].DEAD == 0)
	{
		cout << p[0].gold <<  "Ｇ" << endl;
		output("1 生き返らせる 1人 100Ｇ") ;
		output("2 生き返らせない") ;

		cin >> choice;

		//蘇生
		if(choice == 1)
		{
			int j = 0;
			int G = 0;
			if(p[0].gold >= 100)
			{
				for(int i = 0; i < 4 ; i++)
				{
					if(p[i].DEAD == 0)
					{
						j++;
						G = j * 100;
						cout << j * 100 <<  "Ｇです。" << endl;
						if(p[0].gold >= G)
						{
							for(int i = 0; i < 4; i++)
							{
								if(p[i].DEAD == 0)
								{
									p[i].HP = p[i].MAX_HP;
									p[i].DEAD = 1;
								}
								game_main->judge_goal -= G;
								output("死んでいた仲間が生き返った") ;
								output("あまり無茶をしてはいけませんよ") ;
								city_main(p, game_main);
							}
						}else{
							output("お金が足りない・・・") ;
							output("教会を後にした") ; 
							city_main(p, game_main);
						}
					}
				}
			
			}else{
				output("お金が足りない・・・") ;
				output("教会を後にした") ;
				city_main(p, game_main); 
			}
		}
	}else{
		output("今は教会に用はない") ;
		city_main(p, game_main);
	}
}

//街から出る
void City::out_city(Player p[], Game_main* game_main)
{
	output("街を出ました") ;
	p[0].y1 -= 1; 
	game_main->judge_city = 0;
}