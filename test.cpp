#include <iostream>
#include <string>
#include "console.h"
// #include <thread>  // For std::this_thread::sleep_for
// #include <chrono>  // For std::chrono::seconds
#include <unistd.h>
//#include <sys/select.h>
//#include <termios.h>

#define PAUSE(x) std::this_thread::sleep_for(std::chrono::seconds(x))
#define TAIL snake_len-2
#define SCR_LEN 40
#define SCR_WID 20

using namespace std;

int main()
{
    int c;

    //if(listenForKeyPress(1) == ESC_KEY){
    while (1)
    {
    
 //   c = listenForKeyPress(1);

    if (c == ESC_KEY){ // Escape sequence
        if (getchar() == 91){ // '['
            c=getch();
            if (c == UP_KEY || c == DOWN_KEY || c == RIGHT_KEY || c == LEFT_KEY){
                return c;
            }
        }else if (getchar() == ESC_KEY){
            return c;
        }
    }//f
    }
    return 0;
}