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
void printSolution(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void task5CrosswordGenerator() {

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
                    printSolution(board, size);
                }
                else
                    printf("This puzzle cannot be solved.\n");

                break;
            }

            //creates a crossword puzzle from given words and grid size, if possible
            case 5: {
                int dimension, slot_number;
                char grid[MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE];

                printf("Please enter the dimensions of the crossword grid:\n");

                task5CrosswordGenerator();
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