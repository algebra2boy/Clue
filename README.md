# Clue

## Description

Step into a thrilling text adventure game, clue, set on a 3 x 3 gameboard. Use your wits and deductive abilities to uncover the secrets behind a mysterious murder. Rumors suggest that Anan has been murdered, with Jeff suspecting that Matt may have strangled Anan with a rope in the study room. Navigate through rooms, investigate weapons, and interact with characters: Anan, Jeff, Matt, Eric, and Adam, to unveil the truth.

## Implementation Overview

- **Gameboard Configuration**: 
  - Created using a 2D array with `malloc`, making each room a pointer.
  - Each room is a pointer containing:
    - Pointers to adjacent rooms (North, South, East, West).
    - Name of the NPC.
    - LinkedList storing items in the room (at the start, each room contains at most one item).
    - 4 pointers per room, 36 pointers in total.
  - LinkedList for items is implemented with pointers; the next item in the list is another item pointer.
  - The avatar's information, including its location and inventory, is stored in a struct called `Avatar`.
  
- **Memory Management**:
  - After the program concludes, memory allocated for the board, avatar's current room, inventory, and name are deallocated.
  - Memory of nodes removed from a LinkedList is also deallocated.
  - Includes edge-case handling for invalid user inputs.

- **Requirements Satisfied**:
  1. Game has 9 rooms, including the starting room, connected via pointers.
  2. Rooms are randomly initialized on the game board at the start.
  3. Game features at least 6 items and 5 characters apart from the player's avatar.
  4. A room, an item, and a character are randomly chosen as the game's answer.
  5. Each room has a LinkedList of items.
  6. The avatar has an inventory.
  7. Command table (all commands are in `adventure.c` within the main function):
      - `help`, `list`, `look`, `go`, `take`, `drop`, `inventory`, `clue` 
        (with sub-actions detailed under `clue`).

## Compilation

To compile and run the program:

```c
gcc adventure.c room.c -o myProgram
./myProgram
```

## User Input Guide

- Input commands are case-sensitive.
- Use `scanf("%s %s", first, second)` for reading two-word commands.
- For commands with a single word, append a "~": e.g., `help ~` or `look ~`.
- For directional commands: `go north`, `go south`, etc. (Don't use room names like `go Bathroom`).
- For item commands: use the item name, e.g., `take bible`. Valid items: `axe`, `poison`, `knife`, `gun`, `bible`, `rope`.
- For clues: use the character name, e.g., `clue Adam`. Valid characters: `Anan`, `Jeff`, `Matt`, `Eric`, `Adam`.