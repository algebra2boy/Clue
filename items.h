#include <stdio.h>

#ifndef ITEMS_H
#define ITEMS_H

// a Struct representing a LinkedList of items
struct item
{
    char *item_name;        // each item has its own name
    struct item *next_item; // the memory adderss of next item
};

// adding/moving the item from one room to the avatar's inventory or other way around
// adding the item to the begin of LinkedList
// parameter: the name of a new item, the pointer of the previous head node
struct item *add_item(char *name, struct item *old_item);

// dropping/removing the item from the avatar's inventory or the other way around
// deallocate the memory of the removed item
// parameters: the name of the current item, the pointer of the old item
struct item *drop_item(char *name, struct item *item);

// print out the list of items
// parameter: the head of the Linkedlist that is the struct item, not pointer
void printList(struct item head);

// check the room if it exists
// parameter: the room that is either at North, East, West, South of the current room, but not the current room
// return: room exist returns 1, otherwise return 0
int checkRoomExist(struct Room *r);

// check the item room if it valids
// parameter: a string of the item
// return: item name exist returns 1, otherwise return 0
int checkItemNameValid(char *name, struct item *list_item);

// check the charcater name if it valids
// parameter: a string of character name
// return: character name exist returns 1, otherwise return 0
int checkCharacterNameValid(char *name, char *character_list[]);

// check the itemlist if it exists
// parameter: a pointer of itemlist
// return: itemlist exist returns 1, otherwise returns 0
int checkItemlistValid(struct item *itemlist);

#endif