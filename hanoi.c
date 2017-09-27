#include <stdio.h>

#define NO_DISK 0

#define N 4 // Initial tower size

typedef unsigned int	Disk; // A disk is defined by his radius
typedef Disk			Pillar[N]; // A pillar is an array of N Disk
typedef Pillar			Game[3]; // The game is an array of 3 Pillar

/*
 * Function declaration
 */
void					init(Disk game[3][N]);
void					display_char(char c, int nb);
void					display_disk(Disk disk);
void					display_game(Disk game[3][N]);
size_t					top(Pillar pillar);
void					move(Pillar origin, Pillar dest);
unsigned int			other(unsigned int p1, unsigned int p2);
void					hanoi(unsigned int n, unsigned int origin,
							  unsigned int dest, Disk game[3][N]);


int						main(void) {
	Game				game;

	init(game);
	display_game(game);
	hanoi(N, 0, 2, game);
	return (0);
}

/*
 * Initialise the game
 */
void					init(Game game) {
	for (size_t pillar_nb = 0; pillar_nb < 3; pillar_nb++) {
		for (size_t disk_slot = 0; disk_slot < N; disk_slot++) {
			if (pillar_nb == 0) { // First pillar is initialized with the radius
				game[pillar_nb][disk_slot] = disk_slot + 1;
			} else { // Second and third Pillar are initialized with NO_DISK
				game[pillar_nb][disk_slot] = NO_DISK;
			}
		}
	}
}

/*
 * Display nb times the char c
 */
void					display_char(char c, int nb) {
	while (nb--) {
		printf("%c", c);
	}
}

/*
 * Display a Disk
 */
void					display_disk(Disk disk) {
	if (disk == NO_DISK) {
		display_char(' ', N - 1);
		display_char('|', 1);
		display_char(' ', N);
	} else {
		display_char(' ', N - disk);
		display_char('-', 2 * disk - 1);
		display_char(' ', N - disk + 1);
	}
}

/*
 * Display the Game
 *
 * Unlike the function init, here we iterate through the Game array by column
 * first and then by row because we need to display the Game line by line
 */
void					display_game(Game game) {
	display_char('\n', 1);
	for (size_t col = 0; col < N; col++) {
		for (size_t row = 0; row < 3; row++) {
			display_disk(game[row][col]);
		}
		display_char('\n', 1);
	}
	display_char('#', 6 * N - 1); // Display the base
	display_char('\n', 1);
}

/*
 * Return the position of the first Disk of a Pillar, or N if there is no Disk
 */
size_t					top(Pillar pillar) {
	size_t				top = 0;

	while (top < N && pillar[top] == NO_DISK) {
		top++;
	}
	return (top);
}

/*
 * Check if the move is correct and if so move the Disk from orign to dest
 */
void					move(Pillar origin, Pillar dest) {
	size_t				top_origin;
	size_t				top_dest;

	top_origin = top(origin);
	if (top_origin < N) { // Check that there is a Disk at the specified origin
		top_dest = top(dest);
		/*
		 * Here we check that the move is valid, before moving it
		 *
		 * We check if top_dest == N, wich would mean that the destination
		 * Pillar is empty
		 *
		 * Or if the Disk on the top of the origin pillar is smaller than the
		 * disk on the top of the destination Pillar
		 */
		if (top_dest == N || origin[top_origin] < dest[top_dest]) {
			dest[top_dest - 1] = origin[top_origin];
			origin[top_origin] = NO_DISK;
		}
	}
}

/*
 * Return the index of the third pillar given the two other
 */
unsigned int			other(unsigned int p1, unsigned int p2) {
	return (3 - p1 - p2);
}

/*
 * Solve and display recursively the game
 */
void					hanoi(unsigned int n, unsigned int origin,
							  unsigned int dest, Game game) {
	unsigned int		third_pillar;

	if (n != 0) {
		third_pillar = other(origin, dest);
		hanoi(n - 1, origin, third_pillar, game);
		move(game[origin], game[dest]);
		display_game(game);
		hanoi(n - 1, third_pillar, dest, game);
	}
}
