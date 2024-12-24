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
}

//gets input for cheerleader pyramid weights
int getCheerleaderWeights(float cheerleader_weights[], int size, int level_amount) {
    for(int i = 0; i < level_amount; i++) {
        for(int j = 0; j <= i; j++) {
            /*
             gets input by combining level and position
             i*(i + 1)/2 : sum of all previous level numbers(known mathematical identity)
            */
            scanf("%f", &cheerleader_weights[(i * (i + 1) / 2) + j]);

            //make sure that input isn't negative. if negative - exit
            if(cheerleader_weights[(i * (i + 1) / 2) + j] < 0) {
                return 0;
            }
        }
    }

    return 1;
}

//prints weight for a specific cheerleader according to given position and level in the pyramid
float task2HumanPyramid(float cheerleader_weights[], int level, int position) {
    //if top was reached - return the weight of the top cheerleader
    if(level == 0) {
        return cheerleader_weights[(level * (level + 1) / 2) + position];
    }

    //if cheerleader is on the left side add only the right shoulder weight
    if(position == 0) {
        return cheerleader_weights[(level * (level + 1) / 2) + position] +
            task2HumanPyramid(cheerleader_weights, level - 1, position) / 2;
    }

    //if cheerleader is on the right side add only the left shoulder weight
    if(position == level) {
        return cheerleader_weights[(level * (level + 1) / 2) + position] +
            task2HumanPyramid(cheerleader_weights, level - 1, position - 1) / 2;
    }

    //own weight + right shoulder weight + left shoulder weight
    return cheerleader_weights[(level * (level + 1) / 2) + position] +
        task2HumanPyramid(cheerleader_weights, level - 1, position) / 2 +
            task2HumanPyramid(cheerleader_weights, level - 1, position - 1)/2;
}

//checks if a character is an opened parenthesis of some type
int checkIfOpenParenthesis(char char_to_check) {
    switch (char_to_check) {
        case '(': return 1;
        case '[': return 1;
        case '<': return 1;
        case '{': return 1;
        default: return 0;
    }
}

//checks if the character is a closed parenthesis of some type
int checkIfCloseParenthesis(char char_to_check) {
    switch (char_to_check) {
        case ')': return 1;
        case ']': return 1;
        case '}': return 1;
        case '>': return 1;
        default: return 0;
    }
}

//checks if two parentheses given are matching
int checkParenthesisMatch(char open_parenthesis, char closed_parenthesis) {
    switch (open_parenthesis) {
        case '(': return (closed_parenthesis == ')');
        case '{': return (closed_parenthesis == '}');
        case '[': return (closed_parenthesis == ']');
        case '<': return (closed_parenthesis == '>');
        default: return 0;
    }
}

//gets input until \n and checks if the parentheses in the expression are well organized
int task3ParenthesisValidator(char input_char, char parenthesis_to_close) {
    //get character
    scanf("%c", &input_char);

    //if the end of the string is reached
    if(input_char == '\n') {
        return 1;
    }

    //if closed parenthesis
    if(checkIfCloseParenthesis(input_char)) {
        if(checkParenthesisMatch(input_char, parenthesis_to_close)) {
            return 1;
        }
    }

    //if new opened parenthesis
    if(checkIfOpenParenthesis(input_char)) {
        return (task3ParenthesisValidator(input_char, input_char));
    }

    //keep checking
    return task3ParenthesisValidator(input_char, parenthesis_to_close);
}


//get values for board zones from the user
void getBoardZones(char zone_map[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            scanf(" %c", &zone_map[i][j]);
        }
    }
}

//set board to *'s before attempting to solve it(without loops sadly)
void initBoardValues(char board_to_set[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size, int row, int col) {

    //if rows are done insertion is complete
    if(row >= size)
        return;

    //if col index has reached the end of the col go to the next row
    if(col >= size)
        return initBoardValues(board_to_set, size, row + 1, 0);

    //set value
    board_to_set[row][col] = '*';

    //go to the next column
    initBoardValues(board_to_set, size, row, col + 1);
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
    char zone_map[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col,
    char zone_to_check
    ) {

    //if row exceeds given size track back
    if(row >= size) {
        return 0;
    }

    //if col exceeds given size check the next/prev row
    if(col >= size) {
        return zoneHasAQueen(board, zone_map, size, row + 1, 0, zone_to_check);
    }

    //if the zone type is the same as required check if there is a queen
    if(zone_to_check == zone_map[row][col]) {
        if(board[row][col] == 'X')
            return 1;
    }

    //keep checking the column values
    return zoneHasAQueen(board, zone_map, size, row, col + 1, zone_to_check);
}

//check all the conditions(row, col, zone, diagonal) to place a queen
int checkIllegalQueenPlacementConditions(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    char zone_map[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int size,
    int row,
    int col
    ) {

    return rowHasAQueen(board, size, row, 0) ||
        colHasAQueen(board, size, 0, col) ||
        diagonalHasAQueen(board, size, row, col) ||
        zoneHasAQueen(board, zone_map, size, 0, 0, zone_map[row][col]);
}

/*
 check for possible solution for the n-queens puzzle,
 depending on the given size for the grid and the zone layout
*/
int task4QueensBattle(
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    char zone_map[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
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
    if(!(checkIllegalQueenPlacementConditions(board, zone_map, size, row, col))) {

        //try a possible solution path with the queen placed at the current coordinate
        board[row][col] = 'X';

        //continue checking for the next row
        if(task4QueensBattle(board, zone_map, size, row + 1, 0)) {
            return 1;
        }

        //if the queen placement has been tried here and no solution was reached, place *
        board[row][col] = '*';
    }

    //try the next index in the row
    return task4QueensBattle(board, zone_map, size, row, col + 1);
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
    int word_length,
    int row_index,
    int col_index,
    int i,
    char word[MAX_WORD_LENGTH]) {

    //if end of line is reached - not occupied
    if(i >= word_length)
        return 1;

    //if a letter is found - check equation between characters
    if(grid[row_index][col_index] != '#') {
        if(grid[row_index][col_index] == word[i]) {
            return  wordCanBePlacedHorizontally(grid,
                word_length,
                row_index,
                col_index + 1,
                i + 1,
                word);
        }

        return 0;
    }

    //check next index
    return wordCanBePlacedHorizontally(grid,
        word_length,
        row_index,
        col_index + 1,
        i + 1,
        word);
}

//checks if the vertical word space is already occupied
int wordCanBePlacedVertically(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int word_length,
    int row_index,
    int col_index,
    int j,
    char word[MAX_WORD_LENGTH]) {

    //if end of line is reached - not occupied
    if(j >= word_length)
        return 1;

    //if a letter is found - check equation between characters
    if(grid[row_index][col_index] != '#') {
        if(grid[row_index][col_index] == word[j]) {
            return wordCanBePlacedVertically(grid,
            word_length,
            row_index + 1,
            col_index,
            j + 1,
            word);
        }

        return 0;
    }

    //check next index
    return wordCanBePlacedVertically(grid,
        word_length,
        row_index + 1,
        col_index,
        j + 1,
        word);
}

//checks if the intended word space is already occupied
int wordCanBePlaced(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int word_length,
    int row_index,
    int col_index,
    int i,
    int j,
    char direction,
    char word[MAX_WORD_LENGTH][MAX_WORD_LENGTH]) {

    if(direction == HORIZONTAL) return wordCanBePlacedHorizontally(grid, word_length, row_index, col_index, i, word);
    return wordCanBePlacedVertically(grid, word_length, row_index, col_index, j, word);
}

//place a given word in the matching slot horizontally
void placeWordInSlotHorizontally(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    char word[MAX_WORD_LENGTH],
    int word_length,
    int row_index,
    int col_index,
    int i) {

    //if end of word is reached return
    if(i >= word_length) {
        return;
    }

    //place the character in the corresponding place
    grid[row_index][col_index] = word[i];

    //place the next character
    placeWordInSlotHorizontally(grid,
                    word,
                    word_length,
                    row_index,
                    col_index + 1,
                    i + 1);
}

//erases a word from a place it was placed in horizontally
void eraseWordFromSlotHorizontally(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int word_length,
    int row_index,
    int col_index,
    int i) {

    //if end of word is reached return
    if(i >= word_length) {
        return;
    }

    //place the character in the corresponding place
    grid[row_index][col_index] = '#';

    //place the next character
    eraseWordFromSlotHorizontally(grid,
                    word_length,
                    row_index,
                    col_index + 1,
                    i + 1);
}

//place a given word in the matching slot vertically
void placeWordInSlotVertically(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    char word[MAX_WORD_LENGTH],
    int word_length,
    int row_index,
    int col_index,
    int j) {

    //if end of word is reached return
    if(j >= word_length) {
        return;
    }

    //place the character in the corresponding place
    grid[row_index][col_index] = word[j];

    //place the next character
    placeWordInSlotVertically(grid,
                    word,
                    word_length,
                    row_index + 1,
                    col_index,
                    j + 1);
}

//erases a word from a place it was placed in horizontally
void eraseWordFromSlotVertically(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE],
    int word_length,
    int row_index,
    int col_index,
    int j) {

    //if end of word is reached return
    if(j >= word_length) {
        return;
    }

    //place the character in the corresponding place
    grid[row_index][col_index] = '#';

    //place the next character
    eraseWordFromSlotVertically(grid,
                    word_length,
                    row_index + 1,
                    col_index,
                    j + 1);
}


//try to build a crossword on given grid
int task5CrosswordGenerator(char grid[MAX_BOARD_SIZE][MAX_BOARD_SIZE],
    int dimension,
    int slot_details[MAX_SLOT_AMOUNT][NUMBER_OF_DETAILS],
    int number_of_slots,
    char dictionary[MAX_SLOT_AMOUNT][MAX_WORD_LENGTH],
    int number_of_words,
    char directions[MAX_SLOT_AMOUNT],
    int i,
    int j,
    int used_words[MAX_SLOT_AMOUNT]
    ) {

    //if all slots have been filled crossword has been successfully created
    if(i >= number_of_slots)
        return 1;

    //if number of words has been exceeded back track
    if(j >= number_of_words)
        return 0;

    //check if the word fits in the current slot and if it wasn't already used
    if(strlen(dictionary[j]) == slot_details[i][2] && used_words[j] == 0 &&
        wordCanBePlaced(grid,
            strlen(dictionary[j]),
            slot_details[i][0],
            slot_details[i][1],
            0,
            0,
            directions[i],
            dictionary[j])) {

        //place word in slot depending on the direction
        if(directions[i] == HORIZONTAL) {
            placeWordInSlotHorizontally(grid,
                dictionary[j],
                strlen(dictionary[j]),
                slot_details[i][0],
                slot_details[i][1],
                0);
        }
        else {
            placeWordInSlotVertically(grid,
                dictionary[j],
                strlen(dictionary[j]),
                slot_details[i][0],
                slot_details[i][1],
                0);
        }

        //mark the word as used so that we won't be able to use it once more
        used_words[j] = 1;

        //try placing a word in the next slot
        if(task5CrosswordGenerator(grid,
            dimension,
            slot_details,
            number_of_slots,
            dictionary,
            number_of_words,
            directions,
            i + 1,
            0,
            used_words)) {
            return 1;
        }

        /*
         if solution path wasn't successful, erase the word from the space it was put in
         additionally, reset used words to all 0's
        */
        used_words[j] = 0;

        if(directions[i] == HORIZONTAL) {
            eraseWordFromSlotHorizontally(grid,
                strlen(dictionary[j]),
                slot_details[i][0],
                slot_details[i][1],
                0);
        }
        else {
            eraseWordFromSlotVertically(grid,
                strlen(dictionary[j]),
                slot_details[i][0],
                slot_details[i][1],
                0);
        }
    }

    //try testing the next word
    return task5CrosswordGenerator(grid,
        dimension,
        slot_details,
        number_of_slots,
        dictionary,
        number_of_words,
        directions,
        i,
        j + 1,
        used_words);
}

//print the final crossword solution
void printCrosswordPuzzleSolution(char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE], int dimension) {
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            printf("| %c ", grid[i][j]);
        }
        printf("\n");
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
                int x, y, total_path_number;

                //get input for the coords
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d", &x, &y);

                //save the result
                total_path_number = task1RobotPaths(x, y);

                //print the result
                printf("The total number of paths the robot can take to reach home is: %d\n", total_path_number);
                break;
            }

            //human cheerleader weight calculation
            case 2: {
                float cheerleader_weights[NUM_OF_CHEERLEADERS], weight_to_print;
                int is_valid_input;

                //ask for weights of all cheerleaders
                printf("Please enter the weights of the cheerleaders:\n");

                //get input for cheerleader weights and any negative input was detected exit to menu
                is_valid_input = getCheerleaderWeights(cheerleader_weights,
                    NUM_OF_CHEERLEADERS,
                    NUM_OF_PYRAMID_LEVELS);

                if(!is_valid_input) {
                    printf("Negative weights are not supported.\n");
                    break;
                }

                //calculates weights of every cheerleader
                for(int i = 0; i < NUM_OF_PYRAMID_LEVELS; i++) {
                    for(int j = 0; j <= i; j++) {
                        weight_to_print = task2HumanPyramid(cheerleader_weights,
                            i,
                            j);
                        printf("%.2f ", weight_to_print);
                    }
                    printf("\n");
                }

                break;
            }

            //gets input and checks if parentheses are opened and closed in a valid way
            case 3: {
                char input_char = '\0';

                //get input for term
                printf("Please enter a term for validation:\n");
                scanf("%c", &input_char);

                //checks the term's validity
                int is_string_valid = task3ParenthesisValidator(input_char, '\0');

                //clean buffer after the function's end
                scanf("%*[^\n]");
                scanf("%*c");

                //prints result based on the check
                if(is_string_valid == 0)
                    printf("The parentheses are not balanced correctly.\n");
                if(is_string_valid == 1) {
                    printf("The parentheses are balanced correctly.\n");
                }

                break;
            }

            //receives grid details and board zones, and prints a solution to the N queens problem accordingly
            case 4: {
                int size;
                char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {0};
                char zone_map[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

                //get board size
                printf("Please enter the board dimensions:\n");
                scanf("%d", &size);

                //get input for board
                printf("Please enter the %d*%d puzzle board\n", size, size);
                getBoardZones(zone_map, size);

                //initialize board to *'s according to given size
                initBoardValues(board, size, 0, 0);

                int result = task4QueensBattle(board, zone_map, size, 0, 0);

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
                int dimension, number_of_slots, number_of_words;
                char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE] = {0};
                char dictionary[MAX_SLOT_AMOUNT][MAX_WORD_LENGTH];
                char directions[MAX_SLOT_AMOUNT];
                int slot_details[MAX_SLOT_AMOUNT][NUMBER_OF_DETAILS];
                int used_words[MAX_SLOT_AMOUNT] = {0};

                //get dimension
                printf("Please enter the dimensions of the crossword grid:\n");
                scanf("%d", &dimension);

                //get the amount of slots
                printf("Please enter the number of slots in the crossword:\n");
                scanf("%d", &number_of_slots);

                //get the details for the skeleton of the crossword
                printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                for(int i = 0; i < number_of_slots; i++) {
                        scanf("%d %d %d %c",
                            &slot_details[i][0],
                            &slot_details[i][1],
                            &slot_details[i][2],
                            &directions[i]);
                }

                //get the number of words in the dictionary
                printf("Please enter the number of words in the dictionary:\n");
                scanf("%d", &number_of_words);

                //if number of words is smaller than the number of slots ask for number of words again
                while(number_of_words < number_of_slots) {
                    printf("The dictionary must contain at least %d words."
                           " Please enter a valid dictionary size:\n", number_of_slots);
                    scanf("%d", &number_of_words);
                }

                //get the words for the dictionary
                printf("Please enter the words for the dictionary:\n");
                for(int i = 0; i < number_of_words; i++) {
                    scanf("%s", &dictionary[i]);
                }

                //initialize values for the grid with # before sending it to the function
                initGridValues(grid, dimension, 0, 0);

                //check for a possible crossword puzzle creation path
                int result = task5CrosswordGenerator(grid,
                    dimension,
                    slot_details,
                    number_of_slots,
                    dictionary,
                    number_of_words,
                    directions,
                    0,
                    0,
                    used_words);

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