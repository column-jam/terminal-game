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

void setCursorPosition(int x, int y) { //Resets the room
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
	if (maze_flag) return; //Disabling the standard print process for the maze room, that has its own function
	for (int i = 0; i < height; i++) {
		string colored_string = "\0";
		for (int j = 0; j < width; j++) {
			switch (room_layout[room_number][i][j]) {
                case '#':        //Concatenating the color codes to the string based on what char is in each cell
                    if (room_color[room_number][i][j] == 0) {
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
		std::cout << colored_string;
		if (i != height - 1) std::cout << "\n";
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
	return 0;
}

void maze_functionality() {
    char lit_maze_tiles[5][7];
	for (int i = 0; i < 7; i++) {
	    for (int j = 0; j < 7; j++) {
	        int row = i + y_pos - 2;
	        int col = j + x_pos - 3;
	        if (row >= 0 && row < height && col >= 0 && col < width) {
	            lit_maze_tiles[i][j] = room_layout[room_number][row][col];
	        }
	    }
	}
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
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

class Laser {
	private:
		int y = 21;
		int x = 60;
		int direction = 1;
		
		bool isLaserActive = 1;
		bool isDoorDown = 0;
		
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
			    room_layout[room_number][i] = room_two_but_technically_the_third_copy[i]; //Reset the room if the beam fails
			}
			isLaserActive = 0;
		}
		void break_door() {
			room_layout[room_number][2] = "########################################################         #######################################################"; //Remove door
			isDoorDown = 1;
		}
		
	public:
		void update() {
			print();
			change_direction();
			if (isLaserBlocked()) reset();
			if (check_adjacent('X', y + 1, x)) break_door();
		}
		bool get_is_laser_active() {
			return isLaserActive;	
		}
		bool get_is_door_down() {
			return isDoorDown;
		}
};

class Mirror {
	private:
		
	public:
		int check_direction(char symbol) {
			return check_adjacent(symbol, y_pos, x_pos);
		}
		void turn(int direction, char symbol) {
			switch(direction) {
				case 1: room_layout[room_number][y_pos - 1][x_pos] = symbol; break;
				case 2: room_layout[room_number][y_pos][x_pos + 1] = symbol; break;
				case 3: room_layout[room_number][y_pos + 1][x_pos] = symbol; break;
				case 4: room_layout[room_number][y_pos][x_pos - 1] = symbol; break;
			}
			flag_mirror_turned = 1;
		}
};

void room_interactions() {
	switch(room_number) {
		case 0:
			if (check_adjacent('O', y_pos, x_pos)) { //Button deletes door
					room_layout[0][2] = "########################################################         #######################################################";
			} 
			break;
		case 1:
			if (x_pos == 83 && y_pos == 17) {
				flag_second_room_button_one = 1;
				room_layout[room_number][23] = "###########################                              *Click!                             ###########################";
				setCursorPosition(0, 0);
				print_room();
   				std::cout << "\033[?25l";
				Sleep(500);
				room_layout[room_number][23] = "###########################                                                                  ###########################";
			}
			if (x_pos == 38 && y_pos == 25) {
				flag_second_room_button_two = 1;
				room_layout[room_number][23] = "###########################                              *Click!                             ###########################";
				setCursorPosition(0, 0);
				print_room();
   				std::cout << "\033[?25l";
				Sleep(500);
				room_layout[room_number][23] = "###########################                                                                  ###########################";
			}
			break;
		case 2:
			Mirror mirror;
			if (mirror.check_direction('/')) {  //Checking whether there's a / or \ present, then swapping them
				mirror.turn(mirror.check_direction('/'), '\\');
			} else if (mirror.check_direction('\\')) {
				mirror.turn(mirror.check_direction('\\'), '/');
			}
			
			if (check_adjacent('O', y_pos, x_pos)) {
				for (int i = 0; i < height; i++) {
			    	room_two_but_technically_the_third_copy[i] = room_layout[room_number][i]; //Store the room before the laser activates
				}
				Laser laser;
				while (laser.get_is_laser_active()) {
					laser.update();
				}
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
			if (check_adjacent('O', *y_pos, *x_pos) && room_layout[0][2][59] == 'X') {
					room_layout[room_number][15] = "###########################       *Interact with green buttons to make things happen         ###########################";
					flag_first_room_button_text = 1;
			} else if (flag_first_room_button_text == 1){
				room_layout[room_number][15] = "###########################                                                                  ###########################";
				flag_first_room_button_text = 0;
			} else if (room_layout[room_number][*y_pos - 1][*x_pos] == 'X') {
				room_layout[room_number][15] = "###########################                     *It seems to be locked                       ###########################";
				flag_first_room_door_text = 1;
			} else if (flag_first_room_door_text == 1){
				room_layout[room_number][15] = "###########################                                                                  ###########################";
				flag_first_room_door_text = 0;
			}
			if (*x_pos <= 64 && *x_pos >= 56 && *y_pos == 0) { //If player reaches the top of the screen, move them to the next room
				room_number++;
				(*x_pos) = 61;
				(*y_pos) = 28;
			} 
			break;
   		case 1:
   			if (room_layout[room_number][*y_pos - 1][*x_pos] == '_') {
   				room_layout[room_number][23] = "###########################                  *Looks like some kind of mirror                 ###########################";
   				flag_second_room_mirror_text = 1;
			} else if (flag_second_room_mirror_text == 1) {
				room_layout[room_number][23] = "###########################                                                                  ###########################";
				flag_second_room_mirror_text = 0;
			}
			if (flag_second_room_button_one == 1 && flag_second_room_button_two == 1) {
				room_layout[room_number][14] = "###########################                                                                  ###########################";
			}
			if (*x_pos <= 64 && *x_pos >= 56 && *y_pos == 0) {
				room_number++;
				(*x_pos) = 61;
				(*y_pos) = 28;
			}
			break;
		case 2:
			if (check_adjacent('^', *y_pos, *x_pos)) {
				room_layout[room_number][9] = "###########################             *A laser? Maybe it can break that door...            ###########################";
   				flag_third_room_light_text = 1;
			} else if (flag_third_room_light_text == 1) {
				room_layout[room_number][9] = "###########################                                                                  ###########################";
				flag_third_room_light_text = 0;
			}
			if ((check_adjacent('/', *y_pos, *x_pos) || check_adjacent('\\', *y_pos, *x_pos)) && !flag_mirror_turned) {
				room_layout[room_number][9] = "###########################                 *I think I can turn that mirror                  ###########################";
			} else if (room_layout[room_number][9][44] == '*' && (flag_mirror_turned || !check_adjacent('/', *y_pos, *x_pos) || !check_adjacent('\\', *y_pos, *x_pos))) {
				room_layout[room_number][9] = "###########################                                                                  ###########################";
			}
			if (*x_pos <= 64 && *x_pos >= 56 && *y_pos == 0) {
				room_number++;
				(*x_pos) = 61;
				(*y_pos) = 28;
		    	setCursorPosition(0, 0);
   				std::cout << "\033[?25l";
				maze_flag = 1;  //To prevent the code from performing the normal room printing function
				maze_functionality(); //Calling this now, otherwise the room wouldn't print until the player moved
			}
			break;
		case 3:
			maze_functionality();
			break;
		case 4:
			break;
	}
}

void player_action(int *x_pos, int *y_pos) {
	temp_x = *x_pos;
	temp_y = *y_pos;
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