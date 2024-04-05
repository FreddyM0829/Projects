#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];           //global variable for our 2D board 
const char PLAYER = 'X';    //global variable to make us the player X
const char COMPUTER = 'O';  //global variable to make the computer O

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner = ' ';  //this will give us who is the winner
    char response;
    
    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();

        while(winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

        }

        printBoard();

        printWinner(winner);
        
        printf("\nWould you like to play again? (Y/N): ");
        scanf("%c");
        scanf("%c", &response);
        response = toupper(response);

    } while (response == 'Y');

    printf("\nTHANK YOU FOR PLAYING :)");
    
    return 0;
}

void resetBoard()
{
    for(int i = 0; i < 3; i++)          //will loop around the board in the i dimension
    {
        for (int j = 0; j < 3; j++)     //will loop around the board in the j dimension
        {
            board[i][j] = ' ';          //will go around the board making all the spaces empty again "reseting the board"
        }
    }
}
void printBoard()
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");

}
int checkFreeSpaces()
{
    int freeSpaces = 9;
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}
void playerMove()
{
    int x;
    int y;
    
    do
    {
        printf("Enter row #(1-3)\n"); //since a computer starts from 0 our user wont know that
        scanf("%d", &x);
        x--;                        //this is why we decrement it 
        printf("Enter column #(1-3)\n");  //since a computer starts from 0 our user wont know that
        scanf("%d", &y);
        y--;                            //this is why we decrement it 

        if (board[x][y] != ' ')
        {
            printf("INVALID move\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
    
}
void computerMove()
{
    //random number generation will nees a seed based off of cureent time
    srand(time(0));
    int x;
    int y;

    if(checkFreeSpaces() > 0)
    {
        do 
        {
            x = rand() % 3;
            y = rand() % 3;
        } while(board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else 
    {
        printWinner(' ');
    }
}
char checkWinner()
{
    for(int i = 0; i < 3; i++)   //check rows
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2])    //this whole if statement will check if there are any wins through out the rows 
        {
            return board[i][0];
        }
    }

    for(int i = 0; i < 3; i++)   //check columns
    {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i])    //this whole if statement will check if there are any wins through out the columns
        {
            return board[0][i];
        }
    }

   //check diagnols
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2])    //this if statement will check if there are any wins through one of the diagnols 
    {
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0])    //this if statement will check if there are any wins through one of the diagnols 
    {
        return board[0][2];
    }

    return ' ';
    
}
void printWinner(char winner)
{
    if(winner == PLAYER)
    {
        printf("YOU WIN!!!");
    }
    else if(winner == COMPUTER)
    {
        printf("YOU LOSE!");
    }
    else
    {
        printf("ITS A TIE!");
    }
}