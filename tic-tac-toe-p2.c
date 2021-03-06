#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct{int y, x;} playerSelector;

playerSelector movePlayer1(int keyInput, playerSelector coordinate) {
    // movement
    if(keyInput == KEY_DOWN && coordinate.y < 3) {
        coordinate.y = coordinate.y + 1;
    }
    if(keyInput == KEY_UP && coordinate.y > 1) {
        coordinate.y = coordinate.y - 1;
    }
    if(keyInput == KEY_RIGHT && coordinate.x < 3) {
        coordinate.x = coordinate.x + 1;
    }
    if(keyInput == KEY_LEFT && coordinate.x > 1) {
        coordinate.x = coordinate.x - 1;
    }

    return coordinate;
}

int main() {
    int screenY = 0;
    int screenX = 0;

    int currScreenY = 0;
    int currScreenX = 0;

    char movementInstruction[] = "The | | symbols indicates the selected cell. Use arrow keys to navigate.";
    char turnInstruction[] = "Press enter (return) to make a turn.";
    char exitInstruction[] = "Press ~ to exit. Press r to restart.";
    int ribbonHeight = 4;

    int playerTurn = 1;
    int playerTurns = 0;

    playerSelector selector = {1, 1};

    int player[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int computer[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int randomY = rand() % 3;
    int randomX = rand() % 3;

    int playerWin = 0;
    int computerWin = 0;

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
            if(playerWin == 1 && windowState != 4) {
                windowState = 4;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(((screenY - ribbonHeight) - tableHeight)/2, (screenX - strlen("You win. Good job."))/2, "You win. Good job.");
                mvprintw(((screenY - ribbonHeight) - tableHeight)/2 + 1, (screenX - strlen("Press ~ to exit. Press r to restart."))/2, "Press ~ to exit. Press r to restart.");

            } else if(computerWin == 1 && windowState != 5) {
                windowState = 5;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(((screenY - ribbonHeight) - tableHeight)/2, (screenX - strlen("You lose. Try again."))/2, "You lose. Try again.");
                mvprintw(((screenY - ribbonHeight) - tableHeight)/2 + 1, (screenX - strlen("Press ~ to exit. Press r to play again."))/2, "Press ~ to exit. Press r to play again.");

            } else if(playerTurns >= 5 && windowState != 6 && playerWin != 1 && computerWin != 1) {
                windowState = 6;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(((screenY - ribbonHeight) - tableHeight)/2, (screenX - strlen("It's a draw. Try harder."))/2, "It's a draw. Try harder.");
                mvprintw(((screenY - ribbonHeight) - tableHeight)/2 + 1, (screenX - strlen("Press ~ to exit. Press r to play again."))/2, "Press ~ to exit. Press r to play again.");

            } else if((windowState != 7 || screenY != currScreenY || screenX != currScreenX) && playerWin != 1 && computerWin != 1 && playerTurns < 5) {
                windowState = 7;
                clear();

                currScreenY = screenY;
                currScreenX = screenX;

                mvprintw(((screenY - ribbonHeight) - tableHeight)/2, (screenX - strlen(movementInstruction))/2, "%s", movementInstruction);
                mvprintw(((screenY - ribbonHeight) - tableHeight)/2 + 1, (screenX - strlen(turnInstruction))/2, "%s", turnInstruction);
                mvprintw(((screenY - ribbonHeight) - tableHeight)/2 + 2, (screenX - strlen(exitInstruction))/2, "%s", exitInstruction);
            }

            int gridTopRow = ((screenY - ribbonHeight) - tableHeight)/2 + ribbonHeight;
            int gridLeastColumn = (screenX - tableWidth)/2;
            for(int y = 0; y < tableHeight; y++) {
                for(int x = 0; x < tableWidth; x++) {
                    if((y + 1) % 2 != 0) {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, "-");
                    } else if(x % ((tableWidth-1) / 3) == 0) {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, "|");
                    } else if(y == (selector.y * ((tableHeight - 1) / 3) - ((tableHeight - 1) / 6)) && x == (selector.x * ((tableWidth - 1) / 3) - ((tableWidth - 1) / 6)) - 1) {
                        mvprintw(gridTopRow + y, gridLeastColumn + x, "|");
                    } else if(y == (selector.y * ((tableHeight - 1) / 3) - ((tableHeight - 1) / 6)) && x == (selector.x * ((tableWidth - 1) / 3) - ((tableWidth - 1) / 6)) + 1) {
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

        // movement
        selector = movePlayer1(keyInput, selector);

        // restart game
        if(keyInput == 'r' || keyInput == 'R') {
            for(int y = 0; y < 3; y++) {
                for(int x = 0; x < 3; x++) {
                    player[y][x] = 0;
                    computer[y][x] = 0;
                }
            }

            playerTurn = 1;
            playerTurns = 0;
            playerWin = 0;
            computerWin = 0;
        }

        // player turn
        if(keyInput == ((char)10) && player[selector.y - 1][selector.x - 1] == 0 && playerTurn == 1 && computer[selector.y - 1][selector.x - 1] == 0 && playerWin != 1 && computerWin != 1) {
            player[selector.y - 1][selector.x - 1] = 1;
            playerTurn = 0;
            playerTurns = playerTurns + 1;
        }

        // exit game
        if(keyInput == '`' || keyInput == '~') {
            windowActive = FALSE;
        }

        // check if win
        if(playerWin != 1 || computerWin != 1) {
            for(int y = 0; y < 3; y++) {
                if((player[y][0] == 1 && player[y][1] == 1 && player[y][2] == 1) || (player[0][y] == 1 && player[1][y] == 1 && player[2][y] == 1)) {
                    playerWin = 1;
                } else if((computer[y][0] == 1 && computer[y][1] == 1 && computer[y][2] == 1) || (computer[0][y] == 1 && computer[1][y] == 1 && computer[2][y] == 1)) {
                    computerWin = 1;
                }
            }

            if((player[0][0] == 1 && player[1][1] == 1 && player[2][2] == 1) || (player[0][2] == 1 && player[1][1] == 1 && player[2][0] == 1)) {
                playerWin = 1;
            } else if((computer[0][0] == 1 && computer[1][1] == 1 && computer[2][2] == 1) || (computer[0][2] == 1 && computer[1][1] == 1 && computer[2][0] == 1)) {
                computerWin = 1;
            }
        }

        randomY = rand() % 3;
        randomX = rand() % 3;
        if(playerTurn == 0 && playerTurns < 5 && playerWin != 1 && computerWin != 1) {
            while(player[randomY][randomX] == 1 || computer[randomY][randomX] == 1) {
                randomY = rand() % 3;
                randomX = rand() % 3;
            }

            computer[randomY][randomX] = 1;

            playerTurn = 1;
        }

        // check if win
        if(playerWin != 1 || computerWin != 1) {
            for(int y = 0; y < 3; y++) {
                if((player[y][0] == 1 && player[y][1] == 1 && player[y][2] == 1) || (player[0][y] == 1 && player[1][y] == 1 && player[2][y] == 1)) {
                    playerWin = 1;
                } else if((computer[y][0] == 1 && computer[y][1] == 1 && computer[y][2] == 1) || (computer[0][y] == 1 && computer[1][y] == 1 && computer[2][y] == 1)) {
                    computerWin = 1;
                }
            }

            if((player[0][0] == 1 && player[1][1] == 1 && player[2][2] == 1) || (player[0][2] == 1 && player[1][1] == 1 && player[2][0] == 1)) {
                playerWin = 1;
            } else if((computer[0][0] == 1 && computer[1][1] == 1 && computer[2][2] == 1) || (computer[0][2] == 1 && computer[1][1] == 1 && computer[2][0] == 1)) {
                computerWin = 1;
            }
        }
    }

    endwin();
    return 0;
}
