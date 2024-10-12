#include "craps.h"

/*
	Function: players_choice
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: prompts the user with 2 choices: display rules, or play game
	Input parameters: none
	Returns: none, goes through choices and when they choose play game, the function ends and the game is played in play_game()
	Preconditions: N/A
	Postconditions: N/A
*/
void display_choices(void)
{
	int choice = 0;
	while (choice != 2)
	{
		system("cls");
		printf("Please choose:\n");
		printf("1) Show game rules\n2) Play game\n");
		scanf("%d", &choice);
		printf("\n");
		if (choice == 1)
		{
			print_game_rules();
		}

	}
}

/*
	Function: print_game_rules
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: displays the rules of the game
	Input parameters: no input parameters, simply prints rules when called
	Returns: none, just prints the rules
	Preconditions: N/A
	Postconditions: N/A
*/
void print_game_rules(void)
{
	system("cls");
	printf("The following description has been adopted from Deitel & Deitel. One of the most\n");
	printf("popular games of chance is a dice game called \"craps\", which is played in casinos and\n");
	printf("back alleys throughout the world. The rules of the game are straightforward:\n");
	printf("A player rolls two dice. Each die has six faces. These faces contain 1, 2, 3, 4, 5, and 6\n");
	printf("spots. After the dice have come to rest, the sum of the spots on the two upward\n");
	printf("faces is calculated. If the sum is 7 or 11 on the first throw, the player wins. If the\n");
	printf("sum is 2, 3, or 12 on the first throw (called \"craps\"), the player loses (i.e. the \"house\"\n");
	printf("wins). If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the\n");
	printf("player's \"point\". To win, you must continue rolling the dice until you \"make your\n");
	printf("point\". The player loses by rolling a 7 before making the point.\n");
	system("pause");
	printf("\n");
}

/*
	Function: play_game
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: plays craps
	Input parameters: no input parameters, simply plays craps
	Returns: none, just plays craps
	Preconditions: N/A
	Postconditions: N/A
*/
void play_game(void)
{
	int choice = 0, dice_1 = 0, dice_2 = 0, sum_dice = 0, win_or_loss = 0, point_value = 0, number_rolls = 0, times_played = 0;
	double initial_bank_balance = 0.0, current_bank_balance = 0.0, wager = 0.0;
	char play_again = '\0';

	printf("Welcome to craps!\n");
	system("pause");
	printf("\n");

	do
	{
		play_again = '\0';
		number_rolls = 0;

		display_choices();

		current_bank_balance = get_bank_balance(current_bank_balance);

		if (times_played == 0)
		{
			initial_bank_balance = current_bank_balance;
		}

		do
		{
			wager = get_wager_amount();
		} while (!check_wager_amount(wager, current_bank_balance));

		roll_both_dice(&dice_1, &dice_2, &number_rolls);

		sum_dice = calculate_sum_dice(dice_1, dice_2);

		win_or_loss = is_win_loss_or_point(sum_dice);

		chatter_messages(number_rolls, win_or_loss, initial_bank_balance, current_bank_balance, times_played);

		if (win_or_loss == 1)
		{
			printf("Congrats you win! You scored %d.\n", sum_dice);
			current_bank_balance = adjust_bank_balance(current_bank_balance, wager, win_or_loss);
			printf("You won $%.2lf! Your new bank balance is now: $%.2lf.\n", wager, current_bank_balance);
		}
		else if (win_or_loss == 0)
		{
			printf("Unfortunately you lost! You scored %d.\n", sum_dice);
			current_bank_balance = adjust_bank_balance(current_bank_balance, wager, win_or_loss);
			printf("You lost $%.2lf! Your new bank balance is now: $%.2lf.\n", wager, current_bank_balance);
		}
		else if (win_or_loss == -1)
		{
			do
			{
				point_value = sum_dice;
				printf("You scored %d. You must score %d again, however if you score 7 first, you lose!\n", sum_dice, sum_dice);
				system("pause");
				roll_both_dice(&dice_1, &dice_2, &number_rolls);
				sum_dice = calculate_sum_dice(dice_1, dice_2);
				win_or_loss = is_point_loss_or_neither(sum_dice, point_value);
				if (win_or_loss == 0)
				{
					printf("You scored %d! You lost!\n", sum_dice);
					current_bank_balance = adjust_bank_balance(current_bank_balance, wager, win_or_loss);
					printf("You lost $%.2lf! Your new bank balance is now: $%.2lf.\n", wager, current_bank_balance);
				}
				else if (win_or_loss == 1)
				{
					printf("You scored %d again! Congrats! You win!\n", sum_dice);
					current_bank_balance = adjust_bank_balance(current_bank_balance, wager, win_or_loss);
					printf("You won $%.2lf! Your new bank balance is now: $%.2lf.\n", wager, current_bank_balance);
				}
			} while (win_or_loss == -1);
		}

		while (play_again != 'Y' && play_again != 'y' && play_again != 'N' && play_again != 'n')
		{
			printf("Would you like to play again (Y/N)? ");
			scanf(" %c", &play_again);
		}

		times_played++;
	} while (play_again == 'Y' || play_again == 'y');
	printf("We hope to see you again!\n");
}

/*
	Function: get_bank_balance 
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: asks the user for their bank balance 
	Input parameters: none, asks the user for the bank balance
	Returns: bank balance as a double
	Preconditions: N/A
	Postconditions: N/A
*/
double get_bank_balance(double current_bank_balance)
{
	double bank_balance = 0.0;
	char adjust = '\0';
	system("cls");
	printf("Your current bank balance is: $%.2lf. Would you like to adjust it (Y/N)? ", current_bank_balance);
	scanf(" %c", &adjust);
	bank_balance = current_bank_balance;
	if (adjust == 'Y' || adjust == 'y')
	{
		printf("Please enter your new bank balance: $");
		scanf("%lf", &bank_balance);
	}

	return bank_balance;
}

/*
	Function: get_wager_amount
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: asks the user for the amount they want to wager 
	Input parameters: none, asks the user for the wager amount
	Returns: wager as a double
	Preconditions: N/A
	Postconditions: N/A
*/
double get_wager_amount(void)
{
	double wager_amount = 0;
	printf("How much would you like to wager? $");
	scanf("%lf", &wager_amount);
	return wager_amount;
}

/*
	Function: check_wager_amount
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: checks if the wager amount is within their balance
	Input parameters: doubles: wager and balance
	Returns: 1: if wager is less than balance and 0: if wager is greater than balance
	Preconditions: N/A
	Postconditions: N/A
*/
int check_wager_amount(double wager, double balance)
{
	if (wager > balance || wager < 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
	Function: roll_dice
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: picks a random number between 1-6
	Input parameters: no input, just rolls
	Returns: the value of the dice as an integer
	Preconditions: N/A
	Postconditions: N/A
*/
int roll_die(void)
{
	int dice_value = 0;
	dice_value = (rand() % 6) + 1;
	printf("You rolled a %d!\n", dice_value);
	return dice_value;
}

/*
	Function: roll_both_dice
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: prolls both dice at the same time
	Input parameters: no input, just rolls
	Returns: each value of each die to its respective dice and adds to the total number of rolls
	Preconditions: N/A
	Postconditions: N/A
*/
void roll_both_dice(int* dice_1_ptr, int* dice_2_ptr, int* number_rolls_ptr)
{
	system("cls");
	*dice_1_ptr = roll_die();
	*number_rolls_ptr++;
	system("pause");
	*dice_2_ptr = roll_die();
	*number_rolls_ptr++;
	system("pause");
	printf("\n");
}

/*
	Function: calculate_sum_dice
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: adds the values of 2 rolled dice
	Input parameters: value of first roll and value of second roll
	Returns: the total value of the two rolls
	Preconditions: N/A
	Postconditions: N/A
*/
int calculate_sum_dice(int die1_value, int die2_value)
{
	return die1_value + die2_value;
}

/*
	Function: is_win_loss_or_point
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: checks if the first roll is a win, loss, or a point value
	Input parameters: the sum of the dice
	Returns: 1: if win, 0: if loss, -1: if point
	Preconditions: N/A
	Postconditions: N/A
*/
int is_win_loss_or_point(int sum_dice)
{
	if (sum_dice == 7 || sum_dice == 11)
	{
		return 1;
	}
	else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/*
	Function: is_point_loss_or_neither
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: checks if rolls 2-infinity are a loss (7) or a win (point value)
	Input parameters: the sum of the dice from the roll that just happened, and the point value to determine if the player won
	Returns: 1: if win, 0: if loss, -1: if different point value
	Preconditions: N/A
	Postconditions: N/A
*/
int is_point_loss_or_neither(int sum_dice, int point_value)
{
	if (sum_dice == 7)
	{
		return 0;
	}
	else if (sum_dice == point_value)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

/*
	Function: adjust_bank_balance
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: adjusts the players bank balance based on win/loss and wager amount
	Input parameters: bank balance, wager amount, and whether or not the player won or loss (1 or 0)
	Returns: new bank balance
	Preconditions: N/A
	Postconditions: N/A
*/
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	if (add_or_subtract)
	{
		bank_balance += wager_amount;
	}
	else
	{
		bank_balance -= wager_amount;
	}

	return bank_balance;
}

/*
	Function: chatter_messages
	Date Created: 09/26/24
	Date Last Modified: 09/26/24
	Programmer: Henry Phelps
	Description: displays a message to the player based on how many rolls, current balance, and win/loss
	Input parameters: number of rolls, win or loss, starting bank balance, current bank balance
	Returns: does not return anything, prints a message to the screen, chatting to the player
	Preconditions: N/A
	Postconditions: N/A
*/
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance, int times_played)
{
	if (number_rolls < 3 && win_loss_neither == 1)
	{
		printf("Woah that was fast nice job!\n");
	}
	else if (number_rolls == 18 && win_loss_neither == -1)
	{
		printf("Alright that's it. I'm done. Goodluck.\n");
	}
	else if (number_rolls >= 16 && win_loss_neither == -1)
	{
		printf("I'm about done waiting for you! Win or lose already!\n");
	}
	else if (number_rolls >= 14 && win_loss_neither == -1)
	{
		printf("HURRY UP!\n");
	}
	else if (number_rolls >= 10 && win_loss_neither == -1)
	{
		printf("Please hurry up!\n");
	}
	else if (number_rolls >= 8 && win_loss_neither == -1)
	{
		printf("This is taking a while, can you please hurry up!\n");
	}

	if (current_bank_balance < initial_bank_balance && times_played > 0 && win_loss_neither == 0)
	{
		printf("I see you've been losing some money! Keep playing to win big (please)!\n");
	}
	else if (current_bank_balance > initial_bank_balance && times_played > 0 && win_loss_neither == 1)
	{
		printf("I see you've been earning some money! Keep playing to earn even more!\n");
	}
}