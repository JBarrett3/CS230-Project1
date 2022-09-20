#include "rooms.h"
#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void setBoard(struct Room *board[3][3], struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]);
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

void playGame(struct Room* board[3][3], struct Room* roomList[9], struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]) {
    int attemptCount = 0;
    struct Player player = {.item=NULL, .currRoom = board[1][1]};
    printf("Welcome to Clue\n");
    char input[2048];
    char* token;
    char delim[2] = " ";
    while (1) {
        printf("What would you like to do:\n");
        fgets(input, 2048, stdin);
        token = strtok(input,delim);
        if (token == NULL) {
            continue;
        }
        if (compString(token,"help") == 0) {
            help();
        } else if (compString(token,"list")) {
            list(roomList, characterList, itemList);
        } else if (compString(token,"look")) {
            look(&player);
        } else if (compString(token,"go")) {
            go(&player);
        } else if (compString(token,"take")) {
            take(&player, itemList);
        } else if (compString(token,"drop")) {
            drop(&player, itemList);
        } else if (compString(token, "inventory")) {
            inventory(&player);
        } else if (compString(token, "clue")) {
            char* characterFirstName = strtok(NULL, delim);
            if (characterFirstName == NULL) {
                printf("You should specify a character and an item, try again?\n");
                continue;
            }
            char* characterLastName = strtok(NULL, delim);
            if (characterLastName == NULL) {
                printf("You should specify a character and an item, try again?\n");
                continue;
            }
            char* itemName = strtok(NULL, delim);
            if (itemName == NULL) {
                printf("You should specify a character and an item, try again?\n");
                continue;
            }
            char characterFullName[2048] = "";
            strcat(characterFullName, characterFirstName);
            strcat(characterFullName, " ");
            strcat(characterFullName, characterLastName);
            if (clue(&player, characterFullName, itemName, &attemptCount, roomList, characterList, itemList)) {
                printf("Congratulations, you've won\n");
                freeVars(roomList,  characterList, itemList);
                exit(0);
            } else {
                continue;
            }
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
    printf("\t\tclue notation => clue <character first name> <character last name> <item>\n");
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