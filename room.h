#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef ROOM_H
#define ROOM_H
#define MAX_CHARACTER 6 // the maximum number of characters that can be in the room is 6

//  Struct representing a room board
struct Room{
    char * name; // the name of the room such as "kitchen", "bathroom"
    struct Room *North;
    struct Room *South;
    struct Room *East;
    struct Room *West;
    struct item *itemlist;          // LinkedList structure
    char *character[MAX_CHARACTER]; // the name of all the players in this room // NULL for character do not exist 
};

// Create a 3x3 room via pointers with 2D malloc
struct Room **createBoard();

// connect the room via pointers in four directions, North, South, West, East
// parameter: the 2D board
struct Room **connectRoom(struct Room **board);

// creating an pointer linkedList to make itemlist for each room
// which contains the memory address of first item in that room
// return: a linkedlist of items
struct item *get_item_array();

// return an struct item array that contains all the weapons, does not include empty item
struct item *get_all_item();

// randomly initialize the location of each room in the game board before the game starts
//  parameter: 1D array Room with sorted order, R1,R2,....R9 and its size, which is 9
//  return : a randomized array with an unpredictable order
struct Room *randomizeLocation(struct Room *room_1D, int size);

// TO DO: randomly pick a number to pick a room, an item, and a character as the answer
// return: a number from 0 to the length of the array
int randomNumber(int size);

// TO DO: print out the name of characters in each room in 2D array format
// parameter: the game board
void print_character(struct Room **board);

// print out all the character of one room
// paramter: a pointer of that room
void print_characterForOneRoom(struct Room *r);

// TO DO: print out the name of rooms in 2D array format
// parameter: the game board
void print_room(struct Room **board);

// TO DO: print out the name of items in each room in 2D array format
// parameter: the game board
void print_items(struct Room **board);

// show the Message that each time the user enters the room
//paramter: the current room the avatar is at
void showMessage(struct Room *current_room);

// print out the room name given by one room 
// parameter: a pointer of only one room
char* print_single_room(struct Room *r,char* direction);

// check the name if it is empty
// parameter: the room that is either at North, East, West, South of the current room, but not the current room
// return: room exist returns 1, otherwise return 0
int checkRoomExist(struct Room *r);

// check if the direction is valid 
// paramter: the string of the room name
// return 1 if the direction is valid, otherwise is 0
int checkDirectionValid(char* direction);
#endif