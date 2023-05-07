//!information 
//?https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
#include <iostream>
#include <ncurses.h>
#include "enemy.h"
#include <vector>

using namespace std;

bool spawn = true;
bool running = true;
int life = 5;
//!inicialize colors 
#define mapWidth 49
#define mapHeight 25
#define MAXPOINT 10

class Walls{
    public:
    char side;
    char top;
};
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
void printMap(WINDOW* window){

    Walls walls=Walls();
    walls.side='|';
    walls.top='=';
    Player player = Player();


    for(int i=0;i<=mapWidth;i++){
        for(int j=0;j<=mapHeight;j++){
            
            init_pair(2, COLOR_BLUE, COLOR_BLACK);
            if(mvwinch(window,j,i) == ' ' || mvwinch(window,i,j)=='*'){
                wattroff(window, COLOR_PAIR(2));
                
            }
            else{
                start_color();
                wattron(window, COLOR_PAIR(2));
            }
            


            //!immer section 1
            
            box(window,walls.side,walls.top);

            //!immer section 2 

            if((i==4 || i==mapWidth-5)&& j>=2 && j<=mapHeight-3)
            mvwprintw(window,j,i,"%c",walls.side);
        
            if((j==2 || j==mapHeight-3) && i>=4 && i<=mapWidth-5)
            mvwprintw(window,j,i,"%c",walls.top);

             //!immer section 3

            if((i==8 || i==mapWidth-9)&& j>=4 && j<=mapHeight-5)
            mvwprintw(window,j,i,"%c",walls.side);
        
            if((j==4 || j==mapHeight-5) && i>=8 && i<=mapWidth-9)
            mvwprintw(window,j,i,"%c",walls.top);



            //!immer section 4

            if((i==12 || i==mapWidth-13)&& j>=6 && j<=mapHeight-7)
            mvwprintw(window,j,i,"%c",walls.side);
        
            if((j==6 || j==mapHeight-7) && i>=12 && i<=mapWidth-13)
            mvwprintw(window,j,i,"%c",walls.top);


            //!immer section 5

            if((i==16 || i==mapWidth-17)&& j>=8 && j<=mapHeight-9)
            mvwprintw(window,j,i,"%c",walls.side);
        
            if((j==8 || j==mapHeight-9) && i>=16 && i<=mapWidth-17)
            mvwprintw(window,j,i,"%c",walls.top);

            //!immer section 6

            if((i==20 || i==mapWidth-21 )&& j>=10 && j<=mapHeight-11)
            mvwprintw(window,j,i,"%c",walls.side);
        



            //!dors on vertical lines 
            if( //! section 1
                (i==4 && j==7)||
                (i==4 && j==mapHeight-8)||
                (i==mapWidth-5 && j==7)||
                (i==mapWidth-5 && j==mapHeight-8)||

                //!section 2
                (i==8 && j==mapHeight/2)||
                (i==mapWidth-9 && j==mapHeight/2)||

                //!section 3 
                (i==12 && j==9)||
                (i==12 && j==mapHeight-10)||
                (i==mapWidth-13 && j==9)||
                (i==mapWidth-13 && j==mapHeight-10)||

                //!section 4
                (i==16 && j==mapHeight/2)||
                (i==mapWidth-17 && j==mapHeight/2)
            )
            mvwprintw(window,j,i," ");
            
            
            //!dors on horizontal lines 
            if( //! section 1
                ((i==mapWidth/2-1 || i==mapWidth/2-2|| i==mapWidth/2-3) && j==2)||
                ((i==mapWidth/2-1 || i==mapWidth/2-2|| i==mapWidth/2-3) && j==mapHeight-3)||
                
                //!section 2
                ((i==mapWidth/2-11 || i==mapWidth/2-12 || i==mapWidth/2-13) && j==4)||
                ((i==mapWidth/2+7 || i==mapWidth/2+8 || i==mapWidth/2+9) && j==4)||
                ((i==mapWidth/2-11 || i==mapWidth/2-12 || i==mapWidth/2-13) && j==mapHeight-5)||
                ((i==mapWidth/2+7 || i==mapWidth/2+8 || i==mapWidth/2+9) && j==mapHeight-5)||

                //!section 3
                ((i==mapWidth/2 || i==mapWidth/2-1|| i==mapWidth/2-2) && j==6)||
                ((i==mapWidth/2 || i==mapWidth/2-1|| i==mapWidth/2-2) && j==mapHeight-7)
                
            )
            mvwprintw(window,j,i," ");
        
        }

        
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
        if(mvwinch(window,enemies[i].getcory(),enemies[i].getcorx()-2)=='*'){
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx()+2,' ');
            mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx()+2,'*');
        }
        else {
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx()+2,' ');
        }
        break;
        
        case 2:
        enemies[i].sety(enemies[i].getcory()-1);//?for changing position
        mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx(),enemies[i].getform());//?getting position
        if(mvwinch(window,enemies[i].getcory()-1,enemies[i].getcorx())=='*'){
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory()+1,enemies[i].getcorx(),'*');
        }
        else {
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory()+1,enemies[i].getcorx(),' ');
        }
        break;


        case 3:
        enemies[i].setx(enemies[i].getcorx()+2);//?for changing position
        mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx(),enemies[i].getform());//?getting position
        if(mvwinch(window,enemies[i].getcory(),enemies[i].getcorx()+2)=='*'){
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx()-2,' ');
            mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx()-2,'*');
        }
        else {
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx()-2,' ');
        }
        break;

        case 4:
        enemies[i].sety(enemies[i].getcory()+1);//?for changing position
        mvwaddch(window,enemies[i].getcory(),enemies[i].getcorx(),enemies[i].getform());//?getting position
        if(mvwinch(window,enemies[i].getcory()+1,enemies[i].getcorx())=='*'){
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory()-1,enemies[i].getcorx(),' ');
            mvwaddch(window,enemies[i].getcory()-1,enemies[i].getcorx(),'*');
        }
        else {
            wattrset(window, A_NORMAL);
            mvwaddch(window,enemies[i].getcory()-1,enemies[i].getcorx(),' ');
        }
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
void LOOSEGAME(WINDOW* window){
    initialize_colors();
    delwin(window);
    WINDOW *win = newwin(mapHeight/2, mapWidth/2+10, 0, 0);
    
    int max_x = getmaxx(win);
    int max_y = getmaxy(win);

    int x = (getmaxx(window) - max_x) / 2;
    int y = (getmaxy(window) - max_y) / 2;
    mvwin(win, y, x);
    
    wattron(win , COLOR_PAIR(7));
    mvwprintw(win,max_y/2,max_x/2-5,"game over");    
    wattroff(win , COLOR_PAIR(7));
    
    box(win, 0, 0);
    wrefresh(win);
    window = win;
}
void WINGAME(WINDOW* window){
    initialize_colors();
    delwin(window);
    WINDOW *win = newwin(mapHeight/2, mapWidth/2+10, 0, 0);
    
    int max_x = getmaxx(win);
    int max_y = getmaxy(win);

    int x = (getmaxx(window) - max_x) / 2;
    int y = (getmaxy(window) - max_y) / 2;
    mvwin(win, y, x);
    
    wattron(win , COLOR_PAIR(8));
    mvwprintw(win,max_y/2,max_x/2-5,"YOU WIN!!");    
    wattroff(win , COLOR_PAIR(8));
    
    box(win, 0, 0);
    wrefresh(win);
    window = win;
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
    mvwprintw(win,max_y/2,max_x/2-11,"press 'F1' to use EXIT" );    
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
        
        printMap(window);
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
                            WINGAME(window);
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
                            WINGAME(window);
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
                            WINGAME(window);
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
                            WINGAME(window);
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
        if(ch==KEY_F(1)) running =false;
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
            }
            if(checkContact(player,enemies,k) && life == -1) {
                
                //?delay game tuning off 
                napms(400);
                //!game lost 
                LOOSEGAME(window);
                napms(600);
                system("clear");
                delwin(window);
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