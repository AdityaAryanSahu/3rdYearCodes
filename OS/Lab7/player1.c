#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_ttt.h"
#include "ttt_help.c"

int main() {
    int shmid;
    struct shared_game *game;
    
    shmid = shmget((key_t)1234, sizeof(struct shared_game), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    
    game = (struct shared_game *)shmat(shmid, NULL, 0);
    if (game == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            game->board[i][j] = ' ';

    game->turn = 1;
    game->game_over = 0;

    printf("Player 1 (X) vs Player 2 (O)\n");

    while (!game->game_over) {
        if (game->turn == 1) {
            print_board(game->board);
            int row, col;
            printf("Player 1 (X), enter row and col (0-2 0-2): ");
            scanf("%d %d", &row, &col);

            if (row < 0 || row > 2 || col < 0 || col > 2 || game->board[row][col] != ' ') {
                printf("Invalid move! Try again.\n");
                continue;
            }

            game->board[row][col] = 'X';

            if (check_winner(game->board)) {
                print_board(game->board);
                printf("Player 1 (X) wins!\n");
                game->game_over = 1;
            } else if (is_draw(game->board)) {
                print_board(game->board);
                printf("It's a draw!\n");
                game->game_over = 1;
            } else {
                game->turn = 2;
            }
        } else {
            sleep(1); 
        }
    }

    shmdt(game);
    shmctl(shmid, IPC_RMID, 0); 
    return 0;
}
