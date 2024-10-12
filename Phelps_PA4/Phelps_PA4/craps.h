#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef craps
#define craps

/*
	Programmer: Henry Phelps
	Class: CptS 121 Lab Section 19
	Assignment: PA4 (Craps)

	Description: This program is the game of Craps! Psuedo code description is below:

	Psuedo Code (made before code was implemented):
	1.	Print 2 options for the user: show game rules, play game
	2.	Ask for wager amount
	3.	Roll dice
	4.	Add up number on dice
	5.	If = 7 or 11 WIN
	6.	If = 2, 3, or 12 LOSE
	7.	If = 4, 5, 6, 8, 9, 10: WINNING value = rolled value
	8.	Roll again
	9.	If = 7 LOSE
	10.	If = winning value WIN
	11.	If = anything else: role again
	12.	Repeat steps 8 – 11 until 7 or winning value is rolled
	13. If WIN: bank_balance + wager
	14. If LOSE: bank_balance - wager
	15. ask user if they want to play again
	16. DONE
*/

void display_choices(void);
double players_choice(int choice);
void print_game_rules(void);
void play_game(void);
double get_bank_balance(double current_bank_balance);
double get_wager_amount(void);
int check_wager_amount(double wager, double balance);
int roll_die(void);
void roll_both_dice(int* dice_1_ptr, int* dice_2_ptr, int* number_rolls_ptr);
int calculate_sum_dice(int die1_value, int die2_value);
int is_win_loss_or_point(int sum_dice);
int is_point_loss_or_neither(int sum_dice, int point_value);
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance, int times_played);

#endif