/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/07 18:03:16 by ibertran         ###   ########lyon.fr   */
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

int8_t drop_pawn(board_t *board, uint32_t x) {
  if (EMPTY != get_pawn(board, x, 0)) {
    return (-1);
  }
  uint8_t y = 0;
  while (y < board->height && EMPTY == get_pawn(board, x, y)) {
    if ((uint32_t)TIME_TO_DROP / board->height > 5000) {
      set_pawn(board, x, y, board->next_play);
      display_grid(board);
      usleep(TIME_TO_DROP / board->height);
      set_pawn(board, x, y, EMPTY);
    }

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

  display_grid(&board);

  while (board.played_pawns < board.width * board.height &&
         !board.is_finished) {
    if (board.next_play == PLAYER) {
      int8_t play = user_play(&board);
      if (play) {
        deinitialize_board(&board);
        return (play == -1);
      }
    } else {
      ai_play(&board);
    }
  }
  deinitialize_board(&board);
  return 0;
}
