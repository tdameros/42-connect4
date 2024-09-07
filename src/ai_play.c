/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_play.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:27:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/07 21:40:51 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

#include <libft.h>
#include "connect4.h"

static uint32_t count_empty_pawn(board_t *board);
static uint32_t sim_drop_pawn(board_t *board, uint32_t x);
static uint32_t ia_get_column(board_t *board);
static int32_t ia_backtracking(board_t *board, uint32_t depth, pawn_t player);

void ai_play(board_t *board) {
  if (drop_pawn(board, ia_get_column(board)) == -1)
  {
    while (drop_pawn(board, rand() % board->width))
      ;
    display_grid(board);
    ft_printf("AI Played random...\n");
  }
  else 
    display_grid(board);
}

static uint32_t ia_get_column(board_t *board) {
  uint32_t best_column = 0;
  uint32_t best_score = INT_MIN;
  for (uint32_t y = 0; y < board->width; y++) {
    uint32_t new_score = ia_backtracking(board, 0, IA);
    if (new_score > best_score) {
      best_column = y;
      best_score = new_score;
    }
  }
  return best_column;
}

// TODO: calculer match null
static int32_t ia_backtracking(board_t *board, uint32_t depth, pawn_t player){
  (void) depth;
  if (board->is_finished) {
    board->is_finished = 0;
    uint32_t score = 0;
    if (PLAYER == board->next_play) {
      score = count_empty_pawn(board) / 2 + 1;
    } else {
      score = count_empty_pawn(board) / 2 * -1 - 1;
    }
    return (score);
  }
  uint32_t current_score = player == IA ? INT_MIN: INT_MAX;

  for (uint32_t x = 0 ; x < board->width; x++) {
    if (x < board->width && EMPTY == get_pawn(board, x, 0)) {
      uint32_t drop = sim_drop_pawn(board, x);
      set_pawn(board, x, drop, player);
      check_win(board, x, drop);
      uint32_t new_score = ia_backtracking(board, x + 1, PLAYER == player ? IA : PLAYER);
      if (player == IA) {
        current_score = current_score > new_score ? current_score: new_score;
      } else {
        current_score = current_score > new_score ? new_score: current_score;
      }
      set_pawn(board, x, drop, EMPTY);
    }
  }
  return current_score;
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
