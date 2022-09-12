#include "rooms.h"
#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

#define MAX_CHARACTER 6

void setBoard(struct Room *board[3][3], struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]);
//void getStatus(struct Room *board[3][3]); //debugging purposes
void playGame(struct Room *board[3][3], struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]);
void help();
void list(struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]);

int main() {
    srand(time(NULL));
    //Creating board
    struct Room* board[3][3];
    struct Room* roomList[9];
    struct Character* characterList[MAX_CHARACTER];
    struct Item* itemList[6];
    setBoard(board, roomList, characterList, itemList);
    playGame(board,roomList, characterList, itemList);
}

void setBoard(struct Room *board[3][3], struct Room* roomList[9], struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]) {
    populateRooms(board, roomList);
    populateItems(board, itemList);
    populateCharacters(board, characterList);
}

//void getStatus(struct Room *board[3][3]) { //debugging purposes
//    printf("Rooms:\n");
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            printf("%s ",board[i][j]->name);
//        }
//        printf("\n");
//    }
//    printf("\n");
//
//    printf("Items:\n");
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            printf("Items in the %s: ", board[i][j]->name);
//            if (board[i][j]->item == NULL) {
//                printf("%s\n", "None");
//            } else {
//                struct Item* itemPtr = board[i][j]->item;
//                while (itemPtr != NULL) {
//                    printf("%s, ", itemPtr->name);
//                    itemPtr = itemPtr->next;
//                }
//                printf("\n");
//            }
//        }
//    }
//    printf("\n");
//
//    printf("Characters:\n");
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            struct Character* tempChar;
//            printf("Characters in the %s: ", board[i][j]->name);
//            if (board[i][j]->character[0] == NULL) {
//                printf("%s\n", "None");
//            } else {
//                for (int k = 0; k < MAX_CHARACTER; k++) {
//                    tempChar = board[i][j]->character[k];
//                    if (tempChar == NULL) {
//                        break;
//                    } else {
//                        printf("%s, ", tempChar->name);
//                    }
//                }
//                printf("\n");
//            }
//        }
//    }
//}

void playGame(struct Room* board[3][3], struct Room* roomList[9], struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]) {
    int attemptCount = 0;
    struct Player player = {.item=NULL, .currRoom = board[1][1]};
    printf("Welcome to Clue\n");
    char input[2048];
    char* token;
    char delim[2] = " ";
    while (1) {
        printf("What would you like to do:\n");
        gets(input);
        token = strtok(input,delim);
        if (token == NULL) {
            continue;
        }
        if (strcmp(token,"help") == 0) {
            help();
        } else if (compString(input,"list")) {
            list(roomList, characterList, itemList);
        } else if (compString(input,"look")) {
            look(&player);
        } else if (compString(input,"go")) {
            token = strtok(NULL, delim);
            if (token == NULL) {
                printf("You should specify a direction, try again?\n");
                continue;
            }
            go(&player, token);
        } else if (compString(input,"take")) {
            token = strtok(NULL, delim);
            if (token == NULL) {
                printf("You should specify an item, try again?\n");
                continue;
            }
            take(&player, token);
        } else if (compString(input,"drop")) {
            token = strtok(NULL, delim);
            if (token == NULL) {
                printf("You should specify a item, try again?\n");
                continue;
            }
            drop(&player, token);
        } else if (compString(input, "inventory")) {
            inventory(&player);
        } else if (compString(input, "clue")) {
            char* characterName = strtok(NULL, delim);
            if (token == NULL) {
                printf("You should specify a character and an item, try again?\n");
                continue;
            }
            char* itemName = strtok(NULL, delim);
            if (token == NULL) {
                printf("You should specify a character and an item, try again?\n");
                continue;
            }
            if (clue(&player, characterName, itemName, &attemptCount, roomList, characterList, itemList)) {
                printf("Congratulations, you've won\n");
                freeVars(roomList,  characterList, itemList);
                exit(0);
            } else {
                continue;
            } //otherwise, function displays results.
        } else if (token != NULL) {
            printf("Please start with a command (no spaces)\n");
        } else {
            printf("We couldn't understand that command, try again?\n");
        }
    }
}

void help() {
    printf("Command list: \n");
    printf("\thelp : to see the command list\n");
    printf("\tlist : to lookup the list of items, rooms, and characters\n");
    printf("\tlook : to see the room you are are in\n");
    printf("\tgo : to travel North, South, East, or West\n");
    printf("\ttake : to pick up items\n");
    printf("\tdrop : to drop an item\n");
    printf("\tinventory : to see items in your inventory\n");
    printf("\tclue : to guess the secret answer\n");
    printf("\t\tclue notation => clue <character> <item>\n");
    printf("\n");
}

void list(struct Room* roomList[9], struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]) {
    printf("Rooms:\n");
    for (int i = 0; i < 9; i++) {
        printf("%s,\n", roomList[i]->name);
    }
    printf("\nCharacters:\n");
    for (int i = 0; i < MAX_CHARACTER; i++) {
        printf("%s,\n", characterList[i]->name);
    }
    printf("\nItems:\n");
    for (int i = 0; i < 6; i++) {
        printf("%s,\n", itemList[i]->name);
    }
    printf("\n");
}