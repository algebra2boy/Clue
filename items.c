#include "items.h"
#include <string.h>

// adding/moving the item from one room to the avatar's inventory or other way around, adding the item to the begin of LinkedList
// parameter: the name of a new item, the pointer of the previous head node
struct item *add_item(char *name, struct item *old_item){
    // memory address (pointer) of the new item
    struct item *new_item = (struct item *) malloc(sizeof(struct item));

    // dereference the new pointer, then assign values
    new_item->item_name = name;
    new_item->next_item = old_item;

    return new_item; // this becomes the new head of the Linked List
}

// dropping/removing the item from the avatar's inventory or the other way around
// deallocate the memory of the removed item
// parameters: the name of the current item, the pointer of the old item
struct item *drop_item(char *name, struct item *item){
    struct item *current_item = item;
    struct item *head = item;
    // case 1: only one node
    if (strcmp(item->item_name, name) == 0 && item->next_item == NULL){
        head = NULL;
    }  // case 2: deleting at the front
    else if (strcmp(item->item_name, name) == 0 && item->next_item != NULL){
        struct item * store = item;
        head = current_item->next_item;
        free(store);
    }else{ // case 3: deleting at the middle or back
        while (current_item->next_item != NULL){
            if (strcmp(current_item->next_item->item_name, name) == 0){
                struct item * store = current_item->next_item;
                current_item->next_item = store->next_item;
                free(store);
                break;
            }
            current_item = current_item->next_item;       
        }
    }
    return head;
}

// print out the list of items of the 
// parameter: the head of the Linkedlist that is the struct item, not pointer
void printList(struct item head){
        struct item *current_item = &head;
        // traverse the linkedlist
        while(current_item != NULL){
            if(strcmp(current_item->item_name, "") !=0){
                printf("%s ", current_item->item_name);
            }
                current_item = current_item->next_item;
        }
}

// check the room if it exists
// parameter: the room that is either at North, East, West, South of the current room, but not the current room
// return: room exist returns 1, otherwise return 0
int checkRoomExist(struct Room *r){
    return (r != NULL);
}

// check the item room if it valids 
//parameter: a string of the item 
// return: item name exist returns 0, otherwise return 1
int checkItemNameValid(char * name, struct item *list_item){
    int invalid = 1;
    for(int i = 0;i<6;i++){
        if(strcmp(name, list_item[i].item_name) == 0){ // the item is found in the list item
            invalid = 0;
        }
    }
    return invalid;
}

// check the charcater name if it valids
// parameter: a string of character name
// return: character name exist returns 1, otherwise return 0 
int checkCharacterNameValid(char * name, char * character_list[]){
    int invalid = 1;
    for(int i = 0; i<5;i++){
        if(strcmp(name, character_list[i]) == 0){
            invalid = 0;
        }
    }
    return invalid;
}

// check the itemlist if it exists 
// parameter: a itemlist 
// return: itemlist exist returns 1, otherwise returns 0
int checkItemlistValid(struct item *itemlist){
    return itemlist != NULL;
}