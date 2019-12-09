#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int screenY = 0;
    int screenX = 0;

    int currScreenY = 0;
    int currScreenX = 0;

    char movementInstruction[] = "The + symbols indicates the selected cell. Use arrow keys to navigate.";
    char turnInstruction[] = "Press enter (return) to make a turn.";
    char exitInstruction[] = "Press ~ to exit.";
    int ribbonHeight = 4;

    int playerTurn = 1;
    int playerTurns = 0;

    int test = 0;

    int selectorY = 1;
    int selectorX = 1;

    int player[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int computer[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    int tableHeight = 7;
    int tableWidth = 13;

    bool windowActive = TRUE;
    int windowState = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    while(windowActive) {
        getmaxyx(stdscr, screenY, screenX);
        int keyInput = getch();

        if(screenX < strlen(movementInstruction) && screenY < ribbonHeight + tableHeight) {
            if(windowState != 1 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 1;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(screenY/2, (screenX - strlen("Expand window height and width."))/2, "Expand window height and width.");
            }
        } else if(screenX < strlen(movementInstruction)) {
            if(windowState != 2 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 2;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(screenY/2, (screenX - strlen("Expand window width."))/2, "Expand window width.");
            }
        } else if(screenY < ribbonHeight + tableHeight) {
            if(windowState != 3 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 3;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(screenY/2, (screenX - strlen("Expand window height."))/2, "Expand window height.");
            }
        } else {
            if(windowState != 4 || screenY != currScreenY || screenX != currScreenX) {
                windowState = 4;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(0, 0, "%s", movementInstruction);
                mvprintw(1, 0, "%s", turnInstruction);
                mvprintw(2, 0, "%s", exitInstruction);

                for(int x = 0; x < screenX - 1; x++) {
                    mvprintw(ribbonHeight - 1, x, "-");
                }
            }

            int gridTopRow = ((screenY - ribbonHeight) - tableHeight)/2 + ribbonHeight;
            int gridLeastColumn = (screenX - tableWidth)/2;
            for(int y = 0; y < tableHeight; y++) {
                for(int x = 0; x < tableWidth; x++) {
                    if((y + 1) % 2 != 0) {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, "-");
                    } else if(x % ((tableWidth-1) / 3) == 0) {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, "|");
                    } else if(y == (selectorY * ((tableHeight - 1) / 3) - ((tableHeight - 1) / 6)) && x == (selectorX * ((tableWidth - 1) / 3) - ((tableWidth - 1) / 6)) - 1) {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, "|");
                    } else if(y == (selectorY * ((tableHeight - 1) / 3) - ((tableHeight - 1) / 6)) && x == (selectorX * ((tableWidth - 1) / 3) - ((tableWidth - 1) / 6)) + 1) {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, "|");
                    } else {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, " ");
                    }
                }
            }

            for(int y = 0; y < 3; y++) {
                for(int x = 0; x < 3; x++) {
                    if(player[y][x] == 1) {
                        mvprintw(gridTopRow + (y + 1) * ((tableHeight - 1) / 3) - ((tableHeight - 1) / 6), gridLeastColumn + (x + 1) * ((tableWidth - 1) / 3) - ((tableWidth - 1) / 6), "X");
                    } else if(computer[y][x] == 1) {
                        mvprintw(gridTopRow + (y + 1) * ((tableHeight - 1) / 3) - ((tableHeight - 1) / 6), gridLeastColumn + (x + 1) * ((tableWidth - 1) / 3) - ((tableWidth - 1) / 6), "O");
                    }
                }
            }
        }

        if(keyInput == KEY_DOWN && selectorY < 3) {
            selectorY = selectorY + 1;
        }

        if(keyInput == KEY_UP && selectorY > 1) {
            selectorY = selectorY - 1;
        }

        if(keyInput == KEY_RIGHT && selectorX < 3) {
            selectorX = selectorX + 1;
        }

        if(keyInput == KEY_LEFT && selectorX > 1) {
            selectorX = selectorX - 1;
        }

        if(keyInput == ((char)10) && player[selectorY - 1][selectorX - 1] == 0 && playerTurn == 1) {
            player[selectorY - 1][selectorX - 1] = 1;
            playerTurn = 0;
            playerTurns = playerTurns + 1;
        }

        if(keyInput == '`' || keyInput == '~') {
            windowActive = FALSE;
        }

        if(playerTurn == 0 && playerTurns < 5) {
            int randomY = rand() % 3;
            int randomX = rand() % 3;

            while(player[randomY][randomX] == 1 || computer[randomY][randomX] == 1) {
                randomY = rand() % 3;
                randomX = rand() % 3;
            }

            computer[randomY][randomX] = 1;

            playerTurn = 1;
        }
    }

    endwin();
    return 0;
}

