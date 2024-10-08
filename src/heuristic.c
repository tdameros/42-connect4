/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:06:35 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 23:06:36 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

static bool is_heuristic_win_horizontally(board_t *board, uint32_t x,
                                          uint32_t y, pawn_t pawn);
static bool is_heuristic_win_vertically(board_t *board, uint32_t x, uint32_t y,
                                        pawn_t pawn);
static bool is_heuristic_win_left_diagonally(board_t *board, uint32_t x,
                                             uint32_t y, pawn_t pawn);
static bool is_heuristic_win_right_diagonally(board_t *board, uint32_t x,
                                              uint32_t y, pawn_t pawn);
static int32_t get_heuristic_score(board_t *board, uint32_t x, uint32_t y,
                                   pawn_t pawn);

int32_t get_heuristic_total_score(board_t *board, pawn_t pawn) {
  int32_t score = 0;
  for (uint32_t y = 0; y < board->height; y++) {
    for (uint32_t x = 0; x < board->width; x++) {
      score += get_heuristic_score(board, x, y, pawn) *
               get_heuristic_factor(board, x, y);
    }
  }
  return score / 10;
}

static int32_t get_heuristic_score(board_t *board, uint32_t x, uint32_t y,
                                   pawn_t pawn) {
  pawn_t enemy = pawn == AI ? PLAYER : AI;
  int32_t my_score = is_heuristic_win_horizontally(board, x, y, pawn) +
                     is_heuristic_win_vertically(board, x, y, pawn) +
                     is_heuristic_win_left_diagonally(board, x, y, pawn) +
                     is_heuristic_win_right_diagonally(board, x, y, pawn);
  int32_t enemy_score = is_heuristic_win_horizontally(board, x, y, enemy) +
                        is_heuristic_win_vertically(board, x, y, enemy) +
                        is_heuristic_win_left_diagonally(board, x, y, enemy) +
                        is_heuristic_win_right_diagonally(board, x, y, enemy);
  return my_score - enemy_score;
}

static bool is_heuristic_win_horizontally(board_t *board, uint32_t x,
                                          uint32_t y, pawn_t pawn) {
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && x + offset < board->width &&
         (get_pawn(board, x + offset, y) == pawn ||
          EMPTY == get_pawn(board, x + offset, y))) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)x - offset >= 0 &&
         (get_pawn(board, x - offset, y) == pawn ||
          EMPTY == get_pawn(board, x - offset, y))) {
    count++;
    offset++;
  }
  return (count >= 3);
}

static bool is_heuristic_win_vertically(board_t *board, uint32_t x, uint32_t y,
                                        pawn_t pawn) {
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && y + offset < board->height &&
         (get_pawn(board, x, y + offset) == pawn ||
          EMPTY == get_pawn(board, x, y + offset))) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)y - offset >= 0 &&
         (get_pawn(board, x, y - offset) == pawn ||
          EMPTY == get_pawn(board, x, y - offset))) {
    count++;
    offset++;
  }
  return (count >= 3);
}

static bool is_heuristic_win_left_diagonally(board_t *board, uint32_t x,
                                             uint32_t y, pawn_t pawn) {
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && x + offset < board->width &&
         y + offset < board->height &&
         (get_pawn(board, x + offset, y + offset) == pawn ||
          EMPTY == get_pawn(board, x + offset, y + offset))) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && (int32_t)x - offset >= 0 && (int32_t)y - offset >= 0 &&
         (get_pawn(board, x - offset, y - offset) == pawn ||
          EMPTY == get_pawn(board, x - offset, y - offset))) {
    count++;
    offset++;
  }
  return (count >= 3);
}

static bool is_heuristic_win_right_diagonally(board_t *board, uint32_t x,
                                              uint32_t y, pawn_t pawn) {
  uint8_t count = 0;
  uint8_t offset = 1;

  while (offset < 4 && (int32_t)x - offset >= 0 && y + offset < board->height &&
         (get_pawn(board, x - offset, y + offset) == pawn ||
          EMPTY == get_pawn(board, x - offset, y + offset))) {
    count++;
    offset++;
  }
  offset = 1;
  while (offset < 4 && x + offset < board->width && (int32_t)y - offset >= 0 &&
         (get_pawn(board, x + offset, y - offset) == pawn ||
          EMPTY == get_pawn(board, x + offset, y - offset))) {
    count++;
    offset++;
  }
  return (count >= 3);
}
