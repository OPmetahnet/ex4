/******************
Name: Oz Pinto
ID: 212320733
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define NUM_OF_CHEERLEADERS 15
#define NUM_OF_PYRAMID_LEVELS 5

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
                printf("Negative weights are not supported.\n");
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

void task3ParenthesisValidator() {

}

void task4QueensBattle() {

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
                //
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

            case 3:
                task3ParenthesisValidator();
                break;
            case 4:
                task4QueensBattle();
                break;
            case 5:
                task5CrosswordGenerator();
                break;
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