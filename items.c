#include "items.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void add_item(struct Item** oldItem, struct Item* newItem) {
    struct Item** temp = oldItem;
    if ((*temp) == NULL) {
        *oldItem = newItem;
    } else {
        while((*temp)->next != NULL) {
            temp = &(*temp)->next;
        }
        (*temp)->next = newItem;
    }
}

void drop_item(struct Item** oldItem, char target[2048]) {
    struct Item** temp = oldItem;
    struct Item** prev = NULL;

    if ((*temp) != NULL && compString((*temp)->name,target)) {
        *oldItem = (*temp)->next;
        return;
    }

    while ((*temp) != NULL && !compString((*temp)->name, target)) {
        prev = temp;
        temp = &(*temp)->next;
    }

    if ((*temp) == NULL) {
        return;
    }

    (*prev)->next = (*temp)->next;
}

struct Item* check_item(struct Item** desiredItem, char target[2048]) {
    struct Item** temp = desiredItem;
    while ((*temp) != NULL) {
        if (compString((*temp)->name, target)) {
            return *temp;
        }
        temp = &((*temp)->next);
    }
    return NULL;
}

bool itemExists(char* potItem, struct Item* itemList[6]) {
    for (int i = 0; i < 6; i++) {
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
    revolver->secret = false;
    struct Item* dagger = malloc(sizeof(struct Item));
    dagger->name = "dagger";
    dagger->next = NULL;
    dagger->secret = false;
    struct Item* pipe = malloc(sizeof(struct Item));
    pipe->name = "pipe";
    pipe->next = NULL;
    pipe->secret = false;
    struct Item* rope = malloc(sizeof(struct Item));
    rope->name = "rope";
    rope->next = NULL;
    rope->secret = false;
    struct Item* candlestick = malloc(sizeof(struct Item));
    candlestick->name = "candlestick";
    candlestick->next = NULL;
    candlestick->secret = false;
    struct Item* wrench = malloc(sizeof(struct Item));
    wrench->name = "wrench";
    wrench->next = NULL;
    wrench->secret = false;

    //creating itemList
    itemList[0] = revolver; itemList[1] = dagger; itemList[2] = pipe;
    itemList[3] = rope; itemList[4] = candlestick; itemList[5] = wrench;

    //randomizing itemList
    for (int i = 6 - 1; i >= 1; i--) {
        int j = rand() % (i+1); //j is a random integer where 0 <= j <= i
        struct Item* temp = itemList[i]; //swap itemList[i] with itemList[j]
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
    mrsWhite->secret = false;
    struct Character* mrsPeacock = malloc(sizeof(struct Character));
    mrsPeacock->name = "Mrs Peacock";
    mrsPeacock->secret = false;
    struct Character* professorPlum = malloc(sizeof(struct Character));
    professorPlum->name = "Professor Plum";
    professorPlum->secret = false;
    struct Character* colonelMustard = malloc(sizeof(struct Character));
    colonelMustard->name = "Colonel Mustard";
    colonelMustard->secret = false;
    struct Character* missScarlett = malloc(sizeof(struct Character));
    missScarlett->name = "Miss Scarlett";
    missScarlett->secret = false;

    //creating characterList
    characterList[0] = mrsWhite; characterList[1] = mrsPeacock; characterList[2] = professorPlum;
    characterList[3] = colonelMustard; characterList[4] = missScarlett;

    //randomizing characterList
    for (int i = MAX_CHARACTER - 1; i >= 1; i--) {
        int j = rand() % (i+1); //j is a random integer where 0 <= j <= i
        struct Character* temp = characterList[i]; //swap itemList[i] with itemList[j]
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

void take(struct Player* player, struct Item* itemList[6]) {
    char input[2048];
    char* token;
    char delim[2] = " ";
    printf("What would you like to take:\n");
    while (1) {
        fgets(input, 2048, stdin);
        token = strtok(input,delim);
        if (token == NULL) {
            continue;
        } else if (compString(token, "exit")) {
            break;
        }
        if (!itemExists(token, itemList)) {
            printf("%s is not an item\n", token);
            printf("try again? Or enter \"exit\" to return to other actions\n");
        } else {
            struct Item* removedItem = check_item(&(player->currRoom->item), token);
            if (removedItem == NULL) {
                printf("%s not in inventory\n", token);
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
        if (token == NULL) {
            continue;
        } else if (compString(token, "exit")) {
            break;
        }
        if (!itemExists(token, itemList)) {
            printf("%s is not an item\n", token);
            printf("try again? Or enter \"exit\" to return to other actions\n");
        } else {
            struct Item* removedItem = check_item(&(player->item), token);
            if (removedItem == NULL) {
                printf("%s not in inventory\n", token);
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