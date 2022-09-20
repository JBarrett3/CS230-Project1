#ifndef itemsDuplicateCheck
#define itemsDuplicateCheck

#include "rooms.h"
#include <stdbool.h>

struct Item {
    char* name;
    struct Item* next;
    bool secret;
};

struct Player {
    struct Item* item;
    struct Room currRoom;
};

struct Character {
    char* name;
    bool secret;
};

void populateItems(struct Room *board[3][3], struct Item *itemList[6]);

void populateCharacters(struct Room *board[3][3], struct Character *characterList[MAX_CHARACTER]);

void inventory(struct Player* player);

void take(struct Player* player, struct Item* itemList[6]);

void drop(struct Player* player, struct Item* itemList[6]);

#endif