/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_play.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:27:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 11:50:15 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

#include <libft.h>
#include "connect4.h"

static uint32_t count_empty_pawn(board_t *board);
static uint32_t sim_drop_pawn(board_t *board, uint32_t x);
static int32_t ia_backtracking(board_t *board, uint32_t depth, pawn_t pawn);
static uint32_t ai_get_best_column(board_t *board);

void ai_play(board_t *board) {
  drop_pawn(board, ai_get_best_column(board));
  display_grid(board);
}

static uint32_t ai_get_best_column(board_t *board) {
  int32_t best_x = -1;
  int32_t best_score = INT32_MIN;
  for (uint32_t i = 0; i < board->width; i++) {
    uint32_t x = board->col_order[i];
    if (EMPTY != get_pawn(board, x, 0)) {
      continue;
    }
    uint32_t drop = sim_drop_pawn(board, x);
    set_pawn(board, x, drop, board->next_play);
  
    if (check_win(board, x, drop)) {
      board->is_finished = 0;
      best_x = x;
      set_pawn(board, x, drop, EMPTY);
      break;
    }

    int32_t score = -ia_backtracking(board, 0, board->next_play == IA ? PLAYER : IA);
    ft_printf("%d=%d\n", x, score);
    if (score > best_score) {
      best_score = score;
      best_x = x;
    }
    set_pawn(board, x, drop, EMPTY);
  }
  return best_x;
} 

static int32_t ia_backtracking(board_t *board, uint32_t depth, pawn_t pawn) {
  if (0 == count_empty_pawn(board)) {
    return (0);
  } else if (MAX_DEPTH == depth) {
    return get_heuristic_total_score(board, pawn);
  }

  for (uint32_t x = 0 ; x < board->width; x++) {
    if (EMPTY != get_pawn(board, x, 0)) {
      continue;
    }
    uint32_t drop = sim_drop_pawn(board, x);
    set_pawn(board, x, drop, pawn);

    if (check_win(board, x, drop)) {
      int32_t score = count_empty_pawn(board) / 2 + 1;
      board->is_finished = 0;
      set_pawn(board, x, drop, EMPTY);
      return (score);
    } else {
      set_pawn(board, x, drop, EMPTY);
    }
  }

  int32_t best_score = INT32_MIN + 1;
  for (uint32_t i = 0 ; i < board->width; i++) {
    uint32_t x = board->col_order[i];
      if (EMPTY != get_pawn(board, x, 0)) {
        continue;
      }
      uint32_t drop = sim_drop_pawn(board, x);
      set_pawn(board, x, drop, pawn);
      check_win(board, x, drop);
      int32_t score = -ia_backtracking(board, depth + 1, pawn == IA ? PLAYER : IA);
      if (score > best_score) {
        best_score = score;
      }
      set_pawn(board, x, drop, EMPTY);
  }
  return best_score;
}


static uint32_t sim_drop_pawn(board_t *board, uint32_t x) {
  uint32_t y = 0;
  while (y < board->height && EMPTY == get_pawn(board, x, y)) {
    y++;
  }
  return y - 1;
}

static uint32_t count_empty_pawn(board_t *board) {
  return (board->max_pawns - board->played_pawns);
}
