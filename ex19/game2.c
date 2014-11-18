#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "game.h"

int Map_init(void *self)
{
	Map *map = self;

	// make some rooms for a small map
	Room *hall = NEW(Room, "The great Hall");
	assert(hall != NULL);
	Room *throne = NEW(Room, "The throne room");
	assert(throne != NULL);
	Room *arena = NEW(Room, "The arena, with the minotaur");
	assert(arena != NULL);
	Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
	assert(kitchen != NULL);

	// put the bad guy in the arena
	arena->bad_guy = NEW(Monster, "The evil minotaur");
	assert(arena->bad_guy != NULL);

	// setup the map rooms
	hall->north = throne;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;

	arena->east = throne;
	kitchen->west = throne;

	// start the map and the character off in the hall
	map->start = hall;
	map->location = hall;

	return 1;
}

Object MapProto = {
	.init = Map_init,
	.move = Map_move,
	.attack = Map_attack
};

int main(int argc, char *argv[])
{
	// simple way to setup the randomness
	srand(time(NULL));

	// make our map to work with
	Map *game = NEW(Map, "The Hall of the Minotaur.");
	assert(game != NULL);

	printf("You enter the ");
	game->location->_(describe)(game->location);

	while(process_input(game)) {
	}

	return 0;
}
