#include "room.h"
#include <stdlib.h>
#include "items.c"
#include <string.h>

// creating a pointer linkedList to make itemlist for each room
// which contains the memory address of first item in that room
struct item *get_item_array(){
    struct item *items = malloc(9 * sizeof(struct item));
    char *list_item_name[9] = {"", "axe", "poison", "knife", "gun", "bible", "", "", "rope"};
    for (int i = 0; i < 9; i++){
        // each item is a "head node"
        struct item room_item = {.item_name = list_item_name[i], .next_item = NULL};
        items[i] = room_item;
    }
    return items;
}

// Create a 3x3 room via pointers with 2D array and malloc
struct Room **createBoard(){
    // creating 9 rooms for the 3 x 3 gameboard
    int row = 3, column = 3;
    struct Room **board;

    board = malloc(sizeof(struct Room *) * row); // making 3 rows of array

    // making 3 columns for the array
    for (int j = 0; j < column; j++){
        board[j] = malloc(sizeof(struct Room) * column);
    }

    // get a linkedList of item for each room
    struct item *list = get_item_array();

    // a char array that contains the name of NPC in room1,room2,...room9, respectively
    char *character_name[9] = {"Anan", "", "Jeff", "", "", "Matt", "Eric", "", "Adam"};

    // a char array that contains the name of each room
    char *room_name[9] = {"Kitchen", "Bathroom", "Basement", "MusicRoom", "Bedroom", "Attic", "Balcony", "Elevator", "StudyRoom"};

    // 1D array storing each room
    struct Room *room_1D = malloc(sizeof(struct Room) * 9);
    for (int i = 0; i < 9; i++){
        // initializing room
        struct Room room = {.name = room_name[i], .North = NULL, .South = NULL, .East = NULL, .West = NULL, .itemlist = &list[i], .character = character_name[i]};
        room_1D[i] = room;
    }
    // randomize the 1D array
    room_1D = randomizeLocation(room_1D, 9);

    // putting randomized 1D array room to 2D array room
    int row_add = 0, col_add = 0;
    // creating 9 rooms individually with a loop
    for (int i = 0; i < 9; i++){
        board[row_add][col_add] = room_1D[i]; // placing the room into the board
        col_add++;            // adding the room to right
        if (col_add % 3 == 0){ // if it reaches to the  of column, go to the next row
            row_add++;
            col_add = 0;
        }
    }
    board = connectRoom(board);
    return board;
}

// randomly initialize the location of each room in the game board before the game starts
//  parameter: 1D array Room with sorted order, R1,R2,....R9 and its size, which is 9
//  return : a randomized array with an unpredictable order that is within the range
struct Room *randomizeLocation(struct Room *room_1D, int size){
    srand(time(0)); // gives the random function a new seed
    for (int i = 0; i < size; i++){
        int random_number = rand() % size;
        struct Room temp = room_1D[i]; // important in case to lose the oringinal room
        room_1D[i] = room_1D[random_number];
        room_1D[random_number] = temp;
    }
    return room_1D;
}

// TO DO : connect the room via pointers in four directions, North, South, West, East
// parameter: the 2D board
struct Room **connectRoom(struct Room **board){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i == 0){
                if (j == 0){
                    board[i][j].West = board[i][j].North = NULL;
                    board[i][j].East = &board[i][j + 1];
                    board[i][j].South = &board[i + 1][j];
                }
                else if (j == 1){
                    board[i][j].North = NULL;
                    board[i][j].West = &board[i][j - 1];
                    board[i][j].East = &board[i][j + 1];
                    board[i][j].South = &board[i + 1][j];
                }
                else{// j ==2
                    board[i][j].North = NULL;
                    board[i][j].West = &board[i][j - 1];
                    board[i][j].East = NULL;
                    board[i][j].South = &board[i + 1][j];
                }
            }
            else if (i == 1){
                if (j == 0){
                    board[i][j].West = NULL;
                    board[i][j].North = &board[i - 1][j];
                    board[i][j].East = &board[i][j + 1];
                    board[i][j].South = &board[i + 1][j];
                }
                else if (j == 1){
                    board[i][j].North = &board[i - 1][j];
                    board[i][j].West = &board[i][j - 1];
                    board[i][j].East = &board[i][j + 1];
                    board[i][j].South = &board[i + 1][j];
                }
                else{ // j ==2
                    board[i][j].North = &board[i - 1][j];
                    board[i][j].West = &board[i][j - 1];
                    board[i][j].East = NULL;
                    board[i][j].South = &board[i + 1][j];
                }
            }
            else{ // i ==2
                if (j == 0){
                    board[i][j].West = board[i][j].South = NULL;
                    board[i][j].North = &board[i - 1][j];
                    board[i][j].East = &board[i][j + 1];
                }
                else if (j == 1){
                    board[i][j].North = &board[i - 1][j];
                    board[i][j].West = &board[i][j - 1];
                    board[i][j].East = &board[i][j + 1];
                    board[i][j].South = NULL;
                }
                else{ // j ==2
                    board[i][j].North = &board[i - 1][j];
                    board[i][j].West = &board[i][j - 1];
                    board[i][j].East = board[i][j].South = NULL;
                }
            }
        }
    }
    return board;
}

// TO DO: randomly pick a number to pick a room, an item, and a character as the answer
// purpose: conveniently to randomize with a given size
// return: a number from 0 to the size
int randomNumber(int size){
    srand(time(0));       // gives the random function a new seed
    return rand() % size; // guarantee to return an index that is not out of bound
}

// TO DO: print out the characters in each room in 2D array
// parameter: the game board
void print_character(struct Room **board){
    printf("the list of characters: ");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (strcmp(*board[i][j].character, "") != 0){
                printf("%s ", *board[i][j].character);
            }
        }
    }
    printf("\n");
}

// TO DO: print out the name of rooms in 2D array format
// parameter: the game board
void print_room(struct Room **board){
    printf("the list of rooms: ");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%s ", board[i][j].name);
        }
    }
    printf("\n");
}

// TO DO: print out the name of items in each room in 2D array format
// parameter: the game board
void print_items(struct Room **board){
    printf("the list of items: ");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            struct item *list = board[i][j].itemlist;
            printList(*list); // dereference, open the box
        }
    }
    printf("\n");
}

// return an array that contains all the weapons, does not include empty item
struct item *get_all_item(struct Room **board){
    struct item *items = malloc(6 * sizeof(struct item)); // only 6 murder weapon
    int index = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (strcmp(board[i][j].itemlist->item_name, "") !=0){
                items[index] = *board[i][j].itemlist;
                index++;
            }
        }
    }
    return items;
}

// show clues that each time the user enters the room
//paramter: the current room the avatar is at
void showMessage(struct Room *current_room){
    char *room_name = current_room->name;
    if (strcmp("Bathroom", room_name) == 0){
        printf("Does not seem like it has any water stain on the bathtub\n");
    }
    else if (strcmp("Basement", room_name) == 0){
        printf("Jeff was playing music at the MusicRoom with Adam before Matt went to eat cake with him\n");
    }
    else if (strcmp("Attic", room_name) == 0){
        printf("Matt was eating the cake with Adam at Yummy Yummy\n");
    }
    else if (strcmp("Balcony", room_name) == 0){
        printf("Eric was showering in the bathroom\n");
    }
    else if (strcmp("StudyRoom", room_name) == 0){
        printf("Why is Anan in the study room? Today is Saturday!\n");
    }
    else{
        printf("No evidence has found in %s\n", room_name);
    }
}

// print out the room name given by one room 
// parameter: a pointer of only one room
char* print_single_room(struct Room *r, char *direction){
    char *name;
    if(strcmp(direction, "north") == 0 && r->North != NULL){
        name = r->North->name;
    }else if(strcmp(direction, "south") == 0 && r->South!= NULL){
        name = r->South->name;
    }else if(strcmp(direction, "west") == 0 && r->West != NULL){
        name = r->West->name;
    }else if(strcmp(direction, "east") == 0 && r->East != NULL){
        name = r->East->name;
    }else{  // room must be empty
        name = "empty";
    }
    return name;
}

// print out all the character of one room
// paramter: a pointer of that room
void print_characterForOneRoom(struct Room * room){
    if(room == NULL){
        printf(" and no one is here");
    }else{
       for(int i = 0; i<MAX_CHARACTER;i++){
           if(room->character[i] != NULL && strcmp(room->character[i], "") !=0){
                printf("%s ",room->character[i]);
           } 
       }
       printf("\n");   
    }
}

// check if the direction is valid 
// paramter: the string of the room name
// return 1 if the direction is valid, otherwise is 0
int checkDirectionValid(char *direction){
    int invalid = 0;
    if(strcmp(direction, "north") != 0){
        return !invalid;
    }else if(strcmp(direction, "south") != 0){
        return !invalid;
    }else if(strcmp(direction, "east") != 0){
        return !invalid;
    }else if(strcmp(direction, "west") != 0){
        return !invalid;
    }
    return invalid;
}