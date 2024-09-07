/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_play.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:24:02 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/07 20:57:33 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "connect4.h"
#include "libft.h"

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
    if (*endptr != '\n' || errno || parse < 0 || parse >= board->width) {
      display_grid(board);
    } else if (drop_pawn(board, parse)) {
      display_grid(board);
      // ft_printf("full row: %s\n",  parse);
      free(gnl);
      return (0);
    };
    free(gnl);
  }
  display_grid(board);
  return (0);
}
