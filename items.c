#include "items.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void add_item(struct Item** oldItem, struct Item* newItem) {
    struct Item** temp = oldItem;
    if ((*temp) == NULL) { //empty list
        *oldItem = newItem; //set list to inputted item
    } else {
        while((*temp)->next != NULL) { //move to end of list
            temp = &(*temp)->next;
        }
        (*temp)->next = newItem; //add new item
    }
}

void drop_item(struct Item** oldItem, char target[2048]) {
    struct Item** temp = oldItem;
    struct Item** prev = NULL;

    if ((*temp) != NULL && compString((*temp)->name,target)) { //item found and is first item
        *oldItem = (*temp)->next;
        return;
    }

    while ((*temp) != NULL && !compString((*temp)->name, target)) { //item not found but list continues
        prev = temp; //update pointers
        temp = &(*temp)->next; //update pointers
    }

    if ((*temp) == NULL) { //item not found and list ended
        return;
    }

    (*prev)->next = (*temp)->next; //update pointers forward
}

struct Item* check_item(struct Item** originalItem, char target[2048]) {
    struct Item** temp = originalItem; //temp pointer to original item to avoid losing reference
    while ((*temp) != NULL) {
        if (compString((*temp)->name, target)) {
            return *temp; //target found, returns target
        }
        temp = &((*temp)->next); //update pointers to next item
    }
    return NULL; //item not found
}

bool itemExists(char* potItem, struct Item* itemList[6]) {
    for (int i = 0; i < 6; i++) { //iterates through item list to find item
        if (compString(potItem, itemList[i]->name)) {
            return true;
        }
    }
    return false;
}

void populateItems(struct Room *board[3][3], struct Item *itemList[6]) {
    //creating Items
    struct Item* revolver = malloc(sizeof(struct Item));
    revolver->name = "revolver";
    revolver->next = NULL;
    struct Item* dagger = malloc(sizeof(struct Item));
    dagger->name = "dagger";
    dagger->next = NULL;
    struct Item* pipe = malloc(sizeof(struct Item));
    pipe->name = "pipe";
    pipe->next = NULL;
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
    itemList[0] = revolver; itemList[1] = dagger; itemList[2] = pipe;
    itemList[3] = rope; itemList[4] = candlestick; itemList[5] = wrench;
    for (int i = 0; i < 6; i++) {
        itemList[i]->secret = false;
    }

    //randomizing itemList
    for (int i = 6 - 1; i >= 1; i--) {
        int j = rand() % (i+1); //j is a random integer where 0 <= j <= i
        struct Item* temp = itemList[i]; //swap itemList[i] with itemList[j]
        itemList[i] = itemList[j];
        itemList[j] = temp;
    }

    //setting secret room
    itemList[rand() % (6)]->secret = true;

    //randomly selecting rooms to receive items
    int itemRooms[6] = {-1, -1, -1, -1, -1, -1};
    int itemsDistributed = 0;
    int potentialRoom;
    while (itemsDistributed < 6) {
        potentialRoom = rand() % 8;
        for (int i = 0; i < 6; i++) {
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
    mrsWhite->name = "Mrs White";
    struct Character* mrsPeacock = malloc(sizeof(struct Character));
    mrsPeacock->name = "Mrs Peacock";
    struct Character* professorPlum = malloc(sizeof(struct Character));
    professorPlum->name = "Professor Plum";
    struct Character* colonelMustard = malloc(sizeof(struct Character));
    colonelMustard->name = "Colonel Mustard";
    struct Character* missScarlett = malloc(sizeof(struct Character));
    missScarlett->name = "Miss Scarlett";

    //creating characterList
    characterList[0] = mrsWhite; characterList[1] = mrsPeacock; characterList[2] = professorPlum;
    characterList[3] = colonelMustard; characterList[4] = missScarlett;
    for (int i = 0; i < MAX_CHARACTER; i++) {
        characterList[i]->secret = false;
    }

    //randomizing characterList
    for (int i = MAX_CHARACTER - 1; i >= 1; i--) {
        int j = rand() % (i+1); //j is a random integer where 0 <= j <= i
        struct Character* temp = characterList[i]; //swap itemList[i] with itemList[j]
        characterList[i] = characterList[j];
        characterList[j] = temp;
    }

    //setting secret character
    characterList[rand() % (MAX_CHARACTER)]->secret = true;

    //randomly selecting rooms to receive characters
    int itemRooms[6] = {-1, -1, -1, -1, -1, -1};
    int itemsDistributed = 0;
    int potentialRoom;
    while (itemsDistributed < 6) {
        potentialRoom = rand() % 8;
        for (int i = 0; i < 6; i++) {
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
    struct Item** temp = &(player->item); //creating temp pointer to item in inventory to avoid losing reference
    if (temp == NULL) { //
        printf("Inventory is empty\n");
    } else {
        printf("Items in inventory: ");
        while (*temp != NULL) {
            printf("%s, ", (*temp)->name);
            temp = &((*temp)->next);
        }
        printf("\n");
    }
    printf("\n");
}

void take(struct Player* player, struct Item* itemList[6]) {
    char input[2048];
    char* token;
    char delim[2] = " ";
    printf("What would you like to take:\n");
    while (1) {
        fgets(input, 2048, stdin);
        token = strtok(input,delim);
        if (token == NULL) { //handling enter key case
            continue;
        } else if (compString(token, "exit")) {
            break; //handling no item in room locked in method case
        }
        if (!itemExists(token, itemList)) { //handling item doesn't exist case
            printf("%s is not an item\n", token);
            printf("try again? Or enter \"exit\" to return to other actions\n");
        } else {
            struct Item* removedItem = check_item(&(player->currRoom->item), token);
            if (removedItem == NULL) {
                printf("%s not in room\n", token); //handling item not in room case
            } else {
                add_item(&player->item, removedItem);
                drop_item(&player->currRoom->item, token);
                removedItem->next = NULL;
                printf("%s added to inventory\n", removedItem->name);
                break;
            }
        }
    }
}

void drop(struct Player* player, struct Item* itemList[6]) {
    char input[2048];
    char* token;
    char delim[2] = " ";
    printf("What would you like to take:\n");
    while (1) {
        fgets(input, 2048, stdin);
        token = strtok(input,delim);
        if (token == NULL) { //handling enter key case
            continue;
        } else if (compString(token, "exit")) {
            break; //handling no item in room locked in method case
        }
        if (!itemExists(token, itemList)) { //handling item doesn't exist case
            printf("%s is not an item\n", token);
            printf("try again? Or enter \"exit\" to return to other actions\n");
        } else {
            struct Item* removedItem = check_item(&(player->item), token);
            if (removedItem == NULL) {
                printf("%s not in inventory\n", token); //handling item not in room case
            } else {
                add_item(&player->currRoom->item, removedItem);
                drop_item(&player->item, token);
                removedItem->next = NULL;
                printf("%s added to room\n", removedItem->name);
                break;
            }
        }
    }
}