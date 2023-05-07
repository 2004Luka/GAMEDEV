#pragma once
#include <iostream>
#include <ncurses.h>

using namespace std;
#define mapx    49
#define mapy    25

class Enemy{
    private:
    char form;
    int enemy_count;
    int corx;
    int cory;
    int direction;

    public:
    void setform(char Form){
        form=Form;
    }
    char getform(){
        return form;
    }
    

    void setx(int x){
        corx=x;
    }
    int getcorx(){
        return corx;
    }
    

    void sety(int y){
        cory=y;
    }
    int getcory(){
        return cory;
    }
    void setdirection(int dir){
        direction=dir;
    }
    int getdirection(){
        return direction;
    }
    
    
};


