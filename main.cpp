#include <iostream>
#include "conio/conio.h"
#include <ctime>
#include <cstdlib>
#include <unistd.h>

// variables //
const int window_width = 40;
const int window_height = 40;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int n_tail;
bool is_game_over;
char snake_head = '0';
char snake_tail = 'o';
char fruit = 'F';
enum Directions {
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
Directions dir;
// end variables //

// functions //
void setup() {
	is_game_over = false;
	dir = STOP;

	// Divide the dimentions by 2 to center the snake in the screen //
	x = window_width / 2;
	y = window_height / 2;

	srand(time(nullptr));
	fruit_x = rand() % window_width;
	fruit_y = rand() % window_height;
	score = 0;
}
void draw() {
	system("clear"); // if you on windows change "clear" to "cls" //

	// draw the top wall //
	for(int i = 0 ; i < window_width ; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;
	// end draw the top wall //

	// print the map //
	for(int i = 0 ; i < window_height ; i++) {
		for(int j = 0 ; j < window_width ; j++) {
			if(j == 0) {
				std::cout << "#";
			}
			// print the snake head //
			if(i == y && j == x) {
				std::cout << snake_head;
			}
			else if(i == fruit_y && j == fruit_x) {
				std::cout << fruit;
			}
			else {
				bool is_printed = false;
				for(int k = 0 ; k < n_tail ; k++) {
					if(tail_x[k] == j && tail_y[k] == i) {
						std::cout << snake_tail;
						is_printed == true;
					}
				}
				if(!is_printed) {
					std::cout << " ";
				}
			}
			if(j == window_width - 1) {
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
	// draw the bottom wall //
	for(int i = 0 ; i < window_height ; i++) {
		std::cout << "#";
	}
	std::cout << std::endl;
	// end draw the bottom wall //

	// print score //
	std::cout << "Score : " << score << std::endl;
}
void user_input() {
	// check if button is pressed //
	if(kbhit()) {
		// check the type of button //
		switch(getch()) {
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'x':
				is_game_over = true;
				break;
		}
	}
}
void game_logic() {
	// check the directions //

	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int second_prev_x, second_prev_y;
	tail_x[0] = x;
	tail_y[0] = y;
	for(int i = 1 ; i < n_tail ; i++) {
		second_prev_x = tail_x[i];
		second_prev_y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = second_prev_x;
		prev_y = second_prev_y;
	}

	switch(dir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	// check if the head of snake is hit the wall //
	if(x < 0 || x >= window_width || y < 0 || y >= window_height) {
        	is_game_over = true;
    	}

	for(int i = 0 ; i < n_tail ; i++) {
		if(tail_x[i] == x && tail_y[i] == y) {
			is_game_over = true;
		}
	}

	// increase the score while the snake eat it //
	if(x == fruit_x && y == fruit_y) {
		score += 1;
		fruit_x = rand() % window_width;
		fruit_y = rand() % window_height;
		n_tail++;
	}
}
// end functions //

int main() {
	setup();
	while(!is_game_over) {
		draw();
		user_input();
		game_logic();
		sleep(1);
	}

	return EXIT_SUCCESS;
}
