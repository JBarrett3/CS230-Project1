#ifndef roomsDuplicateCheck
#define roomsDuplicateCheck

#define MAX_CHARACTER 5

#include "items.h"
#include <stdbool.h>

/**
 * struct Room provides a structure for the room, its neighboring rooms, an array of characters in the room,
 * a linked list of items in the room, and a boolean for if it is randomly selected to be the secret room
 */
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

/**
 *
 * @param input
 * @param expected
 * @return boolean of whether the strings are equivalent
 *
 * Compares each character of strings case independently
 */
bool compString(char* input, char* expected);

/**
 *
 * @param board
 * @param roomList
 *
 * Sets the setBoard function to populate the board with randomized rooms
 * Also selects a random room to be the secret room
 */
void populateRooms(struct Room *board[3][3], struct Room *roomList[9]);

/**
 *
 * @param player
 *
 * Shows the player's current room, its neighboring rooms, the items and the characters in the room
 */
void look(struct Player* player);

/**
 *
 * @param player
 *
 * Allows the player to travel to its neighboring rooms
 */
void go(struct Player* player);

/**
 *
 * @param character
 * @param destination
 * @return the index of the room the character is moved to
 *
 * Moves the selected character from it's original room to the selected destination room
 */
int moveCharacter(struct Character* character, struct Room* destination);

/**
 *
 * @param roomList
 * @param charName
 * @param destination
 * @return the pointer to the character requested
 *
 * Finds and moves the requested character to the player's current room using the moveCharacter function
 */
struct Character* findAndMoveCharacter(struct Room* roomList[9], char* charName, struct Room* destination);

/**
 *
 * @param player
 * @param itemName
 * @return the item if found, null otherwise
 *
 * Finds the requested item and checks if it is in the player's current room
 */
struct Item *testItemInInventoryOrRoom(struct Player *player, char *itemName);

/**
 *
 * @param guessCharacter
 * @param guessRoom
 * @param guessItem
 * @param attemptCount
 * @return true if the guess matches the secret, false otherwise
 *
 * Tests whether the player's guess matches the randomly selected secret character, room, and item
 * It also prints <element> match if the room, item, or character elements match the secret
 */
bool testGuess(struct Character *guessCharacter, struct Room *guessRoom, struct Item *guessItem, int* attemptCount);

/**
 *
 * @param player
 * @param characterName
 * @param itemName
 * @param attemptCount
 * @param roomList
 * @param characterList
 * @param itemList
 * @return true if the guess matches the secret, false otherwise
 */
bool clue(struct Player *player, char* characterName, char* itemName, int* attemptCount,
          struct Room* roomList[9],  struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]);

/**
 *
 * @param roomList
 * @param characterList
 * @param itemList
 *
 * Frees all variables malloced earlier in the code
 */
void freeVars(struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]);

#endif