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
	Room *dungeon = NEW(Room, "A grimdark dungeon, where troll lives");
	assert(dungeon != NULL);
	Room *boudoir = NEW(Room, "Princess' boudoir");
	assert(boudoir != NULL);

	// put the bad guy in the arena
	arena->bad_guy = NEW(Monster, "The evil minotaur");
	assert(arena->bad_guy != NULL);
	dungeon->bad_guy = NEW(Monster, "The cave troll");
	assert(dungeon->bad_guy != NULL);
	boudoir->bad_guy = NEW(Monster, "The nymphomaniac princess");
	assert(boudoir->bad_guy != NULL);

	// setup the map rooms
	hall->north = throne;
	hall->east = dungeon;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;
	throne->north = boudoir;

	arena->east = throne;
	kitchen->west = throne;
	boudoir->south = dungeon;

	dungeon->west = hall;

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
