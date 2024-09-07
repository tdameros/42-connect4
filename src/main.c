/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/07 14:00:16 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "libft.h"
#include "connect4.h"

int8_t initialize_board(board_t *board, uint32_t height, uint32_t width) {
  if (NULL == board) {
    return -1;
  }
  board->grid = malloc(height * width * sizeof(*board->grid));
  if (NULL == board->grid) {
    return -1;
  }
  for (uint32_t i = 0; i < height * width; i++) {
    board->grid[i] = EMPTY;
  }
  board->height = height;
  board->width = width;
  board->played_pawns = 0;
  board->next_play = rand() % 2 ? PLAYER : IA;
  board->is_finished = 0;
  return 0;
}

void deinitialize_board(board_t *board) {
  free(board->grid);
  board->height = 0;
  board->width = 0;
  board->played_pawns = 0;
}

pawn_t get_pawn(board_t *board, uint32_t x, uint32_t y) {
  return board->grid[y * board->width + x];
}

void set_pawn(board_t *board, uint32_t x, uint32_t y, pawn_t pawn) {
  board->grid[y * board->width + x] = pawn;
}

bool is_win(board_t *board, uint32_t x, uint32_t y) {
  uint8_t count = 0;
  pawn_t pawn = get_pawn(board, x, y);

  // uint8_t yi = 0;
  // while (x + y ) {
    
  // }

  for (uint8_t i = 0; i < 3; i++) {
    if (x + i >= board->width || get_pawn(board, x + i, y) != pawn) {
      break;
    }
    count++;
  }  
  int32_t new_x = x;
  for (int8_t i = 0; i < 3; i++) {
    if (new_x - i < 0 || get_pawn(board, x - i, y) != pawn) {
      break;
    }
    count++;
  }
  printf("X: %u Y: %u\n", x, y);
  printf("Count %d\n", count);
  board->is_finished = count >= 3;
  return (count >= 3);
}

int8_t drop_pawn(board_t *board, uint32_t x) {
  if (EMPTY != get_pawn(board, x, 0)) {
    return (-1);
  }
  uint8_t y = 0;
  while (y < board->height && EMPTY == get_pawn(board, x, y)) {
    y++;
  }
  set_pawn(board, x, y - 1, board->next_play);
  is_win(board, x, y - 1);
  board->played_pawns++;
  if (PLAYER == board->next_play) {
    board->next_play = IA;
  } else {
    board->next_play = PLAYER;
  }
  return (0);
}


int main(int argc, char **argv) {
  srand(time(NULL));

  board_t board;

  if (argc == 1) {
    if (initialize_board(&board, GRID_MIN_RAWS, GRID_MIN_COLS)) {
      return (1);
    }
  } else if (argc == 3) {
    //custom grid
  } else {
    // ft_dprintf(STDERR_FILENO, "error: Invalid arguments\nusage: ./connect4 [GRID SIZE X] [GRID SIZE Y]");
    ft_printf("error: Invalid arguments\nusage: ./connect4 [GRID SIZE X] [GRID SIZE Y]");
    return (1);
  }

  drop_pawn(&board, 0);
  // drop_pawn(&board, 0);
  // drop_pawn(&board, 1);
  // drop_pawn(&board, 1);
  // drop_pawn(&board, 2);
  // drop_pawn(&board, 2);
  // drop_pawn(&board, 3);
  // drop_pawn(&board, 3);

  // printf("Is win: %d\n", board.is_finished);
  display_grid(&board);
  
  // while (board.played_pawns < board.width * board.height && !board.is_finished) {
  //   while (drop_pawn(&board, rand() % board.width))
  //     ;
  //   display_grid(&board);
  //   printf("\n");
  //   usleep(100000);
  // }

  (void)argv;
  deinitialize_board(&board);
  return 0;
}
