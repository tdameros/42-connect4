/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_play.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:27:45 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 02:05:36 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

#include <libft.h>
#include "connect4.h"

static uint32_t count_empty_pawn(board_t *board);
static uint32_t sim_drop_pawn(board_t *board, uint32_t x);
static int32_t ia_backtracking(board_t *board, uint32_t depth, goal_t player);

void ai_play(board_t *board) {
  int32_t best_x = -1;
  int32_t best_score = INT32_MIN;
  for (uint32_t x = 0; x < board->width; x++) {
    if (EMPTY != get_pawn(board, x, 0)) {
      continue;
    }
    uint32_t drop = sim_drop_pawn(board, x);
    set_pawn(board, x, drop, board->next_play);
    board->played_pawns++;
    if (check_win(board, x, drop)) {
      set_pawn(board, x, drop, EMPTY);
      board->is_finished = 0;
      best_x = x;
      break;
    }

    int32_t score = ia_backtracking(board, 0, WIN);
    ft_printf("col%d->%d\n", x, score);
    if (score > best_score) {
      best_score = score;
      best_x = x;
    }

    set_pawn(board, x, drop, EMPTY);
    board->played_pawns--;
    }

  if (drop_pawn(board, best_x) == -1)
  {
    while (drop_pawn(board, rand() % board->width))
      ;
    display_grid(board);
    ft_printf("AI Played random...\n");
  }
  else 
    display_grid(board);
}

#include <unistd.h>

static int32_t ia_backtracking(board_t *board, uint32_t depth, goal_t goal) {
  // ft_printf("DEPTH=%d...\n", depth);
  // usleep(250000);
  // display_grid(board);
  if (0 == count_empty_pawn(board)) {
    return (0);
  } else if (MAX_DEPTH == depth) {
    // ft_printf("heuristic!\n");
    return (rand() % 10 - 5); // to replace with heuristic function
  } else if (board->is_finished) {
    board->is_finished = false;
    return (count_empty_pawn(board) / 2 + 1) * goal;
  }

  int32_t best_score = INT_MAX * -goal;
  for (uint32_t x = 0 ; x < board->width; x++) {
    if (EMPTY != get_pawn(board, x, 0)) {
      continue;
    }
    uint32_t drop = sim_drop_pawn(board, x);
    set_pawn(board, x, drop, WIN == goal ? PLAYER : IA);
    board->played_pawns++;
    check_win(board, x, drop);
      // ft_printf("WIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");


    int32_t score = ia_backtracking(board, depth + 1, -goal);
    // ft_printf("col%d->%d\n", x, score);
    if (WIN == goal) {
      best_score = best_score > score ? best_score: score;
    } else {
      best_score = best_score > score ? score: best_score;
    }

    set_pawn(board, x, drop, EMPTY);
    board->played_pawns--;
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
