#include "rooms.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool compString(char* input, char* expected) {
    if (strlen(input) != strlen(expected)) {
        return false;
    }
    for (int i = 0; i < strlen(expected); i++) {
        if (tolower(input[i]) != tolower(expected[i])) {
            return false;
        }
    }
    return true;
}

void populateRooms(struct Room board[3][3], struct Room roomList[9]) {
    //creating Rooms
    struct Room* kitchen = malloc(sizeof(struct Room));
    kitchen->name="kitchen";
    kitchen->secret = false;
    struct Room* hall = malloc(sizeof(struct Room));
    hall->name="hall";
    hall->secret = false;
    struct Room* ballroom = malloc(sizeof(struct Room));
    ballroom->name="ballroom";
    ballroom->secret = false;
    struct Room* conservatory = malloc(sizeof(struct Room));
    conservatory->name="conservatory";
    conservatory->secret = false;
    struct Room* diningRoom = malloc(sizeof(struct Room));
    diningRoom->name="dining room";
    diningRoom->secret = false;
    struct Room* study = malloc(sizeof(struct Room));
    study->name="study";
    study->secret = false;
    struct Room* billiardRoom = malloc(sizeof(struct Room));
    billiardRoom->name="billiard room";
    billiardRoom->secret = false;
    struct Room* library = malloc(sizeof(struct Room));
    library->name="library";
    library->secret = false;
    struct Room* lounge = malloc(sizeof(struct Room));
    lounge->name="lounge";
    lounge->secret = false;

    //creating roomList
    roomList[0] = kitchen; roomList[1] = hall; roomList[2] = ballroom;
    roomList[3] = conservatory; roomList[4] = diningRoom; roomList[5] = study;
    roomList[6] = billiardRoom; roomList[7] = library; roomList[8] = lounge;

    //randomizing roomList
    for (int i = 9 - 1; i >= 1; i--) {
        int j = rand() % (i+1); //j is a random integer where 0 <= j <= i
        struct Room* temp = roomList[i]; //swap itemList[i] with itemList[j]
        roomList[i] = roomList[j];
        roomList[j] = temp;
    }

    roomList[rand() % (9)]->secret = true;

    //populating board from room list
    int across = 0;
    int down = 0;
    for (int i = 0; i < 9; i++) {
        if (across == 3) {
            across = 0;
            down++;
        }
        board[down][across] = roomList[i];
        across++;
    }

    //setting directions
    for (int i = 0; i < 9; i++) {
        if (i < 6) { //excludes bottom row - 7,8,9
            roomList[i]->South = roomList[i + 3];
        } else {
            roomList[i]->South = NULL;
        }
        if (i > 2) { //excludes top row - 0,1,2
            roomList[i]->North = roomList[i - 3];
        } else {
            roomList[i]->North = NULL;
        }
        if (i % 3 != 2) { //excludes right column - 2,5,8
            roomList[i]->East = roomList[i + 1];
        } else {
            roomList[i]->East = NULL;
        }
        if (i % 3 != 0) { //excludes left column - 0,3,6
            roomList[i]->West = roomList[i - 1];
        } else {
            roomList[i]->West = NULL;
        }
    }
}

void look(struct Player* player) {
    printf("You are in the %s\n", player->currRoom->name);
    if (player->currRoom->North == NULL) {
        printf("To your North : %s\n", "empty");
    } else {
        printf("To your North : %s\n", player->currRoom->North->name);
    }
    if (player->currRoom->East == NULL) {
        printf("To your East : %s\n", "empty");
    } else {
        printf("To your East : %s\n", player->currRoom->East->name);
    }
    if (player->currRoom->South == NULL) {
        printf("To your South : %s\n", "empty");
    } else {
        printf("To your South : %s\n", player->currRoom->South->name);
    }
    if (player->currRoom->West == NULL) {
        printf("To your West : %s\n", "empty");
    } else {
        printf("To your West : %s\n", player->currRoom->West->name);
    }
    struct Item* itemInRoom = player->currRoom->item;
    printf("Items in room: ");
    if (itemInRoom == NULL) {
        printf("Room is empty\n");
    } else {
        while (itemInRoom != NULL) {
            printf("%s, ", itemInRoom->name);
            itemInRoom = itemInRoom->next;
        }
        printf("\n");
    }
    printf("Characters in room: ");
    if (player->currRoom->character[0] == NULL) {
        printf("No characters in room\n");
    } else {
        for (int i = 0; i < MAX_CHARACTER; i++) {
            if (player->currRoom->character[i] == NULL) {
                break;
            } else {
                printf("%s, ", player->currRoom->character[i]->name);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void go(struct Player* player) {
    char input[2048];
    char* token;
    char delim[2] = " ";
    printf("In what direction would you like to go?:\n");
    while (1) {
        gets(input);
        token = strtok(input,delim);
        if (token == NULL) {
            continue;
        } else if (compString(token, "exit")) {
            break;
        }
        if (compString(token,"North")) {
            if (player->currRoom->North == NULL) {
                printf("There is no room north of you\n");
            } else {
                printf("Going North...\n");
                player->currRoom = player->currRoom->North;
            }
            break;
        } else if (compString(token,"East")) {
            if (player->currRoom->East == NULL) {
                printf("There is no room east of you\n");
            } else {
                printf("Going East...\n");
                player->currRoom = player->currRoom->East;
            }
            break;
        } else if (compString(token,"South")) {
            if (player->currRoom->South == NULL) {
                printf("There is no room south of you\n");
            } else {
                printf("Going South...\n");
                player->currRoom = player->currRoom->South;
            }
            break;
        } else if (compString(token, "West")) {
            if (player->currRoom->West == NULL) {
                printf("There is no room west of you\n");
            } else {
                printf("Going West...\n");
                player->currRoom = player->currRoom->West;
            }
            break;
        } else {
            printf("I couldn't understand that direction, try again? Or enter \"exit\" to return the other actions\n");
        }
    }
    printf("\n");
}

int moveCharacter(struct Character* character, struct Room* destination) {
    for (int k = 0; k < MAX_CHARACTER; k++) {
        if (destination->character[k] == NULL) {
            destination->character[k] = character;
            return k;
        }
    }
    printf("ERROR : Room at max capacity"); //defensive coding
    return 0;
}

struct Character* findAndMoveCharacter(struct Room* roomList[9], char* charName, struct Room* destination) {
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < MAX_CHARACTER; k++) {
            if (roomList[i]->character[k] == NULL) {
                continue;
            }
            if (compString(roomList[i]->character[k]->name, charName)) {
                int index;
                if (compString(destination->name, roomList[i]->name)) {
                    return destination->character[k];
                } //no move required
                index = moveCharacter(roomList[i]->character[k], destination);
                roomList[i]->character[k] = NULL;
                return destination->character[index];
            }
        }
    }
    printf("%s is not a character\n", charName);
    return NULL;
}

struct Item *testItemInInventoryOrRoom(struct Player *player, char *itemName) {
    struct Item* itemInventory = player->item;
    while (itemInventory != NULL) {
        if (compString(itemInventory->name, itemName)) {
            return itemInventory;
        }
        itemInventory = itemInventory->next;
    }
    struct Item* itemRoom = player->currRoom->item;
    while (itemRoom != NULL) {
        if (compString(itemRoom->name, itemName)) {
            return itemRoom;
        }
        itemRoom = itemRoom->next;
    }
    return NULL;
}

bool testGuess(struct Character *guessCharacter, struct Room *guessRoom, struct Item *guessItem, int* attemptCount) {
    if (guessCharacter->secret == true) {
        printf("Character match\n");
    }
    if (guessRoom->secret == true) {
        printf("Room match\n");
    }
    if (guessItem->secret == true) {
        printf("Item match\n");
    }
    if (guessCharacter->secret && guessRoom->secret && guessItem->secret) {
        return true;
    } else {
        printf("Make another guess\n");
        *attemptCount = *attemptCount + 1;
        return false;
    }
}

bool clue(struct Player *player, char* characterName, char* itemName, int* attemptCount,
          struct Room* roomList[9],  struct Character* characterList[MAX_CHARACTER], struct Item* itemList[6]) {
    if (*attemptCount >= 10) {
        printf("Guess count reached. Sorry\n");
        freeVars(roomList,  characterList, itemList);
        exit(0);
    }
    struct Room* guessRoom = player->currRoom;
    struct Item* guessItem = testItemInInventoryOrRoom(player, itemName);
    if (guessItem == NULL) {
        printf("Item not in inventory or room, guess not acceptable\n");
        *attemptCount = *attemptCount+1;
        return false;
    }
    struct Character* guessCharacter = findAndMoveCharacter(roomList, characterName, player->currRoom);
    if (guessCharacter == NULL) {
        return false; //not a character
    }
    return testGuess(guessCharacter, guessRoom, guessItem, attemptCount);
}

void freeVars(struct Room *roomList[9], struct Character *characterList[MAX_CHARACTER], struct Item *itemList[6]) {
    for (int i = 0; i < 9; i++) {
        free(roomList[i]);
    }
    for (int i = 0; i < MAX_CHARACTER; i++) {
        free(characterList[i]);
    }
    for (int i = 0; i < 6; i++) {
        free(itemList[i]);
    }
}
