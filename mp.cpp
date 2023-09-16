#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

    int rows = 0;
    int columns = 0;
    int mines = 0;
    int level = 0;
    string name;

    /*
    Description:
        This function checks whether a specific row and column is a mine.

    Arguments:
        int inputRow - A specific row.
        int inputColumn - A specific column.
        vector<vector<char>> &revealedBoard - An argument passed by reference; This is the board when it is revealed. It contains the mines & the numbers which tell how many adjacent mines there are.
`
    Returns:
        True, if a specific row and column is a mine.
        False otherwise.

    */

    bool isMine(int inputRow, int inputColumn, vector<vector<char>> &revealedBoard){
        return (revealedBoard[inputRow][inputColumn] == '*'); 
    }

    /*
    Description:
        This function checks whether a specific row and column is valid. Valid in a way such that it is not beyond the game board.

    Arguments:
        int inputRow - A specific row.
        int inputColumn - A specific column.
        vector<vector<char>> &revealedBoard - An argument passed by reference; This is the board when it is revealed. It contains the mines & the numbers which tell how many adjacent mines there are.

    Returns:
        True, if a specific row and column is valid.
        False otherwise.

    */

    bool isValid(int inputRow, int inputColumn){
        return (inputRow >= 0) && (inputRow < rows) && (inputColumn >= 0) && (inputColumn < columns); 
    }

    /*
    Description:
        This function checks if the player has satisfied the requirements for winning.

    Arguments:
        vector<vector<char>> &revealedBoard - An argument passed by reference; This is the board when it is revealed. It contains the mines & the numbers which tell how many adjacent mines there are.
        vector<vector<char>> &unrevealedBoard - An argument passed by reference; This is the board when it is unrevealed. It only contains dots. Moreover, it is where you can perform the action 'flag'.

    Returns:
        True, if all mines have been flagged.
        False otherwise.

    */

    bool isWin (vector<vector<char>> &revealedBoard, vector<vector<char>> &unrevealedBoard, int flags){  
        vector <int> v1;
        vector <int> v2;
        vector <int> v3;
        vector <int> v4;

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if (unrevealedBoard[i][j] == 'f') {
                    v1.push_back(i);
                    v2.push_back(j);       
                }
            }
        }

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if (revealedBoard[i][j] == '*') {
                    v3.push_back(i);
                    v4.push_back(j);       
                }
            }
        }

        if (flags == 0){
            if ((v1 == v3) && (v2 == v4)){
                return true;
            }
        }

        return false;
    }       

    /*
    Description:
        This function lets the player select a difficulty level.

    Arguments:
        -

    Returns:
        The game level the player has selected.
            0 - beginner
            1 - intermediate
            2 - expert

    */
    int chooseLevel(){
        cout << "Select a Difficulty Level" << endl;
        cout << "Press 0...BEGINNER (9 x 9 grid, 10 mines)" << endl;
        cout << "Press 1... INTERMEDIATE (16 x 16 grid, 40 mines)" << endl;
        cout << "Press 2...EXPERT (16 x 30 grid, 99 mines)" << endl;
        cin >> level;

        switch(level){
        case 0:
            rows = 9;
            columns = 9;
            mines = 10;
            break;

        case 1:
            rows = 16;
            columns = 16;
            mines = 40;
            break;

        case 2:
            rows = 16;
            columns = 30;
            mines = 99;
            break;

        default:
            cout << "Invalid input" << endl;
        }

        return level;
    }


    /*
    Description:
        This sets the columns and rows of the unrevealed board as dots.

    Arguments:
        vector<vector<char>> &unrevealedBoard - An argument passed by reference; This is the board when it is unrevealed. It only contains dots. Moreover, it is where you can perform the action 'flag'.

    Returns:
        -

    */

    void setUnrevealedBoard(vector<vector<char>> &unrevealedBoard){
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                unrevealedBoard[i][j] = '.'; //set board as dots
            }
        }

        return;
    }

    /*
    Description:
        This adds random mines to the revealed board.

    Arguments:
       vector<vector<char>> &revealedBoard - An argument passed by reference; This is the board when it is revealed. It contains the mines & the numbers which tell how many adjacent mines there are.

    Returns:
        -

    */

    void addMines(int mines, vector<vector<char>> &revealedBoard){
        int added = 0;
        int ranRow = 0;
        int ranColumn = 0;

        while (added < mines){
                ranRow = rand() % rows; //random row
                ranColumn = rand() % columns; //random column
                if (revealedBoard[ranRow][ranColumn] == '*') continue; //if already a mine
                revealedBoard[ranRow][ranColumn] = '*';
                added++;
            }

        return;
    }

     /*
    Description:
        This counts the number of mines adjacent to a cell, then it sets that cell to whatever number it counted. This will iterate for all the cells that is not a mine.

    Arguments:
       vector<vector<char>> &revealedBoard - An argument passed by reference; This is the board when it is revealed. It contains the mines & the numbers which tell how many adjacent mines there are.

    Returns:
        -

    */
    void minesAdjacentToCell (int rows, int columns, vector<vector<char>> &revealedBoard){ 
        int minesAdjacent = 0;

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if (revealedBoard[i][j] != '*'){ //if a specific coordinate is not a mine
                    for (int dx = -1; dx < 2; dx++){   //coordinates of adjacent cells; e.g. if (0,0) = (-1,-1)(-1,0)(-1,1)(0,-1)(0,1)(1,-1)(1,0)(1,1)
                        for (int dy = -1; dy < 2; dy++){
                            int adjacentX = i + dx;
                            int adjacentY = j + dy;

                            if (isValid(adjacentX, adjacentY)){
                                if (revealedBoard[adjacentX][adjacentY] == '*'){ //if the adjacent cell is a mine
                                    minesAdjacent++; 
                                }
                            }
                        }
                    }
                }

                if (revealedBoard[i][j] != '*'){
                    revealedBoard[i][j] = minesAdjacent + '0';  //this turns the integer to character, as board is a character
                        minesAdjacent = 0;
                        }
            }
        }

        return;
    }

     /*
        Description:
            This prints the unrevealed board which consists of dots or flags. This also prints the integers 0 to 9 repeatedly to help guide the user with the rows and columns.

        Arguments:
            vector<vector<char>> &unrevealedBoard - An argument passed by reference; This is the board when it is unrevealed. It only contains dots. Moreover, it is where you can perform the action 'flag'.

        Returns:
            -

    */
    void printUnrevealedBoard(vector<vector<char>> &unrevealedBoard){
        for (int j = 0; j < columns; ++j){
            if (j < 10){
                cout << j << " ";
            }

            else if (j >= 10 && j < 99){
                cout << j % 10 << " ";
            }

            else if (j >= 100 && j < 999){
                cout << j % 100 << " ";
            }
        }

        cout << endl;

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cout << unrevealedBoard[i][j] << " ";
            }

        if (i < 10){
            cout << i << " ";
        }

        else if (i >= 10 && i < 99){
            cout << i % 10 << " ";
        }

        else if(i >= 100 && i < 999){
            cout << i % 100 << " ";
        }

        cout << endl;
        }

        return;
    }

     /*
        Description:
            This swaps the content of a specific coordinate (row and column) from the revealed and unrevealed boards.
                e.g.
                . <-> *
                . <-> 0/1/2/3/4/5/6/7/8

        Arguments:
            vector<vector<char>> &unrevealedBoard - An argument passed by reference; This is the board when it is unrevealed. It only contains dots. Moreover, it is where you can perform the action 'flag'.
            vector<vector<char>> &revealedBoard - An argument passed by reference; This is the board when it is revealed. It contains the mines & the numbers which tell how many adjacent mines there are.
            int inputRow - A specific row.
            int inputColumn - A specific column.

        Returns:
            -

    */

    void swapBoard(vector<vector<char>> &unrevealedBoard, vector<vector<char>> &revealedBoard, int inputRow, int inputColumn){
        swap(unrevealedBoard[inputRow][inputColumn], revealedBoard[inputRow][inputColumn]);
    }

    /*
        Description:
            If the adjacent cells of a specific row and column are equal to zero (no mines adjacent to those cells), this function reveals those cells. Moreover, this function calls itself recursively. 

        Arguments:
            vector<vector<char>> &unrevealedBoard - An argument passed by reference; This is the board when it is unrevealed. It only contains dots. Moreover, it is where you can perform the action 'flag'.
            vector<vector<char>> &revealedBoard - An argument passed by reference; This is the board when it is revealed. It contains the mines & the numbers which tell how many adjacent mines there are.
            int inputRow - A specific row.
            int inputColumn - A specific column.

        Returns:
            -

    */

    void revealAdjacent(vector<vector<char>> &unrevealedBoard, vector<vector<char>> &revealedBoard, int inputRow, int inputColumn){
       for (int dx = -1; dx < 2; dx++){   //if adjacent cells are 0, reveal those cells
            for (int dy = -1; dy < 2; dy++){
                int adjacentX = inputRow + dx;
                int adjacentY = inputColumn + dy;
                    if (isValid(adjacentX, adjacentY)){
                        if (revealedBoard[adjacentX][adjacentY] == '0'){
                            swapBoard(unrevealedBoard, revealedBoard, adjacentX, adjacentY);
                            revealAdjacent(unrevealedBoard, revealedBoard, adjacentX, adjacentY);
                        }
                    }
            }
        }
   }

    /*
        Description:
            This shifts the names and scores of the users in the leaderboard when there is a new high scorer.
        
        Arguments:
            string names[5] - An array of size 5. The names of the 5 users in the leaderboard.
            double highscores[5] - An array of size 5. The scores (elapsed time while playing) of the 5 users in the leaderboard.
            string name - The name of the current user that is playing the game.
            double timeTaken - The elapsed time (in seconds) on how long the user had beaten the game.

        Returns:
            -

    */

    void shiftLeaderboard(string names[5], double highscores[5], string name, double timeTaken){
        if (timeTaken < highscores[0]){
            names[4] = names[3];
            names[3] = names[2];
            names[2] = names[1];
            names[1] = names[0];
            names[0] = name;

            highscores[4] = highscores[3];
            highscores[3] = highscores[2];
            highscores[2] = highscores[1];
            highscores[1] = highscores[0];
            highscores[0] = timeTaken;
        }

        else if (timeTaken < highscores[1]){
            names[4] = names[3];
            names[3] = names[2];
            names[2] = names[1];
            names[1] = name;

            highscores[4] = highscores[3];
            highscores[3] = highscores[2];
            highscores[2] = highscores[1];
            highscores[1] = timeTaken;
        }

        else if (timeTaken < highscores[2]){
            names[4] = names[3];
            names[3] = names[2];
            names[2] = name;

            highscores[4] = highscores[3];
            highscores[3] = highscores[2];
            highscores[2] = timeTaken;
        }

        else if (timeTaken < highscores[3]){
            names[4] = names[3];
            names[3] = name;

            highscores[4] = highscores[3];
            highscores[3] = timeTaken;
        }

        else if (timeTaken < highscores[4]){
            names[4] = name;
            highscores[4] = timeTaken;
        }
    }

    /*
        Description:
            This reads and writes the names and scores of the top 5 scorers to a .txt file. There is a unique .txt file for each difficulty level. Moreover, this will print the leaderboard if the current user is part of the top 5 scorers.
        
        Arguments:
            double timeTaken - The elapsed time (in seconds) on how long it took the user had beaten the game.
            int level - The difficulty level the user has chosen. (0 - beginner; 1 - intermediate; 2 - expert).
            string name - The name of the current user that is playing the game.

        Returns:
            -

    */
    
    void leaderboard(double timeTaken, int level, string name){
        double highscores[5];
        string names[5];

        if (level == 0){
            ifstream input("leaderboardBeginner.txt"); //input file stream; used to read information from files
            
            for (int i = 0; i < 5; ++i){
                input >> names[i];
                input >> highscores[i];
            }
             
            ofstream output("leaderboardBeginner.txt"); //output file stream; used to write information in files
            shiftLeaderboard(names, highscores, name, timeTaken);

            cout << endl << "- BEGINNER LEADERBOARD -" << endl; 

            for (int i = 0; i < 5; ++i){
                output << names[i] << " ";
                cout << names[i] << " ";
                output << highscores[i] << endl;
                cout << highscores[i] << endl;
            }
        }

        else if (level == 1){
            ifstream input("leaderboardIntermediate.txt");

            for (int i = 0; i < 5; ++i){
                input >> highscores[i];
                input >> names[i];
            }
            
            ofstream output("leaderboardIntermediate.txt");
            shiftLeaderboard(names, highscores, name, timeTaken);

             cout << endl << "- INTERMEDIATE LEADERBOARD -" << endl; 

            for (int i = 0; i < 5; ++i){
                output << names[i] << " ";
                cout << names[i] << " ";
                output << highscores[i] << endl;
                cout << highscores[i] << endl;
            }
        }

        else if (level == 2){

            ifstream input("leaderboardExpert.txt");

            for (int i = 0; i < 5; ++i){
                input >> names[i];
                input >> highscores[i];
            }
            
            ofstream output("leaderboardExpert.txt");
            shiftLeaderboard(names, highscores, name, timeTaken);

             cout << endl << "- EXPERT LEADERBOARD -" << endl; 

            for (int i = 0; i < 5; ++i){
                output << names[i] << " ";
                cout << names[i] << " ";
                output << highscores[i] << endl;
                cout << highscores[i] << endl;
            }
        }    

        return;
    }

    /*
        Description:
            This is where the actual game occurs. This function includes:
                - Getting the amount of time it takes for the user to win the game.
                - Asking the user for their moves (row, column, action).
                - Revealing or flagging a specific coordinate (row and column).
                - The conditions for winning or losing the game.
                - Illegal moves.

                Moreover, it calls all other functions declared earlier.

        Arguments:
            -

        Returns:
            -

    */

    void play(){
        auto start = chrono::steady_clock::now(); // timer starts
        int inputRow = 0;
        int inputColumn = 0;
        char action;

        vector<vector<char>> unrevealedBoard(rows, vector<char> (columns));
        vector<vector<char>> revealedBoard(rows, vector<char> (columns));
        vector<vector<int>> vector1;
        vector<vector<int>> vector2;

        setUnrevealedBoard(unrevealedBoard);
        addMines(mines, revealedBoard);
        minesAdjacentToCell(rows, columns, revealedBoard);

        int flags = mines;
        bool gameOver = false;
        
        while (!gameOver){
            printUnrevealedBoard(unrevealedBoard);
            
            cout << endl << "- Your Move -" << endl;
            cout << "Flags left: " << flags << endl << endl;

            cout << "Row: ";
            cin >> inputRow;

            cout << "Column: ";
            cin >> inputColumn;

            cout << "Action [reveal (r) or flag (f)]: ";
            cin >> action;


            if (action == 'r'){
                if (isValid(inputRow, inputColumn)){
                    if (revealedBoard[inputRow][inputColumn] != '*'){ //if not a mine
                        swapBoard(unrevealedBoard, revealedBoard, inputRow, inputColumn);
                        revealAdjacent(unrevealedBoard, revealedBoard, inputRow, inputColumn);
                    }

                    else if (revealedBoard[inputRow][inputColumn] == '*'){ //if a mine
                        swapBoard(unrevealedBoard, revealedBoard, inputRow, inputColumn);
                        printUnrevealedBoard(unrevealedBoard);
                        cout << endl << "Game Over, You lost! :(";
                        gameOver = true;
                    }
                }

                else{ //not valid
                    cout << endl << "Illegal move." << endl;
                }
            }

            else if (action == 'f'){
                if (flags >= 1){
                    if (isValid(inputRow, inputColumn)){
                        if (unrevealedBoard[inputRow][inputColumn] == '.'){
                            unrevealedBoard[inputRow][inputColumn] = 'f';
                            flags--;

                            if (isWin(revealedBoard, unrevealedBoard, flags)){
                                cout << endl << "Congratulations! You won! :)" << endl;

                                auto end = chrono::steady_clock::now(); //timer ends
                                double elapsedTime = double (chrono::duration_cast <chrono:: nanoseconds> (end-start).count()); //counts the seconds from start to end
                                double timeTaken = elapsedTime/1e9;
                                cout << "Elapsed time: "<< timeTaken << "s" << endl; //prints time

                                leaderboard(timeTaken, level, name);
                                gameOver = true;
                            }
                        }

                        else if (unrevealedBoard[inputRow][inputColumn] == 'f'){ //removes a flag on the board
                            unrevealedBoard[inputRow][inputColumn] = '.';
                            flags++;
                        }
                    }

                    else{ //not valid
                        cout << endl << "Illegal move" << endl;
                    }
                }

                else if (flags == 0){
                    if (unrevealedBoard[inputRow][inputColumn] == 'f'){ 
                        unrevealedBoard[inputRow][inputColumn] = '.';
                        flags++;
                    }

                    else {
                        cout << endl << "Illegal move" << endl; //adding more flags than what is allowed
                    }
                }
            }

            else{ //action not r or f
                cout << endl << "Illegal move." << endl;
            }
        }
        return;
    }
    
    /*
        Description:
            The main function of the code. The user has an option to create a custom game by typing their preffered number of rows, columns, and mines in the command line.
                e.g.
                -r 8 -c 5 -m 7

        Arguments:
            int argc - The number of command line arguments.
            char *argv[] - An array of character pointers listing all the command line arguments.

        Returns:
            0 - the standard for the "successful execution of the program".

    */
    int main(int argc, char *argv[]){ 
        if (argc == 1){
            cout << "Enter your name: ";
            cin >> name;
            transform(name.begin(), name.end(), name.begin(), ::toupper); //turns name to upper case
            chooseLevel();
        }

        else {
            rows = atoi(argv[2]); //atoi turns string to int
            columns = atoi(argv[4]);
            mines = atoi(argv[6]);
        }

        play();
        
        return 0;
    }

