#include <stdio.h>
#include <string.h>
#include "room.h"
#include "items.h"

// a Struct representing the user player, which is YOU
struct Avatar
{
    char *my_name;
    struct Room *current_room;
    struct item *inventory; // a little backpack to store items
};

// allow players to lookup the command in the table with the "help"
void help()
{
    printf("        Command Table Overview (lower case only)\n");
    printf("(1)         help: lookup the command\n");
    printf("(2)         list: lookup items, rooms, and characters\n");
    printf("(3)         look: see where you are right now\n");
    printf("(4)           go: go to a room at north, south, east, or west\n");
    printf("(5)         take: take an item from the room\n");
    printf("(6)         drop: drop an item to the room\n");
    printf("(7)    inventory: check items in the avatar's inventory\n");
    printf("(8)         clue:make a guess\n");
    printf("(9)         quit: leave the game\n");
}

// allow players to lookup the list of items, rooms, and characters with the "list"
// parameter: the game board
void list(struct Room **board)
{
    print_items(board);
    print_room(board);
    print_character(board);
}

// allow an avatar to move through each room via room pointer
// parameter: the string that represents the direction, the board, the struct avatar
// return : a new room that the avatar goes to
struct Room *go(char *direction, struct Room **board, struct Avatar avatar)
{
    if (strcmp(direction, "north") == 0)
    {
        if ((avatar.current_room->North) == NULL)
        { // check if that room exists or not
            printf("room does not exist, try again\n");
        }
        else
        { // the room exists then investigate
            avatar.current_room = avatar.current_room->North;
            showMessage(avatar.current_room); // show the evidence after entering the room
        }
    }
    else if (strcmp(direction, "south") == 0)
    {
        if ((avatar.current_room->South) == NULL)
        { // check if that room exists or not
            printf("room does not exist, try again\n");
        }
        else
        { // the room exists
            avatar.current_room = avatar.current_room->South;
            showMessage(avatar.current_room);
        }
    }
    else if (strcmp(direction, "west") == 0)
    {
        if ((avatar.current_room->West) == NULL)
        { // check if that room exists or not
            printf("room does not exist, try again\n");
        }
        else
        { // the room exists
            avatar.current_room = avatar.current_room->West;
            showMessage(avatar.current_room);
        }
    }
    else if (strcmp(direction, "east") == 0)
    {
        if ((avatar.current_room->East) == NULL)
        { // check if that room exists or not
            printf("room does not exist, try again\n");
        }
        else
        { // the room exists
            avatar.current_room = avatar.current_room->East;
            showMessage(avatar.current_room);
        }
    }
    else
    { // invalid input
        printf("direction is an invalid input,please try again\n");
    }
    return avatar.current_room;
}

/* allow an avatar to "see" the room they are in with the "look"
   including the room in each direction, the character in the room and items in the room */
void look(struct Avatar avatar)
{
    printf("I am at %s ", avatar.current_room->name);
    printf("and it has ");
    if (avatar.current_room->itemlist == NULL)
    {
        printf("nothing");
    }
    else
    {
        printList(*(avatar.current_room->itemlist));
    }
    printf(", who is in the room:");
    print_characterForOneRoom(avatar.current_room);

    if (checkRoomExist(avatar.current_room->North) == 0)
    { // North
        printf("North is %s\n", print_single_room(avatar.current_room, "north"));
    }
    else
    { // room exists == 1
        printf("North is %s and it has ", print_single_room(avatar.current_room, "north"));
        if (checkItemlistValid(avatar.current_room->North->itemlist))
        {
            printList(*(avatar.current_room->North->itemlist));
        }
        printf(",who is in the room:");
        print_characterForOneRoom(avatar.current_room->North);
    }
    if (checkRoomExist(avatar.current_room->South) == 0)
    { // South
        printf("South is %s\n", print_single_room(avatar.current_room, "south"));
    }
    else
    { // room exists == 1
        printf("South is %s and it has ", print_single_room(avatar.current_room, "south"));
        if (checkItemlistValid(avatar.current_room->South->itemlist))
        {
            printList(*(avatar.current_room->South->itemlist));
        }
        printf(",who is in the room:");
        print_characterForOneRoom(avatar.current_room->South);
    }
    if (checkRoomExist(avatar.current_room->West) == 0)
    { // West
        printf("West is %s\n", print_single_room(avatar.current_room, "west"));
    }
    else
    { // room exists == 1
        printf("West is %s and it has ", print_single_room(avatar.current_room, "west"));
        if (checkItemlistValid(avatar.current_room->West->itemlist))
        {
            printList(*(avatar.current_room->West->itemlist));
        }
        printf(",who is in the room:");
        print_characterForOneRoom(avatar.current_room->West);
    }
    if (checkRoomExist(avatar.current_room->East) == 0)
    { // East
        printf("East is %s\n", print_single_room(avatar.current_room, "east"));
    }
    else
    { // room exists == 1
        printf("East is %s and it has ", print_single_room(avatar.current_room, "east"));
        if (checkItemlistValid(avatar.current_room->East->itemlist))
        {
            printList(*(avatar.current_room->East->itemlist));
        }
        printf(",who is in the room:");
        print_characterForOneRoom(avatar.current_room->East);
    }
}

// allow an avatar to pick up items from the room with the command “take”
// guaranteen that we have something to pick up, prevent segmentation fault
// paramter: name of the item, avatar
// return : a new avatar with updated items
struct Avatar take(char *item_name, struct Avatar avatar)
{
    // add the item to inventory  = remove the item from that room
    avatar.inventory = add_item(item_name, avatar.inventory);
    printf("my inventory has ");
    printList(*(avatar.inventory));
    avatar.current_room->itemlist = drop_item(item_name, avatar.current_room->itemlist);
    if (avatar.current_room->itemlist == NULL)
    {
        printf("\nThe room now contains no item.\n");
    }
    else
    {
        printList(*(avatar.current_room->itemlist));
    }
    printf("\nI have picked up a %s\n", item_name);
    return avatar;
}

// allow an avatar to drop an item with the command “drop”
// guaranteen that we have something to drop off, prevent segmentation fault
// paramter: name of the item, avatar
// return : a new avatar with updated items
struct Avatar drop(char *item_name, struct Avatar avatar)
{
    // drop the item from avatar's inventory = add the item to room
    avatar.current_room->itemlist = add_item(item_name, avatar.current_room->itemlist);
    avatar.inventory = drop_item(item_name, avatar.inventory);
    printf("\nI have dropped a %s\n", item_name);
    return avatar;
}

// print every item name of the inventory
// parameter: the struct Avatar avatar
void printInventory(struct Avatar avatar)
{
    printList(*(avatar.inventory));
}

// quit the game if the game is too hard or simply give up
// parameter: 2D board and struct Avatar
void quit(struct Room **board, struct Avatar avatar)
{
    for (int i = 0; i < 3; i++)
    {
        free(board[i]);
    }
    free(avatar.current_room);
    free(avatar.inventory);
    free(avatar.my_name);
    free(board);
    printf("\nYou have exited the game\n");
    exit(0);
}

// To see if the item matches with the item_answer
// return: an interger 1 if the item of the answer is found either in the room or inventory, otherwise 0
int itemMatch(struct Avatar avatar, struct item *item_answer)
{
    int match = 0;
    // check if the answer of item exists inventory first
    struct item *current_item = avatar.inventory;
    while (current_item != NULL)
    { // traverse the linkedlist
        if (strcmp(current_item->item_name, item_answer->item_name) == 0)
        { // Found it
            return !match;
        }
        current_item = current_item->next_item;
    }
    // then check if the answer of item exists in the current room
    current_item = avatar.current_room->itemlist;
    while (current_item != NULL)
    { // traverse the linkedlist
        if (strcmp(current_item->item_name, item_answer->item_name) == 0)
        {
            return !match;
        }
        current_item = current_item->next_item;
    }
    return match;
}

// give hints to the avatar
// parameter: the name of the character, 2D board and struct Avatar
// return: if the player hit all 3 matches in a single clue command, returns 1, otherwise 0;
int clue(char *character_name, struct Room **board, struct Avatar avatar, struct Room *room_answer, char *character_answer, struct item *list_item_answer)
{

    int room_match = 0, character_match = 0, item_match = 0;
    // Room: If the player avatar is in the room of the answer, show the message “Room Match”.
    if (strcmp(avatar.current_room->name, room_answer->name) == 0)
    { // same room name
        printf("Room Match\n");
        room_match = 1;
    }
    // Character: If the character of the answer is in the room, show the message “Character Match”.
    for (int found = 0; found < 6; found++)
    {
        if (strcmp(character_answer, avatar.current_room->character[found]) == 0)
        {
            printf("Character Match\n");
            room_match = 1;
            break;
        }
    }

    // Item: if the item of the answer is in the room, show the message “Item Match”
    if (itemMatch(avatar, list_item_answer))
    {
        printf("Item Match\n");
        item_match = 1;
    }
    return room_match && character_match && item_match; // hit 3 matches YES
}

// Remove the character from the board if we use the "clue" command
// parameter: 2D board, struct Avatar, and the character name
// return: an updated board with character if that character exists
struct Room **removeCharacterFromBoard(struct Room **board, char *character_name)
{
    for (int i = 0; i < 3; i++)
    { // go through all rows
        for (int j = 0; j < 3; j++)
        { // go through all columns
            for (int found = 0; found < 6; found++)
            { // traverse the character list
                if (board[i][j].character[found] != NULL && (strcmp(board[i][j].character[found], character_name) == 0))
                {
                    board[i][j].character[found] = NULL; // only need to remove one character
                    break;
                }
            }
        }
    }
    return board;
}

// Move the character stated in the command to the same room of avatar.
// paramter: the struct Avatar avatar, and the character name
// return: an updated avatar with character if that character exists
struct Avatar addCharacterToAvatarRoom(struct Avatar avatar, char *character_name)
{
    for (int found = 0; found < 6; found++)
    {
        if (avatar.current_room->character[found] == NULL)
        { // find empty slot, then assign value
            avatar.current_room->character[found] = character_name;
            break; // onldy need to add one character
        }
    }
    return avatar;
}

// introduce to the player what the game is about and spread a rumor to the player
void introduction()
{
    printf("\n");
    printf("This is a text adventure game where it creates a 3 x 3 gameboard room.\nYou need to figure out a way to find the one murderer with your brilliant brain.\nThere are five characters as they are Anan, Jeff, Matt, Eric and Adam.\nUse your intelligence to investigate the weapons!!\n");
    printf("Anan has been murdered.\nRumor: Jeff suspects that Matt strangles Anan with the rope in study room.\n");
    printf("Type \"help ~\" to ask for command table \n\n");
    printf("put ~ as the second word if your command has only one word\n");
}

int main()
{
    struct Room **board = createBoard();
    struct Avatar avatar = {.my_name = "Yongye", .current_room = &board[randomNumber(3)][randomNumber(3)], .inventory = NULL}; // place avatar in a random room with nothing on it
    char *character_name[5] = {"Anan", "Jeff", "Matt", "Eric", "Adam"};                                                        // 5 characters in this game non including the avatar
    struct item *list_item = get_all_item(board);

    // randomly pick a room(struct ptr), an item(struct ptr), and a character(string) as the answer
    struct Room *room_answer = &board[randomNumber(3)][randomNumber(3)];
    char *character_answer = character_name[randomNumber(4)];
    struct item *item_answer = &list_item[randomNumber(6)];

    introduction(); // introduce the game

    // game officially starts here
    int clue_Attempt = 1;
    char first[20], second[20]; // first, second are the first and second word the user types, respectively
    while (clue_Attempt < 10)
    {                                    // losing state: if the player cannot hit all 3 matches after she made her 10th clue command.
        char *temp = malloc((size_t)20); // to store the second to prevent buffer overflow
        printf("input command: ");       // reading inputs
        scanf("%s %s", first, second);

        // switch around different cases of command
        if (strcmp(first, "help") == 0)
        {
            help();
            printf("\n");
        }
        else if (strcmp(first, "list") == 0)
        {
            list(board);
            printf("\n");
        }
        else if (strcmp(first, "go") == 0)
        {
            if (checkDirectionValid(strcpy(temp, second)) == 0)
            { // invalid direction
                printf("invalid direction\n");
            }
            else
            { // valid direction
                struct Room *updateRoom = go(second, board, avatar);
                avatar.current_room = updateRoom;
                printf("Now I am at %s ", avatar.current_room->name);
                printf("and it has ");
                printList(*(avatar.current_room->itemlist));
                printf(", who is in the room:");
                print_characterForOneRoom(avatar.current_room);
            }
        }
        else if (strcmp(first, "look") == 0)
        {
            look(avatar);
            printf("\n");
        }
        else if (strcmp(first, "take") == 0)
        {
            if (checkItemNameValid(second, list_item))
            { // retype an ITEM name if the item name is not valid
                printf("item name is not valid\n");
            }
            else
            {
                if (avatar.current_room->itemlist == NULL)
                {
                    printf("Nothing in the room\n");
                }
                else
                {
                    avatar = take(strcpy(temp, second), avatar);
                }
            }
            printf("\n");
        }
        else if (strcmp(first, "drop") == 0)
        {
            if (checkItemNameValid(second, list_item))
            { // retype an ITEM name if the item name is not valid
                printf("item name is not valid\n");
            }
            else
            {
                if (avatar.inventory == NULL)
                {
                    printf("There is nothing in the inventory, invalid\n");
                }
                else
                {
                    avatar = drop(strcpy(temp, second), avatar);
                }
            }
            printf("\n");
        }
        else if (strcmp(first, "inventory") == 0)
        {
            printf("My inventory has ");
            if (avatar.inventory == NULL)
            {
                printf("nothing\n");
            }
            else if (avatar.inventory != NULL)
            {
                printInventory(avatar);
            }
            printf("\n");
        }
        else if (strcmp(first, "quit") == 0)
        {
            quit(board, avatar);
        }
        else if (strcmp(first, "clue") == 0)
        {
            if (checkCharacterNameValid(second, character_name))
            {
                printf("charcter name is not invalid\n");
            }
            else
            {                                                                    // valid character name
                board = removeCharacterFromBoard(board, strcpy(temp, second));   // remove the character from the room stated in the command.
                avatar = addCharacterToAvatarRoom(avatar, strcpy(temp, second)); // Move the character stated in the command to the same room of avatar.
                int state = clue(second, board, avatar, room_answer, character_answer, item_answer);
                if (state)
                { // winning state: hit all three states in one clue
                    printf("CONGRATULATIONS, YOU HAVE SOLVED THE MYSTERY!\n");
                    break; // break out immediately when the avatar has figure out
                }
                printf("\n");
            }
        }
        else
        { // allow an avatar to retype a command if the command is not one of the above
            printf("No such command exists, try again\n");
        }
        printf("\n");
        clue_Attempt++; // incremented the the number of attemp that is up to 10
    }
    if (clue_Attempt == 10)
    { // losing state: if the player cannot hit all 3 matches after he/she made his/her 10th clue command.
        printf("UNFORTUNATELY, YOU HAVE LOST THE GAME, TRY AGAIN MAYBE?!\n");
    }
    // deallocate the memory
    for (int i = 0; i < 3; i++)
    {
        free(board[i]);
    }
    free(avatar.current_room);
    free(avatar.inventory);
    free(avatar.my_name);
    free(board);
}