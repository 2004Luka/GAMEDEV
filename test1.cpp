//!information 
//?https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
#include <iostream>
#include <ncurses.h>
#include "enemy.hpp"
#include "mapPrinter.hpp"
#include <vector>

using namespace std;

bool spawn = true;
bool running = true;
int life = 5;
//!inicialize colors 
#define mapWidth 49
#define mapHeight 25
#define MAXPOINT 1

void initialize_colors() {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_RED, COLOR_RED);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    init_pair(9, COLOR_MAGENTA, COLOR_BLACK);
}
class Player{
    public:    
    string name;
    char character;
    int ycordinate =1;
    int xcordinate =2;
    int playerscore=0;   
    int ability =3; 
    

    void respawn(){
        ycordinate =mapHeight/2;
        xcordinate =mapWidth/2;
    }
};
class GameOverScreen {
private:
    WINDOW* window;
    int max_x, max_y;

public:
    GameOverScreen(WINDOW* parent_window, int width, int height) {
        initialize_colors();
        max_x = width / 2 + 10;
        max_y = height / 2;
        window = newwin(max_y, max_x, 0, 0);
        mvwin(window, (height - max_y) / 2, (width - max_x) / 2);
    }

    ~GameOverScreen() {
        delwin(window);
    }

    void show() {
        wattron(window, COLOR_PAIR(7));
        mvwprintw(window, max_y / 2, max_x / 2 - 5, "game over");
        wattroff(window, COLOR_PAIR(7));
        box(window, 0, 0);
        wrefresh(window);
    }
};
class WinGame {
private:
    WINDOW* window;
    int max_x, max_y;

public:
    WinGame(WINDOW* parent_window, int width, int height) {
        initialize_colors();
        max_x = width / 2 + 10;
        max_y = height / 2;
        window = newwin(max_y, max_x, 0, 0);
        mvwin(window, (height - max_y) / 2, (width - max_x) / 2);
    }

    ~WinGame() {
        delwin(window);
    }

    void show() {
        wattron(window, COLOR_PAIR(8));
        mvwprintw(window, max_y / 2, max_x / 2 - 5, "YOU WIN");
        wattroff(window, COLOR_PAIR(8));
        box(window, 0, 0);
        wrefresh(window);
    }
};

void spawnpoints(WINDOW* window){
        
        int xlocations[9]={2,6,10,14,18,30,34,42,46};
        int ylocations[10]={1,3,5,7,9,15,17,19,21,23};
        int xrandindex=0;
        int yrandindex=0;
        xrandindex = rand() % 9;
        yrandindex = rand() % 10;
        
        int x=xlocations[xrandindex];
        int y=ylocations[yrandindex];
        mvwaddch(window,y,x,'*');  
        wrefresh(window); 
        spawn=false;     
}
void checkEnemyCollisionx(WINDOW *window, vector<Enemy>& enemies, int i,int x,int y,int originalx) {
    
    if (mvwinch(window,y,originalx-x) == '*') {
        wattrset(window, A_NORMAL);
        mvwaddch(window,y,originalx+x,' ');
        mvwaddch(window,y,originalx+x,'*');
    }
    else {
        wattrset(window, A_NORMAL);
        mvwaddch(window,y,originalx+x,' ');
    }
}
void checkEnemyCollisiony(WINDOW *window, vector<Enemy>& enemies, int i,int x,int y,int originaly) {
    if (mvwinch(window,originaly-y,x) == '*') {
        wattrset(window, A_NORMAL);
        mvwaddch(window,originaly+y,x,' ');
        mvwaddch(window,originaly+y,x,'*');
    }
    else {
        wattrset(window, A_NORMAL);
        mvwaddch(window,originaly+y,x,' ');
    }
}
void enemyfunction(WINDOW* window ,vector<Enemy>& enemies,int i,int color){
    int x = enemies[i].getcorx();
    int y = enemies[i].getcory();

    
    
    if((x==mapWidth-19 && y== 15) || (x==mapWidth-15 && y==17) || (x==mapWidth-11 && y==19) 
    || (x==mapWidth-7 && y==mapHeight-4) || (x==mapWidth-3 && y==mapHeight-2))                                                  enemies[i].setdirection(1);
    
    else if((x==18 && y== 15) || (x==14 && y==17) || (x==10 && y==19) || (x==6 && y==mapHeight-4) || (x==2 && y==mapHeight-2))  enemies[i].setdirection(2);
    
    else if((x==2 && y== 1) || (x==6 && y==3) || (x==10 && y==5) || (x==14 && y==7) || (x==18 && y==9))                         enemies[i].setdirection(3);
    
    else if((x==mapWidth-3 && y== 1) || (x==mapWidth-7 && y==3) || (x==mapWidth-11 && y==5) 
    || (x==mapWidth-15 && y==7) || (x==mapWidth-19 && y==9))                                                                    enemies[i].setdirection(4);
    
    wattron(window,COLOR_PAIR(color));
    switch(enemies[i].getdirection()){
        case 1:
        enemies[i].setx(enemies[i].getcorx()-2);//?for changing position
        mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx(),enemies[i].getform());//?getting position
        checkEnemyCollisionx(window, enemies, i,2 ,enemies[i].getcory(),enemies[i].getcorx());
        break;
        
        case 2:
        enemies[i].sety(enemies[i].getcory()-1);//?for changing position
        mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx(),enemies[i].getform());//?getting position
        checkEnemyCollisiony(window, enemies, i,enemies[i].getcorx() ,1,enemies[i].getcory());
        break;


        case 3:
        enemies[i].setx(enemies[i].getcorx()+2);//?for changing position
        mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx(),enemies[i].getform());//?getting position
        checkEnemyCollisionx(window, enemies, i,-2,enemies[i].getcory(),enemies[i].getcorx());
        break;

        case 4:
        enemies[i].sety(enemies[i].getcory()+1);//?for changing position
        mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx(),enemies[i].getform());//?getting position
        checkEnemyCollisiony(window, enemies, i,enemies[i].getcorx() ,-1,enemies[i].getcory());
        break;
    }
    wattroff(window,COLOR_PAIR(color));
    
    
}
void printenemy(WINDOW* window ,vector<Enemy>& enemies){
    //!1 enemy 
    enemyfunction(window,enemies,0,3);
    //!2 enemy 
    enemyfunction(window,enemies,1,4);
    //!3 enemy 
    enemyfunction(window,enemies,2,5);
    //!4 enemy 
    enemyfunction(window,enemies,3,6);
    //!5 enemy 
    enemyfunction(window,enemies,4,3);
}
bool checkContact(Player player, vector<Enemy>& enemies, int i) {
    if (player.xcordinate == enemies[i].getcorx() && player.ycordinate == enemies[i].getcory()) 
    {   
        life--;
        return true;
    }
    else if (player.xcordinate  == enemies[i].getcorx() && player.ycordinate -1 == enemies[i].getcory()) 
    {   
        life--;
        return true;
    }
    else if (player.xcordinate == enemies[i].getcorx() && player.ycordinate +1 == enemies[i].getcory()) 
    {   
        life--;
        return true;
    }
    else if (player.xcordinate+2 == enemies[i].getcorx() && player.ycordinate == enemies[i].getcory()) 
    {   
        life--;
        return true;
    }
    else if (player.xcordinate-2 == enemies[i].getcorx() && player.ycordinate == enemies[i].getcory()) 
    {   
        life--;
        return true;
    }
    
    return false;
}
void INFO(WINDOW* window){
    initialize_colors();
    WINDOW *win = newwin(mapHeight/2, mapWidth/2+10, 0, 0);
    
    int max_x = getmaxx(win);
    int max_y = getmaxy(win);

    int x = (getmaxx(window) - max_x) / 2;
    int y = (getmaxy(window) - max_y) / 2;
    mvwin(win, y, x);
    
    wattron(win , COLOR_PAIR(8));
    mvwprintw(win,max_y/2-2,max_x/2-10,"GET 10 points to win");    
    wattroff(win , COLOR_PAIR(8));
    
    wattron(win , COLOR_PAIR(9));
    mvwprintw(win,max_y/2-1,max_x/2-12,"press 'z' to use ability" );   
    wattroff(win , COLOR_PAIR(9)); 
    
    wattron(win , COLOR_PAIR(7));
    mvwprintw(win,max_y/2,max_x/2-11,"press 'q' to use EXIT" );    
    wattroff(win , COLOR_PAIR(7));
    
    
    wrefresh(win);
    napms(5000); // wait for 5 seconds
    
    werase(win);
    wrefresh(win);
    
    delwin(win);
}
int main (){
    
    
    vector<Enemy> enemies;
    int numEnemies = 5; // or whatever number you want
    for(int i = 0; i < numEnemies; i++)
    {
        //!import from emeny.h file
        Enemy enemy;
        enemy.setform('#');
        enemies.push_back(enemy); // add enemy to vector
    }

    //!starting position of enemies
    //?    1
    enemies[0].setx(mapWidth-3); enemies[0].sety(mapHeight-2); enemies[0].setdirection(1);
    //?    2
    enemies[1].setx(mapWidth-5); enemies[1].sety(mapHeight-4); enemies[1].setdirection(1);
     //?    3
    enemies[2].setx(mapWidth-5); enemies[2].sety(mapHeight-6); enemies[2].setdirection(1);
     //?    4
    enemies[3].setx(mapWidth-5); enemies[3].sety(mapHeight-8); enemies[3].setdirection(1);
     //?    5
    enemies[4].setx(mapWidth-5); enemies[4].sety(mapHeight-10); enemies[4].setdirection(1);
    
    
    
    
    

    //?================================================================
    //!get name of player and select character
    system("clear");
    string PlayerName;
    char PlayerCharacter;
    cout<<"Enter player name: ";
    cin >> PlayerName;
    cout<<"Enter player character: ";
    cin >> PlayerCharacter;



    //!getting information about player
    Player player = Player();
    player.name = PlayerName;
    player.character = PlayerCharacter;
    
    
    


    //?================================================================



    
    //!initialize 
    initscr();
    attron(A_BOLD);//?for larger text


    keypad(stdscr,TRUE);
    noecho();
    WINDOW *window =newwin(mapHeight,mapWidth,0,0);
    nodelay(window,true);
    INFO(window);
    
    
    while (running){
        
        initialize_colors();
        //!print window and refresh
        
        wtimeout(stdscr,150);
        int ch=getch();
        if(spawn==true)
        {
            wattrset(window, A_NORMAL);
            spawnpoints(window);
            spawn=false;
        }
        WinGame winGame(window, mapWidth, mapHeight);
        MapPrinter::printMap(window);
        printenemy(window,enemies);



        if(ch!=ERR)
        switch (ch)
        {
            case KEY_UP:
                
                
                if((mvwinch(window,player.ycordinate-1,player.xcordinate))==' ' 
                || (mvwinch(window,player.ycordinate-1,player.xcordinate))=='*'
                ){                  
                    if((mvwinch(window,player.ycordinate-1,player.xcordinate))=='*')
                    {//?check if player is on * if true then +1 point
                        player.playerscore += 1;
                        wattrset(window, A_NORMAL);
                        mvwaddch(window,player.ycordinate-1,player.xcordinate,' ');
                        spawn=true;
                        //? check if player score is 10 if  true then end the game
                        if(player.playerscore==MAXPOINT) 
                        {
                            napms(400);
                            //!game win
                            winGame.show();
                            napms(600);
                            system("clear");
                            delwin(window);
                            running = false;
                        }
                    }
                    if(spawn) spawnpoints(window);
                    player.ycordinate -= 1; 
                    
                }               
            break;

            case KEY_DOWN:
                
                if((mvwinch(window,player.ycordinate+1,player.xcordinate)==' ' 
                || (mvwinch(window,player.ycordinate+1,player.xcordinate))=='*')
                ){  
                    if((mvwinch(window,player.ycordinate+1,player.xcordinate))=='*')
                    {   //?check if player is on * if true then +1 point 
                        player.playerscore += 1;
                        wattrset(window, A_NORMAL);
                        mvwaddch(window,player.ycordinate+1,player.xcordinate,' ');
                        spawn=true;
                        //? check if player score is 10 if  true then end the game
                        if(player.playerscore==MAXPOINT) 
                        {
                            napms(400);
                            //!game win
                            winGame.show();
                            napms(600);
                            system("clear");
                            delwin(window);
                            running = false;
                        }
                    }
                    if(spawn) spawnpoints(window);
                    player.ycordinate += 1; 
                }
            break;

            case KEY_RIGHT:
                
                if((mvwinch(window,player.ycordinate,player.xcordinate+2)==' ' 
                || (mvwinch(window,player.ycordinate,player.xcordinate+2))=='*')
                ){    
                    if((mvwinch(window,player.ycordinate,player.xcordinate+2))=='*')
                    {   //?check if player is on * if true then +1 point 
                        player.playerscore += 1;
                        wattrset(window, A_NORMAL);
                        mvwaddch(window,player.ycordinate,player.xcordinate+2,' ');
                        spawn=true;
                        //? check if player score is 10 if  true then end the game
                        if(player.playerscore==MAXPOINT) 
                        {
                            napms(400);
                            //!game win
                            winGame.show();
                            napms(600);
                            system("clear");
                            delwin(window);
                            running = false;
                        }
                    }
                    if(spawn) spawnpoints(window);
                    player.xcordinate+=2;
                }
            break;

            case KEY_LEFT:
                
                if((mvwinch(window,player.ycordinate,player.xcordinate-2)==' ' 
                || (mvwinch(window,player.ycordinate,player.xcordinate-2))=='*')
                ){    
                    if((mvwinch(window,player.ycordinate,player.xcordinate-2))=='*')
                    {   //?check if player is on * if true then +1 point 
                        player.playerscore += 1;
                        wattrset(window, A_NORMAL);
                        mvwaddch(window,player.ycordinate,player.xcordinate-2,' ');
                        spawn=true;
                        //? check if player score is 10 if  true then end the game
                        if(player.playerscore==MAXPOINT) 
                        {
                            napms(400);
                            //!game win
                            winGame.show();
                            napms(600);
                            system("clear");
                            delwin(window);
                            running = false;
                        }
                    }
                    if(spawn) spawnpoints(window);
                    player.xcordinate-=2;
                }
            break;
            
            
        }
        //? if pressed f1 turn of the game
        if(ch=='q') running =false;
        //!first ability
        if(ch=='z' && player.ability!=0) {
            player.xcordinate = 2;
            player.ycordinate = 1;
            player.ability -=1;
        }
        //? if player = enemie turn of the game
        for(int k=0;k<numEnemies;k++){
            if(checkContact(player,enemies,k)){
                player.respawn();
            
                if(life <= 0) {
                    
                    //?delay game tuning off 
                    napms(400);
                    //!game lost 
                    GameOverScreen gameOverScreen(window, mapWidth, mapHeight);
                    gameOverScreen.show();
                    napms(600);
                    system("clear");
                    delwin(window);
                }
            }
        }
        //!define colors
        
        //!print character and change color
        start_color();
        attron(COLOR_PAIR(1));
            mvaddch(player.ycordinate,player.xcordinate,player.character);
        attroff(COLOR_PAIR(1));        
        
        
        
        
        //?add score and player name        
        attron(COLOR_PAIR(8));
        mvprintw(mapHeight,0,"%s's SCORE: %d",player.name.c_str(),player.playerscore);
        attroff(COLOR_PAIR(8));
        
        attron(COLOR_PAIR(7));
        mvprintw(mapHeight,mapWidth-7,"life: %d",life);
        attroff(COLOR_PAIR(7));

        attron(COLOR_PAIR(9));
        mvprintw(mapHeight,mapWidth/2,"ability: %d",player.ability);
        attroff(COLOR_PAIR(9));
        
        
        attroff(A_BOLD);
        wrefresh(window);
    }
    
    
    endwin();
    

    return 0;
}