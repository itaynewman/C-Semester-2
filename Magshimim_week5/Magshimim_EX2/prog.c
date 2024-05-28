/*********************************
* Class: MAGSHIMIM C2			 *
* Week 6           				 *
* HW Bingo solution			 	 *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BOARD_SIZE 5
#define MAX_VAL 75
#define FALSE 0
#define TRUE !FALSE
#define HIT 'X'

#define STR_LEN 20
#define NO_WINNER -1

typedef struct {
    char name[STR_LEN];
    char board[BOARD_SIZE][BOARD_SIZE];
} BingoPlayer;

typedef struct {
    int* numsDrawn;
    int numOfNumsDrawn;
    BingoPlayer* players;
    int numPlayers;
} BingoGame;

void initGame(BingoGame* game, int players);
void initBingoPlayer(BingoPlayer* pPlayer);
int updateGame(BingoGame* game, int num);
int numInArr(char arr[][BOARD_SIZE], int num);
void updateBoard(BingoPlayer* player, int num);
void printBoard(BingoPlayer player);
void printBoards(BingoGame game);
int hasWon(BingoPlayer player);
void myFgets(char str[], int n);

int main(void)
{
    int numPlayers = 0;
    int winner = NO_WINNER;
    int drawnAlready = TRUE;
    int num = 0;
    int i = 0;
    BingoGame game = { NULL, 0, NULL, 0 };

    srand((unsigned int)time(NULL));

    printf("How many players? ");
    scanf("%d", &numPlayers);
    getchar(); // clean buffer

    initGame(&game, numPlayers);

    printBoards(game);

    while (winner == NO_WINNER)
    {
        while (drawnAlready)
        {
            num = (rand() % MAX_VAL) + 1;
            drawnAlready = FALSE;
            for (i = 0; i < game.numOfNumsDrawn; i++)
            {
                drawnAlready = drawnAlready || (num == game.numsDrawn[i]);
            }
        }
        // num now contains a new drawn number!
        winner = updateGame(&game, num);
        drawnAlready = TRUE;
    }
    printf("%s won the match! The winning board:\n", game.players[winner].name);
    printBoard(game.players[winner]);

    getchar();
    return 0;
}

void initGame(BingoGame* game, int players)
{
    int i = 0;
    game->numsDrawn = NULL;
    game->numOfNumsDrawn = 0;
    game->numPlayers = players;
    game->players = (BingoPlayer*)malloc(sizeof(BingoPlayer) * players); // Allocating memory for players
    for (i = 0; i < game->numPlayers; i++)
    {
        initBingoPlayer(&(game->players[i]));
    }
}

void initBingoPlayer(BingoPlayer* pPlayer)
{
    int i = 0, j = 0;
    int num = 0;

    printf("What is the player's name?\n");
    myFgets(pPlayer->name, STR_LEN);

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            pPlayer->board[i][j] = 0;
        }
    }

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            num = (rand() % MAX_VAL) + 1;

            while (numInArr(pPlayer->board, num))
            {
                num = (rand() % MAX_VAL) + 1;
            }

            pPlayer->board[i][j] = (char)num;
        }
    }
}

int numInArr(char arr[][BOARD_SIZE], int num)
{
    int i = 0, j = 0;
    int found = FALSE;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if ((int)arr[i][j] == num)
            {
                found = TRUE;
                i = BOARD_SIZE;
                break;
            }
        }
    }
    return found;
}

int updateGame(BingoGame* game, int num)
{
    int i = 0;
    int winner = NO_WINNER;

    game->numOfNumsDrawn++;
    game->numsDrawn = (int*)realloc(game->numsDrawn, sizeof(int) * game->numOfNumsDrawn);
    game->numsDrawn[game->numOfNumsDrawn - 1] = num;

    for (i = 0; i < game->numPlayers && NO_WINNER; i++)
    {
        updateBoard(&(game->players[i]), num);
        if (hasWon(game->players[i]))
        {
            winner = i;
        }
    }

    return winner;
}

void updateBoard(BingoPlayer* player, int num)
{
    int i = 0, j = 0;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if ((int)player->board[i][j] == num)
            {
                player->board[i][j] = HIT;
            }
        }
    }
}

void printBoard(BingoPlayer player)
{
    int i = 0, j = 0;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (player.board[i][j] == HIT)
            {
                printf(" X  ");
            }
            else
            {
                printf("%3d ", (int)player.board[i][j]);
            }
        }
        printf("\n\n");
    }
}

void printBoards(BingoGame game)
{
    int i = 0;
    for (i = 0; i < game.numPlayers; i++)
    {
        printf("%s's board:\n", game.players[i].name);
        printBoard(game.players[i]);
    }
}

int hasWon(BingoPlayer player)
{
    int won = FALSE;
    int i = 0, j = 0;
    int counter = 0;

    for (i = 0; i < BOARD_SIZE && !won; i++)
    {
        for (j = 0; j < BOARD_SIZE && !won; j++)
        {
            if (player.board[i][j] == HIT)
            {
                counter++;
            }
            else
            {
                break; // if this row has no X, certainly it's not a winner! continue to next row
            }
            if (counter == BOARD_SIZE) // a whole row of X's!
            {
                won = TRUE;
                break; // no need to continue
            }
        }
    }
    return won;
}

void myFgets(char str[], int n)
{
    fgets(str, n, stdin);
    str[strcspn(str, "\n")] = 0;
}
