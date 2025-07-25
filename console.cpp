//#include "console.h"
#include <termios.h>
#include <unistd.h>
//#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

/* void PrintMenu(){
    // printing the menu
    printf(" This a Tree Data Structure\n");
    printf("===========================\n");
    printf("> isert node\n");
    printf("> print tree preorder\n");
    printf("> print tree inorder\n");
    printf("> print tree postorder\n");
    printf("> exit\n");
} */

/* void returnToMainMenu(int* py){
    system("clear");
    PrintMenu();
    *py=3;
    gotoxy(0, *py);
} */


void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}


int getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);          // Save the terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply the new settings

    ch = getchar();                          // Read a single character

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore the terminal attributes
    return ch;
}


/* bool listenForKeyPressWithTimeout(int durationSeconds) {
    struct termios oldt, newt;
    fd_set set;
    struct timeval timeout;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Set terminal to non-canonical mode
    newt.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Initialize the file descriptor set and timeout
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    timeout.tv_sec = durationSeconds;
    timeout.tv_usec = 0;

    // Wait for input with the specified timeout
    int res = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

    // Restore the original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (res > 0) {
        char c;
        read(STDIN_FILENO, &c, 1);  // Read the key pressed
        return true;                // A key was pressed within the timeout
    } else {
        return false;               // No key press detected within the timeout
    }
} */
/* int listenForKeyPress(int durationSeconds) {
    initscr();                    // Initialize ncurses mode
    nodelay(stdscr, TRUE);         // Make getch() non-blocking
    timeout(durationSeconds * 1000);  // Set timeout in milliseconds

    int ch = getch();              // Get the key press (non-blocking with timeout)
    endwin();                      // End ncurses mode

    if (ch != ERR) {
        return ch;                 // Return the key pressed as an int
    }

    return -1;                     // Return -1 if no key was pressed within the timeout
} */

/* int get_ctrl_input(){
    int c = getch();

    if (c == ESC_KEY){ // Escape sequence
        if (getch() == 91){ // '['
            c=getch();
            if (c == UP_KEY || c == DOWN_KEY || c == RIGHT_KEY || c == LEFT_KEY){
                return c;
            }
        }else if (getchar() == ESC_KEY){
            return c;
        }
    }

    //printf("non-Control Key %d is hit.\n", c);
    return -1;
}//f */

