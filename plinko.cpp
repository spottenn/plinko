/*
My outpur is really long so this is just a simplified version.
test case 1
Inp	Expected				output
	Plinko					Plinko
	MENU					MENU
10	INVALID, MENU			INVALID, MENU
D 	INVALID, MENU			INVALID, MENU
1	SINGLE					SINGLE
	Slot:					Slot:
9	INVALID, MENU			INVALID, MENU
1	SINGLE					SINGLE
	Slot:					Slot:
-1	INVALID, MENU			INVALID, MENU
1	SINGLE					SINGLE
	Slot:					Slot:
D 	INVALID, MENU			INVALID, MENU
1	SINGLE					SINGLE
	Slot:					Slot:
8	Path: …winnings:, MENU	Path: …winnings: $500.00, MENU
4	GOODBYE					GOODBYE


test case 2
In	Expected							output
	Plinko								Plinko
	MENU								MENU
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
4	Slot:								Slot:
-2	INVALID, MENU						INVALID, MENU
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
7	Slot:								Slot:
3	Won average: Menu					Won $1000.00, average: $333.33, Menu
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
4	Slot:								Slot:
9	INVALID, MENU						INVALID, MENU
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
0	INVALID, MENU						INVALID, MENU
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
-2	INVALID, MENU						INVALID, MENU
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
no	INVALID, MENU						INVALID, MENU
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
3	Slot:								Slot:
6	Won:, average:, Menu				Won $10600.00, average: $3533.33, Menu
2	MULTIPLE CHIPS 1 SLOT, Chips:		MULTIPLE CHIPS 1 SLOT, Chips:
1000Slot:								Slot:
4	Won:, average:, Menu				Won $2570200.00, average: $2570.20, Menu
4	GOODBYE								GOODBYE

test case 3
Inp	Expected				output
	Plinko									Plinko
	MENU									MENU
2	MULTIPLE CHIPS MULTIPLE SLOTs, Chips:	MULTIPLE CHIPS MULTIPLE SLOT, Chips:
p	INVALID, MENU							INVALID, MENU
2	MULTIPLE CHIPS MULTIPLE SLOTs, Chips:	MULTIPLE CHIPS MULTIPLE SLOT, Chips:
-8	INVALID, MENU							INVALID, MENU
2	MULTIPLE CHIPS MULTIPLE SLOTs, Chips:	MULTIPLE CHIPS MULTIPLE SLOT, Chips:
6	Slot 1, 2, etc, Won:, average:, Menu	Slot 1, 2, etc, Won:, average:, Menu
2	MULTIPLE CHIPS MULTIPLE SLOTs, Chips:	MULTIPLE CHIPS MULTIPLE SLOT, Chips:
1000Slot 1, 2, etc, Won:, average:, Menu	Slot 1, 2, etc, Won:, average:, Menu
4	GOODBYE									GOODBYE
*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
using namespace std;

const int CIN_IGNORE_AMOUNT = 1000;
double input_verify(int min, int max, bool &error)
{
	double input = 0.;
	if (!(cin >> input))
	{
		cin.clear();
		cin.ignore(CIN_IGNORE_AMOUNT, '\n');
		error = true;
	}
	if ((input < min || input > max) || error == true)
	{
		cout << "INVALID INPUT: \n\tThe input you entered didn't fit the syntax given in the prompts.\n(follow the prompts in parenthasis)";
		error = true;
	}
	return input;
}

const int SELECTOR_SINGLE = 1;
const int SELECTOR_MULTIPLE_CHIPS_SINGLE_SLOT = 2;
const int SELECTOR_MULTIPLE_CHIPS_MULTIPLE_SLOT = 3;
const int SELECTOR_QUIT = 4;
int selector_prompt()
{
	cout << "\n_______________________________________________________________________________________________________________________";
	cout << "\nMENU: How you want to drop chips?";
	cout << "\n\t1 - Single Chip";
	cout << "\n\t2 - Multiple chips in the same slot";
	cout << "\n\t3 - Multiple chips in every slot";
	cout << "\n\t4 - Quit";
	cout << "\n(Enter a number between 1 and 4)\n";
	bool input_error= false;
	int selection = input_verify(SELECTOR_SINGLE, SELECTOR_QUIT, input_error);
	return selection;
}

const int SLOTS_0_8_WINNINGS = 100;
const int SLOTS_1_7_WINNINGS = 500;
const int SLOTS_2_6_WINNINGS = 1000;
const int SLOTS_3_5_WINNINGS = 0;
const int SLOT_4_WINNINGS = 10000;
int winnings(int slot)
{
	if (slot == 0 || slot == 8) return SLOTS_0_8_WINNINGS;
	else if (slot == 1 || slot == 7) return SLOTS_1_7_WINNINGS;
	else if (slot == 2 || slot == 6) return SLOTS_2_6_WINNINGS;
	else if (slot == 3 || slot == 5) return SLOTS_3_5_WINNINGS;
	else if (slot == 4) return SLOT_4_WINNINGS;
	return 0;
}

const int SLOT_MIN = 0;
const int SLOT_MAX = 8;
const double SLOT_MOVE_AMOUT = .5;
double chip_move(double slot)
{
	if (slot == SLOT_MIN) slot += SLOT_MOVE_AMOUT;
	else if (slot == SLOT_MAX) slot -= SLOT_MOVE_AMOUT;
	else slot += rand() % 2 - SLOT_MOVE_AMOUT;
	return slot;
}

const int PEG_ROW_MIN = 0;
const int PEG_ROW_MAX = 11;
void single_chip_drop()
{
	cout << "\n\n\n_______________________________________________________________________________________________________________________";
	cout << "\nSINGLE CHIP DROP:";
	cout << "\n\tslot: Which slot do you want to drop the chip in?\n\n\n\n(Enter a number between 0 and 8)\n";
	bool input_error = false;
	double slot = input_verify(SLOT_MIN, SLOT_MAX, input_error);
	if (input_error) return;
	cout << "PATH:[";
	cout << setprecision(1) << fixed;
	for (int peg_row = PEG_ROW_MIN; peg_row <= PEG_ROW_MAX; peg_row++)
	{
		cout << slot << " ";
		slot = chip_move(slot);
	}
	cout << slot << "]\n";
	cout << setprecision(2) << fixed;
	cout << "WINNINGS: You won $" << winnings(slot) << "!\n";
}

double multiple_chip_single_slot_simulation(int chips, int slot)
{
	int total_winnings = 0;
	for (int chips_counter = chips; chips_counter > 0; chips_counter--)
	{
		double path = slot;
		for (int peg_row = PEG_ROW_MIN; peg_row <= PEG_ROW_MAX; peg_row++) path = chip_move(path);
		total_winnings += winnings(path);
	}
	return total_winnings;
}

const int PRECISION_FOR_CENTS = 2;
const int MIN_CHIPS = 1;
void multiple_chip_drop()
{
	cout << "\n\n\n_______________________________________________________________________________________________________________________";
	cout << "\nSINGLE SLOT, MULTIPLE CHIPS:";
	cout << "\n\tChips: How many chips do you want to drop?\n\n\n\n(Enter a positive number)\n";
	bool input_error = false;
	int chips = input_verify(MIN_CHIPS, INT_MAX, input_error);
	if (input_error) return;
	cout << "\n\n\n_______________________________________________________________________________________________________________________";
	cout << "\nSINGLE SLOT, MULTIPLE CHIPS:";
	cout << "\n\tSlot: Which slot do you want to drop the chip in?\n\n\n\n(Enter a number between 0 and 8)\n";
	int slot = input_verify(SLOT_MIN, SLOT_MAX, input_error);
	if (input_error) return;
	double total_winnings = multiple_chip_single_slot_simulation(chips, slot);
	cout << setprecision(PRECISION_FOR_CENTS) << fixed;
	cout << "WINNINGS: You won $" << total_winnings << "!\nAVERAGE PER CHIP: $" << total_winnings / chips << "\n" ;
}

const int CELL_WIDTH = 12;
const int DECIMAL_PLACES_TO_REMOVE_FOR_CENTS = -4;
void multiple_chip_drop_multiple_slots()
{
	cout << "\n\n\n_______________________________________________________________________________________________________________________";
	cout << "\nMULTIPLE SLOTS, MULTIPLE CHIPS:";
	cout << "\n\tChips: How many chips do you want to drop in each slot?\n\n\n\n(Enter a positive number)\n";
	bool input_error = false;
	int chips = input_verify(MIN_CHIPS, INT_MAX, input_error);
	if (input_error) return;
	double slot_winnings[SLOT_MAX + 1];
	for (int slot = SLOT_MIN; slot <= SLOT_MAX; slot++)
	{
		slot_winnings[slot] = multiple_chip_single_slot_simulation(chips, slot);
	}
	cout << "SLOT:   ";
	for (int slot = SLOT_MIN; slot <= SLOT_MAX; slot++)
	{
		string slot_num_str = "Slot " + to_string(slot);
		cout << setw(12) << slot_num_str;
	}
	cout << "\nWINNING:";
	for (int slot = SLOT_MIN; slot <= SLOT_MAX; slot++)
	{
		string winning_amount_str = "$" + to_string(slot_winnings[slot]);
		cout << setw(CELL_WIDTH) << winning_amount_str.substr(0, winning_amount_str.length() + DECIMAL_PLACES_TO_REMOVE_FOR_CENTS);
	}
	cout << "\nAVERAGE:";
	for (int slot = SLOT_MIN; slot <= SLOT_MAX; slot++)
	{
		string winnings_average_str = "$" + to_string(slot_winnings[slot] / chips);
		cout << setw(CELL_WIDTH) << winnings_average_str.substr(0, winnings_average_str.length() + DECIMAL_PLACES_TO_REMOVE_FOR_CENTS);
	}
}

int main()
{
	cout << "********************************************************PLINKO*********************************************************\n"
		<< "For the best experience and if applicable shrink the window height to fit the contents, the **plinko** and input lines\n"
		<< "visible, in other words, 11 lines high.";
	srand((unsigned)time(NULL));
	bool quit = false;
	while (!quit)
	{
		int selection = selector_prompt();
		if (selection == SELECTOR_SINGLE) single_chip_drop();
		else if (selection == SELECTOR_MULTIPLE_CHIPS_SINGLE_SLOT) multiple_chip_drop();
		else if (selection == SELECTOR_MULTIPLE_CHIPS_MULTIPLE_SLOT) multiple_chip_drop_multiple_slots();
		else if (selection == SELECTOR_QUIT)
		{
			quit = true;
			cout << "GOODBYE\n";
		}
	}
	return 0;
};