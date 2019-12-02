#include <ncurses.h>

int main() {
    int screenY = 0;
    int screenX = 0;

    int dotPosY = 0;
    int dotPosX = 0;

    bool windowActive = TRUE;

    initscr();
    cbreak(); // each key the user hits is returned immediately
    noecho(); // character will not be printed on the screen
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // getch() works in a non-blocking manner

    getmaxyx(stdscr, screenY, screenX);

    char screenString[50];
    sprintf(screenString, "%c", (char)82);

    while (windowActive) {
        clear();
        mvprintw(dotPosY, dotPosX, screenString);
        refresh();

        int keyInput = getch();

        if(keyInput == KEY_DOWN && dotPosY < screenY - 1) {
            dotPosY = dotPosY + 1;
        }

        if(keyInput == KEY_UP && dotPosY > 0) {
            dotPosY = dotPosY - 1;
        }

        if(keyInput == KEY_RIGHT && dotPosX < screenX - 1) {
            dotPosX = dotPosX + 1;
        }

        if(keyInput == KEY_LEFT && dotPosX > 0) {
            dotPosX = dotPosX - 1;
        }

        // exits program
        if(keyInput == 96) {
            windowActive = FALSE;
            endwin();
        }
    }

    endwin();

    return 0;
}
