/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_play.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:27:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 23:06:25 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

static uint32_t count_empty_pawn(board_t *board);
static uint32_t sim_drop_pawn(board_t *board, uint32_t x);
static int32_t minimax(board_t *board, uint32_t depth, pawn_t pawn,
                       int32_t alpha, int32_t beta, pawn_t maximize);
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

    if (check_win(board, x, drop, true)) {
      board->is_finished = 0;
      best_x = x;
      set_pawn(board, x, drop, EMPTY);
      break;
    }
    int32_t score = -minimax(board, ft_max(MIN_DEPTH, 77 / board->width),
                             board->next_play == AI ? PLAYER : AI, INT32_MIN,
                             INT32_MAX, board->next_play);
    if (score > best_score) {
      best_score = score;
      best_x = x;
    }
    set_pawn(board, x, drop, EMPTY);
  }
  return best_x;
}

static int32_t minimax(board_t *board, uint32_t depth, pawn_t pawn,
                       int32_t alpha, int32_t beta, pawn_t maximize) {
  if (0 == count_empty_pawn(board)) {
    return (0);
  } else if (0 == depth) {
    return get_heuristic_total_score(board, pawn);
  }

  for (uint32_t x = 0; x < board->width; x++) {
    if (EMPTY != get_pawn(board, x, 0)) {
      continue;
    }
    uint32_t drop = sim_drop_pawn(board, x);
    set_pawn(board, x, drop, pawn);

    if (check_win(board, x, drop, true)) {
      int32_t score = count_empty_pawn(board) / 2 + 1;
      board->is_finished = 0;
      set_pawn(board, x, drop, EMPTY);
      return (score);
    } else {
      set_pawn(board, x, drop, EMPTY);
    }
  }

  int32_t best_score = INT32_MIN + 1;
  for (uint32_t i = 0; i < board->width; i++) {
    uint32_t x = board->col_order[i];
    if (EMPTY != get_pawn(board, x, 0)) {
      continue;
    }
    uint32_t drop = sim_drop_pawn(board, x);
    set_pawn(board, x, drop, pawn);
    check_win(board, x, drop, false);
    int32_t score = -minimax(board, depth - 1, pawn == AI ? PLAYER : AI, alpha,
                             beta, maximize);
    best_score = ft_max(best_score, score);
    if (maximize == pawn) {
      alpha = ft_max(alpha, best_score);
    } else {
      beta = ft_min(beta, -best_score);
    }
    set_pawn(board, x, drop, EMPTY);
    if (beta <= alpha) break;
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
