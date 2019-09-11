#define PDC_DLL_BUILD 1
#define menu_color 1
#define input_window_color 2

#include <curses.h>
//#include <curspriv.h>
#include <panel.h>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main(void)
{
    //initialize our screen
    initscr();
    //turn off keyboard echo
    noecho();
    cbreak();
    
    start_color();
    
    int input_y = 1;
    int input_x = 1;
    
    WINDOW* file_window = newwin(3, 8, 0, 0);
    WINDOW* edit_window = newwin(3, 8, 0, 9);
    WINDOW* search_window = newwin(3, 10, 0, 18);
    WINDOW* view_window = newwin(3, 8, 0, 29);
    WINDOW* options_window = newwin(3, 10, 0, 38);
    WINDOW* help_window = newwin(3, 8, 0, 49);
    WINDOW* info_window = newwin(3, 22, 0, 58);
    WINDOW* input_window = newwin(20, 0, 4, 0);
    
    
    //window border. Integer values relate to the character used for the border lengthwise and widthwise (lines for integer 0)
    
    init_pair(menu_color, COLOR_BLACK, COLOR_WHITE);
    
    
    wbkgd(file_window, COLOR_PAIR(menu_color));
    wbkgd(edit_window, COLOR_PAIR(menu_color));
    wbkgd(search_window, COLOR_PAIR(menu_color));
    wbkgd(view_window, COLOR_PAIR(menu_color));
    wbkgd(options_window, COLOR_PAIR(menu_color));
    wbkgd(help_window, COLOR_PAIR(menu_color));
    
    box(input_window, 0, 0);
    box(edit_window, 0, 0);
    box(file_window, 0, 0);
    box(search_window, 0, 0);
    box(view_window, 0, 0);
    box(options_window, 0, 0);
    box(help_window, 0, 0);
    box(info_window, 0, 0);

    //turn on keypad input
    keypad(input_window, TRUE);

    //show the cursor
    curs_set(TRUE);

    //MAIN PROGRAM LOGIC GOES HERE
    //add character to the screen
    
    wmove(input_window, input_y, input_x);
    refresh();
    wrefresh(input_window);
    
    //outputs the word File to screen
    mvwprintw(file_window, 1, 2, "File");
    
    //outputs the word Edit to screen
    mvwprintw(edit_window, 1, 2, "Edit");
    
    //outputs the word Search to screen
    mvwprintw(search_window, 1, 2, "Search");
    
    //outputs the word View to screen
    mvwprintw(view_window, 1, 2, "View");
    
    //outputs the word Options to screen
    mvwprintw(options_window, 1, 2, "Options");
    
    //outputs the word Help to screen
    mvwprintw(help_window, 1, 2, "Help");
    
    mvwprintw(info_window, 1, 6, "Q to QUIT");
    
    
    //refresh tells curses to draw everything
    refresh();
    wrefresh(file_window);
    wrefresh(edit_window);
    wrefresh(search_window);
    wrefresh(view_window);
    wrefresh(options_window);
    wrefresh(help_window);
    wrefresh(info_window);

    //END OF PROGRAM LOGIC GOES HERE
    //Pause for user input
    int input;
    int max_input_x = getmaxx(input_window);
    const int max_right = 5;
    //27 is also the number assigned to the ESC character
    while((input = wgetch(input_window)) != 'Q')
    {
        switch (input)
        {
            case (KEY_LEFT):
                input_x--;
                wmove(input_window, input_y, input_x);
                break;
            case (KEY_RIGHT):
                input_x++;
                wmove(input_window, input_y, input_x);
                break;
            case (KEY_UP):
                input_y--;
                wmove(input_window, input_y, input_x);
                break;
            case (KEY_DOWN):
                input_y++;
                wmove(input_window, input_y, input_x);
                break;
            case (10): //10 is the numeric value for enter in ncurses
                input_x = 1;
                input_y++;
                wmove(input_window, input_y, input_x);
                break;
            case (max_right):
                if (input_x == max_input_x - 1)
                {
                    input_x = 1;
                    input_y++;
                    wmove(input_window, input_y, input_x);
                }
                break;
            default:
                input_x++;
                waddch(input_window, input);
                wmove(input_window, input_y, input_x);
                break;
        }
    
        wrefresh(input_window);
    }
    
    //end curses mode
    endwin();
    
    return 0;

}
