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
the input to the corresponding functions. Of the routable functions, there is help, list, look, go, take, drop,
inventory, and clue. The help function displays the available functions with descriptions on how to use them. The
list function provides a guide to the items, characters, and rooms in play by iterating through the lists created in
the main function. List goes through each of the surrounding rooms and prints their names with the directions they are
in. List also iterates through the item linked list and character arrays to list the items and characters in the room.
The go function accepts input for the direction the player would like to travel and requests re-input if not fitting the
valid selection (North, East, South, West).
    Take and drop take input for the requested item to be taken from the room or dropped from the inventory. It accepts
exit to allow the user to exit the situation if they decide not to take or drop an item. The functions also handle the
cases where the items are not in the room or inventory or do not exist. Inventory produces a list of items in the
inventory by iterating through the player's item attribute. Lastly, before entering the clue function, the main method
concatenates the input into the character's full name. Then, the clue function checks if the attempt count variable
from the main is greater than or equal to 10, and if so frees the variables with the freeVars function. The freeVars
function uses the list from the main to iterate through and free each dynamically allocated element. If the
attempt count is less than 10, the code checks if the item is valid/available using the testItemInInventoryOrRoom
function and uses a findAndMoveCharacter function and an enclosed moveCharacter function. Lastly, the code uses a
testGuess function which tests the movedCharacter (pointer to this passed by findAndMoveCharacter function), item
(pointer to passed by testItemInInventoryOrRoom), and room by the player's pointer. If it is successful or failing, the
function returns to the original while loop in the main for the player to continue their journey.
    The game exits when the attempt count is reached or the guess is successful, which is visible in the clue function.

User input:
    The user input is managed by accepting any of the base functions (help, list, look, go, take, drop, inventory, and
clue) in the main while loop. Then, if the base functions match the user input, more input is requested by the interface
for each of the functions. Go for instance, requests the direction after the go keyword is submitted. Drop and take
request the items that should be dropped or taken from or to the inventory/room. Clue accepts more input in the initial
keyword (character name and item). If these functions aren't properly used or mistyped, the interface asks for re-input.