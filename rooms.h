#ifndef roomsDuplicateCheck
#define roomsDuplicateCheck

#define MAX_CHARACTER 5

#include "items.h"
#include <stdbool.h>

struct Room {
    char* name;
    struct Room* North;
    struct Room* South;
    struct Room* East;
    struct Room* West;
    struct Item* item;
    struct Character* character[MAX_CHARACTER];
    bool secret;
};

bool compString(char* input, char* expected);

void populateRooms(struct Room *board[3][3], struct Room *roomList[9]);

void look(struct Player* player);

void go(struct Player* player);

int moveCharacter(struct Character* character, struct Room* destination);

struct Character* findAndMoveCharacter(struct Room* roomList[9], char* charName, struct Room* destination);

struct Item *testItemInInventoryOrRoom(struct Player *player, char *itemName);

bool testGuess(struct Character *guessCharacter, struct Room *guessRoom, struct Item *guessItem, int* attemptCount);

bool clue(struct Player *player, char* characterName, char* itemName, int* attemptCount,
          struct Room* roomList[9],  struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]);

void freeVars(struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]);

#endif