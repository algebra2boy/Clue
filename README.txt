What is this game about (overview/description)
---------------------------------------------
Description: 
This is a text adventure game where it creates a 3 x 3 gameboard room.
You need to figure out a way to find the one murderer with your brilliant brains. 
There are five characters as they are Anan, Jeff, Matt, Eric and Adam. Use your intelligence 
to investigate the weapons!! Rumor: Anan has been murdered.\nRumor: Jeff suspects that Matt strangles Anan with the rope in study room

Overview:
I implemented a 2D array with mallloc, making each room a pointer. Each room is a pointer and it
contains pointers pointing at rooms from North, South, East, West, name of NPC, also
a LinkedList that stores all item in that room. There are 4 x 9 = 36 pointers in total for rooms. 
The Linkedlist is implemented by pointers as well, the next item of the list is another pointer of an item.
Each room only contain at most one item at the beginning. I also have struct Avatar where I store the information of the avatar, such as
where the avatar is located at, and the inventory. After finishing the program, I deallocate the memory of the board, the avatar's current room,
its inventory, its name. I have also deallocated the memory of the node if that is being removed from a linkedlist.
Note: I have many edge cases to prevent the user to input invalid inputs. 

Implementation my code satisfies each of the requirements of the project
1. Your game must have 9 rooms including the starting room. -> line 20 to 64 from createBoard() in room.c
    - The room should be connected via pointers -> line 82 to 145 from connectRoom() in room.c
2. randomly initialize the location of each room in the game board before the game starts -> line 69 to 78 from randomizeLocation() room.c
3. must have at least 6 items and 5 characters other than the player's avatar -> line 8 to 17 from get_item_array(), line 269 in adventure.c and createBoard() in room.c
4. randomly pick a room, an item, and a character as the answer -> line 274 to 276 in adventure.c
5. each room to have a linkedList of items -> line 7 to 10 in items.h
6. an avatar where the avatar has an inventory -> line 7 to 10 in adventure.c
7. table of commands (all in adventure.c) -> All in main function 
    a. help -> line 14 to 25
    b. list  -> line 29 to 33
    c. look  -> line 83 to 139
    d. go   -> line 38 to 80
    e. take -> line 144 to 157
    f. drop  -> line 163 to 169
    g. inventory  -> line 173 to 175, then call a function in items.c from line 47 to 56
    h. clue -> 
        - Move the character stated in the command to the same room of avatar -> line 245 to 270 
        -  must tell the player the matching detail between the rumor and the answer based on the game status -> line 217 to 240
        - Check winning or losing states
             winning state -> line 362 to 366
             losing state -> line 295, 297, 375-377, 373

How to complie this program
---------------------------------------------
First: use gcc adventure.c room.c -o myProgram
Second: use ./myProgram


How to manage user input 
---------------------------------------------
I use scanf("%s %s", first, second) to read the two words
Some commands have two words but some have one word. Every time it pops up the 
"input command:", please input "command_name ~" if there are two words. There is a space betweem 
"command_name" and "~". For example, "help ~", "look ~". 
But for those who have only have two words, that is no problem. For example, "go north"
Remember to lower case every word you input (EXCEPT CHARACTER NAME where you have to capitalize the first letter of character name)

if you want to go to the rooms that are at north, south, east or west, you have to put either
"go north", "go south".... but you are not supposed to put "go Bathroom", which is the name of the room

if you want to input the item name for "take" or "drop", you have to put either 
"axe", "poison", "knife", "gun", "bible", "rope", such as "take bible". Otherwise, it is an invalid input.

if you want to input the character name for "clue", you have to put either 
"Anan", "Jeff", "Matt", "Eric", "Adam", such as "clue Adam". Otherwise, it is an invalid input.