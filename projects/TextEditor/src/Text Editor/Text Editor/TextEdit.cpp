#define PDC_DLL_BUILD 1
#define menu_color 1
#define window_color 2

#include <curses.h>
//#include <curspriv.h>
#include <panel.h>
#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    //initialize our screen
    initscr();
    //turn off keyboard echo
    noecho();
    cbreak();
    
    start_color();

    int max_x = 0;
    int max_y = 0;
    int input_y = 3;
    int input_x = 0;
    WINDOW* menu_window = newwin(3, max_x, 0, 0);
    WINDOW* input_window = newwin(max_y, max_x, input_y, input_x);
    wmove(input_window, input_y, input_x);
    //resize our window
    getmaxyx(stdscr, max_y, max_x);
    //window border. Integer values relate to the character used for the border lengthwise and widthwise (lines for integer 0)
    box(input_window, 0, 0);
    box(menu_window, 0, 0);

    //turn on keypad input
    keypad(stdscr, TRUE);

    //hide the cursor
    curs_set(TRUE);

    //MAIN PROGRAM LOGIC GOES HERE
    //add character to the screen
    
    init_pair(menu_color, COLOR_BLACK, COLOR_WHITE);
    
    wbkgd(menu_window, menu_color);
    
    //outputs the word File to screen
    mvwprintw(menu_window, 1, 1, "File");
    
    //outputs the word Edit to screen
    mvwprintw(menu_window, 1, 9, "Edit");
    
    //outputs the word Search to screen
    mvwprintw(menu_window, 1, 18, "Search");
    
    //outputs the word View to screen
    mvwprintw(menu_window, 1, 29, "View");
    
    //outputs the word Options to screen
    mvwprintw(menu_window, 1, 38, "Options");
    
    //outputs the word Help to screen
    mvwprintw(menu_window, 1, 50, "Help");
    
    
    //refresh tells curses to draw everything
    refresh();
    wrefresh(input_window);
    wrefresh(menu_window);

    //END OF PROGRAM LOGIC GOES HERE
    //Pause for user input
    int input;
    while((input = getch()) != 'q')
    {
        switch (input)
        {
            case (KEY_LEFT):
                input_x--;
                break;
            case (KEY_RIGHT):
                input_x++;
                break;
            case (KEY_UP):
                input_y--;
                break;
            case (KEY_DOWN):
                input_y++;
                break;
            default:
                input_x++;
                waddch(input_window, input);
                break;
        }
        
        wmove(input_window, input_y, input_x);
        refresh();
        wrefresh(input_window);
    }
    
    //end curses mode
    endwin();
    
    return 0;

}
