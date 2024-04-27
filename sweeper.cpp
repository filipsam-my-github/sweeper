
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h> 
#include <string>

using namespace std;

/**
 * loads levels (starting on 1).
 * 
 * @param name that is name of file which contains levels
 * @param level the int which is represents number of level (stars on 1)
 * @return vector<string> which represent game board.
 */
vector<string> loadLevel(string name, int level) {
    vector<string> game;


    string filename = name + ".txt";
    ifstream inFile;

    inFile.open(filename);

    if (inFile.fail())
    {
        cout << "Error opening file." << endl;
        return game;
    }

    string str;
    int levelNow = 0;

    while (getline(inFile, str))
    {
        if (str[0] == 'S') {
            levelNow += 1;
        }
        else if (str[0] == 'E' && levelNow == level) {
            break;
        }
        else if (levelNow == level) {
            game.push_back(str);
        }

    }

    inFile.close();
    return game;
}

/**
 * this will cout the given map (vector<string>).
 * 
 * @param mapToDisplay that is game map which you'd to display
 * @return void/none/null
 */
void display(vector<string> mapToDisplay) {
    cout << "  12345678" << endl;
    cout << " _________" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << "|" << mapToDisplay[i] << endl;
    }
}

/**
 * discovers an empty square next to an empty square.
 * 
 * @param realMap that is map board
 * @param view that is what player can see represented by another map
 * @param yCord y cord of target empty square
 * @param xCord x cord of target empty square
 * @return new view variable that represents what player can see 
 */
vector<string> mapReveal(vector<string> realMap, vector<string> view, int yCord, int xCord) {
    bool changed = false;

    if (realMap[yCord][xCord] == '#') {
        view[yCord][xCord] = '#';
    }


    if (yCord > 0) {
        if (realMap[yCord - 1][xCord] == '#' && view[yCord - 1][xCord] != '#') {
            view = mapReveal(realMap, view, yCord - 1, xCord);
        }else{
            view[yCord - 1][xCord] = realMap[yCord - 1][xCord];
        }
    }
    if (yCord < 7) {
        if (realMap[yCord + 1][xCord] == '#' && view[yCord + 1][xCord] != '#') {
            view = mapReveal(realMap, view, yCord + 1, xCord);
        }else {
            view[yCord + 1][xCord] = realMap[yCord + 1][xCord];
        }
    }

    if (xCord > 0) {
        if (realMap[yCord][xCord - 1] == '#' && view[yCord][xCord - 1] != '#') {
            view = mapReveal(realMap, view, yCord, xCord - 1);
        }else{
            view[yCord][xCord - 1] = realMap[yCord][xCord - 1];
        }
    }
    if (xCord < 7) {
        if (realMap[yCord][xCord + 1] == '#' && view[yCord][xCord + 1] != '#') {
            view = mapReveal(realMap, view, yCord, xCord + 1);
        }else{
            view[yCord][xCord + 1] = realMap[yCord][xCord + 1];
        }
    }

    return view;


}

/**
 * runs game loop (sweeper).
 * 
 * @param playerView that is what player can see (represented by another map)
 * @param board map of the game
 * @return true or false (true if player win otherwise it returns false)
 */
bool gameLoop(vector<string> playerView, vector<string> board) {
    int xCord, yCord;
    bool placeMine;
    char localCharInput;


    while (true) {
        if (playerView == board) {
            return true;
        }

        cout << "do you want to place mine mark?(y/n)" << endl;
        cin >> localCharInput;
        placeMine = (localCharInput == 'y') ? true : false;

        cout << "now pleas give x and y" << endl;
        cin >> xCord;
        cin >> yCord;

        xCord--;
        yCord--;

        if (abs(yCord) > 7)
            yCord = 7;
        if (abs(xCord) > 7)
            xCord = 7;

        xCord = abs(xCord);
        yCord = abs(yCord);

        if (placeMine) {
            if (playerView[yCord][xCord] == '*') {
                playerView[yCord][xCord] = 'X';
            }
            else if (playerView[yCord][xCord] == 'X') {
                playerView[yCord][xCord] = '*';
            }
        }
        else if (board[yCord][xCord] == '*') {
            return false;
        }
        else if (board[yCord][xCord] == '#') {

            playerView = mapReveal(board, playerView, yCord, xCord);
        }
        else {
            playerView[yCord][xCord] = board[yCord][xCord];
        }

        system("cls");
        display(playerView);

    }

}



int main(void)
{

    vector<string> playerView;
    vector<string> game;
    
    for (int i = 0; i < 8; i++){
        playerView = {};
        game = loadLevel("Data", i+1);

        cout << "Wellcome in level " << i+1 << endl << endl;

        for (int i = 0; i < 8; i++) {
            playerView.push_back("XXXXXXXX");
        }

        if (gameLoop(playerView, game)) {
            cout << "    you won!" << endl;
            display(game);
        }
        else {
            cout << "    you lose!" << endl;
            display(game);

            break;
        }
    }
    

    cin;
    return 0;
}