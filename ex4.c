/******************
Name: Oz Pinto
ID: 212320733
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

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

void task2HumanPyramid() {

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
            case 1: {
                int x, y, total_number_of_paths;

                //get input for the coords
                printf("Please enter the coordinates of the robot (column, row):\n");
                scanf("%d %d", &x, &y);

                //save the result
                total_number_of_paths = task1RobotPaths(x, y);

                //print the result
                printf("The total number of paths the robot can take to reach home is: %d\n", total_number_of_paths);
                break;
            }
            case 2:
                task2HumanPyramid();
                break;
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