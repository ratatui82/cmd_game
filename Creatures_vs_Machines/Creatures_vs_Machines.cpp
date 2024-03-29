
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
using namespace std;

	//initializing global variables, because it`s easier to use global variables when you deal with functions
int player_HP = 100; //hp points
int player_EP = 50; //energy points
int enemy_HP = 100;
int enemy_EP = 50;
int EP_charge_rate = 6;
int max_HP = 100;
int max_EP = 50;
int mix_HP = 0;
int min_EP = 0;

int normal_attack_dmg = 5;
int special_attack_dmg = 16;
int normal_attack_EP = 10;
int special_attack_EP = 25;
int dogde_EP = 7;
int re_cahrge_EP_cahrge_rate = 4;

int update_hit_chance_normal_attack_player;
int update_miss_chance_normal_attack_player;
int update_hit_chance_special_attack_player;
int update_miss_chance_special_attack_player;
int dogde_hit_chance_normal_attack_player;
int dogde_miss_chance_normal_attack_player;
int dogde_hit_chance_special_attack_player;
int dogde_miss_chance_special_attack_player;
char did_the_player_use_dogde;
char did_the_player_use_re_charge;

int update_hit_chance_normal_attack_enemy;
int update_miss_chance_normal_attack_enemy;
int update_hit_chance_special_attack_enemy;
int update_miss_chance_special_attack_enemy;
int dogde_hit_chance_normal_attack_enemy;
int dogde_miss_chance_normal_attack_enemy;
int dogde_hit_chance_special_attack_enemy;
int dogde_miss_chance_special_attack_enemy;
char did_the_enemy_use_dogde;
char did_the_enemy_use_re_charge;

char player_plays_or_quits; //a char that hold the decision of the player whether he want to continue playing or quit 
//char player_replays_or_quits; //holds the decision if the player whants to play again after the game has ended
char player_choice; //char that holds the players choice of action move
char player_choice_1 = '1'; //i used magical numbers in the char variables, because it`s easier to change them later on
char player_choice_2 = '2'; //if i want them to be letters instead of numbers
char player_choice_3 = '3';
char player_choice_4 = '4';
char player_choice_5 = '5';

//player
//this variable calculates the hit chance for the normal attack
//we know that 80% out of 5 (because 5 is the dmg of the normal attack) is 4. So the numbers that x >= 1 && x <= 4 are hit
int successful_hit_attack_player = (80 / 100) * normal_attack_dmg;
//and for the miss chance we have that 20 % 5 = 1. So we have 2 options for the miss numbers - 0 and 1
int its_a_miss_attack_player = (20 / 100) * normal_attack_dmg;
//i have more explenation in the funtions body
int hit_chance_attack_player(int& hit_chance_attack_player);
int miss_chance_attack_player(int& miss_chance_attack_player);

//same for the special attack, but here we have 50% to 50% chance. 50 % 16 = 8 , so i decided to split the numbers in half
//the numbers x >= 1 && x <= 4 are hit
int successful_hit_special_attack_player = (50 / 100) * special_attack_dmg;
// and the numbers x >= 5 && x <= 8 are miss. More explenation in the functions body
int its_a_miss_special_attack_player = (50 / 100) * special_attack_dmg;
int hit_chance_special_attack_player(int& hit_chance_speical_attack_player);
int miss_chance_special_attack_player(int& miss_chance_special_attack_player);

//we know that the re-charge action move gives +10% hit chance to the other player
//now the hit chance for the normal attack has changed. 90 % 5 = 4.5 (but i am using int so it`s rounded to 5, and that`s how i want it to be
//so for the hit numbers we have x > 1 && x <= 5
int successful_hit_re_charge_attack_player = (90 / 100) * normal_attack_dmg; // +10%
//because we have that 10 % 5 = 0.5 ( again rounded to 1). So the miss number is 1. That`s why the hit numbers must start form 2
int its_a_miss_re_charge_attack_player = (10 / 100) * normal_attack_dmg;
//more explenations in the functions body
int hit_chance_re_charge_attack_player(int& hit_chance_re_charge_attack_player);
int miss_chance_re_charge_attack_player(int& miss_chance_re_charge_attack_player);

//it`s the same for the special attack, but here 60 % 16 = 10 (9.6). So the hit numbers are x >= 6 && x <= 10
int successful_hit_re_charge_special_attack_player = (60 / 100) * special_attack_dmg; // +10%
//and the miss numbers are x >= 1 && x <= 4
int its_a_miss_re_charge_special_attack_player = (40 / 100) * special_attack_dmg;
//more expelantions in the functions body
int hit_chance_re_charge_special_attack_player(int& hit_chance_re_charge_special_attack_player);
int miss_chance_re_charge_special_attack_player(int& miss_chance_re_charge_special_attack_player);

//the dogde attack move takes -30% hit chance. So now we have 50 % 5 = 3 (2.5) and the hit numbers are x >= 0 && x <= 1
int successful_hit_dogde_attack_player = (50 / 100) * normal_attack_dmg; // -30%, = 8
int hit_chance_dogde_attack_player(int& hit_chance_dogde_attack_player);
int miss_chance_dogde_attack_player(int& miss_chance_dogde_attack_player);
//and the miss numbers are x >= 2 && x <= 3
int its_a_miss_dogde_attack_player = (50 / 100) * normal_attack_dmg; // -30%, = 8
int hit_chance_dogde_attack_player(int& hit_chance_dogde_attack_player);
int miss_chance_dogde_attack_player(int& miss_chance_dogde_attack_player);

//for the special attack we have 20 & 16 = 1 (1.25). So the hit numbers are x >= 0 && x <= 1
int successful_hit_dogde_special_attack_player = (20 / 100) * special_attack_dmg; // -30%, = 8
int hit_chance_dogde_special_attack_player(int& hit_chance_dogde_attack_player);
int miss_chance_dogde_special_attack_player(int& miss_chance_dogde_attack_player);
//and the for the miss numbers we have 80 & 16 = 13. So x >= 2 && x <= 13. More explenations in the functions body
int its_a_miss_dogde_special_attack_player = (80 / 100) * special_attack_dmg; // -30%, = 8
int hit_chance_dogde_special_attack_player(int& hit_chance_dogde_special_attack_player);
int miss_chance_dogde_special_attack_player(int& miss_chance_dogde_special_attack_player);

//enemy
//same logic
int successful_hit_attack_enemy = (80 / 100) * normal_attack_dmg;
int its_a_miss_attack_enemy = (20 / 100) * normal_attack_dmg;
int hit_chance_attack_enemy(int& hit_chance_attack_enemy);
int miss_chance_attack_enemy(int& miss_chance_attack_enemy);

int successful_hit_special_attack_enemy = (50 / 100) * special_attack_dmg;
int its_a_miss_special_attack_enemy = (50 / 100) * special_attack_dmg;
int hit_chance_special_attack_enemy(int& hit_chance_special_attack_enemy);
int miss_chance_special_attack_enemy(int& miss_chance_special_attack_enemy);

int successful_hit_re_charge_attack_enemy = (90 / 100) * normal_attack_dmg; // +10%
int its_a_miss_re_charge_attack_enemy = (10 / 100) * normal_attack_dmg;
int hit_chance_re_charge_attack_enemy(int& hit_chance_re_charge_attack_enemy);
int miss_chance_re_charge_attack_enemy(int& miss_chance_re_charge_attack_enemy);

int successful_hit_re_charge_special_attack_enemy = (60 / 100) * special_attack_dmg; // +10%
int its_a_miss_re_charge_special_attack_enemy = (40 / 100) * special_attack_dmg;
int hit_chance_re_charge_special_attack_enemy(int& hit_chance_re_charge_special_attack_enemy);
int miss_chance_re_charge_special_attack_enemy(int& miss_chance_re_charge_special_attack_enemy);

int successful_hit_dogde_attack_enemy = (50 / 100) * normal_attack_dmg; // -30%
int hit_chance_dogde_attack_enemy(int& hit_chance_dogde_attack_enemy);
int miss_chance_dogde_attack_enemy(int& miss_chance_dogde_attack_enemy);

int its_a_miss_dogde_attack_enemy = (50 / 100) * normal_attack_dmg; // -30%, = 8
int hit_chance_dogde_attack_enemy(int& hit_chance_dogde_attack_enemy);
int miss_chance_dogde_attack_enemy(int& miss_chance_dogde_attack_enemy);

int successful_hit_dogde_special_attack_enemy = (20 / 100) * special_attack_dmg; // -30%, = 8
int hit_chance_dogde_special_attack_enemy(int& hit_chance_dogde_attack_enemy);
int miss_chance_dogde_special_attack_enemy(int& miss_chance_dogde_attack_enemy);

int its_a_miss_dogde_special_attack_enemy = (80 / 100) * special_attack_dmg; // -30%, = 8
int hit_chance_dogde_special_attack_enemy(int& hit_chance_dogde_special_attack_enemy);
int miss_chance_dogde_special_attack_enemy(int& miss_chance_dogde_special_attack_enemy);

//attack moves list
void list_of_action_moves();

//player
//all of the functions with the players action moves
int attack_1_player(int& update_enemy_HP, int& update_player_EP);
int special_attack_2_player(int& update_enemy_HP, int& update_player_EP);
int re_charge_player_3(int& update_player_EP);
int dogde_player_4(int& update_player_EP);
int heal_5_player(int& update_player_EP, int& update_player_HP);

//enemy
//all of the functions with the enemys action moves
int attack_1_enemy(int& update_player_HP, int& update_enemy_EP);
int special_attack_2_enemy(int& update_player_HP, int& update_enemy_EP);
int re_charge_enemy_3(int& update_enemy_EP);
int dogde_enemy_4(int& update_enemy_EP);
int heal_5_enemy(int& update_enemy_EP, int& update_enemy_HP);

int main()
{
	cout << "                                      Welcome to Creatures vs Machines" << endl;
	cout << "" << endl;
	cout << "The rules of the game are:" << endl;
	cout << "   Both you and the enemy will take turns and choose what action to take per turn." << endl;
	cout << "   You are controling a creature and you have to defeate your PC!" << endl;
	cout << "   Your creature has " << player_HP << "HP and " << player_EP << "EP " << "and the enemy has " << enemy_HP << "HP and " << enemy_EP << "EP" << endl;
	cout << "   The EP charging rate is " << EP_charge_rate << " per turn. You can not exceed starting EP" << endl;
	cout << "   When you use Heal, you can not exceed starting HP. After you use this action is still your turn!" << endl;
	cout << "" << endl;
	cout << "Continue playing or quit (c/q): ";
	cin >> player_plays_or_quits;

	if (player_plays_or_quits == 'c') //continue
	{
		cout << "" << endl;
		while (enemy_HP > 0)
		{
			if (player_HP > 0)
			{
				list_of_action_moves();
				cout << "\nStats: " << player_HP << "HP, " << player_EP << "EP" << endl;
				cout << "Make your move: ";
				cin >> player_choice;

				//player choice of moves
				if (player_choice == player_choice_1) //normal attack
				{
					if (player_EP >= normal_attack_EP) //checks if the player has enough EP to make the move
					{
						if (did_the_enemy_use_re_charge != player_choice_3) // i need to make this check because when re-charge or dogde is used
						{//the values for the miss and hit chance are different and one if satement wont do the logic
							hit_chance_attack_player(successful_hit_attack_player);
							miss_chance_attack_player(its_a_miss_attack_player);

							if (update_hit_chance_normal_attack_player >= 1 && update_hit_chance_normal_attack_player <= 4)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_player(enemy_HP, player_EP);
								cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
							}
							//if not throws a miss message
							else if (update_miss_chance_normal_attack_player == 0 || update_miss_chance_normal_attack_player == 1)
							{
								cout << "Sorry your target was too swift and you missed your attack." << endl;
							}
							cout << "" << endl;
						}
						else if (did_the_enemy_use_re_charge == player_choice_3)
						{
							hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
							miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

							if (update_hit_chance_normal_attack_player >= 2 && update_hit_chance_normal_attack_player <= 5)
								//here i need the rand to be between 1-2 (1>rand<2)
							{	//because it would overlay with the other if statements
								attack_1_player(enemy_HP, player_EP);
								cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
							}
							//if not throws a miss message
							else if (update_miss_chance_normal_attack_player <= 1)
							{
								cout << "Sorry your target was too swift and you missed your attack." << endl;
							}
						}
						else if (did_the_enemy_use_dogde != player_choice_4) //again checking for the dogde
						{
							hit_chance_attack_player(successful_hit_attack_player);
							miss_chance_attack_player(its_a_miss_attack_player);//first calls a function to calculate the hit chance
							//checks is the players hit chance is in the range for the attack to be successful
							if (update_hit_chance_normal_attack_player >= 1 && update_hit_chance_normal_attack_player <= 4)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_player(enemy_HP, player_EP);
								cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
							}
							//if not throws a miss message
							else if (update_miss_chance_normal_attack_player == 0 || update_miss_chance_normal_attack_player == 1)
							{
								cout << "Sorry your target was too swift and you missed your attack." << endl;
							}
							cout << "" << endl;
						}
						else if (did_the_enemy_use_dogde == player_choice_4)
						{
							hit_chance_dogde_attack_player(successful_hit_attack_player);
							miss_chance_dogde_attack_player(its_a_miss_attack_player);

							if (update_hit_chance_normal_attack_player >= 1 && update_hit_chance_normal_attack_player <= 2)
								//here i need the rand to be between 1-2 (1>rand<2)
							{	//because it would overlay with the other if statements
								attack_1_player(enemy_HP, player_EP);
								cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
							}
							//if not throws a miss message
							else if (update_miss_chance_normal_attack_player >= 0 && update_miss_chance_normal_attack_player <= 1)
							{
								cout << "Sorry your target was too swift and you missed your attack." << endl;
							}
						}
					}
					else if (player_EP < normal_attack_EP) //and if the player doesnt have enought EP to make that move it asks him to make another one
					{
						cout << "Sorry, not enough EP! Make another move: ";
						cin >> player_choice;
						cout << "" << endl;
					}
				}
				else if (player_choice == player_choice_2) //special attack
				{
						if (player_EP >= special_attack_EP)
						{
							if (did_the_enemy_use_re_charge != player_choice_3) //same check for the special attack
							{
								hit_chance_special_attack_player(successful_hit_special_attack_player);
								miss_chance_special_attack_player(its_a_miss_special_attack_player);

								if (update_hit_chance_special_attack_player >= 1 && update_hit_chance_special_attack_player <= 4)
									//here i need the rand to be between 1-4 (1>rand<4)
								{	//because it would overlay with the other if statements
									special_attack_2_player(enemy_HP, player_EP);
									cout << "You did " << special_attack_dmg << " damage to the enemy" << endl;
								}
								//if not throws a miss message
								else if (update_miss_chance_special_attack_player == 0 || update_miss_chance_special_attack_player == 1)
								{
									cout << "Sorry your target was too swift and you missed your attack." << endl;
								}
								cout << "" << endl;
							}
							else if (did_the_enemy_use_re_charge == player_choice_3)
							{
								hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
								miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

								if (update_hit_chance_special_attack_player >= 1 && update_hit_chance_special_attack_player <= 6)
								{
									special_attack_2_player(enemy_HP, player_EP);
									cout << "You did " << special_attack_dmg << " damage to the enemy" << endl;
									cout << "" << endl;
								}
								else if (update_miss_chance_special_attack_player >= 7 && update_miss_chance_special_attack_player <= 10)
								{
									cout << "Sorry your target was too swift and you missed your attack." << endl;
								}
							}
							else if (did_the_enemy_use_dogde != player_choice_4)
							{
								hit_chance_special_attack_player(successful_hit_special_attack_player);
								miss_chance_special_attack_player(its_a_miss_special_attack_player);

								if (update_hit_chance_special_attack_player >= 1 && update_hit_chance_special_attack_player <= 4)
									//here i need the rand to be between 1-4 (1>rand<4)
								{	//because it would overlay with the other if statements
									special_attack_2_player(enemy_HP, player_EP);
									cout << "You did " << special_attack_dmg << " damage to the enemy" << endl;
								}
								//if not throws a miss message
								else if (update_miss_chance_special_attack_player == 0 || update_miss_chance_special_attack_player == 1)
								{
									cout << "Sorry your target was too swift and you missed your attack." << endl;
								}
								cout << "" << endl;
							}
							else if (did_the_enemy_use_dogde == player_choice_4)
							{
								hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
								miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

								if (update_hit_chance_special_attack_player >= 0 && update_hit_chance_special_attack_player <= 4)
									//here i need the rand to be between 1-4 (1>rand<4)
								{	//because it would overlay with the other if statements
									special_attack_2_player(enemy_HP, player_EP);
									cout << "You did " << special_attack_dmg << " damage to the enemy" << endl;
								}
								//if not throws a miss message
								else if (update_miss_chance_normal_attack_player >= 5 && update_miss_chance_normal_attack_player <= 13)
								{
									cout << "Sorry your target was too swift and you missed your attack." << endl;
								}
							}
						}
					
					else //and if the player doesnt have enought EP to make that move it asks him to make another one
					{
						cout << "Sorry, not enough EP!";
						cout << "" << endl;
					}
				}
				else if (player_choice == player_choice_3) //re-charge
				{
					did_the_player_use_re_charge = player_choice_3;
					re_charge_player_3(player_EP);

					hit_chance_re_charge_attack_enemy(successful_hit_re_charge_attack_enemy);
					miss_chance_re_charge_attack_enemy(its_a_miss_re_charge_attack_enemy);

					hit_chance_re_charge_special_attack_enemy(successful_hit_re_charge_special_attack_enemy);
					miss_chance_re_charge_special_attack_enemy(its_a_miss_re_charge_special_attack_enemy);

					cout << "You used re-charge!" << endl;
					cout << "" << endl;
				}
				else if (player_choice == player_choice_4) //dogde
				{
					if (player_EP >= dogde_EP) //checks the player EP
					{
						did_the_player_use_dogde  = player_choice_4;
						dogde_player_4(player_EP);

						hit_chance_dogde_attack_enemy(successful_hit_dogde_attack_enemy);
						miss_chance_dogde_attack_enemy(its_a_miss_dogde_attack_enemy);

						hit_chance_dogde_special_attack_enemy(successful_hit_dogde_special_attack_enemy);
						miss_chance_dogde_special_attack_enemy(its_a_miss_dogde_special_attack_enemy);

						cout << "You used dogde!" << endl;
						cout << "" << endl;
					}
					else //and if the player doesnt have enought EP to make that move it asks him to make another one
					{
						cout << "Sorry, not enough EP!";
						cout << "" << endl;
					}
				}
				else if (player_choice == player_choice_5) //heal
				{ //basically we make the heal move and then repeat the logic for the rest moves 
					if (player_EP != 0) //first checks if the player EP is not 0, because he hand trade half of 0 for HP
					{
						heal_5_player(player_EP, player_HP);
						cout << "New Stats: " << player_HP << "HP, " << player_EP << "EP" << endl;
						cout << "Make your next move. Choose between 1, 2, 3, 4: "; //then asks for the second move
						cin >> player_choice;

						//then repeats the logic of all the moves fo the second move
						if (player_choice == player_choice_1) // normal attack
						{
							if (player_EP >= normal_attack_EP)
							{
								if (did_the_enemy_use_re_charge != player_choice_3) // i need to make this check because when re-charge or dogde is used
								{//the values for the miss and hit chance are different and one if satement wont do the logic
									hit_chance_attack_player(successful_hit_attack_player);
									miss_chance_attack_player(its_a_miss_attack_player);

									if (update_hit_chance_normal_attack_player >= 1 && update_hit_chance_normal_attack_player <= 4)
										//here i need the rand to be between 1-4 (1>rand<4)
									{	//because it would overlay with the other if statements
										attack_1_player(enemy_HP, player_EP);
										cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
									}
									//if not throws a miss message
									else if (update_miss_chance_normal_attack_player == 0 || update_miss_chance_normal_attack_player == 1)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
									cout << "" << endl;
								}
								else if (did_the_enemy_use_re_charge == player_choice_3)
								{
									hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
									miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

									if (update_hit_chance_normal_attack_player >= 2 && update_hit_chance_normal_attack_player <= 5)
										//here i need the rand to be between 1-2 (1>rand<2)
									{	//because it would overlay with the other if statements
										attack_1_player(enemy_HP, player_EP);
										cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
									}
									//if not throws a miss message
									else if (update_miss_chance_normal_attack_player <= 1)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
								}
								else if (did_the_enemy_use_dogde != player_choice_4) //again checking for the dogde
								{
									hit_chance_attack_player(successful_hit_attack_player);
									miss_chance_attack_player(its_a_miss_attack_player);//first calls a function to calculate the hit chance
									//checks is the players hit chance is in the range for the attack to be successful
									if (update_hit_chance_normal_attack_player >= 1 && update_hit_chance_normal_attack_player <= 4)
										//here i need the rand to be between 1-4 (1>rand<4)
									{	//because it would overlay with the other if statements
										attack_1_player(enemy_HP, player_EP);
										cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
									}
									//if not throws a miss message
									else if (update_miss_chance_normal_attack_player == 0 || update_miss_chance_normal_attack_player == 1)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
									cout << "" << endl;
								}
								else if (did_the_enemy_use_dogde == player_choice_4)
								{
									hit_chance_dogde_attack_player(successful_hit_attack_player);
									miss_chance_dogde_attack_player(its_a_miss_attack_player);

									if (update_hit_chance_normal_attack_player >= 1 && update_hit_chance_normal_attack_player <= 2)
										//here i need the rand to be between 1-2 (1>rand<2)
									{	//because it would overlay with the other if statements
										attack_1_player(enemy_HP, player_EP);
										cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
									}
									//if not throws a miss message
									else if (update_miss_chance_normal_attack_player >= 0 && update_miss_chance_normal_attack_player <= 1)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
								}
								if (update_hit_chance_normal_attack_player >= 1 && update_hit_chance_normal_attack_player <= 4)
								{	//here i need the rand to be between 1-4 (1>rand<4)
									//because it would overlay with the other if statements
									attack_1_player(enemy_HP, player_EP);
									cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
								}
								else if (update_miss_chance_normal_attack_player == 0 || update_miss_chance_normal_attack_player == 0)
								{
									cout << "Sorry your target was too swift and you missed your attack." << endl;
								}
								cout << "" << endl;
							}
							else
							{
								cout << "Sorry, not enough EP!";
								cout << "" << endl;
							}
						}
						else if (player_choice == player_choice_2) //special attack
						{
							if (player_EP >= special_attack_EP)
							{
								if (did_the_enemy_use_re_charge != player_choice_3) //same check for the special attack
								{
									hit_chance_special_attack_player(successful_hit_special_attack_player);
									miss_chance_special_attack_player(its_a_miss_special_attack_player);

									if (update_hit_chance_special_attack_player >= 1 && update_hit_chance_special_attack_player <= 4)
										//here i need the rand to be between 1-4 (1>rand<4)
									{	//because it would overlay with the other if statements
										special_attack_2_player(enemy_HP, player_EP);
										cout << "You did " << special_attack_dmg << " damage to the enemy" << endl;
									}
									//if not throws a miss message
									else if (update_miss_chance_special_attack_player == 0 || update_miss_chance_special_attack_player == 1)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
									cout << "" << endl;
								}
								else if (did_the_enemy_use_re_charge == player_choice_3)
								{
									hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
									miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

									if (update_hit_chance_special_attack_player >= 1 && update_hit_chance_special_attack_player <= 6)
									{
										special_attack_2_player(enemy_HP, player_EP);
										cout << "You did " << special_attack_dmg << " damage to the enemy" << endl;
										cout << "" << endl;
									}
									else if (update_miss_chance_special_attack_player >= 7 && update_miss_chance_special_attack_player <= 10)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
								}
								else if (did_the_enemy_use_dogde != player_choice_4)
								{
									hit_chance_special_attack_player(successful_hit_special_attack_player);
									miss_chance_special_attack_player(its_a_miss_special_attack_player);

									if (update_hit_chance_special_attack_player >= 1 && update_hit_chance_special_attack_player <= 4)
										//here i need the rand to be between 1-4 (1>rand<4)
									{	//because it would overlay with the other if statements
										special_attack_2_player(enemy_HP, player_EP);
										cout << "You did " << special_attack_dmg << " damage to the enemy" << endl;
									}
									//if not checks if the rand is 0 or 1
									else if (update_miss_chance_special_attack_player == 0 || update_miss_chance_special_attack_player == 1)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
									cout << "" << endl;
								}
								else if (did_the_enemy_use_dogde == player_choice_4)
								{
									hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
									miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

									if (update_hit_chance_special_attack_player >= 0 && update_hit_chance_special_attack_player <= 4)
										//here i need the rand to be between 1-4 (1>rand<4)
									{	//because it would overlay with the other if statements
										special_attack_2_player(enemy_HP, player_EP);
										cout << "You did " << normal_attack_dmg << " damage to the enemy" << endl;
									}
									//if not throws a miss message
									else if (update_miss_chance_special_attack_player >= 5 && update_miss_chance_special_attack_player <= 13)
									{
										cout << "Sorry your target was too swift and you missed your attack." << endl;
									}
								}
							}
							else
							{
								cout << "Sorry, not enough EP!";
								cout << "" << endl;
							}
						}
						else if (player_choice == player_choice_3) //re-charge
						{
							did_the_player_use_re_charge = player_choice_3;
							re_charge_player_3(player_EP);

							hit_chance_re_charge_attack_enemy(successful_hit_re_charge_attack_enemy);
							miss_chance_re_charge_attack_enemy(its_a_miss_re_charge_attack_enemy);

							hit_chance_re_charge_special_attack_enemy(successful_hit_re_charge_special_attack_enemy);
							miss_chance_re_charge_special_attack_enemy(its_a_miss_re_charge_special_attack_enemy);

							cout << "" << endl;
							cout << "You used re-cahrge!" << endl;
						}
						else if (player_choice == player_choice_4) //dogde
						{
							if (player_EP >= dogde_EP)
							{
								did_the_player_use_dogde = player_choice_4;
								dogde_player_4(player_EP);

								hit_chance_dogde_attack_enemy(successful_hit_dogde_attack_enemy);
								miss_chance_dogde_attack_enemy(its_a_miss_dogde_attack_enemy);

								hit_chance_dogde_special_attack_enemy(successful_hit_dogde_special_attack_enemy);
								miss_chance_dogde_special_attack_enemy(its_a_miss_dogde_special_attack_enemy);

								cout << "You used dogde!" << endl;
							}
							else
							{
								cout << "Sorry, not enough EP!";
								cout << "" << endl;
							}
						}
						else if (player_choice == player_choice_5) //chek if the user input is correct, because he can`t use Heal again
						{
							cout << "Please make a legal move: ";
							cin >> player_choice;
						}
					}
					else // if the player doesnt have enough EP to trade throws a message and asks for another move
					{
						cout << "Stats: " << player_HP << "HP, " << player_EP << "EP" << endl;
						cout << "Not enought EP to trade for HP!";
					}
				}
				// enemy choice of moves   //normal attack
				//same logic for the moves               //just for fun 
				if (player_choice == player_choice_1 || player_choice == player_choice_4 || enemy_EP == normal_attack_EP) //it will make a normal attack when the player makes a normal attack
				{																						//also when the player used dogde, because the normal attack has a bigger hit chance
					if (enemy_EP >= normal_attack_EP) // if it has enough EP it will make the move
					{
						if (did_the_player_use_re_charge != player_choice_3)
						{
							hit_chance_attack_enemy(successful_hit_attack_enemy);
							miss_chance_attack_enemy(its_a_miss_attack_enemy);

							if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_enemy(player_HP, enemy_EP);
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_re_charge == player_choice_3)
						{
							hit_chance_re_charge_attack_enemy(successful_hit_re_charge_attack_enemy);
							miss_chance_re_charge_attack_enemy(its_a_miss_re_charge_attack_enemy);

							if (update_hit_chance_normal_attack_enemy >= 2 && update_hit_chance_normal_attack_enemy <= 5)
							{
								attack_1_enemy(player_HP, enemy_EP);
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy <= 1)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_dogde != player_choice_4)
						{
							hit_chance_attack_enemy(successful_hit_attack_enemy);
							miss_chance_attack_enemy(its_a_miss_attack_enemy);

							if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_enemy(player_HP, enemy_EP);
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_dogde == player_choice_4)
						{
							hit_chance_dogde_attack_enemy(successful_hit_dogde_attack_enemy);
							miss_chance_dogde_attack_enemy(its_a_miss_dogde_attack_enemy);
							
							if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 2)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_enemy(player_HP, enemy_EP);
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						cout << "" << endl;
					}
					else if (enemy_EP < normal_attack_EP && enemy_EP >= dogde_EP) // but if it doesnt it will use dogde, because dogde has 
						//the less cost of EP and if it doesnt even have 7 EP it will need to use re-charge
					{
						did_the_enemy_use_dogde = player_choice_4;
						dogde_enemy_4(enemy_EP);

						hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
						miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

						hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
						miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

						cout << "The enemy used dogde. Stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						cout << "" << endl;
						cout << "=======================================================================================================================";
					}
					else if (enemy_EP < dogde_EP) //otherwise it uses re-charge
					{
						did_the_enemy_use_re_charge = player_choice_3;
						re_charge_enemy_3(enemy_EP);

						hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
						miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

						hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
						miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

						cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						cout << "" << endl;
						cout << "=======================================================================================================================";
					}
				}
				//special attack
				else if (player_choice == player_choice_3 || player_HP <= special_attack_dmg)
					//it will use special attack when the player_HP is less or equel to 16, becuase it will kil the player in one move
					//or when the player had used re-charge, because that`s when it has bigger chance for a successful hit.
				{
					if (enemy_EP >= special_attack_EP) //checks for enough EP
					{
						if (did_the_player_use_re_charge != player_choice_3)
						{
							hit_chance_special_attack_enemy(successful_hit_special_attack_enemy);
							miss_chance_special_attack_enemy(its_a_miss_special_attack_enemy);

							if (update_hit_chance_special_attack_enemy >= 1 && update_hit_chance_special_attack_enemy <= 4)
							{
								special_attack_2_enemy(player_HP, enemy_EP);
								cout << "You took " << special_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_special_attack_enemy >= 5 && update_miss_chance_special_attack_enemy <= 8)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_re_charge == player_choice_3)
						{
							hit_chance_re_charge_special_attack_enemy(successful_hit_re_charge_special_attack_enemy);
							miss_chance_re_charge_special_attack_enemy(its_a_miss_re_charge_special_attack_enemy);

							if (update_hit_chance_special_attack_enemy >= 1 && update_hit_chance_special_attack_enemy <= 6)
							{
								special_attack_2_enemy(player_HP, enemy_EP);
								cout << "You took " << special_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_special_attack_enemy >= 7 && update_miss_chance_special_attack_enemy <= 10)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_dogde != player_choice_4)
						{
							hit_chance_special_attack_enemy(successful_hit_special_attack_enemy);
							miss_chance_special_attack_enemy(its_a_miss_special_attack_enemy);

							if (update_hit_chance_special_attack_enemy >= 1 && update_hit_chance_special_attack_enemy <= 4)
							{
								special_attack_2_enemy(player_HP, enemy_EP);
								cout << "You took " << special_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_special_attack_enemy >= 5 && update_miss_chance_special_attack_enemy <= 8)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_dogde == player_choice_4)
						{
							hit_chance_dogde_special_attack_enemy(successful_hit_dogde_special_attack_enemy);
							miss_chance_dogde_special_attack_enemy(its_a_miss_dogde_special_attack_enemy);

							if (update_hit_chance_special_attack_enemy >= 0 && update_hit_chance_special_attack_enemy <= 4)
							{
								special_attack_2_enemy(player_HP, enemy_EP);
								cout << "You took " << special_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_special_attack_enemy >= 5 && update_miss_chance_special_attack_enemy <= 13)
							{
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
					}
					//and if the enemy doesnt have enough EP, it just makes a normal attack
					else if (enemy_EP >= normal_attack_EP)
					{
						if (did_the_player_use_re_charge != player_choice_3)
						{
							hit_chance_attack_enemy(successful_hit_attack_enemy);
							miss_chance_attack_enemy(its_a_miss_attack_enemy);

							if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_enemy(player_HP, enemy_EP);
								cout << "" << endl;
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy == 1 || update_miss_chance_normal_attack_enemy == 0)
							{
								cout << "" << endl;
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_re_charge == player_choice_3)
						{
							hit_chance_re_charge_attack_enemy(successful_hit_re_charge_attack_enemy);
							miss_chance_re_charge_attack_enemy(its_a_miss_re_charge_attack_enemy);

							if (update_hit_chance_normal_attack_enemy >= 2 && update_hit_chance_normal_attack_enemy <= 5)
							{
								attack_1_enemy(player_HP, enemy_EP);
								cout << "" << endl;
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy <= 1)
							{
								cout << "" << endl;
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_dogde != player_choice_4)
						{
							hit_chance_attack_enemy(successful_hit_attack_enemy);
							miss_chance_attack_enemy(its_a_miss_attack_enemy);

							if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_enemy(player_HP, enemy_EP);
								cout << "" << endl;
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
							{
								cout << "" << endl;
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						else if (did_the_player_use_dogde == player_choice_4)
						{
							hit_chance_dogde_attack_enemy(successful_hit_dogde_attack_enemy);
							miss_chance_dogde_attack_enemy(its_a_miss_dogde_attack_enemy);

							if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 2)
								//here i need the rand to be between 1-4 (1>rand<4)
							{	//because it would overlay with the other if statements
								attack_1_enemy(player_HP, enemy_EP);
								cout << "" << endl;
								cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
								cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
							else if (update_miss_chance_normal_attack_enemy == 1)
							{
								cout << "" << endl;
								cout << "You predicted the future and saw the enemy`s attack!" << endl;
								cout << "" << endl;
								cout << "=======================================================================================================================";
							}
						}
						if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
							//here i need the rand to be between 1-4 (1>rand<4)
						{	//because it would overlay with the other if statements
							attack_1_enemy(player_HP, enemy_EP);
							cout << "" << endl;
							cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
							cout << "Enemy`s stats are: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
							cout << "" << endl;
							cout << "=======================================================================================================================";
						}
						else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
						{
							cout << "" << endl;
							cout << "You predicted the future and saw the enemy`s attack!" << endl;
							cout << "" << endl;
							cout << "=======================================================================================================================";
						}
						cout << "" << endl;
					}
					//but if it doesnt have enought EP it uses dogde, because normal attack cost 10EP and dogde costs 7EP
					else if (enemy_EP < normal_attack_EP && enemy_EP >= dogde_EP)
					{
						did_the_enemy_use_dogde = player_choice_4;
						dogde_enemy_4(enemy_EP);
					
						hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
						miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

						hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
						miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

						cout << "The enemy used dogde. Stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						cout << "" << endl;
						cout << "=======================================================================================================================";
					}
					else if (enemy_EP < normal_attack_EP && enemy_EP < dogde_EP) //but if enemy doesnt have enough EP for dogde
					{//it uses re-charge
						did_the_enemy_use_re_charge = player_choice_3;
						re_charge_enemy_3(enemy_EP);
					
						hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
						miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

						hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
						miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

						cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						cout << "" << endl;
						cout << "=======================================================================================================================";
					}
				}
				else if (enemy_EP == 0 || enemy_EP <= 20) //if it runs low on EP it uses re-charge
				{
					did_the_enemy_use_re_charge = player_choice_3;
					re_charge_enemy_3(enemy_EP);

					hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
					miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

					hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
					miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

					cout << "The enemy re-charged" << endl;
					cout << "New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
					cout << "" << endl;
					cout << "=======================================================================================================================";
				}
				//dogde
				else if (player_EP >= special_attack_EP && enemy_HP <= normal_attack_dmg || player_choice == player_choice_2) //it uses dogde the same time the player uses dogde just to make it a bit harder
				{
					if (enemy_EP >= dogde_EP) //checks for enought EP
					{
						did_the_enemy_use_dogde = player_choice_4;
						dogde_enemy_4(enemy_EP);

						hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
						miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

						hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
						miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

						cout << "The enemy used dogde. Stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						cout << "" << endl;
						cout << "=======================================================================================================================";
					}
					else if (enemy_EP < dogde_EP) // if it doesnt have enough EP for dogde it uses re-charge, because the dogde
						//move costs the less and there is nothing else of the enemy to do
					{
						did_the_enemy_use_re_charge = player_choice_3;
						re_charge_enemy_3(enemy_EP);
					
						hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
						miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

						hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
						miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);


						cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						cout << "" << endl;
						cout << "=======================================================================================================================";
					}
				}
				else if (enemy_HP <= special_attack_dmg) //second option for the enemy to use dogde
				{
					if (enemy_EP >= dogde_EP) //checks for enought EP
					{
						did_the_enemy_use_dogde = player_choice_4;
						dogde_enemy_4(enemy_EP);

						hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
						miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

						hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
						miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

						cout << "The enemy used dogde. Stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						cout << "" << endl;
						cout << "=======================================================================================================================";
					}
				}
				else if (enemy_EP < dogde_EP) // if it doesnt have enough EP for dogde it uses re-charge, because the dogde
											//move costs the less and there is nothing else of the enemy to do
				{
					did_the_enemy_use_re_charge = player_choice_3;
					re_charge_enemy_3(enemy_EP);

					hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
					miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

					hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
					miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

					cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
					cout << "" << endl;
					cout << "=======================================================================================================================";
				}
				else if (enemy_HP <= special_attack_dmg || enemy_HP <= normal_attack_dmg) //when is low on HP it heals
				{
					//same logic fo the moves after heal, because the enemy gets a second move
					if (enemy_EP != 1)
					{
						heal_5_enemy(enemy_EP, enemy_HP);
						cout << "The enemy used Heal! It`s stats are now: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
						//normal attack
						if (player_choice == player_choice_1 || enemy_EP == normal_attack_EP)
						{
							if (enemy_EP >= normal_attack_EP)
							{
								if (did_the_player_use_re_charge != player_choice_3)
								{
									hit_chance_attack_enemy(successful_hit_attack_enemy);
									miss_chance_attack_enemy(its_a_miss_attack_enemy);

									if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
									{
										attack_1_enemy(player_HP, enemy_EP);
										cout << "" << endl;
										cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
									else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
									{
										cout << "" << endl;
										cout << "You predicted the future and saw the enemy`s attack!" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
								}
								else if (did_the_player_use_re_charge == player_choice_3)
								{
									hit_chance_re_charge_attack_enemy(successful_hit_re_charge_attack_enemy);
									miss_chance_re_charge_attack_enemy(its_a_miss_re_charge_attack_enemy);

									if (update_hit_chance_normal_attack_enemy >= 2 && update_hit_chance_normal_attack_enemy <= 5)
									{
										attack_1_enemy(player_HP, enemy_EP);
										cout << "" << endl;
										cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
									else if (update_miss_chance_normal_attack_enemy <= 1)
									{
										cout << "" << endl;
										cout << "You predicted the future and saw the enemy`s attack!" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
								}
								else if (did_the_player_use_dogde != player_choice_4)
								{
									hit_chance_attack_enemy(successful_hit_attack_enemy);
									miss_chance_attack_enemy(its_a_miss_attack_enemy);

									if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
									{
										attack_1_enemy(player_HP, enemy_EP);
										cout << "" << endl;
										cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
									else if (update_miss_chance_normal_attack_enemy == 1 || update_miss_chance_normal_attack_enemy == 0)
									{
										cout << "" << endl;
										cout << "You predicted the future and saw the enemy`s attack!" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
									else if (did_the_player_use_dogde == player_choice_4)
									{
										hit_chance_dogde_attack_enemy(successful_hit_dogde_attack_enemy);
										miss_chance_dogde_attack_enemy(its_a_miss_dogde_attack_enemy);

										if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 2)
										{
											attack_1_enemy(player_HP, enemy_EP);
											cout << "" << endl;
											cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
											cout << "" << endl;
											cout << "=======================================================================================================================";
										}
										else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
										{
											cout << "" << endl;
											cout << "You predicted the future and saw the enemy`s attack!" << endl;
											cout << "" << endl;
											cout << "=======================================================================================================================";
										}
									}
									else if (enemy_EP < normal_attack_EP && enemy_EP >= dogde_EP)
									{
										did_the_enemy_use_dogde = player_choice_4;
										dogde_enemy_4(enemy_EP);
									
										hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
										miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

										hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
										miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

										cout << "The enemy used dogde. Stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
									else if (enemy_EP < dogde_EP)
									{
										did_the_enemy_use_re_charge = player_choice_3;
										re_charge_enemy_3(enemy_EP);

										hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
										miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

										hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
										miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

										cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
									cout << "" << endl;
								}
								//special attack
								else if (player_choice == player_choice_3 || player_choice == player_choice_2 || player_HP <= special_attack_dmg)
								{
									if (enemy_EP >= special_attack_EP)
									{
										if (did_the_enemy_use_re_charge != player_choice_3)
										{
											hit_chance_special_attack_enemy(successful_hit_special_attack_enemy);
											miss_chance_special_attack_enemy(its_a_miss_special_attack_enemy);

											if (update_hit_chance_special_attack_enemy >= 1 && update_hit_chance_special_attack_enemy <= 4)
											{
												special_attack_2_enemy(player_HP, enemy_EP);
												cout << "The enemy did a special attack and you took " << special_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_special_attack_enemy >= 5 && update_miss_chance_special_attack_enemy <= 8)
											{
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
										}
										else if (did_the_enemy_use_re_charge == player_choice_3)
										{
											hit_chance_re_charge_special_attack_enemy(successful_hit_re_charge_special_attack_enemy);
											miss_chance_re_charge_special_attack_enemy(its_a_miss_re_charge_special_attack_enemy);

											if (update_hit_chance_special_attack_enemy >= 1 && update_hit_chance_special_attack_enemy <= 6)
											{
												special_attack_2_enemy(player_HP, enemy_EP);
												cout << "The enemy did a special attack and you took " << special_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_special_attack_enemy >= 7 && update_miss_chance_special_attack_enemy <= 10)
											{
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
										}
										else if (did_the_player_use_dogde != player_choice_4)
										{
											if (update_hit_chance_special_attack_enemy >= 1 && update_hit_chance_special_attack_enemy <= 4)
											{
												special_attack_2_enemy(player_HP, enemy_EP);
												cout << "The enemy did a special attack and you took " << special_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_special_attack_enemy >= 5 && update_miss_chance_special_attack_enemy <= 8)
											{
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
										}
										else if (did_the_player_use_dogde == player_choice_4)
										{
											hit_chance_dogde_special_attack_enemy(successful_hit_dogde_special_attack_enemy);
											miss_chance_dogde_special_attack_enemy(its_a_miss_dogde_special_attack_enemy);

											if (update_hit_chance_special_attack_enemy >= 0 && update_hit_chance_special_attack_enemy <= 4)
											{
												special_attack_2_enemy(player_HP, enemy_EP);
												cout << "The enemy did a special attack and you took " << special_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_special_attack_enemy >= 5 && update_miss_chance_special_attack_enemy <= 13)
											{
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
										}
									}
									// if it doesnt have enough EP, it just makes a normal attack
									else if (enemy_EP >= normal_attack_EP)
									{
										if (did_the_player_use_re_charge != player_choice_3)
										{
											hit_chance_attack_enemy(successful_hit_attack_enemy);
											miss_chance_attack_enemy(its_a_miss_attack_enemy);

											if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
												//here i need the rand to be between 1-4 (1>rand<4)
											{	//because it would overlay with the other if statements
												attack_1_enemy(player_HP, enemy_EP);
												cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_normal_attack_enemy == 1)
											{
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_normal_attack_enemy == 0)
											{
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											cout << "" << endl;
										}
										else if (did_the_player_use_re_charge == player_choice_3)
										{
											hit_chance_re_charge_attack_enemy(successful_hit_re_charge_attack_enemy);
											miss_chance_re_charge_attack_enemy(its_a_miss_re_charge_attack_enemy);

											if (update_hit_chance_special_attack_enemy >= 1 && update_hit_chance_special_attack_enemy <= 4)
											{
												special_attack_2_enemy(player_HP, enemy_EP);
												cout << "The enemy did a special attack and you took " << special_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_special_attack_enemy == 1 && update_miss_chance_special_attack_enemy == 0)
											{
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
										}
										else if (did_the_player_use_dogde != player_choice_4)
										{
											hit_chance_attack_enemy(successful_hit_attack_enemy);
											miss_chance_attack_enemy(its_a_miss_attack_enemy);

											if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 4)
											{
												attack_1_enemy(player_HP, enemy_EP);
												cout << "" << endl;
												cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_normal_attack_enemy == 1 || update_miss_chance_normal_attack_enemy == 0)
											{
												cout << "" << endl;
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
										}
										else if (did_the_player_use_dogde == player_choice_4)
										{
											hit_chance_dogde_attack_enemy(successful_hit_dogde_attack_enemy);
											miss_chance_dogde_attack_enemy(its_a_miss_dogde_attack_enemy);

											if (update_hit_chance_normal_attack_enemy >= 1 && update_hit_chance_normal_attack_enemy <= 2)
											{
												attack_1_enemy(player_HP, enemy_EP);
												cout << "" << endl;
												cout << "The enemy did a basic attack and you took " << normal_attack_dmg << " damage" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
											else if (update_miss_chance_normal_attack_enemy == 0 || update_miss_chance_normal_attack_enemy == 1)
											{
												cout << "" << endl;
												cout << "You predicted the future and saw the enemy`s attack!" << endl;
												cout << "" << endl;
												cout << "=======================================================================================================================";
											}
										}
									}
									//but if it doesnt have enought EP it uses dogde, because normal attack cost 10EP and dogde costs 7EP
									else if (enemy_EP < normal_attack_EP && enemy_EP >= dogde_EP)
									{
										did_the_enemy_use_dogde = player_choice_4;
										dogde_enemy_4(enemy_EP);
									
										hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
										miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

										hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
										miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

										cout << "The enemy used dogde. Stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
										cout << "=======================================================================================================================";
									}
									else if (enemy_EP < dogde_EP) //but if enemy doesnt have enough EP for dogde
									{//it uses re-charge
										did_the_enemy_use_re_charge = player_choice_3;
										re_charge_enemy_3(enemy_EP);

										hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
										miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

										hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
										miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

										cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
										cout << "=======================================================================================================================";
									}
									cout << "" << endl;
								}
								//re-charge
								else if (enemy_EP == 0 || enemy_EP < normal_attack_EP)
								{
									did_the_enemy_use_re_charge = player_choice_3;
									re_charge_enemy_3(enemy_EP);

									hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
									miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

									hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
									miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

									cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
									cout << "=======================================================================================================================";
								}
								//dogde
								else if (player_EP >= special_attack_EP && enemy_HP <= normal_attack_dmg)
								{
									if (player_EP >= dogde_EP)
									{
										did_the_player_use_dogde = player_choice_4;
										dogde_enemy_4(enemy_EP);
									
										hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
										miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

										hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
										miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

										cout << "The enemy used dogde!" << endl;
										cout << "=======================================================================================================================";
									}
									//again if the enemy doesnt have enough EP for dogde it cant use anything else, because dogde costs the less
									else if (enemy_EP < dogde_EP) //so the only option it`s left with is re-charge
									{
										did_the_enemy_use_re_charge = player_choice_3;
										re_charge_enemy_3(enemy_EP);
								
										hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
										miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

										hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
										miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

										cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
										cout << "=======================================================================================================================";
									}
									else if (enemy_HP <= special_attack_dmg) //second option for the enemy to use dogde
									{
										if (enemy_EP >= dogde_EP) //checks for enought EP
										{
											did_the_enemy_use_dogde = player_choice_4;
											dogde_enemy_4(enemy_EP);
										
											hit_chance_dogde_attack_player(successful_hit_dogde_attack_player);
											miss_chance_dogde_attack_player(its_a_miss_dogde_attack_player);

											hit_chance_dogde_special_attack_player(successful_hit_dogde_special_attack_player);
											miss_chance_dogde_special_attack_player(its_a_miss_dogde_special_attack_player);

											cout << "The enemy used dogde. Stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
											cout << "" << endl;
											cout << "=======================================================================================================================";
										}
									}
									else if (enemy_EP < dogde_EP) // if it doesnt have enough EP for dogde it uses re-charge, because the dogde
																//move costs the less and there is nothing else of the enemy to do
									{
										did_the_enemy_use_re_charge = player_choice_3;
										re_charge_enemy_3(enemy_EP);
									
										hit_chance_re_charge_attack_player(successful_hit_re_charge_attack_player);
										miss_chance_re_charge_attack_player(its_a_miss_re_charge_attack_player);

										hit_chance_re_charge_special_attack_player(successful_hit_re_charge_special_attack_player);
										miss_chance_re_charge_special_attack_player(its_a_miss_re_charge_special_attack_player);

										cout << "The enemy re-charged. New stats: " << enemy_HP << "HP, " << enemy_EP << "EP" << endl;
										cout << "" << endl;
										cout << "=======================================================================================================================";
									}
								}
							}
						}
					}
				}
			}
			else if (player_HP <= 0)
			{
				cout << "" << endl;
				cout << "Oh, no you have died!" << endl;
				break;
			}
			
		}//end of while
		if (enemy_HP <= 0)
		{
			cout << "Congratulations you have defeated the Mother machine!" << endl;
		}
	}	
	else if (player_plays_or_quits == 'q')
	{
		cout << "" << endl;
		cout << "Sayonara :)" << endl;
	}
}



void list_of_action_moves(void)
{
	cout << " 1.Attak = 5 dmg, 80% hit chance, -" << normal_attack_EP << "EP" << endl;
	cout << " 2.Special attack = 16 dmg, 50% hit chance, -" << special_attack_EP  << "EP" << endl;
	cout << " 3.Re-charge = EP charging speed rate x4 (this turn only), Defence: -10%" << endl;
	cout << " 4.Dogde = Defence: +30%, EP charging rate: -50% (this turn only), -" << dogde_EP << "EP" << endl;
	cout << " 5.Heal = trade half of your EP for HP" << endl;
}
//functions for the hit for the atttack for the player
int hit_chance_attack_player(int& hit_chance_attack_player)
{
	//So to determin if the hit is successful
	//I get a random number between 1-4 and compare it with 4. If the random number is <= to 4 - its a hit.
	srand(time(0));
	hit_chance_attack_player = rand() % (5 - 1) + 1;
	update_hit_chance_normal_attack_player = hit_chance_attack_player;
	return hit_chance_attack_player, update_hit_chance_normal_attack_player;
}

int miss_chance_attack_player(int& miss_chance_attack_player)
{
//for the miss chance only 0 and 1 are the numbers that are a "miss"
//again i get a random number between 1-0 and type 2 "if" statements. If rand = 0 >> miss; If rand = 1 >> miss.
	srand(time(0));
	miss_chance_attack_player = rand() % (1 - 0) + 0;
	update_miss_chance_normal_attack_player = miss_chance_attack_player;
	return miss_chance_attack_player, update_miss_chance_normal_attack_player;
}

int hit_chance_special_attack_player(int& hit_chance_special_attack_player)
{
//here I make the same thing that i did with the "attack" move. The difference here is that we have 50% for success
//We have 8 for both a hit and a miss. So i decided to split the number in half.
//the numbers 1-4 are hit and the numbers 5-8 are miss. I take a random number x >= 1 && x <= 4. If the number is in this range its a hit
	srand(time(0));
	hit_chance_special_attack_player = rand() % (5 - 1) + 1;
	update_hit_chance_special_attack_player = hit_chance_special_attack_player;
	return hit_chance_special_attack_player, update_hit_chance_special_attack_player;
}

int miss_chance_special_attack_player(int& miss_chance_special_attack_player)
{
//and the numbers 5-8 are miss. Again i take a random number between 5-8 and if its x >= 5 && x <= 8 then it`s a miss
	srand(time(0));
	miss_chance_special_attack_player = rand() % (9 - 5) + 5;
	update_miss_chance_special_attack_player = miss_chance_special_attack_player;
	return miss_chance_special_attack_player, update_miss_chance_special_attack_player;
}

int hit_chance_re_charge_attack_player(int& hit_chance_re_charge_attack_player)
{   
//hit chance = 90%
//the re-charge move gives +10% hit chance to the enemy or the player, so the numbers for hit move with 1 up.
//so the hit chance numbers for the enemy become x > 1 && x <= 5. If the random numbers is between them its a hit
	srand(time(0));
	hit_chance_re_charge_attack_player = rand() % (6 - 2) + 2;
	update_hit_chance_normal_attack_player = hit_chance_re_charge_attack_player;
	return hit_chance_re_charge_attack_player, update_hit_chance_normal_attack_player;
}

int miss_chance_re_charge_attack_player(int& miss_chance_re_charge_attack_player)
{//miss chance = 10%
//the re-charge move gives +10% hit chance to the enemy or the player, so the numbers for miss move with 1 down.
//we have that 10 % 5 = 0.5 (1) . So simly the random numbers must be =1 for the attack to miss
	srand(time(0));
	miss_chance_re_charge_attack_player = rand() % (2 - 0) + 0;
	update_miss_chance_normal_attack_player = miss_chance_re_charge_attack_player;
	return miss_chance_re_charge_attack_player, update_miss_chance_normal_attack_player;
}

int hit_chance_re_charge_special_attack_player(int& hit_chance_re_charge_special_attack_player)
{//hit chance = 60% 
//the re-charge move gives +10% hit chance to the enemy or the player, so the numbers for hit move with 1 up.
//for the move to be a hit a get a random number x >= 1 && x <= 6 and if the number is in the range the move is a hit
	srand(time(0));
	hit_chance_re_charge_special_attack_player = rand() % (7 - 1) + 1;
	update_hit_chance_special_attack_player = hit_chance_re_charge_special_attack_player;
	return hit_chance_re_charge_special_attack_player, update_hit_chance_special_attack_player;
}

int miss_chance_re_charge_special_attack_player(int& miss_chance_re_charge_special_attack_player)
{// miss chance = 40% 
//the re-charge move gives +10% hit chance to the enemy or the player, so the numbers for miss move with 1 down.
//for the move to be a miss a get a random number x >= 7 && x <= 10 and if the number is in the range the move is a miss
	srand(time(0));
	miss_chance_re_charge_special_attack_player = rand() % (11 - 7) + 7;
	update_miss_chance_special_attack_player = miss_chance_re_charge_special_attack_player;
	return miss_chance_re_charge_special_attack_player, update_miss_chance_special_attack_player;
}

int hit_chance_dogde_attack_player(int& hit_chance_dogde_attack_player)
{//hit chance = 50%
	//i get a random number and if the number is in the range x >= 0 && x <= 2 the move is a hit
	srand(time(0));
	hit_chance_dogde_attack_player = rand() % (3 - 1) + 1;
	update_hit_chance_normal_attack_player = hit_chance_dogde_attack_player;
	return hit_chance_dogde_attack_player, update_hit_chance_normal_attack_player;
}

int miss_chance_dogde_attack_player(int& miss_chance_dogde_attack_player)
{// miss chance = 50%
	//again i get a random number and if the number is in the range x >= 0 && x <= 1 the move is a miss
	srand(time(0));
	miss_chance_dogde_attack_player = rand() % (1 - 0) + 0;
	update_miss_chance_normal_attack_player = miss_chance_dogde_attack_player;
	return miss_chance_dogde_attack_player, update_miss_chance_normal_attack_player;
}

int hit_chance_dogde_special_attack_player(int& hit_chance_dogde_special_attack_player)
{// hit chance = 20%
//i get a random number between x >= 0 and x <= 3 and if it`s in the range then the attack move is a hit
	srand(time(0));
	hit_chance_dogde_special_attack_player = rand() % (4 - 0) + 0;
	update_hit_chance_special_attack_player = hit_chance_dogde_special_attack_player;
	return hit_chance_dogde_special_attack_player, update_hit_chance_special_attack_player;
}

int miss_chance_dogde_special_attack_player(int& miss_chance_dogde_special_attack_player)
{//miss chacne = 80%
	//x >= 5 && x <= 13 (because 80 % 16 = 13 as an int) and if the number is in the range the attack move is a miss
	srand(time(0));
	miss_chance_dogde_special_attack_player = rand() % (14 - 5) + 5;
	update_miss_chance_special_attack_player = miss_chance_dogde_special_attack_player;
	return miss_chance_dogde_special_attack_player, update_miss_chance_special_attack_player;
}

//same logic for the enemy
int hit_chance_attack_enemy(int& hit_chance_attack_enemy)
{
	srand(time(0));
	hit_chance_attack_enemy = rand() % (5 - 1) + 1;
	update_hit_chance_normal_attack_enemy = hit_chance_attack_enemy;
	return hit_chance_attack_enemy, update_hit_chance_normal_attack_enemy;
}

int miss_chance_attack_enemy(int& miss_chance_attack_enemy)
{
	srand(time(0));
	miss_chance_attack_enemy = rand() % (1 - 0) + 0;
	update_miss_chance_normal_attack_enemy = miss_chance_attack_enemy;
	return miss_chance_attack_enemy, update_miss_chance_normal_attack_enemy;
}

int hit_chance_special_attack_enemy(int& hit_chance_special_attack_enemy)
{
	srand(time(0));
	hit_chance_special_attack_enemy = rand() % (5 - 1) + 1;
	update_hit_chance_special_attack_enemy = hit_chance_special_attack_enemy;
	return hit_chance_special_attack_enemy, update_hit_chance_special_attack_enemy;
}

int miss_chance_special_attack_enemy(int& miss_chance_special_attack_enemy)
{
	srand(time(0));
	miss_chance_special_attack_enemy = rand() % (9 - 5) + 5;
	update_miss_chance_special_attack_enemy = miss_chance_special_attack_enemy;
	return miss_chance_special_attack_enemy, update_miss_chance_special_attack_enemy;
}

int hit_chance_re_charge_attack_enemy(int& hit_chance_re_charge_attack_enemy)
{ 
	srand(time(0));
	hit_chance_re_charge_attack_enemy = rand() % (6 - 2) + 1;
	update_hit_chance_normal_attack_enemy = hit_chance_re_charge_attack_enemy;
	return hit_chance_re_charge_attack_enemy, update_hit_chance_normal_attack_enemy;
}

int miss_chance_re_charge_attack_enemy(int& miss_chance_re_charge_attack_enemy)
{
	srand(time(0));
	miss_chance_re_charge_attack_enemy = rand() % (2 - 0) + 0;
	update_miss_chance_normal_attack_enemy = miss_chance_re_charge_attack_enemy;
	return miss_chance_re_charge_attack_enemy, update_miss_chance_normal_attack_enemy;
}

int hit_chance_re_charge_special_attack_enemy(int& hit_chance_re_charge_special_attack_enemy)
{
	srand(time(0));
	hit_chance_re_charge_special_attack_enemy = rand() % (7 - 1) + 1;
	update_hit_chance_special_attack_enemy = hit_chance_re_charge_special_attack_enemy;
	return hit_chance_re_charge_special_attack_enemy, update_hit_chance_special_attack_enemy;
}

int miss_chance_re_charge_special_attack_enemy(int& miss_chance_re_charge_special_attack_enemy)
{
	srand(time(0));
	miss_chance_re_charge_special_attack_enemy = rand() % (11 - 7) + 7;
	update_miss_chance_special_attack_enemy = miss_chance_re_charge_special_attack_enemy;
	return miss_chance_re_charge_special_attack_enemy, update_miss_chance_special_attack_enemy;
}

int hit_chance_dogde_attack_enemy(int& hit_chance_dogde_attack_enemy)
{
	srand(time(0));
	hit_chance_dogde_attack_enemy = rand() % (3 - 1) + 1;
	update_hit_chance_normal_attack_enemy = hit_chance_dogde_attack_enemy;
	return hit_chance_dogde_attack_enemy, update_hit_chance_normal_attack_enemy;
}

int miss_chance_dogde_attack_enemy(int& miss_chance_dogde_attack_enemy)
{
	srand(time(0));
	miss_chance_dogde_attack_enemy = rand() % (1 - 0) + 0;
	update_miss_chance_normal_attack_enemy = miss_chance_dogde_attack_enemy;
	return miss_chance_dogde_attack_enemy, update_miss_chance_normal_attack_enemy;
}

int hit_chance_dogde_special_attack_enemy(int& hit_chance_dogde_special_attack_enemy)
{
	srand(time(0));
	hit_chance_dogde_special_attack_enemy = rand() % (4 - 0) + 0;
	update_hit_chance_special_attack_enemy = hit_chance_dogde_special_attack_enemy;
	return hit_chance_dogde_special_attack_enemy, update_hit_chance_special_attack_enemy;
}

int miss_chance_dogde_special_attack_enemy(int& miss_chance_dogde_special_attack_enemy)
{
	srand(time(0));
	miss_chance_dogde_special_attack_enemy = rand() % (14 - 5) + 5;
	update_miss_chance_special_attack_enemy = miss_chance_dogde_special_attack_enemy;
	return miss_chance_dogde_special_attack_enemy, update_miss_chance_special_attack_enemy;
}

//attack moves player
int attack_1_player(int& update_enemy_HP, int& update_player_EP) // i didn`t indentify what the function should return
							//so the enemy HP never changed. The function just started calculating from 100 every time
{	
	player_EP -= normal_attack_EP;  //updates the player EP
	update_enemy_HP = enemy_HP - normal_attack_dmg; //does the dmg and updates the enemy_HP
	update_player_EP = player_EP + EP_charge_rate; //apllies the EP charge rate to the player_EP

	if (player_EP > max_EP) //seting back the maks EP to 50
	{
		update_player_EP = max_EP; //That way the player can not exceed the starting EP
		return update_enemy_HP, update_player_EP;
	}
	else if (player_EP < min_EP) //just to make sure that the players EP doesn`t go negative
	{
		player_EP = min_EP;
		update_player_EP = player_EP + EP_charge_rate;
		return update_enemy_HP, update_player_EP;
	}
	return update_enemy_HP, update_player_EP;
}

int special_attack_2_player(int& update_enemy_HP, int& update_player_EP)
{
	
	player_EP -= special_attack_EP; // updates the player EP
	update_enemy_HP = enemy_HP - special_attack_dmg; //does the dmg to the enemy and updates it`s HP
	update_player_EP = player_EP + EP_charge_rate; //applies the EP charge rate to the player_EP

	if (player_EP > max_EP)
	{
		update_player_EP = max_EP; //That way the player can not exceed the starting EP
		return update_enemy_HP, update_player_EP;
	}
	else if (player_EP < min_EP) //just to make sure that the players EP doesn`t go negative
	{
		player_EP = min_EP;
		update_player_EP = player_EP + EP_charge_rate;
		return update_enemy_HP, update_player_EP;
	}
	return update_enemy_HP, update_player_EP;
}

int re_charge_player_3(int& update_player_EP)
{
	int update_EP_charge_rate = EP_charge_rate * re_cahrge_EP_cahrge_rate; //calclulates he x4 times of the charging rate
	update_player_EP = update_EP_charge_rate + player_EP; //updates the player_EP with the updated charge rate
	//a restriction to the player. He wont be able to re-charge over 50, so he wouldnt use the same move every time
	if (player_EP > max_EP)
	{
		update_player_EP = max_EP; //That way the player can not exceed the starting EP
		return update_player_EP;
	}
	else if (player_EP <= min_EP) //just to make sure that the players EP doesn`t go negative
	{
		player_EP = 0;
		update_EP_charge_rate = EP_charge_rate * re_cahrge_EP_cahrge_rate; //i didnt add the functions to give the player
		update_player_EP = update_EP_charge_rate + player_EP; //new EP after re-charge. I was just setting the player EP
		//back to 0, that`s why the re-charge didnt work after the player uses it when he has 0 EP
		return update_player_EP;
	}
	// if the function is not true it returns the updated_EP. 
	return update_player_EP;
}

int dogde_player_4(int& update_player_EP)
{
	int update_EP_charge_rate = EP_charge_rate - (EP_charge_rate / 2);  //upates the charging rate, because when he uses dogde the charge rate is -50%
	update_player_EP = player_EP - dogde_EP; //takes away the dogde_EP from the player_EP
	update_player_EP = player_EP + update_EP_charge_rate; //applies the new charge rate to the player_EP

	if (player_EP > max_EP)
	{
		update_player_EP = max_EP; //That way the player can not exceed the starting EP
		return update_player_EP;
	}
	else if (player_EP < min_EP) //just to make sure that the players EP doesn`t go negative
	{
		player_EP = min_EP;
		update_EP_charge_rate = EP_charge_rate - (EP_charge_rate / 2);
		update_player_EP = player_EP + update_EP_charge_rate;
		return update_player_EP;
	}
	return update_player_EP;
}

int heal_5_player(int& update_player_EP, int& update_player_HP)
{
	update_player_EP = player_EP / 2; //divides the player_EP, because he exchanges half of the EP for HP
	update_player_HP = player_HP + update_player_EP; //applies the divided EP to the HP
	update_player_EP = player_EP + EP_charge_rate;  //applies the Ep charge rate to the player_EP
	//a restriction to the player so he wont be able to heal over 100
	if (player_HP > max_HP)
	{
		update_player_HP = max_HP;
		return update_player_EP, update_player_HP;
	}
	else if (player_EP > max_EP)
	{
		update_player_EP = max_EP;
		return update_player_EP, update_player_HP;
	}
	else if (player_EP < min_EP) //just to make sure the players EP doesn`t go negative
	{
		player_EP = min_EP;
		update_player_EP = player_EP + EP_charge_rate;
		return update_player_EP, update_player_HP;
	}
	// if the function is not true it returns the updated_HP
	return update_player_EP, update_player_HP;
}

//enemy attack moves
//same logic
int attack_1_enemy(int& update_player_HP, int& update_enemy_EP) 						
{
	enemy_EP -= normal_attack_EP;  // EP = 40
	update_player_HP = player_HP - normal_attack_dmg;
	update_enemy_EP = enemy_EP + EP_charge_rate;

	if (enemy_EP > max_EP) //seting back the max EP to 50
	{
		update_enemy_EP = max_EP; //That way the enemy can not exceed the starting EP
		return update_player_HP, update_enemy_EP;
	}
	else if (player_EP < min_EP) //just to make sure that the enemys EP doesn`t go negative
	{
		enemy_EP = min_EP;
		update_enemy_EP = enemy_EP + EP_charge_rate;
		return update_player_HP, update_enemy_EP;
	}
	return update_player_HP, update_enemy_EP;
}

int special_attack_2_enemy(int& update_player_HP, int& update_enemy_EP)
{
	enemy_EP -= special_attack_EP; // EP = 0
	update_player_HP = player_HP - special_attack_dmg;
	update_enemy_EP = enemy_EP + EP_charge_rate;

	if (enemy_EP > max_EP) //seting back the max EP to 50
	{
		update_enemy_EP = max_EP; //That way the enemy can not exceed the starting EP
		return update_player_HP, update_enemy_EP;
	}
	else if (player_EP < min_EP) //just to make sure that the enemys EP doesn`t go negative
	{
		enemy_EP = min_EP;
		update_enemy_EP = enemy_EP + EP_charge_rate;
		return update_player_HP, update_enemy_EP;
	}
	return update_player_HP, update_enemy_EP;
}

int re_charge_enemy_3(int& update_enemy_EP)
{
	int update_EP_charge_rate_enemy = EP_charge_rate * re_cahrge_EP_cahrge_rate; // = 20
	update_enemy_EP = enemy_EP + update_EP_charge_rate_enemy;
	//a restriction to the enemy, so it wont be able to re-charge over 50
	if (enemy_EP > max_EP)
	{
		update_enemy_EP = max_EP;
		return update_enemy_EP;
	}
	else if (enemy_EP < min_EP) //just making sure that the enemy_EP doesnt go negative
	{
		enemy_EP = min_EP; //when EP = 0 it doesnt add the EP charge rate because you havent added the functions in the if statement
		update_EP_charge_rate_enemy = EP_charge_rate * re_cahrge_EP_cahrge_rate;
		update_enemy_EP = enemy_EP + update_EP_charge_rate_enemy;
		return update_enemy_EP;
	}
	// if the function is not true it returns the updated_EP
	return update_enemy_EP;
}

int dogde_enemy_4(int& update_enemy_EP)
{
	update_enemy_EP = enemy_EP - dogde_EP;
	int update_EP_charge_rate = EP_charge_rate - (EP_charge_rate / 2);
	update_enemy_EP = enemy_EP + update_EP_charge_rate;

	if (enemy_EP > max_EP) //making sure that the enemy_EP doesnt exceed the starting EP
	{
		update_enemy_EP = max_EP;
		return update_enemy_EP;
	}
	else if (enemy_EP < min_EP) //just making sure that the enemy_EP doesnt go negative
	{
		enemy_EP = min_EP;
		update_EP_charge_rate = EP_charge_rate - (EP_charge_rate / 2);
		update_enemy_EP = enemy_EP + update_EP_charge_rate;
		return update_enemy_EP;
	}
	return update_enemy_EP;
}

int heal_5_enemy(int& update_enemy_EP, int& update_enemy_HP)
{
	update_enemy_EP = enemy_EP / 2; // = 25
	update_enemy_HP = enemy_HP + update_enemy_EP; // = 100
	update_enemy_EP = enemy_EP + EP_charge_rate;
	//a restriction to the enemy so it wont be able to heal over 100
	if (enemy_HP > max_HP)
	{
		update_enemy_HP = max_HP;
		return update_enemy_EP, update_enemy_HP;
	}
	else if (enemy_EP > max_EP)  //same restrictions
	{
		update_enemy_EP = max_EP;
		return update_enemy_EP, update_enemy_HP;
	}
	else if (enemy_EP < min_EP) //same restrictions
	{
		enemy_EP = min_EP; 
		update_enemy_EP = enemy_EP + EP_charge_rate;
		return update_enemy_EP, update_enemy_HP;
	}
	// if the function is not true it returns the updated_HP
	return update_enemy_EP, update_enemy_HP;
}