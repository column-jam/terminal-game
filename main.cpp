#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <iostream>
#include "room_layouts.h"
#include "globals.h"

using std::string;

void color_maker(int room_color[height][width]) {
    for (int i=0; i < height; i++) {
    	for (int j=0; j < width; j++) {
    		room_color[i][j] = (rand() % 3 < 2) ? 1 : 0; //Randomly assigns a value to the room_color array, with the majority being 1
		}
	}
}

void setCursorPosition(int x, int y) { //Puts cursor in top left of the terminal so that printing resets the room
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void initialize_code() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(console, &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(console, consoleMode); //For color codes and terminal settings
	
	srand(time(NULL)); //Randomizer for the colors
	
	for (int i = 0; i < room_amount; i++) {
		color_maker(room_color[i]);
	}
}

void print_room() {
	if (maze_flag || pause_flag) return; //Disabling the standard print process for the maze room or pause menu, that has its own function
	for (int i = 0; i < height; i++) {
		string colored_string = "\0";
		for (int j = 0; j < width; j++) {
			switch (room_layout[room_number][i][j]) {
                case '#':        //Concatenating the color codes to the string based on what char is in each cell
                    if (room_color[room_number][i][j] == 0) { //Room color codes represent gray or light gray for the walls
                    	colored_string += GRAY;
						break;
					}
                    colored_string += LIGHT_GRAY; break;
                case '*': colored_string += YELLOW; break;
                case 'X': colored_string += RED; break;
                case 'O': colored_string += LIME; break;
                case '_':
                case '/':
                case '\\': colored_string += SILVER; break;
                case '-':
                case '|': colored_string += ORANGE; break;
                case '^': colored_string += WHITE; break;
                default:                    
                    if (x_pos == j && y_pos == i) {
                    	colored_string += WHITE;
                        colored_string += "@";
                        continue;       
                    }
                    break;
            }
            colored_string += room_layout[room_number][i][j]; //Combine the color code with the actual character
		}                             
		std::cout << colored_string; //Prints the whole line of colored characters. Faster and better for performance than printing each character individually
		if (i != height - 1) std::cout << "\n";
	}                             
}

void pause_menu() {
	pause_flag = 1;
	for (int i = 0; i < height; i++) {
		std::cout << LIGHT_GRAY << pause_layout[i];
	}
	while (1) {
		if (kbhit()) { // If the player presses a button
			char user_input = _getch();
			if (user_input == 101) { //E resume
				pause_flag = 0;
				print_room();
				return;
			}
			if (user_input == 27) { //Escp leave
				exit(1);
			}
		}
	}
}

int check_adjacent(char symbol, int y_pos, int x_pos) {
	if (room_layout[room_number][y_pos - 1][x_pos] == symbol) {	//Up
		return 1;
	}
	if (room_layout[room_number][y_pos][x_pos + 1] == symbol) {	//Right
		return 2;
	}
	if (room_layout[room_number][y_pos + 1][x_pos] == symbol) {	//Down
		return 3;
	}
	if (room_layout[room_number][y_pos][x_pos - 1] == symbol) {	//Left
		return 4;
	}
	if (room_layout[room_number][y_pos][x_pos] == symbol) { //On top
		return 5;
	}
	return 0;
}

int go_next_room() {
	if (x_pos <= 64 && x_pos >= 56 && y_pos == 0) { //Checks if the player is at the top of the screen, moves to the next room and reset's player position
		room_number++;
		(x_pos) = 61;
		(y_pos) = 28;
		return 1;
	}
	return 0; //Fails if not in the correct spot
}

class Maze {
	private:
		char lit_maze_tiles[5][7];
	public:
		void initialize() {
			create_array();
		}
		void create_array() {
			for (int i = 0; i < 5; i++) {
			    for (int j = 0; j < 7; j++) {
			        int row = i + y_pos - 2;
			        int col = j + x_pos - 3;
			        if (row >= 0 && row < height && col >= 0 && col < width) {  //Creates an array 7 wide and 5 tall to make a square around the player
			            lit_maze_tiles[i][j] = room_layout[room_number][row][col]; 
			        }
			    }
			}
		}
		void print() {
			for (int y = 0; y < height; y++) {
		        for (int x = 0; x < width; x++) {
		            if ((y >= y_pos - 2 && y <= y_pos + 2) && (x >= x_pos - 3 && x <= x_pos + 3)) {
		                int i = y - (y_pos - 2);  //Centers i and j on the top left corner of the player's square
		                int j = x - (x_pos - 3);
		                if (i == 2 && j == 3) {
		                    std::cout << WHITE << "@";
		                } else if (i == 0 || i == 5 || j == 0 || j == 6) {
		                    std::cout << GRAY << lit_maze_tiles[i][j]; //Gray for the inner ring, light gray for the outer ring, white for the player. Gives the impression of a light centered on the player
		                } else if (i == 1 || i == 4 || j == 1 || j == 5){
		                    std::cout << GRAY_BUT_LIGHTER << lit_maze_tiles[i][j];
		                } else {
		                	std::cout << LIGHT_GRAY << lit_maze_tiles[i][j];
						}
		            } else {
		                std::cout << " "; //ONLY prints the area around the player. The rest gets replaced by whitespace
		            }
		        }
		        std::cout << "\n";
		    }
		}
};

Maze maze;

class RoomText { //Class to reduce repetitive code, as text hints are printed regularly
	public:
		void generate(string text, int row) {
			room_layout[room_number][row] = "###########################" + text + "###########################";
			setCursorPosition(0, 0);
			print_room();
			std::cout << "\033[?25l"; // This hides the cursor so there isn't a blinking tile
		}
		void remove(int row) {
			room_layout[room_number][row] = "###########################                                                                  ###########################";
			setCursorPosition(0, 0);
			print_room();
			std::cout << "\033[?25l";
		}
};

RoomText roomtext;

class Laser {
	private:
		int y = 21;
		int x = 60;
		int direction = 1;
		
		string room_copy[height];
		
		bool isLaserActive;
		bool isDoorDown;
		bool wasLaserUsed;
		
		void print() {
			room_layout[room_number][y][x] = (direction == 1 || direction == 3) ? '|' : '-'; //If light direction is up or down, print |, otherwise print -
			setCursorPosition(0, 0);
			print_room();
			std::cout << "\033[?25l";
			Sleep(50);
		}
		void change_direction() {
			int direction_one = check_adjacent('/', y, x);
			int direction_two = check_adjacent('\\', y, x);
			if (direction_one == direction || direction_two == direction) { //If there's a mirror in the light's way, trigger code
			    switch (direction) {
			        case 1: (direction_one == 1) ? (direction = 2, y--, x++) : (direction = 4, y--, x--); break; //Change light's direction and position based on the mirror it hits and what direction it's going
			        case 2: (direction_one == 2) ? (direction = 1, y--, x++) : (direction = 3, y++, x++); break;
			        case 3: (direction_one == 3) ? (direction = 4, y++, x--) : (direction = 2, y++, x++); break;
			        case 4: (direction_one == 4) ? (direction = 3, y++, x--) : (direction = 1, y--, x--); break;
			    }
			} else {
				switch(direction) { //If nothing is in the light's way, it carries on in its direction
					case 1: y--; break;
					case 2: x++; break;
					case 3: y++; break;
					case 4: x--; break;
				}
			}
		}
		bool isLaserBlocked() {
			return	
			check_adjacent('#', y, x) ||
			check_adjacent('-', y, x) == direction ||
			check_adjacent('|', y, x) == direction;
		};
		void reset() {
			print();
			for (int i = 0; i < height; i++) {
			    room_layout[room_number][i] = room_copy[i]; //Reset the room if the beam fails
			}
			isLaserActive = 0;
		}
		void break_door() {
			room_copy[2] = "########################################################         #######################################################"; //Remove door
			isDoorDown = true;
		}
		
	public:
		void initialize(string room_data[height]) {
			for (int i = 0; i < height; i++) { //Store the room's state before the laser activates
				room_copy[i] = room_data[i];
			}
			y = 21;
			x = 60;
			direction = 1;
			isLaserActive = true;
			wasLaserUsed = true;
		}
		void update() {
			print();
			change_direction();
			if (check_adjacent('X', y + 1, x)) break_door();
			if (isLaserBlocked() || isDoorDown) reset();
		}
		bool get_is_laser_active() {
			return isLaserActive;	
		}
		bool get_is_door_down() {
			return isDoorDown;
		}
		bool get_was_laser_used() {
			return wasLaserUsed;
		}
		void create_text() {
			roomtext.generate("             *A laser? Maybe it can break that door...            ", 9);
		}
		void delete_text() {
			roomtext.remove(9);
		}
};

Laser laser;

class Mirror {
	private:
		bool wasMirrorTurned;
	public:
		int check_direction(char symbol) {
			return check_adjacent(symbol, y_pos, x_pos);
		}
		void turn(int direction, char symbol) { //Changes the tile to whatever 'symbol' is. In practice, it swaps forward slash and backslash
			switch(direction) {
				case 1: room_layout[room_number][y_pos - 1][x_pos] = symbol; break;
				case 2: room_layout[room_number][y_pos][x_pos + 1] = symbol; break;
				case 3: room_layout[room_number][y_pos + 1][x_pos] = symbol; break;
				case 4: room_layout[room_number][y_pos][x_pos - 1] = symbol; break;
			}
			wasMirrorTurned = true;
		}
		bool get_is_mirror_turned() {
			return wasMirrorTurned;
		}
		void remove() {
			roomtext.remove(14); //Gets rid of the room-long line
		}
		void create_text() {
			roomtext.generate("                 *I think I can turn that mirror                  ", 9);
		}
		void delete_text() {
			roomtext.remove(9);
		}

};

Mirror mirror; //on the wall

class Button {
	private:
		int flag_list[width]; //List of all x positions where a button has been pressed
		bool is_in_list(int x) {
			for (int i = 0; i < width; i++) {
				if (flag_list[i] == x) return true;
			}
			return false;
		}
		int find_next_position() {
			for (int i = 0; i < width; i++) {
				if (flag_list[i] == 0) return i; //As a result of i stopping only when it reaches 0, it gives the next available position rather than the last used one
			}
			return 0;
		}
		void add_flag(int x, int direction) {
			if (direction == 2) x++; //Where you are when the button is pressed isn't necessarily where the button is. +1 for on the right, -1 for on the left
			if (direction == 4) x--;
			if (!is_in_list(x)) {
				flag_list[find_next_position()] = x;
			}
		}
	public:
		int adjacent_check() { // Only calls a function, but button.adjacent_check() is more readable than check_adjacent('O', y_pos, x_pos);
			return check_adjacent('O', y_pos, x_pos);
		}
		int press(bool skip) {
			if (adjacent_check() || skip) { //Skip exists purely for the scenario where a button needs to be pressed but is invisible
				add_flag(x_pos, adjacent_check());
				click();
				return 1;
			}
			return 0;
		}
		void remove_flags() {
			for (int i = 0; i < width; i++) {
				flag_list[i] = 0;
			}
		}
		void click() {
			roomtext.generate("                              *Click!                             ", 23);
			setCursorPosition(0, 0);
			print_room();
			std::cout << "\033[?25l";
			Sleep(500); // Prints 'Click!' then removes it. I thought it was cool
			roomtext.remove(23);
		}
		int count_flags() {
			return find_next_position(); //The next available position is also the amount of flags because of indices starting at 0
		}
		void add_text(string text) {
			roomtext.generate(text, 15);
		}
		void remove_text() {
			roomtext.remove(15);
		}
};

Button button;

void room_interactions() { //Only triggers if the player presses E
	switch(room_number) {
		case 0:
			button.press(false);
			break;
		case 1:
			if ((x_pos == 83 && y_pos == 17) || (x_pos == 38 && y_pos == 25)) { //Activates the buttons with skip perms if they're on the spot. Can't just do button.press() because they're invisible
				button.press(true);
			}
			break;
		case 2:
			if (mirror.check_direction('/')) {  //Checking whether there's a / or \ present, then swapping them
				mirror.turn(mirror.check_direction('/'), '\\');
			} else if (mirror.check_direction('\\')) {
				mirror.turn(mirror.check_direction('\\'), '/');
			}
			
			if (button.adjacent_check()) {
				string room_two_but_technically_the_third_copy[height];
				for (int i = 0; i < height; i++) {
			    	room_two_but_technically_the_third_copy[i] = room_layout[room_number][i]; //Store the room before the laser activates
				}
				laser.initialize(room_two_but_technically_the_third_copy);
				do {
					laser.update();
				}
				while (laser.get_is_laser_active());
			}
			break;
		case 3:
			break;
		case 4:
			break;
	}
}

void room_updates(int* x_pos, int* y_pos) {
	switch(room_number) { //Room updates occur every movement, room interactions occur only when E is pressed
		case 0: 
			if (button.adjacent_check() && !button.count_flags()) { //Most of the adjacent_checks and text flags are just for hints
				button.add_text("       *Interact with green buttons to make things happen         ");
				flag_first_room_button_text = 1;
			} else if (flag_first_room_button_text == 1){
				button.remove_text();
				flag_first_room_button_text = 0;
			} else if (check_adjacent('X', *y_pos, *x_pos)) {
				button.add_text("                     *It seems to be locked                       ");
				flag_first_room_door_text = 1;
			} else if (flag_first_room_door_text == 1){
				button.remove_text();
				flag_first_room_door_text = 0;
			}
			
			if (button.count_flags() > 1) { //Buttons delete door
				roomtext.generate("#############################         ############################", 2);
				button.remove_flags();
			} 
			go_next_room();
			break;
   		case 1:
   			if (room_layout[room_number][*y_pos - 1][*x_pos] == '_') {
   				roomtext.generate("                  *Looks like some kind of mirror                 ", 23);
   				flag_second_room_mirror_text = 1;
			} else if (flag_second_room_mirror_text == 1) {
				roomtext.remove(23);
				flag_second_room_mirror_text = 0;
			}
			if (button.count_flags() > 1) { 
				mirror.remove();
				button.remove_flags();
			}
			go_next_room();
			break;
		case 2:
			if (check_adjacent('^', *y_pos, *x_pos) && !laser.get_was_laser_used()) {
				laser.create_text();
			} else if (room_layout[room_number][9][40] == '*') {
				laser.delete_text();
			}

			if ((check_adjacent('/', *y_pos, *x_pos) || check_adjacent('\\', *y_pos, *x_pos)) && !mirror.get_is_mirror_turned()) {
				mirror.create_text();
			} else if (room_layout[room_number][9][44] == '*' && (mirror.get_is_mirror_turned() || !check_adjacent('/', *y_pos, *x_pos) || !check_adjacent('\\', *y_pos, *x_pos))) {
				mirror.delete_text();
			}

			if (go_next_room()) {
				setCursorPosition(0, 0);
   				std::cout << "\033[?25l";
				maze_flag = 1;  //To prevent the code from performing the normal room printing function
				maze.initialize();
				maze.print(); //Calling this now, otherwise the room wouldn't print until the player moved
			}
			break;
		case 3:
			maze.create_array();
			maze.print();
			go_next_room();
			break;
		case 4:
			break;
	}
}

void player_action(int *x_pos, int *y_pos) {
	while (1) {
		if (kbhit()) { // If the player presses a button
			char user_input = _getch();
			if ((user_input == 119 || user_input == 72) && room_layout[room_number][*y_pos - 1][*x_pos] == ' ' && *y_pos != 0) {                 //W Up
				(*y_pos)--;
			} else if ((user_input == 115 || user_input == 80) && room_layout[room_number][*y_pos + 1][*x_pos] == ' ' && *y_pos != 29) {           //S Down
				(*y_pos)++;
			} else if ((user_input == 100 || user_input == 77) && room_layout[room_number][*y_pos][*x_pos + 1] == ' ') {           //D Right
				(*x_pos)++;
			} else if ((user_input == 97 || user_input == 75) && room_layout[room_number][*y_pos][*x_pos - 1] == ' ') {            //A Left
				(*x_pos)--;
			} else if (user_input == 101) { //E interact
				room_interactions();
			} else if (user_input == 27) {
				pause_menu();
			}
			room_updates(x_pos, y_pos);
			break;
		}
	}
	
}

int main(void) {
	initialize_code();
	
    while (1) {
    	setCursorPosition(0, 0);
		print_room();
   		std::cout << "\033[?25l";
		player_action(&x_pos, &y_pos);
	}

	return 0;
}