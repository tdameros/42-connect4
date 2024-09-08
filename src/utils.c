/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:32:21 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 19:00:52 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

pawn_t get_pawn(board_t *board, uint32_t x, uint32_t y) {
  return board->grid[y * board->width + x];
}

void set_pawn(board_t *board, uint32_t x, uint32_t y, pawn_t pawn) {
  board->grid[y * board->width + x] = pawn;
  if (EMPTY == pawn) {
    board->played_pawns--;
  } else if (PLAYER_WIN != pawn && AI_WIN != pawn) {
    board->played_pawns++;
  }
}

uint32_t get_heuristic_factor(board_t *board, uint32_t x, uint32_t y) {
  return (board->heuristic_factor[y * board->width + x]);
}

void set_heuristic_factor(board_t *board, uint32_t x, uint32_t y,
                          int8_t value) {
  board->heuristic_factor[y * board->width + x] = value;
}

int32_t ft_max(int32_t a, int32_t b) { return (a > b ? a : b); }

int32_t ft_min(int32_t a, int32_t b) { return (a < b ? a : b); }
