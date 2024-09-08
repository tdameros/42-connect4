/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:19:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/08 23:07:16 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

static bool is_win_horizontally(board_t *board, uint32_t x, uint32_t y);
static bool is_win_vertically(board_t *board, uint32_t x, uint32_t y);
static bool is_win_left_diagonally(board_t *board, uint32_t x, uint32_t y);
static bool is_win_right_diagonally(board_t *board, uint32_t x, uint32_t y);
static void set_win_pawn_horizontally(board_t *board, uint32_t x, uint32_t y);
static void set_win_pawn_vertically(board_t *board, uint32_t x, uint32_t y);
static void set_win_pawn_left_diagonally(board_t *board, uint32_t x,
                                         uint32_t y);
static void set_win_pawn_right_diagonally(board_t *board, uint32_t x,
                                          uint32_t y);

typedef struct {
  void (*set_win_pawn)(board_t *board, uint32_t x, uint32_t y);
  bool (*is_win)(board_t *board, uint32_t x, uint32_t y);
} _win_table_t;

bool check_win(board_t *board, uint32_t x, uint32_t y, bool is_simulation) {
  _win_table_t win_table[] = {
      {set_win_pawn_horizontally, is_win_horizontally},
      {set_win_pawn_vertically, is_win_vertically},
      {set_win_pawn_left_diagonally, is_win_left_diagonally},
      {set_win_pawn_right_diagonally, is_win_right_diagonally},
  };
  for (uint8_t i = 0; i < 4; i++) {
    if (win_table[i].is_win(board, x, y)) {
      board->is_finished = true;
      if (!is_simulation) {
        win_table[i].set_win_pawn(board, x, y);
      }
      return (true);
    }
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

static void set_win_pawn_horizontally(board_t *board, uint32_t x, uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  pawn_t win_pawn = pawn == PLAYER ? PLAYER_WIN : AI_WIN;
  uint8_t offset = 1;

  set_pawn(board, x, y, win_pawn);
  while (offset < 4 && x + offset < board->width &&
         get_pawn(board, x + offset, y) == pawn) {
    set_pawn(board, x + offset, y, win_pawn);
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)x - offset >= 0 &&
         get_pawn(board, x - offset, y) == pawn) {
    set_pawn(board, x - offset, y, win_pawn);
    offset++;
  }
}

static void set_win_pawn_vertically(board_t *board, uint32_t x, uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  pawn_t win_pawn = pawn == PLAYER ? PLAYER_WIN : AI_WIN;
  uint8_t offset = 1;

  set_pawn(board, x, y, win_pawn);
  while (offset < 4 && y + offset < board->height &&
         get_pawn(board, x, y + offset) == pawn) {
    set_pawn(board, x, y + offset, win_pawn);
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)y - offset >= 0 &&
         get_pawn(board, x, y - offset) == pawn) {
    set_pawn(board, x, y - offset, win_pawn);
    offset++;
  }
}

static void set_win_pawn_left_diagonally(board_t *board, uint32_t x,
                                         uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  pawn_t win_pawn = pawn == PLAYER ? PLAYER_WIN : AI_WIN;
  uint8_t offset = 1;

  set_pawn(board, x, y, win_pawn);
  while (offset < 4 && x + offset < board->width &&
         y + offset < board->height &&
         get_pawn(board, x + offset, y + offset) == pawn) {
    set_pawn(board, x + offset, y + offset, win_pawn);
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)x - offset >= 0 && (int32_t)y - offset >= 0 &&
         get_pawn(board, x - offset, y - offset) == pawn) {
    set_pawn(board, x - offset, y - offset, win_pawn);
    offset++;
  }
}

static void set_win_pawn_right_diagonally(board_t *board, uint32_t x,
                                          uint32_t y) {
  pawn_t pawn = get_pawn(board, x, y);
  pawn_t win_pawn = pawn == PLAYER ? PLAYER_WIN : AI_WIN;
  uint8_t offset = 1;

  set_pawn(board, x, y, win_pawn);
  while (offset < 4 && (int32_t)x - offset >= 0 && y + offset < board->height &&
         get_pawn(board, x - offset, y + offset) == pawn) {
    set_pawn(board, x - offset, y + offset, win_pawn);
    offset++;
  }
  offset = 1;
  while (offset < 4 && x + offset < board->width && (int32_t)y - offset >= 0 &&
         get_pawn(board, x + offset, y - offset) == pawn) {
    set_pawn(board, x + offset, y - offset, win_pawn);
    offset++;
  }
}
