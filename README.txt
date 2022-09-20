Compiling the code:
    The code can be compiled by running "gcc -o <output-name> adventure.c rooms.c items.c" where <exe-name> can
be filled in with a title of the user's choice. Then the code can be executed by running
./<output-name> .

Overview:
    The code first randomly selects a seed. It allocates an attemptCount, 3 by 3 board, a character list, item list,
and room list. Then the setBoard function enters the popualateRooms, populateItems, and populateCharacters
functions that dynamically allocate the rooms, items, and characters respectively. They then randomize the elements,
select a random item to be the secret element. The populateRooms function also sets directions for the rooms
to their neighbors.
    Then the code enters the playGame method that creates a while loop, which continuously takes user input and routes
the input to the corresponding functions. Of the checked functions, there is help, list, look, go, take, drop,
inventory, and clue. The help function displays the available functions with descriptions using print statements. The
list function provides a guide to the items, characters, and rooms in play by iterating through the lists created in
the main function. List goes through each of the surrounding rooms and prints their names with the directions they are
in. List also iterates through the item linked list and character arrays to list the items and characters in the room.
The go function accepts input for the direction the player would like to travel and requests re-input if not fitting the
valid selection (North, East, South, West). It compares the input against the selection and resets the player's pointers
to the new room if there is a new room in that direction. Otherwise, it prints that there is no room in that direction.
    Take and drop take input for the requested item to be taken from the room or dropped from the inventory. It accepts
exit to allow the user to exit the situation if they decide not to take or drop an item. The functions also handle the
cases where the items are not in the room or inventory or do not exist. Inventory produces a list of items in the
inventory by iterating through the player's item attribute. Lastly, before entering the clue function, the main method
concatenates the input into the character's full name. Then, the clue function checks if the attempt count variable
from the main is greater than or equal to 10, and if so frees the variables with the freeVars function. The freeVars
function uses the list from the main to iterate through and free each dynamically allocated element. If the
attempt count is less than 10, the code checks if the item is valid/available using the testItemInInventoryOrRoom
function and uses a findAndMoveCharacter function and an enclosed moveCharacter function. Lastly, the code uses a
testGuess function which tests the movedCharacter (pointer to this passed by findAndMoveCharacter function), selected item
(pointer to passed by testItemInInventoryOrRoom), and room by the player's pointer. If it is successful or failing, the
function returns to the original while loop in the main for the player to continue their journey.
    The game exits when the attempt count is reached or the guess is successful, which is visible in the clue function.

User input:
    The user input is managed by accepting any of the base functions (help, list, look, go, take, drop, inventory, and
clue) in the main while loop. Then, if the base functions match the user input, more input is requested by the interface
for each of the functions if needed. Go for instance, requests the direction after the go keyword is submitted. Drop and
take request the items that should be dropped or taken from or to the inventory/room. Help and list, however,
do need further input and simply output their contents. Clue accepts more input in the initial keyword (character name
and item). If these functions aren't properly used or mistyped, the interface asks for a re-input of the function. If
any of the further information needed by the functions is mistyped, the interface asks for re-input of that specific
data.

Rubric:
Project Requirement (68 points):
Your game must have 9 rooms including the starting room. The game board is a 3 x 3 map.
    The room should be connected via pointers, regardless of whether the room structure is stored in an array. (10 points)
    -> see adventure.c line 56 - setBoard function, and rooms.c line 23 - populateRooms()
Your game must randomly initialize the location of each room in the game board before the game starts. (5 points)
    -> see rooms.c line 53 - populateRooms()
Your game must have at least 6 items and 5 characters other than the player's avatar.
    Each room can only contain at most one item at the beginning. (2 points)
    -> see items.c line 60 - populateItems()
    -> see items.c line 135 - populateCharacters()
Your game must randomly pick a room, an item, and a character as the answer. (2 points)
    -> see rooms.c line 60 for room selection
    -> see items.c line 97 for item selection
    -> see items.c line 164 for character selection
Your game must allow each room to have a linkedList of items. (5 points)
    -> see rooms.h line 19 - struct Room
Your game must implement an avatar where the avatar has an inventory (a linkedList of items). (5 points)
    -> see items.h line 20 - struct Player
You must implement a table of commands (28 points):
Your game must allow players to lookup the command in the table with the command “help”. (2 points)
    -> see adventure.c line 124 - help()
Your game must allow players to lookup the list of items, rooms, and characters with the command “list”. (2 points)
    -> see adventure.c line 138 - list()
Your game must allow an avatar to “see” the room they are in with the command “look”, including the rooms in each
    direction, the characters in the current room and the items in the current room. (4 points)
    -> see rooms.c line 99 - look()
Your game must allow an avatar to move through each room via room pointer using the command “go”. After players
    type “go”, your game must allow the user to type which DIRECTION their avatar wants to go from one of these
     4 directions: north, south, east, west. The game must allow players to retype a direction if the direction
     is not valid. (4 points)
     -> see rooms.c line 148 - go()
Your game must allow an avatar to pick up items with the command “take”. After players type “take”, our game must
    allow the user to type an item name. The game m ust allow players to retype an ITEM name if the item name is
    not valid. (4 points)
    -> see items.c line 218 - take()
Your game must allow an avatar to drop an item with the command “drop”. After players type “drop”, our game must
    allow the user to type an item name. The game must allow players to retype an ITEM name if the item name is
    not valid.  (4 points)
    -> see items.c line 249 - drop()
Your game must allow an avatar to list items in the avatar’s inventory with the command “inventory”.  (4 points)
    -> see items.c line 203 - inventory()
Your game must allow a player to make a guess with the command “clue”. After the player types “clue”, the game must
    allow the user to type a CHARACTER name. The game must allow players to retype a character name if the character
    name is not valid; the player must then type an ITEM name, again allowing a retype if the item is invalid. If there
    are no valid items, the game should not allow the player to perform the clue command, and instead allow them to choose
    another command. (2 points)
    -> see rooms.c line 269 - clue()
The game must allow an avatar to retype a command if the command is not one of the above. (2 points)
    -> see adventure.c lines 118-119 - playGame()
After receiving a valid command “clue”, your game must follow the three steps as below (6 points)
    Move the character stated in the command to the same room of avatar. (2 points)
    -> see rooms.c line 211 - findAndMoveCharacter()
    Your game must tell the player the matching detail between the rumor and the answer based on the game status.
    (2 points)
    -> see rooms.c line 250 testGuess()
    Check winning or losing states. (2 points)
    -> see rooms.c lines 271-274 - clue()
    -> see adventure.c lines 111-114 - playGame()
You should organize your code into multiple C files as stated in the requirement. (5 points)
    -> see file adventure.c, rooms.h, items.h, rooms.c, and items.c
Design and Implementation (10 points)
    Reasonably efficient (things like no obvious places where a for loop could be used to simplify code) (10 points)
    Style/Aesthetic (6 points)
    Consistent bracketing style (2 points)
    Consistent indentation style (2 points)
    Reasonable variable names (2 points)
    -> see entire code project (no specific lines)
Comments (6 points)
    Functions: comments describing purpose, inputs, and returns of functions where applicable (2 points)
    Variables: comments describing the meaning/purpose of non-trivial and non-obvious variables (2 points)
    Misc Code: comments describing non-trivial regions of code/control flow (2 points)
    -> see entire code project (no specific lines)
README (9 points)
    Explains how to compile the code  (3 points)
    -> see README.txt line 1
    Overview/description of the overall structure of the game board with pointers (3 points)
    -> see README.txt line 6
    Explains how to manage user input (3 points)
    -> see README.txt line 35