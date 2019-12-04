#include <ncurses.h>
#include <string.h>

int main() {
    int screenY = 0;
    int screenX = 0;

    int currScreenY = 0;
    int currScreenX = 0;

    char movementInstruction[] = "The + symbols indicates the selected cell. Use arrow keys to navigate.";
    char turnInstruction[] = "Press enter (return) to make a turn.";
    char exitInstruction[] = "Press ~ to exit.";

    int selectorY = 1;
    int selectorX = 1;

    bool windowActive = TRUE;
    int windowState = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while(windowActive) {
        getmaxyx(stdscr, screenY, screenX);
        int keyInput = getch();

        if(screenX < strlen(movementInstruction) && screenY < 9) {
            if(windowState != 1 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 1;
                clear();
            }
            currScreenY = screenY;
            currScreenX = screenX;

            mvprintw(screenY/2, (screenX - strlen("Expand window height and width."))/2, "Expand window height and width.");

        } else if(screenX < strlen(movementInstruction)) {
            if(windowState != 2 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 2;
                clear();
            }
            currScreenY = screenY;
            currScreenX = screenX;

            mvprintw(screenY/2, (screenX - strlen("Expand window width."))/2, "Expand window width.");

        } else if(screenY < 9) {
            if(windowState != 3 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 3;
                clear();
            }
            currScreenY = screenY;
            currScreenX = screenX;

            mvprintw(screenY/2, (screenX - strlen("Expand window height."))/2, "Expand window height.");

        } else {
            if(windowState != 4 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 4;
                clear();
            }
            currScreenY = screenY;
            currScreenX = screenX;

            mvprintw(0, 0, "%s", movementInstruction);
            mvprintw(1, 0, "%s", turnInstruction);
            mvprintw(2, 0, "%s", exitInstruction);

            for(int x = 0; x < screenX; x++) {
                mvprintw(3, x, "-");
            }

        }

        if(keyInput == '`' || keyInput == '~') {
            windowActive = FALSE;
        }
    }

    endwin();
    return 0;
}
