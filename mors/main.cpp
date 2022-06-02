#include "Game.h"

int main()
{
    srand(time(0));
    Game game;
    game.drawFields();
    sleep_for(seconds(1));
    cout << endl << "        MORSKOI BOI             ";
    sleep_for(seconds(2));
    cout << endl;
    cout << endl << "     V Start Game  ";
    cout << endl << "     - Exit Game   " << endl;
    bool choice = false;
    int height = 1;
    while (choice != true) {
        switch (_getch()) {
        case Keys::Down: if (height == 1) {
            gotoxy(5, 15);
            cout << "-";
            gotoxy(5, 16);
            cout << "V";
            height = 0;
            gotoxy(0, 17);
        }
        break;
        case Keys::Up: if (height == 0) {
            gotoxy(5, 16);
            cout << "-";
            gotoxy(5, 15);
            cout << "V";
            height = 1;
            gotoxy(0, 17);
        }
        break;
        case Keys::Enter: {
            if (height == 0)
                return 1;
            else if (height == 1) {
                choice = true;
            }
            break;
        }
        }
    }
    bool restart = true;
    while (restart == true) {
        choice = false;
        height = 1;
        bool like = false;
        game.drawFields();
        cout << endl << endl << "        Select way to place your ships";
        cout << endl << "     V Manually      ";
        cout << endl << "     - Random        ";
        while (choice != true) {
            switch (_getch()) {
            case Keys::Down: if (height == 1) {
                gotoxy(5, 15);
                cout << "-";
                gotoxy(5, 16);
                cout << "V";
                height = 0;
                gotoxy(0, 17);
            }
                           break;
            case Keys::Up: if (height == 0) {
                gotoxy(5, 16);
                cout << "-";
                gotoxy(5, 15);
                cout << "V";
                height = 1;
                gotoxy(0, 17);
            }
                         break;
            case Keys::Enter: {
                if (height == 0) {
                    game.setFieldRandomly('f');
                    gotoxy(0, 12);
                    height = 1;
                    cout << "        Repeat it?            ";
                    cout << endl << "     V Yes            ";
                    cout << endl << "     - No             ";
                    while (like != true) {
                        switch (_getch()) {
                        case Keys::Down: if (height == 1) {
                            gotoxy(5, 13);
                            cout << "-";
                            gotoxy(5, 14);
                            cout << "V";
                            height = 0;
                            gotoxy(0, 15);
                        }
                                       break;
                        case Keys::Up: if (height == 0) {
                            gotoxy(5, 14);
                            cout << "-";
                            gotoxy(5, 13);
                            cout << "V";
                            height = 1;
                            gotoxy(0, 15);
                        }
                                     break;
                        case Keys::Enter: {
                            if (height == 0) {
                                like = true;
                            }
                            else if (height == 1) {
                                game.clearFields('f');
                                game.setFieldRandomly('f');
                                cout << "        Repeat it?            ";
                                cout << endl << "     V Yes            ";
                                cout << endl << "     - No             ";
                            }
                            break;
                        }
                        }
                    }
                }
                else if (height == 1) {
                    game.setFieldManually();
                    gotoxy(0, 12);
                    height = 1;
                    cout << "        Repeat it?            ";
                    cout << endl << "     V Yes            ";
                    cout << endl << "     - No             ";
                    while (like != true) {
                        switch (_getch()) {
                        case Keys::Down: if (height == 1) {
                            gotoxy(5, 13);
                            cout << "-";
                            gotoxy(5, 14);
                            cout << "V";
                            height = 0;
                            gotoxy(0, 15);
                        }
                                       break;
                        case Keys::Up: if (height == 0) {
                            gotoxy(5, 14);
                            cout << "-";
                            gotoxy(5, 13);
                            cout << "V";
                            height = 1;
                            gotoxy(0, 15);
                        }
                                     break;
                        case Keys::Enter: {
                            if (height == 0) {
                                like = true;
                            }
                            else if (height == 1) {
                                game.clearFields('f');
                                game.setFieldManually();
                                cout << "        Repeat it?            ";
                                cout << endl << "     V Yes  ";
                                cout << endl << "     - No  ";
                            }
                            break;
                        }
                        }
                    }
                }
                choice = true;
                break;
            }
            }
        }
        game.setFieldRandomly('e');
        game.setFieldsForGame();
        gotoxy(0, 15);
        cout << "        Let's go!";
        sleep_for(seconds(2));
        char turn = 'f';
        int x = 0;
        int y = 0;
        while (game.isEnd() == false) {
            switch (turn)
            {
            case 'f': {
                gotoxy(0, 15);
                cout << "        Your turn! Select cell for shoot.                 ";
                while (true) {
                    if (game.shoot('f') == false) {
                        turn = 'e';
                        gotoxy(0, 15);
                        cout << "        MISS                                                      ";
                        sleep_for(seconds(1));
                        break;
                    }
                    else {
                        gotoxy(0, 15);
                        cout << "        HIT!                                                      ";
                        sleep_for(seconds(1));
                        if (game.whoIsWinner() != 'n') {
                            game.End();
                            break;
                        }
                        gotoxy(0, 15);
                        cout << "        Your turn! Select cell for shoot.                 ";
                    }
                }
                break;
            }
            case 'e': {
                gotoxy(0, 15);
                cout << "        Enemy turn!                                           ";
                sleep_for(seconds(1));
                while (true) {
                    if (game.shoot('e') == false) {
                        turn = 'f';
                        gotoxy(0, 15);
                        cout << "        ENEMY MISSES                                                  ";
                        sleep_for(seconds(1));
                        break;
                    }
                    else {
                        gotoxy(0, 15);
                        cout << "        HIT!                                                      ";
                        sleep_for(seconds(1));
                        gotoxy(0, 15);
                        if (game.whoIsWinner() != 'n') {
                            game.End();
                            break;
                        }
                        cout << "        Enemy turn!                                           ";
                        sleep_for(seconds(1));
                    }
                }
            }
            }
            char winner = game.whoIsWinner();
            if (winner == 'f') {
                game.End();
                gotoxy(0, 15);
                cout << "WINNER, WINNER, CHICKEN DINNER!!!";
            }
            else if (winner == 'e') {
                game.End();
                gotoxy(0, 15);
                cout << "You lost. Good luck next time!";
            }
        }
        gotoxy(0, 18);
        cout << "You want to play again?    V Yes" << endl;
        cout << "                           - No";
        choice = false;
        height = 1;
        while (choice != true) {
            switch (_getch()) {
            case Keys::Down: if (height == 1) {
                gotoxy(27, 18);
                cout << "-";
                gotoxy(27, 19);
                cout << "V";
                height = 0;
                gotoxy(0, 21);
            }
                           break;
            case Keys::Up: if (height == 0) {
                gotoxy(27, 19);
                cout << "-";
                gotoxy(27, 18);
                cout << "V";
                height = 1;
                gotoxy(0, 21);
            }
                         break;
            case Keys::Enter: {
                if (height == 0) {
                    cout << "Ok. Thanks for playing!";
                    restart = false;
                    choice = true;
                }
                else if (height == 1) {
                    choice = true;
                    game.Restart();
                }
                break;
            }
            }
        }
    }
    sleep_for(seconds(2));
    gotoxy(0, 23);
    return 1;
}