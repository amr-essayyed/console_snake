//#include<bits/stdc++.h>

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include "console.h"
// #include <thread>  // For std::this_thread::sleep_for
// #include <chrono>  // For std::chrono::seconds
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <pthread.h> // POSIX THREAD Library

using namespace std;

#define PAUSE(x) std::this_thread::sleep_for(std::chrono::seconds(x))
#define TAIL snake_len-2
#define SCR_LEN 40
#define SCR_WID 20

int key_code;

void* get_ctrl_in(void* arg);

class snake_vertebra
{
    int x, y;

    public:
    snake_vertebra()
    {
        y = x = 0; 
    }

    snake_vertebra(int _x, int _y)
    {
        x=_x;
        y=_y;      
    }

    void set_xy(int _x, int _y)
    {
        x=_x;
        y=_y;
    }

    void set_x(int _x)
    {
        x=_x;
    }
    
    void set_y(int _y)
    {
        y=_y;
    }

    int get_x()
    {
        return x;
    }

    int get_y()
    {
        return y;
    }

    int operator==(snake_vertebra b){
        return (this->x == b.get_x() && this->y == b.get_y());
    }
};

class screen{
    public:
    static int x_boundry;
    static int y_boundry;

    static void print(){
        gotoxy(1,1);
        // print horizontal
        for(int i=0; i<x_boundry; i++){
            cout<<"+";
        }
        for(int i=0; i<y_boundry-2; i++){
            cout<<"\n";
            cout<<"+";
            for(int i=0; i<x_boundry-2; i++){
                cout<<" ";
            }
            cout<<"+";
        }
        cout<<"\n";
        for(int i=0; i<x_boundry; i++){
            cout<<"+";
        }
        
        
    }
};
int screen::x_boundry = 80;
int screen::y_boundry = 20;

class snake
{
    snake_vertebra skull;
    snake_vertebra* body;
    int snake_len;
    int moving_dir;

    public:
    snake():skull(10,10)
    {
        body = new snake_vertebra(9,10);
        snake_len = 2;
        moving_dir = RIGHT_KEY;
    }
    ~snake()
    {
        delete body;
    }

    snake_vertebra get_skull()
    {
        return skull;
    }

    snake_vertebra* get_body(){
        return body;
    }

    int get_len(){
        return snake_len;
    }
    
    void print(){
        gotoxy(skull.get_x(), skull.get_y());
        cout << "@"<< flush;
        for(int i=0; i< snake_len-1; i++)
        {
            gotoxy(body[i].get_x(), body[i].get_y());
            cout << "o"<< flush;
        }
    }

    void grow()
    {
        snake_vertebra* growing_body = new snake_vertebra[snake_len];
        for(int i=0; i< snake_len-1; i++){
            growing_body[i] = body[i];
        }
        // new vertebra value
        int tail_xorientation;
        int tail_yorientation;

        if(snake_len==2){
            tail_xorientation = body[TAIL].get_x() - skull.get_x();
            tail_yorientation = body[TAIL].get_y() - skull.get_y();
        }else{
            tail_xorientation = body[TAIL].get_x() - body[TAIL-1].get_x();
            tail_yorientation = body[TAIL].get_y() - body[TAIL-1].get_y();
        }

        if(tail_xorientation < 0) // grow to the left
        {
            growing_body[TAIL+1].set_xy( body[TAIL].get_x()-1, body[TAIL].get_y() );
        }
        else if(tail_xorientation > 0) // grow to the right
        {
            growing_body[TAIL+1].set_xy( body[TAIL].get_x()+1, body[TAIL].get_y() );
        }
        else if(tail_yorientation < 0) // grow to above
        {
            growing_body[TAIL+1].set_xy( body[TAIL].get_x(), body[TAIL].get_y()-1 );
        }
        else if(tail_yorientation > 0)
        {
            growing_body[TAIL+1].set_xy( body[TAIL].get_x(), body[TAIL].get_y()+1 );
        }//ifelse
     
        delete(body);
        body = growing_body;
        snake_len++;
    }
    
    void move(int _moving_dir)
    {
        int move=0;
        snake_vertebra spoor[2];
        spoor[0]=skull;
        spoor[1]=body[0];
        
        if(_moving_dir == RIGHT_KEY && moving_dir != LEFT_KEY){
            skull.set_x(skull.get_x()+1);
            move=1;
        }else if(_moving_dir == LEFT_KEY && moving_dir!=RIGHT_KEY){
            skull.set_x(skull.get_x()-1);
            move=1;
        }else if(_moving_dir == DOWN_KEY && moving_dir!=UP_KEY){
            skull.set_y(skull.get_y()+1);
            move=1;
        }else if(_moving_dir == UP_KEY && moving_dir!=DOWN_KEY){
            skull.set_y(skull.get_y()-1);
            move=1;
        }

        if(move){
            for(int i =0, j=0; i<snake_len-1; i++, j=i%2){
                body[i] = spoor[j];
                spoor[j]= body[i+1];
            }
            moving_dir = _moving_dir;
        }
    }

    void move()
    {
        int _moving_dir = moving_dir;

        int move=0;
        snake_vertebra spoor[2];
        spoor[0]=skull;
        spoor[1]=body[0];
        
        if(_moving_dir == RIGHT_KEY && moving_dir != LEFT_KEY){
            skull.set_x(skull.get_x()+1);
            move=1;
        }else if(_moving_dir == LEFT_KEY && moving_dir!=RIGHT_KEY){
            skull.set_x(skull.get_x()-1);
            move=1;
        }else if(_moving_dir == DOWN_KEY && moving_dir!=UP_KEY){
            skull.set_y(skull.get_y()+1);
            move=1;
        }else if(_moving_dir == UP_KEY && moving_dir!=DOWN_KEY){
            skull.set_y(skull.get_y()-1);
            move=1;
        }

        if(move){
            for(int i =0, j=0; i<snake_len-1; i++, j=i%2){
                body[i] = spoor[j];
                spoor[j]= body[i+1];
            }
            moving_dir = _moving_dir;
        }
    }
};

/* 
        else if(_moving_dir == DOWN_KEY && moving_dir!=UP_KEY){
            snake_vertebra spoor[2];
            spoor[0]=skull;
            spoor[1]=body[0];
            
            skull.set_y(skull.get_y()+1);

            for(int i =0, j=0; i<snake_len-1; i++, j=i%2){
                body[i] = spoor[j];
                spoor[j]= body[i+1];
            }
            moving_dir = _moving_dir;
        }
        else if(_moving_dir == LEFT_KEY && moving_dir!=RIGHT_KEY){
            snake_vertebra spoor[2];
            spoor[0]=skull;
            spoor[1]=body[0];
            
            skull.set_x(skull.get_x()-1);

            for(int i =0, j=0; i<snake_len-1; i++, j=i%2){
                body[i] = spoor[j];
                spoor[j]= body[i+1];
            }
            moving_dir = _moving_dir;
        }
        else if(_moving_dir == UP_KEY && moving_dir!=DOWN_KEY){
            snake_vertebra spoor[2];
            spoor[0]=skull;
            spoor[1]=body[0];
            
            skull.set_y(skull.get_y()-1);

            for(int i =0, j=0; i<snake_len-1; i++, j=i%2){
                body[i] = spoor[j];
                spoor[j]= body[i+1];
            }
            moving_dir = _moving_dir;
        } */
 

class food
{
    snake_vertebra pos;
    
    public:

    food():pos(5,5)
    {}

    snake_vertebra get_pos(){
        return pos;
    }

    void set_pos(int _x, int _y){
        pos.set_xy(_x, _y);
    }

    void print()
    {
        // random_device rd;
        // mt19937 gen(rd());
        // uniform_int_distribution<> dis(1, 20);
        // int x = dis(gen);
        // int y = dis(gen);
        gotoxy(pos.get_x(),pos.get_y());
        cout<<"é"<<flush;
    }
}; 

int playing=1;
int main()
{
    
    snake soso;
    int dir;
    food tofaaha;
    int score=0;
    pthread_t ctrl_thrd; // cntrol thread id

    // highest score file
    const string hs_file = "highest_score";
    ifstream infile(hs_file);
    if (!infile.is_open()) {
        // File does not exist, create it
        ofstream outfile(hs_file);
        outfile << 0;
        outfile.close();
    }

    ifstream infile_read(hs_file);
    int hist_score;
    infile_read >> hist_score;
    infile_read.close();

    // initial print
    std::cout << "\033[?25l";  // ANSI escape code to hide the cursor
    std::cout.flush();
    system("clear");
    gotoxy(1,24);
    cout<< "Highest score: "<< hist_score;
    // screen::print();
    // soso.print();
    // tofaaha.print();

    // create control thread
    pthread_create(&ctrl_thrd, NULL, get_ctrl_in, NULL);

    while(playing)
    {
        
        // print
        screen::print();
        soso.print();
        tofaaha.print();

        

        if(key_code){
            //std::cout << '\t'<< key_code <<": OK\n";
            if(key_code == UP_KEY || key_code == DOWN_KEY || key_code == RIGHT_KEY || key_code == LEFT_KEY ){
                soso.move(key_code); key_code=0;
            }else if(key_code == ESC_KEY){
                playing=0;
                system("clear");
                return 0;//playing=0; key_code=0;
            }
        }else{
            soso.move();    
        }
        

        // did he eat?
        if( soso.get_skull() == tofaaha.get_pos() ){
            soso.grow();
            score++;
            // Gen Rand x, y
            srand(time(NULL));
            int x = (rand() % 78) + 2;
            int y = (rand() % 18) + 2;
            tofaaha.set_pos(x,y);
        }
        screen::print();
        soso.print();
        tofaaha.print();
        gotoxy(1,22);
        cout<< "your score: "<< score;
        
        
        //did he crash?
        if(soso.get_skull().get_x() == 1|| soso.get_skull().get_x() == screen::x_boundry || soso.get_skull().get_y() == 1|| soso.get_skull().get_y() == screen::y_boundry){ // hit the wall
            playing=0;
        }

        for(int i=0; i<soso.get_len(); i++){
            if(soso.get_skull()==soso.get_body()[i]){
                playing=0;
            } 
        }
         
        usleep(100000);
    }
    
    //pthread_cancel(ctrl_thrd);
    if(score > hist_score){
        ofstream outfile(hs_file);
        outfile << score;
        outfile.close();
    }
    

    gotoxy(1,21);
    cout << "Game Over!!                 \n";
    getch();
    pthread_join(ctrl_thrd, NULL);
    system("clear");

    return 0;
}


void* get_ctrl_in(void* arg){
    int c;
    while (playing)
    {   
        // getting key-code block
        // gotoxy(1,21);
        // cout<<"control mode ...                             ";
        if(c = getch()) {
            if (c == ESC_KEY){
                if (getch() == 91){
                    c= getch();
                }
            }
        }

        // processing block
        //if (c == UP_KEY || c == DOWN_KEY || c == RIGHT_KEY || c == LEFT_KEY || c == ESC_KEY){
        key_code=c;
        usleep(100000);
        //}
    }
    
    return NULL;
}