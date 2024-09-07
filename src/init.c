/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:27:13 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/07 16:03:49 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "connect4.h"
#include "libft.h"

static int8_t initialize_board(board_t *board, uint32_t height, uint32_t width);

int8_t parse_arguments(int argc, char **argv, board_t *board) {
  if (argc == 1) {
    return (initialize_board(board, GRID_MIN_HEIGHT, GRID_MIN_WIDTH));
  } else if (argc == 3) {
    char *endptr;
    long height;
    long width;

    errno = 0;
    height = ft_strtol(argv[1], &endptr);
    if (*endptr || errno || height < GRID_MIN_HEIGHT || height >= UINT32_MAX) {
      ft_dprintf(STDERR_FILENO, "error: %s: Invalid [ROWS] argument\n",
                 argv[1]);
      return (-1);
    }
    width = ft_strtol(argv[2], &endptr);
    if (*endptr || errno || width < GRID_MIN_WIDTH || width >= UINT32_MAX) {
      ft_dprintf(STDERR_FILENO, "error: %s: Invalid [COLS] argument\n",
                 argv[2]);
      return (-1);
    }
    return (initialize_board(board, height, width));
  }
  ft_dprintf(STDERR_FILENO,
             "error: Invalid arguments\nusage: ./connect4 [ROWS] [COLS]\n");
  return (-1);
}

static int8_t initialize_board(board_t *board, uint32_t height,
                               uint32_t width) {
  srand(time(NULL));
  if (NULL == board) {
    ft_dprintf(STDERR_FILENO, "error: malloc() failure\n");
    return -1;
  }
  board->grid = malloc(height * width * sizeof(*board->grid));
  if (NULL == board->grid) {
    return -1;
  }
  for (uint32_t i = 0; i < height * width; i++) {
    board->grid[i] = EMPTY;
  }
  board->height = height;
  board->width = width;
  board->played_pawns = 0;
  board->next_play = rand() % 2 ? PLAYER : IA;
  board->is_finished = 0;
  return 0;
}

void deinitialize_board(board_t *board) {
  free(board->grid);
  board->height = 0;
  board->width = 0;
  board->played_pawns = 0;
}
