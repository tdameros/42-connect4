/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_play.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:24:02 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 19:05:51 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

#include "connect4.h"

int8_t user_play(board_t *board) {
  uint32_t played = board->played_pawns;
  char *color[] = {"\e[0m", "\e[33m", "\e[31m"};
  char *gnl;
  char *endptr;

  while (played == board->played_pawns) {
    ft_printf("%sYour turn: %s", color[board->next_play], *color);
    if (get_next_line(STDIN_FILENO, &gnl)) {
      return (-1);
    }
    if (!gnl) {
      ft_printf("\n");
      return (1);
    }
    errno = 0;
    long parse = ft_strtol(gnl, &endptr);
    ft_printf("%d\n", parse);
    if (endptr <= gnl || *endptr != '\n' || errno || parse < 0 ||
        parse >= board->width) {
      display_grid(board);
      ft_printf("invalid input!\n");
    } else if (drop_pawn(board, parse)) {
      display_grid(board);
      ft_printf("invalid input!\n");
      free(gnl);
      return (0);
    };
    free(gnl);
  }
  display_grid(board);
  return (0);
}

int8_t drop_pawn(board_t *board, uint32_t x) {
  if (EMPTY != get_pawn(board, x, 0)) {
    return (-1);
  }
  uint8_t y = 0;
  while (y < board->height && EMPTY == get_pawn(board, x, y)) {
    #ifdef ANIMATION
    if ((uint32_t)TIME_TO_DROP / board->height > 5000) {
      set_pawn(board, x, y, board->next_play);
      display_grid(board);
      usleep(TIME_TO_DROP / board->height);
      set_pawn(board, x, y, EMPTY);
    }
    #endif
    y++;
  }
  set_pawn(board, x, y - 1, board->next_play);
  check_win(board, x, y - 1, false);
  if (PLAYER == board->next_play) {
    board->next_play = AI;
  } else {
    board->next_play = PLAYER;
  }
  return (0);
}