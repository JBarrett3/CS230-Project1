#ifndef itemsDuplicateCheck
#define itemsDuplicateCheck

#include "rooms.h"
#include <stdbool.h>

/**
 * struct Item provides a structure for an item, the next item in the
 * linked list, and a boolean to identify it as the secret room if applicable
 */
struct Item {
    char* name;
    struct Item* next;
    bool secret;
};

/**
 * struct provides a player's avatar to navigate the board and pick up items
 */
struct Player {
    struct Item* item;
    struct Room* currRoom;
};

/**
 * struct Character provides a structure for a character with a name and
 * a boolean to identify it as the secret room if applicable
 */
struct Character {
    char* name;
    bool secret;
};

/**
 *
 * @param oldItem
 * @param newItem
 *
 * Provides helper function for adding items to a linked list
 */
void add_item(struct Item** oldItem, struct Item* newItem);

/**
 *
 * @param oldItem
 * @param target
 *
 * Provides helper function for removing items from a linked list
 */
void drop_item(struct Item** oldItem, char target[2048]);

/**
 *
 * @param desiredItem
 * @param target
 * @return requestItem
 *
 * Provides helper function for searching a linked list of pointers and returning the requester pointer
 */
struct Item* check_item(struct Item** desiredItem, char target[2048]);

/**
 *
 * @param potItem
 * @param itemList
 * @return boolean whether the itemExists in the itemList
 *
 * Searches the item list to see if the item name inputted exists
 */
bool itemExists(char* potItem, struct Item* itemList[6]);

/**
 *
 * @param board
 * @param itemList
 *
 * Creates and randomly populates the items into the rooms
 * Also secrets a random secret item
 */
void populateItems(struct Room *board[3][3], struct Item *itemList[6]);

/**
 *
 * @param board
 * @param characterList
 *
 * Creates and randomly populates the characters into the rooms
 * Also secrets a random secret item
 */
void populateCharacters(struct Room *board[3][3], struct Character *characterList[MAX_CHARACTER]);

/**
 *
 * @param player
 *
 * Prints the player's itemList
 */
void inventory(struct Player* player);

/**
 *
 * @param player
 * @param itemList
 *
 * Allows the player to take an item from a room into inventory
 */
void take(struct Player* player, struct Item* itemList[6]);

/**
 *
 * @param player
 * @param itemList
 *
 * Allows the player to drop an item from inventory into a room
 */
void drop(struct Player* player, struct Item* itemList[6]);

#endif