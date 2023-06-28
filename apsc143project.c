// APSC 143 Engineering Programming Project Starter Code
// Feel free to change anything about this file, but do not remove #include "colours.h".

// Make sure to include all relevant libraries
#include <stdio.h>
#include "colours.h"
#include <conio.h>

// You don't need to use these, but they help make your code look more organized
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

// Below are the required functions for this program, but you will need to create your own as well.
// Make sure to specify the required parameters, if any.\

//Read the file and assign values to the 2d malloc array
char **readfile(char *filename){
    //Open the file through the specified file path and read it
    FILE *wallFP = fopen(filename, "r");
    if (wallFP == NULL){
        printf("File not found.\n");
        exit(0);
    }
    //Nested for loop to iterate through and malloc 2d array
    char **mapSide = (char **) malloc(11 * 33 * sizeof(char));
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 34; ++j) {
            mapSide[i] = (char *) malloc(11 * sizeof(char));
        }
    }
    //Assign value to malloc 2d array through the file
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < 34; ++j) {
            //If first and last row
            if(i == 0 || i == 10){
                //If index is divisible by 2, print W, and otherwise print a space
                if((j+1) % 3 == 0) {
                    mapSide[i][j] = WALL;
                }else{
                    mapSide[i][j] = EMPTY;
                }
                //Last line, print new line character for map characters to print on a new line
                mapSide[i][33] = '\n';

            }
            else {
                //If j index is equal to 30, print 2 spaces, then W, then the newline character, this is the edge wall
                if(j == 30){
                    mapSide[i][j] = EMPTY;
                    mapSide[i][j+1] = EMPTY;
                    mapSide[i][j+2] = WALL;
                    mapSide[i][j+3] = '\n';
                }
                    //If j index is equal to 2, print W then space. This is the start of the line and the edge wall
                else if (j == 2){
                    mapSide[i][2] = WALL;
                    mapSide[i][3] = EMPTY;
                    mapSide[i][4] = EMPTY;
                }
                //In between the walls scan the text file information into the file.
                if(j > 3 && j<30){
                    fscanf(wallFP, "%c", &mapSide[i][j+1]);
                }
            }
        }

    }
    mapSide[9][32] = WALL;
    //New line character for the bottom row of walls
    mapSide[9][33] = '\n';
    mapSide[10][34] = '\0';
    //Return the array created
    return mapSide;
}
void printMap(char **visibleMap) {
    //print each character from 2d malloc array to screen
    printf("\n");
    for (int i = 0; i < 11; ++i) {
        for (int j = 2; j < 34; ++j) {
            printf("%c", visibleMap[i][j]);
        }
    }
}
//Check the win condition where is there are 0 dots left the player has eaten them therefore resulting in a win
int winCheck(char **visibleMap) {
    //Set a counter to 0 to start, this determines how many dots are remaining
    int count = 0;

    //Nested for loop to loop through each character of the 2d array
    for (int i = 0; i < 12; ++i) {
        for (int j = 2; j < 34; ++j) {
            //If a dot is encountered add 1 to the total
            if(visibleMap[i][j] == DOT){
                count++;
            }
        }
    }
    //If there are 0 dots counted, the player has eaten them all and has won the game.
    if(count == 0){
        printf("\nCongratulations! You win! Press any key to exit the game");
        return 1;
    }
    return 0;
}
int loseCheck(char **visibleMap, char **invisibleMap) {
    for(int i = 0; i< 12; ++i){
        for(int j = 2; j<34; j++) {
            if(visibleMap[i][j] == PACMAN && invisibleMap[i][j] == GHOST) {
                printf("\nSorry, you lose. Press any key to exit the game");
                fflush(stdout);
                    return 2;
            }
        }
    }
    return 1;
}
int isWall(char **visibleMap, int row, int column) {
    //Check to see if a "W" is encountered at the specified index through the row and column, return 1 meaning a wall is there
    if(visibleMap[row][column] == WALL){
        return 1;
    }
    return 0;
}

void Ghosts(char **invisibleMap, int a, int b, int pac1, int pac2) {
    int p1 = 2, p2 = 2;

    if(a<pac1 && b == pac2) {
        for(int i = a; i < pac1 + 1; i++) {
            if(isWall(invisibleMap, i, b) == 1) {
                p1 = 0;
                break;
            }
            else
                p1 = 1;
        }
    }
    if(a>pac1 && b == pac2) {
        for(int i = pac1; i < a + 1; i++) {
            if(isWall(invisibleMap, i, b) == 1) {
                p1 = 0;
                break;
            }
            else
                p1 = 1;

        }
    }
    if(b<pac2 && a == pac1) {
        for(int i = b; i < pac2 + 1; i++) {
            if (isWall(invisibleMap, a, i) == 1) {
                p2 = 0;
                break;
            }
            else
                p2 = 1;
        }
    }
    if(b>pac2 && a == pac1) {
        for(int i = pac2; i < b + 1; i++) {
            if(isWall(invisibleMap, a, i) == 1) {
                p2 = 0;
                break;
            }
            else
                p2 = 1;
        }
    }
    if(p1 == 1 || p2 == 1) {
        if (p1 == 1) {
            if (a > pac1) {
                invisibleMap[a - 1][b] = GHOST;
            } else if (a < pac1) {
                invisibleMap[a + 1][b] = GHOST;
            }
        }
        else if (p2 == 1) {
            if (b > pac2) {
                invisibleMap[a][b - 3] = GHOST;
            } else if (b < pac2) {
                invisibleMap[a][b + 3] = GHOST;
            }
        }
    }
    else {
        //Ghost coordinate movements
        if (a == 1 && b == 5) {
            invisibleMap[a + 1][b] = GHOST;
        } else if (a == 9 && b == 5) {
            invisibleMap[a][b + 3] = GHOST;
        } else if (b == 5) {
            invisibleMap[a + 1][b] = GHOST;
        } else if (a == 1 && b == 29) {
            invisibleMap[a][b - 3] = GHOST;
        } else if (b == 29) {
            invisibleMap[a - 1][b] = GHOST;
        } else if (a == 9 && b == 14) {
            invisibleMap[a - 1][b] = GHOST;
        } else if (a == 9) {
            invisibleMap[a][b + 3] = GHOST;
        } else if (a == 7 && b == 14) {
            invisibleMap[a][b + 3] = GHOST;
        } else if (a == 1 && b == 20) {
            invisibleMap[a + 1][b] = GHOST;
        } else if (a == 1) {
            invisibleMap[a][b - 3] = GHOST;
        }else if (a == 7 && b == 11) {
            invisibleMap[a][b + 3] = GHOST;
        } else if (a == 3 && b == 11) {
            invisibleMap[a + 1][b] = GHOST;
        }else if (b == 11){
            invisibleMap[a + 1][b] = GHOST;
        }else if (a == 5) {
            invisibleMap[a][b + 3] = GHOST;
        } else if (b == 14) {
            invisibleMap[a - 1][b] = GHOST;
        } else if (a == 7 && b == 23) {
            invisibleMap[a - 1][b] = GHOST;
        } else if (a == 7) {
            invisibleMap[a][b + 3] = GHOST;
        } else if (a == 3 && b == 23) {
            invisibleMap[a][b - 3] = GHOST;
        } else if (b == 23) {
            invisibleMap[a - 1][b] = GHOST;
        } else if (a == 3 && b == 20) {
            invisibleMap[a][b - 3] = GHOST;
        } else if (b == 20) {
            invisibleMap[a + 1][b] = GHOST;
        } else if (a == 3) {
            invisibleMap[a][b - 3] = GHOST;
        } else if (a == 8) {
            invisibleMap[a + 1][b] = GHOST;
        }
    }
    int ghostCounter = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 34; j++) {
            if (invisibleMap[i][j] == GHOST) {
                ghostCounter++;
            }
        }
    }
    if(ghostCounter == 3) {
        invisibleMap[a][b] = EMPTY;
    }
    else if (ghostCounter == 1) {
        invisibleMap[a][b] = GHOST;
    }
}

int PacMan(char **visibleMap){
    //character string for input
    char input;
    scanf("%s", &input);
    //If input is equal to w, move pacman up 1 space
    if(input == UP) {
        //Loop through all elements of file to find the PACMAN with the nested loop
        for (int i = 0; i < 11; ++i) {
            for (int j = 2; j < 34; ++j) {
                if (visibleMap[i][j] == PACMAN) {
                    //If isWall function returns 0, there is no wall where the character would be moved to, character is then moved
                    if (isWall(visibleMap, i - 1, j) == 0) {
                        //Move PACMAN up 1 through the i index
                        visibleMap[i - 1][j] = PACMAN;
                        //Replace the spot the PACMAN just was with a blank space
                        visibleMap[i][j] = EMPTY;
                        return 1;
                        //Break out of loop
                        break;
                    } else {
                        continue;
                    }
                }
            }
        }
    }
    else if(input == LEFT) {
        //Loop through all elements of file to find the PACMAN with the nested loop
        for (int i = 0; i < 11; ++i) {
            for (int j = 2; j < 34; ++j) {
                if (visibleMap[i][j] == PACMAN) {
                    //If isWall function returns 0, there is no wall where the character would be moved to, character is then moved
                    if (isWall(visibleMap, i, j - 3) == 0) {
                        //Move PACMAN left 2 spaces to account for the blank space between characters.
                        visibleMap[i][j - 3] = PACMAN;
                        //Replace the spot the PACMAN just was with a blank space
                        visibleMap[i][j] = EMPTY;
                        return 1;
                    } else {
                        continue;
                    }
                }
            }
        }
    }
    else if(input == DOWN) {
        //Set row and column values
        int row;
        int column;
        //Set a boolean value to indicate if wall has been hit
        int iswall = 0;
        //Loop through all elements of file to find the PACMAN with the nested loop
        for (int i = 0; i < 11; ++i) {
            for (int j = 2; j < 34; ++j) {
                if (visibleMap[i][j] == PACMAN) {
                    //If isWall function returns 0, there is no wall where the character would be moved to, character is then moved
                    if (isWall(visibleMap, i + 1, j) == 0) {
                        //Set row and column values to current loop counters to be used later and boolean value of iswall to true
                        row = i;
                        column = j;
                        iswall = 1;
                        break;
                    } else {
                        continue;
                    }
                }
            }
        }
        //If boolean value is true, move the character using the row and column values that were set earlier.
        if (iswall == 1) {
            //Move PACMAN down 1 space
            visibleMap[row + 1][column] = PACMAN;
            //Replace the spot the PACMAN just was with a blank space
            visibleMap[row][column] = EMPTY;
            return 1;
        }
    }
    else if(input == RIGHT) {
        //Loop through all elements of file to find the PACMAN with the nested loop
        for (int i = 0; i < 11; ++i) {
            for (int j = 2; j < 34; ++j) {
                if (visibleMap[i][j] == PACMAN) {
                    //If isWall function returns 0, there is no wall where the character would be moved to, character is then moved
                    if (isWall(visibleMap, i, j + 3) == 0) {
                        //Move PACMAN right 2 spaces to account for the blank space between characters.
                        visibleMap[i][j + 3] = PACMAN;
                        //Replace the spot the PACMAN just was with a blank space
                        visibleMap[i][j] = EMPTY;
                        return 1;
                    } else {
                        continue;
                    }
                }
            }
        }
    }

}void Locations(char **invisibleMap, char **visibleMap) {
    int a = 100, b, c = 100, d, pac1, pac2;

    for (int i = 1; i < 10; i++) {
        for (int j = 5; j < 30; j++) {
            if (invisibleMap[i][j] == GHOST) {
                a = i;
                b = j;
                break;
            } else
                continue;
        }
        if (a == i)
            break;
    }
    for (int i = 1; i < 10; i++) {
        for (int j = 5; j < 30; j++) {
            if (invisibleMap[i][j] == GHOST) {
                c = i;
                d = j;
            }
        }
    }
    for (int i = 1; i < 10; i++) {
        for (int j = 5; j < 30; j++) {
            if (visibleMap[i][j] == PACMAN) {
                pac1 = i;
                pac2 = j;
            }
        }
    }
    if (loseCheck(visibleMap, invisibleMap) == 2)
        return;
    //only move ghost if pacman movement returns 1 meaning pacman has moved
    if (PacMan(visibleMap) == 1){
        fflush(stdout);
    Ghosts(invisibleMap, a, b, pac1, pac2);
    fflush(stdout);
    Ghosts(invisibleMap, c, d, pac1, pac2);
    fflush(stdout);
    }
}
//Function to print all maps which the user sees
char **combineMap(char **visibleMap, char **invisibleMap,  char **combinedMap) {
    //Loop through invisible map and if location has a ghost, print it onto the combined map which is printed to the user
    for (int i = 1; i < 10; i++) {
        for (int j = 2; j < 37; j++) {
            if (invisibleMap[i][j] == GHOST) {
                combinedMap[i][j] = GHOST;
            } else
                combinedMap[i][j] = visibleMap[i][j];
        }
    }
    return combinedMap;
}
int main() {
    //Read map into 3 different variables for change later
    char **invisibleMap = readfile("C:\\Users\\hanmi\\CLionProjects\\PacManFInal\\mapLarge.txt");
    char **visibleMap = readfile("C:\\Users\\hanmi\\CLionProjects\\PacManFInal\\mapLarge.txt");
    char **combinedMap = readfile("C:\\Users\\hanmi\\CLionProjects\\PacManFInal\\mapLarge.txt");
    //Determine the position of the ghost and change into dot for the map without ghosts, ghosts will be printed on separately
    for (int i = 1; i < 10; i++) {
        for (int j = 5; j < 30; j++) {
            if (visibleMap[i][j] == GHOST) {
                visibleMap[i][j] = DOT;
            }
        }
    }
    printf("press \"w\", \"a\", \"s\", \"d\" to move up, left, down, or right.");
    fflush(stdout);
    //Print the current map to the screen
    printMap(invisibleMap);
    fflush(stdout);
    //Loop through program, while loop breaks when wincheck equals 1 meaning win or loss condition is met
    while(winCheck(visibleMap) == 0){
        //Call the Pacman movement function
        Locations(invisibleMap, visibleMap);
        fflush(stdout);
        //Print the map with ghosts and the map without them
        printMap(combineMap(visibleMap, invisibleMap, combinedMap));
        fflush(stdout);
        //Check if the loss condition is activated and break if activated
        if(loseCheck(visibleMap, invisibleMap) == 2)
            break;
    }

}
