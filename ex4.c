/******************
Name: Oz Pinto
ID: 212320733
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define NUM_OF_CHEERLEADERS 15
#define NUM_OF_PYRAMID_LEVELS 5
#define MAX_BOARD_SIZE 20
#define MAX_CROSSWORD_GRID_SIZE 30
#define MAX_SLOT_AMOUNT 100
#define MAX_WORD_LENGTH 15
#define NUMBER_OF_DETAILS 3
#define HORIZONTAL 'H'

//calculates the total possible amount of paths to make it to (0,0) from given two coords on the grid
int task1RobotPaths(int x, int y) {
    //if the coords are negative return 0
    if(x < 0 || y < 0)
        return 0;

    //if the destination was reached return 1 - success
    if(x == 0 && y == 0)
        return 1;

    //if one side of the grid has been reached, keep progressing only through the other
    if(x == 0 && y > 0)
        return task1RobotPaths(x,y - 1);

    if(x > 0 && y == 0)
        return task1RobotPaths(x - 1,y);

    if(x > 0 && y > 0)
        return task1RobotPaths(x - 1, y) + task1RobotPaths(x, y - 1);

    return 0;
}

//gets input for cheerleader pyramid weights
int getCheerleaderWeights(float cheerLeaderWeights[], int levelAmount) {
    for(int i = 0; i < levelAmount; i++) {
        for(int j = 0; j <= i; j++) {
            /*
             gets input by combining level and position
             i*(i + 1)/2 : sum of all previous level numbers(known mathematical identity)
            */
            scanf("%f", &cheerLeaderWeights[(i * (i + 1) / 2) + j]);

            //make sure that input isn't negative. if negative - exit
            if(cheerLeaderWeights[(i * (i + 1) / 2) + j] < 0) {
                return 0;
            }
        }
    }

    return 1;
}

//prints weight for a specific cheerleader according to given position and level in the pyramid
float task2HumanPyramid(float cheerLeaderWeights[], int level, int position) {
    //if top was reached - return the weight of the top cheerleader
    if(level == 0) {
        return cheerLeaderWeights[(level * (level + 1) / 2) + position];
    }

    //if cheerleader is on the left side add only the right shoulder weight
    if(position == 0) {
        return cheerLeaderWeights[(level * (level + 1) / 2) + position] +
            task2HumanPyramid(cheerLeaderWeights, level - 1, position) / 2;
    }

    //if cheerleader is on the right side add only the left shoulder weight
    if(position == level) {
        return cheerLeaderWeights[(level * (level + 1) / 2) + position] +
            task2HumanPyramid(cheerLeaderWeights, level - 1, position - 1) / 2;
    }

    //own weight + right shoulder weight + left shoulder weight
    return cheerLeaderWeights[(level * (level + 1) / 2) + position] +
        task2HumanPyramid(cheerLeaderWeights, level - 1, position) / 2 +
            task2HumanPyramid(cheerLeaderWeights, level - 1, position - 1)/2;
}

//checks if a character is an opened parenthesis of some type
int checkIfOpenParenthesis(char charToCheck) {
    switch (charToCheck) {
        case '(': return 1;
        case '[': return 1;
        case '<': return 1;
        case '{': return 1;
        default: return 0;
    }
}

//checks if the character is a closed parenthesis of some type
int checkIfCloseParenthesis(char charToCheck) {
    switch (charToCheck) {
        case ')': return 1;
        case ']': return 1;
        case '}': return 1;
        case '>': return 1;
        default: return 0;
    }
}

//checks for the matching closer for the opened parenthesis
char checkParenthesisMatchingCloser(char openParenthesis) {
    switch (openParenthesis) {
        case '(': return ')';
        case '{': return '}';
        case '[': return ']';
        case '<': return '>';
        default: return '\0';
    }
}

//cleans the buffer
void cleanBuffer() {
    scanf("%*s");
}

//gets input until \n and checks if the parentheses in the expression are well organized
int task3ParenthesisValidator(char inputChar, char parenthesisToFind) {
    //get character
    scanf("%c", &inputChar);

    //if the end of the string is reached, check if there are no more opened parentheses which were not closed
    if(inputChar == '\n') {
        return parenthesisToFind == '\0';
    }

    //if new open parenthesis was inputted start a new recursive search for the right closer
    if(checkIfOpenParenthesis(inputChar)) {
        return task3ParenthesisValidator(inputChar, checkParenthesisMatchingCloser(inputChar)) &&
            task3ParenthesisValidator(inputChar, parenthesisToFind);
    }

    //if closer parenthesis check if it matches the required closer
    if(checkIfCloseParenthesis(inputChar)) {
        //if the closer isn't matching - clean buffer and end validation
        if(inputChar != parenthesisToFind) {
            cleanBuffer();
            return 0;
        }

        return 1;
    }

    //check the next character
    return task3ParenthesisValidator(inputChar, parenthesisToFind);
}


//get values for board zones from the user
void getBoardZones(char zoneMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            scanf(" %c", &zoneMap[i][j]);
        }
    }
}

//set board to *'s before attempting to solve it(without loops sadly)
void initBoardValues(char boardToSet[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size, int row, int col) {

    //if rows are done with insertion is complete
    if(row >= size)
        return;

    //if col index has reached the end of the col go to the next row
    if(col >= size)
        return initBoardValues(boardToSet, size, row + 1, 0);

    //set value
    boardToSet[row][col] = '*';

    //go to the next column
    initBoardValues(boardToSet, size, row, col + 1);
}

//check if the given row already has a queen placed in it
int rowHasAQueen(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col) {

    //if col has exceeded size is clean of queens
    if(col >= size)
        return 0;

    //check if the space has a queen in it
    if(board[row][col] == 'X')
        return 1;

    //check the next space in the row
    return rowHasAQueen(board, size, row, col + 1);
}

//check if the col already has a queen placed in it
int colHasAQueen(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col) {

    //if row has exceeded size is clean of queens
    if(row >= size)
        return 0;

    //check if the space has a queen in it
    if(board[row][col] == 'X')
        return 1;

    //check the next space in the row
    return colHasAQueen(board, size, row + 1, col);
}

//check if the surrounding diagonal spaces already have a queen in them
int diagonalHasAQueen(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col
    ) {

    //check upper left space
    if(row > 0 && col > 0)
        if(board[row - 1][col - 1] == 'X')
            return 1;

    //check upper right space
    if(row > 0 && col < size - 1)
        if(board[row - 1][col + 1] == 'X')
            return 1;

    //check lower left space
    if(row < size - 1 && col > 0)
        if(board[row + 1][col - 1] == 'X')
            return 1;

    //check lower right space
    if(row < size - 1 && col < size - 1)
        if(board[row + 1][col + 1] == 'X')
            return 1;

    return 0;
}

//checks if the zone already has a queen placed in it
int zoneHasAQueen(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    char zoneMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col,
    char zoneToCheck
    ) {

    //if row exceeds given size track back
    if(row >= size) {
        return 0;
    }

    //if col exceeds given size check the next/prev row
    if(col >= size) {
        return zoneHasAQueen(board, zoneMap, size, row + 1, 0, zoneToCheck);
    }

    //if the zone type is the same as required check if there is a queen
    if(zoneToCheck == zoneMap[row][col]) {
        if(board[row][col] == 'X')
            return 1;
    }

    //keep checking the column values
    return zoneHasAQueen(board, zoneMap, size, row, col + 1, zoneToCheck);
}

//check all the conditions(row, col, zone, diagonal) to place a queen
int checkIllegalQueenPlacementConditions(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    char zoneMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col
    ) {

    return rowHasAQueen(board, size, row, 0) ||
        colHasAQueen(board, size, 0, col) ||
        diagonalHasAQueen(board, size, row, col) ||
        zoneHasAQueen(board, zoneMap, size, 0, 0, zoneMap[row][col]);
}

/*
 check for possible solution for the n-queens puzzle,
 depending on the given size for the grid and the zone layout
*/
int task4QueensBattle(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    char zoneMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col) {

    //if row exceeded size - no more rows are left to check
    if(row >= size)
        return 1;

    //if col has exceeded size - no queen can be placed in the row and there is no possible solution
    if(col >= size)
        return 0;

    //check if queen can be placed. if so, place it and continue the process
    if(!(checkIllegalQueenPlacementConditions(board, zoneMap, size, row, col))) {

        //try a possible solution path with the queen placed at the current coordinate
        board[row][col] = 'X';

        //continue checking for the next row
        if(task4QueensBattle(board, zoneMap, size, row + 1, 0)) {
            return 1;
        }

        //if the queen placement has been tried here and no solution was reached, place *
        board[row][col] = '*';
    }

    //try the next index in the row
    return task4QueensBattle(board, zoneMap, size, row, col + 1);
}

//print the final solution
void printQueensSolution(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

//initializes the grid to #
void initGridValues(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int dimension,
    int i,
    int j) {
    //if rows are done insertion is complete
    if(i >= dimension)
        return;

    //if col index has reached the end of the col go to the next row
    if(j >= dimension)
        return initGridValues(grid, dimension, i + 1, 0);

    //set value to #
    grid[i][j] = '#';

    //go to the next column
    initGridValues(grid, dimension, i, j + 1);
}

//checks if the horizontal word space is already occupied
int wordCanBePlacedHorizontally(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int wordLength,
    int rowIndex,
    int colIndex,
    int i,
    char word[MAX_WORD_LENGTH]) {

    //if end of line is reached - not occupied
    if(i >= wordLength)
        return 1;

    //if a letter is found - check equation between characters
    if(grid[rowIndex][colIndex] != '#') {
        if(grid[rowIndex][colIndex] == word[i]) {
            return  wordCanBePlacedHorizontally(grid,
                wordLength,
                rowIndex,
                colIndex + 1,
                i + 1,
                word);
        }

        return 0;
    }

    //check next index
    return wordCanBePlacedHorizontally(grid,
        wordLength,
        rowIndex,
        colIndex + 1,
        i + 1,
        word);
}

//checks if the vertical word space is already occupied
int wordCanBePlacedVertically(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int wordLength,
    int rowIndex,
    int colIndex,
    int j,
    char word[MAX_WORD_LENGTH]) {

    //if end of line is reached - not occupied
    if(j >= wordLength)
        return 1;

    //if a letter is found - check equation between characters
    if(grid[rowIndex][colIndex] != '#') {
        if(grid[rowIndex][colIndex] == word[j]) {
            return wordCanBePlacedVertically(grid,
            wordLength,
            rowIndex + 1,
            colIndex,
            j + 1,
            word);
        }

        return 0;
    }

    //check next index
    return wordCanBePlacedVertically(grid,
        wordLength,
        rowIndex + 1,
        colIndex,
        j + 1,
        word);
}

//checks if the intended word space is already occupied
int wordCanBePlaced(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int wordLength,
    int rowIndex,
    int colIndex,
    int i,
    int j,
    char direction,
    char word[MAX_WORD_LENGTH]) {

    if(direction == HORIZONTAL) return wordCanBePlacedHorizontally(grid, wordLength, rowIndex, colIndex, i, word);
    return wordCanBePlacedVertically(grid, wordLength, rowIndex, colIndex, j, word);
}

//place a given word in the matching slot horizontally
void placeWordInSlotHorizontally(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    char word[MAX_WORD_LENGTH],
    int wordLength,
    int rowIndex,
    int colIndex,
    int i) {

    //if end of word is reached return
    if(i >= wordLength) {
        return;
    }

    //place the character in the corresponding place
    grid[rowIndex][colIndex] = word[i];

    //place the next character
    placeWordInSlotHorizontally(grid,
                    word,
                    wordLength,
                    rowIndex,
                    colIndex + 1,
                    i + 1);
}

//erases a word from a place it was placed in horizontally
void eraseWordFromSlotHorizontally(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int wordLength,
    int rowIndex,
    int colIndex,
    int i) {

    //if end of word is reached return
    if(i >= wordLength) {
        return;
    }

    //place the character in the corresponding place
    grid[rowIndex][colIndex] = '#';

    //place the next character
    eraseWordFromSlotHorizontally(grid,
                    wordLength,
                    rowIndex,
                    colIndex + 1,
                    i + 1);
}

//place a given word in the matching slot vertically
void placeWordInSlotVertically(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    char word[MAX_WORD_LENGTH],
    int wordLength,
    int rowIndex,
    int colIndex,
    int j) {

    //if end of word is reached return
    if(j >= wordLength) {
        return;
    }

    //place the character in the corresponding place
    grid[rowIndex][colIndex] = word[j];

    //place the next character
    placeWordInSlotVertically(grid,
                    word,
                    wordLength,
                    rowIndex + 1,
                    colIndex,
                    j + 1);
}

//erases a word from a place it was placed in horizontally
void eraseWordFromSlotVertically(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int wordLength,
    int rowIndex,
    int colIndex,
    int j) {

    //if end of word is reached return
    if(j >= wordLength) {
        return;
    }

    //place the character in the corresponding place
    grid[rowIndex][colIndex] = '#';

    //place the next character
    eraseWordFromSlotVertically(grid,
                    wordLength,
                    rowIndex + 1,
                    colIndex,
                    j + 1);
}


//try to build a crossword on given grid
int task5CrosswordGenerator(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int dimension,
    int slotDetails[MAX_SLOT_AMOUNT][NUMBER_OF_DETAILS],
    int numberOfSlots,
    char dictionary[MAX_SLOT_AMOUNT][MAX_WORD_LENGTH],
    int numberOfWords,
    char directions[MAX_SLOT_AMOUNT],
    int i,
    int j,
    int usedWords[MAX_SLOT_AMOUNT]
    ) {

    //if all slots have been filled crossword has been successfully created
    if(i >= numberOfSlots)
        return 1;

    //if number of words has been exceeded back track
    if(j >= numberOfWords)
        return 0;

    //check if the word fits in the current slot and if it wasn't already used
    if((int)strlen(dictionary[j]) == slotDetails[i][2] && usedWords[j] == 0 &&
        wordCanBePlaced(grid,
            (int)strlen(dictionary[j]),
            slotDetails[i][0],
            slotDetails[i][1],
            0,
            0,
            directions[i],
            dictionary[j])) {

        //place word in slot depending on the direction
        if(directions[i] == HORIZONTAL) {
            placeWordInSlotHorizontally(grid,
                dictionary[j],
                (int)strlen(dictionary[j]),
                slotDetails[i][0],
                slotDetails[i][1],
                0);
        }
        else {
            placeWordInSlotVertically(grid,
                dictionary[j],
                (int)strlen(dictionary[j]),
                slotDetails[i][0],
                slotDetails[i][1],
                0);
        }

        //mark the word as used so that we won't be able to use it once more
        usedWords[j] = 1;

        //try placing a word in the next slot
        if(task5CrosswordGenerator(grid,
            dimension,
            slotDetails,
            numberOfSlots,
            dictionary,
            numberOfWords,
            directions,
            i + 1,
            0,
            usedWords)) {
            return 1;
        }

        /*
         if solution path wasn't successful, erase the word from the space it was put in
         additionally, reset used words to all 0's
        */
        usedWords[j] = 0;

        if(directions[i] == HORIZONTAL) {
            eraseWordFromSlotHorizontally(grid,
                (int)strlen(dictionary[j]),
                slotDetails[i][0],
                slotDetails[i][1],
                0);
        }
        else {
            eraseWordFromSlotVertically(grid,
                (int)strlen(dictionary[j]),
                slotDetails[i][0],
                slotDetails[i][1],
                0);
        }
    }

    //try testing the next word
    return task5CrosswordGenerator(grid,
        dimension,
        slotDetails,
        numberOfSlots,
        dictionary,
        numberOfWords,
        directions,
        i,
        j + 1,
        usedWords);
}

//print the final crossword solution
void printCrosswordPuzzleSolution(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE], int dimension) {
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            printf("| %c ", grid[i][j]);
        }
        printf("|\n");
    }
}

int main()
{
    int task = -1;
    do
    {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task))
        {
            switch (task)
            {
            case 6:
                printf("Goodbye!\n");
                break;

            //get position on the grid(x,y coordinates) and calculate the possible paths leading to (0,0)
            case 1: {
                int x, y, totalPathNumber;

                //get input for the coords
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d", &x, &y);

                //save the result
                totalPathNumber = task1RobotPaths(x, y);

                //print the result
                printf("The total number of paths the robot can take to reach home is: %d\n", totalPathNumber);
                break;
            }

            //human cheerleader weight calculation
            case 2: {
                float cheerLeaderWeights[NUM_OF_CHEERLEADERS], weightToPrint;
                int isValidInput;

                //ask for weights of all cheerleaders
                printf("Please enter the weights of the cheerleaders:\n");

                //get input for cheerleader weights and any negative input was detected exit to menu
                isValidInput = getCheerleaderWeights(cheerLeaderWeights,
                    NUM_OF_PYRAMID_LEVELS);

                if(!isValidInput) {
                    printf("Negative weights are not supported.\n");
                    break;
                }

                printf("The total weight on each cheerleader is:\n");

                //calculates weights of every cheerleader
                for(int i = 0; i < NUM_OF_PYRAMID_LEVELS; i++) {
                    for(int j = 0; j <= i; j++) {
                        weightToPrint = task2HumanPyramid(cheerLeaderWeights,
                            i,
                            j);
                        printf("%.2f ", weightToPrint);
                    }
                    printf("\n");
                }

                break;
            }

            //gets input and checks if parentheses are opened and closed in a valid way
            case 3: {
                char inputChar = '\0';

                //get input for term
                printf("Please enter a term for validation:\n");
                scanf("%c", &inputChar);

                //checks the term's validity
                int isStringValid = task3ParenthesisValidator(inputChar, '\0');

                //prints result based on the check
                if(isStringValid == 0)
                    printf("The parentheses are not balanced correctly.\n");
                if(isStringValid == 1) {
                    printf("The parentheses are balanced correctly.\n");
                }

                break;
            }

            //receives grid details and board zones, and prints a solution to the N queens problem accordingly
            case 4: {
                int size;
                char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {0};
                char zoneMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

                //get board size
                printf("Please enter the board dimensions:\n");
                scanf("%d", &size);

                //get input for board
                printf("Please enter a %d*%d puzzle board:\n", size, size);
                getBoardZones(zoneMap, size);

                //initialize board to *'s according to given size
                initBoardValues(board, size, 0, 0);

                int result = task4QueensBattle(board, zoneMap, size, 0, 0);

                if(result) {
                    printf("Solution:\n");
                    printQueensSolution(board, size);
                }
                else
                    printf("This puzzle cannot be solved.\n");

                break;
            }

            //creates a crossword puzzle from given words and grid size, if possible
            case 5: {
                int dimension, numberOfSlots, numberOfWords;
                char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE] = {0};
                char dictionary[MAX_SLOT_AMOUNT][MAX_WORD_LENGTH];
                char directions[MAX_SLOT_AMOUNT];
                int slotDetails[MAX_SLOT_AMOUNT][NUMBER_OF_DETAILS];
                int usedWords[MAX_SLOT_AMOUNT] = {0};

                //get dimension
                printf("Please enter the dimensions of the crossword grid:\n");
                scanf("%d", &dimension);

                //get the amount of slots
                printf("Please enter the number of slots in the crossword:\n");
                scanf("%d", &numberOfSlots);

                //get the details for the skeleton of the crossword
                printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                for(int i = 0; i < numberOfSlots; i++) {
                        scanf("%d %d %d %c",
                            &slotDetails[i][0],
                            &slotDetails[i][1],
                            &slotDetails[i][2],
                            &directions[i]);
                }

                //get the number of words in the dictionary
                printf("Please enter the number of words in the dictionary:\n");
                scanf("%d", &numberOfWords);

                //if number of words is smaller than the number of slots ask for number of words again
                while(numberOfWords < numberOfSlots) {
                    printf("The dictionary must contain at least %d words."
                           " Please enter a valid dictionary size:\n", numberOfSlots);
                    scanf("%d", &numberOfWords);
                }

                //get the words for the dictionary
                printf("Please enter the words for the dictionary:\n");
                for(int i = 0; i < numberOfWords; i++) {
                    scanf("%s", dictionary[i]);
                }

                //initialize values for the grid with # before sending it to the function
                initGridValues(grid, dimension, 0, 0);

                //check for a possible crossword puzzle creation path
                int result = task5CrosswordGenerator(grid,
                    dimension,
                    slotDetails,
                    numberOfSlots,
                    dictionary,
                    numberOfWords,
                    directions,
                    0,
                    0,
                    usedWords);

                //print messages accordingly to whether a crossword was generated or not
                if(result) {
                    printCrosswordPuzzleSolution(grid, dimension);
                }
                else {
                    printf("This crossword cannot be solved.\n");
                }

                break;
            }
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}