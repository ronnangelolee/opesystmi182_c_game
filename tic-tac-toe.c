#include <ncurses.h>
#include <string.h>

int main() {
    int screenY = 0;
    int screenX = 0;

    char movementInstruction[] = "The + symbols indicates the selected cell. Use arrow keys to navigate.";
    char turnInstruction[] = "Press enter (return) to make a turn.";
    char exitInstruction[] = "Press ~ to exit.";

    int selectorY = 1;
    int selectorX = 1;

    bool windowActive = TRUE;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    while(windowActive) {
        getmaxyx(stdscr, screenY, screenX);
        int keyInput = getch();

        clear();

        if(screenX < strlen(movementInstruction) && screenY < 9) {
            mvprintw(screenY/2, (screenX - strlen("Expand window height and width."))/2, "Expand window height and width.");
        } else if(screenX < strlen(movementInstruction)) {
            mvprintw(screenY/2, (screenX - strlen("Expand window width."))/2, "Expand window width.");
        } else if(screenY < 9) {
            mvprintw(screenY/2, (screenX - strlen("Expand window height."))/2, "Expand window height.");
        } else {
            mvprintw(0, 0, "%s", movementInstruction);
            mvprintw(1, 0, "%s", turnInstruction);
            mvprintw(2, 0, "%s", exitInstruction);

            for(int x = 0; x < screenX - 1; x++) {
                mvprintw(3, x, "-");
            }
        }

        refresh();

        if(keyInput == '`' || keyInput == '~') {
            windowActive = FALSE;
        }
    }

    endwin();
    return 0;
}
