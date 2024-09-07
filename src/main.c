/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/07 15:32:38 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "connect4.h"
#include "libft.h"

pawn_t get_pawn(board_t *board, uint32_t x, uint32_t y) {
  return board->grid[y * board->width + x];
}

void set_pawn(board_t *board, uint32_t x, uint32_t y, pawn_t pawn) {
  board->grid[y * board->width + x] = pawn;
}

static bool is_win_horizontally(board_t *board, uint32_t x, uint32_t y);
static bool is_win_vertically(board_t *board, uint32_t x, uint32_t y);
static bool is_win_left_diagonally(board_t *board, uint32_t x, uint32_t y);
static bool is_win_right_diagonally(board_t *board, uint32_t x, uint32_t y);

bool check_win(board_t *board, uint32_t x, uint32_t y) {
  if (is_win_horizontally(board, x, y) || is_win_vertically(board, x, y) ||
      is_win_left_diagonally(board, x, y) ||
      is_win_right_diagonally(board, x, y)) {
    board->is_finished = 1;
    return (true);
  }
  return (false);
}

static bool is_win_horizontally(board_t *board, uint32_t x, uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && x + offset < board->width &&
         get_pawn(board, x + offset, y) == pawn) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)x - offset >= 0 &&
         get_pawn(board, x - offset, y) == pawn) {
    count++;
    offset++;
  }
  return (count >= 3);
}

static bool is_win_vertically(board_t *board, uint32_t x, uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && y + offset < board->height &&
         get_pawn(board, x, y + offset) == pawn) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)y - offset >= 0 &&
         get_pawn(board, x, y - offset) == pawn) {
    count++;
    offset++;
  }
  return (count >= 3);
}

static bool is_win_left_diagonally(board_t *board, uint32_t x, uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && x + offset < board->width &&
         y + offset < board->height &&
         get_pawn(board, x + offset, y + offset) == pawn) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)x - offset >= 0 && (int32_t)y - offset >= 0 &&
         get_pawn(board, x - offset, y - offset) == pawn) {
    count++;
    offset++;
  }
  return (count >= 3);
}

static bool is_win_right_diagonally(board_t *board, uint32_t x, uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && (int32_t)x - offset >= 0 && y + offset < board->height &&
         get_pawn(board, x - offset, y + offset) == pawn) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && x + offset < board->width && (int32_t)y - offset >= 0 &&
         get_pawn(board, x + offset, y - offset) == pawn) {
    count++;
    offset++;
  }
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
  check_win(board, x, y - 1);
  board->played_pawns++;
  if (PLAYER == board->next_play) {
    board->next_play = IA;
  } else {
    board->next_play = PLAYER;
  }
  return (0);
}

int main(int argc, char **argv) {
  board_t board;

  if (parse_arguments(argc, argv, &board)) {
      return (1);
  }

  //  drop_pawn(&board, 0);
  //  drop_pawn(&board, 0);
  //  drop_pawn(&board, 1);
  //  drop_pawn(&board, 1);
  //  drop_pawn(&board, 2);
  //  drop_pawn(&board, 2);
  //  drop_pawn(&board, 3);
  //  drop_pawn(&board, 3);

  // printf("Is win: %d\n", board.is_finished);
  display_grid(&board);

  while (board.played_pawns < board.width * board.height &&
         !board.is_finished) {
    while (drop_pawn(&board, rand() % board.width))
      ;
    display_grid(&board);
    printf("\n");
    usleep(100000);
  }

  (void)argv;
  deinitialize_board(&board);
  return 0;
}
