#include "items.h"
#include "rooms.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void populateItems(struct Room *board[3][3], struct Item *itemList[6]) {
    //creating Items
    struct Item* revolver = malloc(sizeof(struct Item));
    revolver->name = "revolver";
    revolver->next = NULL;
    struct Item* dagger = malloc(sizeof(struct Item));
    dagger->name = "dagger";
    dagger->next = NULL;
    struct Item* leadPipe = malloc(sizeof(struct Item));
    leadPipe->name = "leadPipe";
    leadPipe->next = NULL;
    struct Item* rope = malloc(sizeof(struct Item));
    rope->name = "rope";
    rope->next = NULL;
    struct Item* candlestick = malloc(sizeof(struct Item));
    candlestick->name = "candlestick";
    candlestick->next = NULL;
    struct Item* wrench = malloc(sizeof(struct Item));
    wrench->name = "wrench";
    wrench->next = NULL;

    //creating itemList
    itemList[0] = revolver; itemList[1] = dagger; itemList[2] = leadPipe;
    itemList[3] = rope; itemList[4] = candlestick; itemList[5] = wrench;

    //randomizing itemList
    for (int i = 0; i < 6; ++i) {
        int j = rand() % (6); //random number between 0 and 5 inclusive
        struct Item* temp = itemList[i]; //swap element in index i with random index
        itemList[i] = itemList[j];
        itemList[j] = temp;
    }

    itemList[rand() % (6)]->secret = true; //setting secret room

    //randomly selecting rooms to receive items
    int itemRooms[6] = {-1, -1, -1, -1, -1, -1};
    int itemsDistributed = 0;
    int potentialRoom;
    while (itemsDistributed < 6) {
        potentialRoom = rand() % 8;
        for (int i = 0; i < 6; i++) { //todo speedUp
            if (itemRooms[i] == potentialRoom) {
                break;
            }
            if (i == itemsDistributed) {
                itemRooms[itemsDistributed] = potentialRoom;
                itemsDistributed++;
                break;
            }
        }
    }

    //pre-setting rooms to NULL
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j]->item = NULL;
        }
    }

    //distributing items into rooms
    int across;
    int down;
    for (int i = 0; i < 6; i++) {
        across = itemRooms[i] % 3;
        down = itemRooms[i] / 3;
        board[down][across]->item = itemList[i];
    }

}

void populateCharacters(struct Room *board[3][3], struct Character *characterList[MAX_CHARACTER]) {
    //creating characters
    struct Character* mrsWhite = malloc(sizeof(struct Character));
    mrsWhite->name = "mrsWhite";
    struct Character* mrsPeacock = malloc(sizeof(struct Character));
    mrsPeacock->name = "mrsPeacock";
    struct Character* professorPlum = malloc(sizeof(struct Character));
    professorPlum->name = "professorPlum";
    struct Character* colonelMustard = malloc(sizeof(struct Character));
    colonelMustard->name = "colonelMustard";
    struct Character* missScarlett = malloc(sizeof(struct Character));
    missScarlett->name = "missScarlett";
    struct Character* reverendGreen = malloc(sizeof(struct Character));
    reverendGreen->name = "reverendGreen";

    //creating characterList
    characterList[0] = mrsWhite; characterList[1] = mrsPeacock; characterList[2] = professorPlum;
    characterList[3] = colonelMustard; characterList[4] = missScarlett; characterList[5] = reverendGreen;
    //TODO implement limiting effect of characterList based on number of characters in play

    //randomizing characterList
    for (int i = 0; i < MAX_CHARACTER; ++i) {
        int j = rand() % (MAX_CHARACTER); //random number between 0 and MAX_CHARACTER exclusive
        struct Character * temp = characterList[i]; //swap element in index i with random index
        characterList[i] = characterList[j];
        characterList[j] = temp;
    }

    characterList[rand() % (MAX_CHARACTER)]->secret = true; //setting secret character

    //randomly selecting rooms to receive characters
    int itemRooms[6] = {-1, -1, -1, -1, -1, -1};
    int itemsDistributed = 0;
    int potentialRoom;
    while (itemsDistributed < 6) {
        potentialRoom = rand() % 8;
        for (int i = 0; i < 6; i++) { //todo speedUp
            if (itemRooms[i] == potentialRoom) {
                break;
            }
            if (i == itemsDistributed) {
                itemRooms[itemsDistributed] = potentialRoom;
                itemsDistributed++;
                break;
            }
        }
    }

    //pre-setting rooms to NULL
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < MAX_CHARACTER; k++) {
                board[i][j]->character[k] = NULL;
            }
        }
    }

    //distributing characters into rooms
    int across;
    int down;
    for (int i = 0; i < 6; i++) {
        across = itemRooms[i] % 3;
        down = itemRooms[i] / 3;
        board[down][across]->character[0] = characterList[i];
    }
}

void inventory(struct Player* player) {
    struct Item* itemInInventory = player->item;
    if (player->item == NULL) {
        printf("Inventory is empty\n");
    } else {
        printf("Items in inventory: ");
        while (itemInInventory != NULL) {
            printf("%s, ", itemInInventory->name);
            itemInInventory = itemInInventory->next;
        }
        printf("\n");
    }
    printf("\n");
}

struct Item* checkIfItemInRoom(struct Room* room, char target[2048]) {
    struct Item* temp = room->item;
    while (temp != NULL) {
        if (compString(temp->name, target)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void removeItemFromRoom(struct Room* room, char target[100]) {
    struct Item* temp = room->item;
    struct Item* prev = NULL;

    if (temp != NULL && compString(temp->name,target)) {
        room->item = temp->next;
        return;
    }

    while (temp != NULL && !compString(temp->name, target)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
}

void addItemToInventory(struct Player* player, struct Item* newItem) {
    struct Item* temp = player->item;
    if (temp == NULL) {
        player->item = newItem;
    } else {
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}

void take(struct Player* player, char* input) {
    struct Item* removedItem = checkIfItemInRoom(player->currRoom, input);
    if (removedItem != NULL) {
        addItemToInventory(player, removedItem);
        removeItemFromRoom(player->currRoom, input);
        removedItem->next = NULL;
        printf("%s added to inventory\n", removedItem->name);
    } else {
        printf("%s not in room\n", input);
    }
}

struct Item* checkIfItemInInventory(struct Player* player, char target[100]) {
    struct Item* temp = player->item;
    while (temp != NULL) {
        if (compString(temp->name, target)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void removeItemFromInventory(struct Player* player, char target[100]) {
    struct Item* temp = player->item;
    struct Item* prev = NULL;

    if (temp != NULL && compString(temp->name,target)) {
        player->item = temp->next;
        return;
    }

    while (temp != NULL && !compString(temp->name, target)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    prev->next = temp->next;
}

void addItemToRoom(struct Player* player, struct Item* newItem) {
    struct Item* itemPtr = player->currRoom->item;
    if (itemPtr == NULL) {
        player->currRoom->item = newItem;
    } else {
        while(itemPtr->next != NULL) {
            itemPtr = itemPtr->next;
        }
        itemPtr->next = newItem;
    }
}

void drop(struct Player* player, char* input) {
    struct Item* removedItem = checkIfItemInInventory(player, input);
    if (removedItem != NULL) {
        addItemToRoom(player, removedItem);
        removeItemFromInventory(player, input);
        removedItem->next = NULL;
        printf("%s added to room\n", removedItem->name);
    } else {
        printf("%s not in inventory\n", input);
    }
}