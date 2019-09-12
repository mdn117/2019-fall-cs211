#define PDC_DLL_BUILD 1
#define menu_color 1
#define input_window_color 2
#define info_window_color 3

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
    //turn off keyboard echo, better to keep it off when user input is implemented
    noecho();
    //turn on character break, which helps with reading input one character at a time
    cbreak();
    //initializes color to be implemented
    start_color();
    
    //input_x and input_y are used to determine cursor placement
    int input_y = 1;
    int input_x = 1;
    
    //each of the following functions create windows, the integers are, from left to right,
    //number of rows, number of columns, starting y position, starting x position
    WINDOW* file_window = newwin(3, 8, 0, 0);
    WINDOW* edit_window = newwin(3, 8, 0, 9);
    WINDOW* search_window = newwin(3, 10, 0, 18);
    WINDOW* view_window = newwin(3, 8, 0, 29);
    WINDOW* options_window = newwin(3, 10, 0, 38);
    WINDOW* help_window = newwin(3, 8, 0, 49);
    WINDOW* info_window = newwin(3, 0, 0, 58);
    WINDOW* input_window = newwin(0, 0, 4, 0);
    
    wmove(input_window, input_y, input_x);
    refresh();
    wrefresh(input_window);
    
    //initializes base colors to create a new color, in this case, gray.
    init_pair(menu_color, COLOR_BLACK, COLOR_WHITE);
    init_pair(input_window_color, COLOR_BLUE, COLOR_WHITE);
    init_pair(info_window_color, COLOR_GREEN, COLOR_BLACK);
    
    //the following block colors the background of the specified window with the color pair
    //specified in the previous function (init_pair).
    wbkgd(input_window, COLOR_PAIR(input_window_color));
    wbkgd(file_window, COLOR_PAIR(menu_color));
    wbkgd(edit_window, COLOR_PAIR(menu_color));
    wbkgd(search_window, COLOR_PAIR(menu_color));
    wbkgd(view_window, COLOR_PAIR(menu_color));
    wbkgd(options_window, COLOR_PAIR(menu_color));
    wbkgd(help_window, COLOR_PAIR(menu_color));
    wbkgd(info_window, COLOR_PAIR(info_window_color));
    
    //window border. Integer values relate to the character used for the border lengthwise and widthwise (lines for integer 0)
    
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
    
    //outputs the word File to the file window
    mvwprintw(file_window, 1, 2, "File");
    
    //outputs the word Edit to the edit window
    mvwprintw(edit_window, 1, 2, "Edit");
    
    //outputs the word Search to the search window
    mvwprintw(search_window, 1, 2, "Search");
    
    //outputs the word View to the view window
    mvwprintw(view_window, 1, 2, "View");
    
    //outputs the word Options to the options window
    mvwprintw(options_window, 1, 2, "Options");
    
    //outputs the word Help to the help window
    mvwprintw(help_window, 1, 2, "Help");
    
    //outputs the phrase Q to QUIT to the info window
    mvwprintw(info_window, 1, 6, "Q to QUIT");
    
    
    //refresh tells curses to draw everything, also have to refresh each individual
    //window in order to have the colors, text, and boxes show up in each window.
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
    
    while((input = wgetch(input_window)) != 'Q') //input helps with the switch statements to pause for user input, capital q is used
                                                 //as a sentinel in order to break out of the while loop
    {
        switch (input)
        {
                //each key case will change the x or y value of the cursor, then use the move function to move the cursoor inside the window
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
            case (127): //127 is the numeric value for backspace in ncurses
                if (input_x == 1)
                {
                    input_y--;
                    input_x = max_input_x - 2;
                }
                else
                {
                    input_x--;
                }
                wmove(input_window, input_y, input_x);
                wdelch(input_window);
                break;
                //default case is pressing a key that has no special function other than outputting that character to the screen
            default:
                if (input_x == max_input_x - 2)
                {
                    input_x = 1;
                    input_y++;
                }
                else
                {
                    input_x++;
                }
                waddch(input_window, input); //since cbreak is on, addch is not called automatically from getch, so we have to do it each time
                wmove(input_window, input_y, input_x);
                break;
        }
        wrefresh(input_window);
    }
    
    //end curses mode
    endwin();
    
    return 0;

}
