#ifndef roomsDuplicateCheck
#define roomsDuplicateCheck

#define MAX_CHARACTER 6

#include "items.h"
#include <stdbool.h>

bool compString(char* input, char* expected);

struct Room {
    char* name;
    struct Room* North;
    struct Room* South;
    struct Room* East;
    struct Room* West;
    struct Item* item;
    struct Character* character[MAX_CHARACTER+1]; //+1 for player to enter
    bool secret;
};

void populateRooms(struct Room *board[3][3], struct Room *roomList[9]);

void look(struct Player* player);

void go(struct Player* player, char* input);

bool clue(struct Player *player, char* characterName, char* itemName, int* attemptCount,
          struct Room* roomList[9],  struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]);

void freeVars(struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]);

#else /* duplicateSafeguard */
#endif