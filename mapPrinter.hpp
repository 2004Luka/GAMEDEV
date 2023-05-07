#pragma once
#include <iostream>
#include <ncurses.h>

using namespace std;
#define mapWidth 49
#define mapHeight 25
class Walls{
    public:
    char side;
    char top;
};
class MapPrinter {
public:
    static void printMap(WINDOW* window) {
        Walls walls;
        walls.side = '|';
        walls.top = '=';

        for (int i = 0; i <= mapWidth; i++) {
            for (int j = 0; j <= mapHeight; j++) {
                init_pair(2, COLOR_BLUE, COLOR_BLACK);
                if (mvwinch(window, j, i) == ' ' || mvwinch(window, i, j) == '*') {
                    wattroff(window, COLOR_PAIR(2));
                } else {
                    start_color();
                    wattron(window, COLOR_PAIR(2));
                }

                //! immer section 1
                box(window, walls.side, walls.top);

                //! immer section 2
                if ((i == 4 || i == mapWidth - 5) && j >= 2 && j <= mapHeight - 3)
                    mvwprintw(window, j, i, "%c", walls.side);

                if ((j == 2 || j == mapHeight - 3) && i >= 4 && i <= mapWidth - 5)
                    mvwprintw(window, j, i, "%c", walls.top);

                //! immer section 3
                if ((i == 8 || i == mapWidth - 9) && j >= 4 && j <= mapHeight - 5)
                    mvwprintw(window, j, i, "%c", walls.side);

                if ((j == 4 || j == mapHeight - 5) && i >= 8 && i <= mapWidth - 9)
                    mvwprintw(window, j, i, "%c", walls.top);

                //! immer section 4
                if ((i == 12 || i == mapWidth - 13) && j >= 6 && j <= mapHeight - 7)
                    mvwprintw(window, j, i, "%c", walls.side);

                if ((j == 6 || j == mapHeight - 7) && i >= 12 && i <= mapWidth - 13)
                    mvwprintw(window, j, i, "%c", walls.top);

                //! immer section 5
                if ((i == 16 || i == mapWidth - 17) && j >= 8 && j <= mapHeight - 9)
                    mvwprintw(window, j, i, "%c", walls.side);

                if ((j == 8 || j == mapHeight - 9) && i >= 16 && i <= mapWidth - 17)
                    mvwprintw(window, j, i, "%c", walls.top);

                //! immer section 6
                if ((i == 20 || i == mapWidth - 21) && j >= 10 && j <= mapHeight - 11)
                    mvwprintw(window, j, i, "%c", walls.side);
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
};