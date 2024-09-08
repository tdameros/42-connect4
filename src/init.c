/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:27:13 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 18:57:34 by ibertran         ###   ########lyon.fr   */
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
    return -1;
  }
  board->grid = malloc(width * height * sizeof(*board->grid));
  board->col_order = malloc(width * sizeof(*board->col_order));
  board->heuristic_factor = malloc(width * height * sizeof(*board->heuristic_factor));
  if (NULL == board->grid
    || NULL == board->col_order
    || NULL == board->heuristic_factor) {
      free(board->grid);
      free(board->col_order);
      free(board->heuristic_factor);
      ft_dprintf(STDERR_FILENO, "error: malloc() failure\n");
      return -1;
  }

  for (uint32_t i = 0; i < width * height; i++) {
    board->grid[i] = EMPTY;
  }

  board->height = height;
  board->width = width;
  int32_t middle = board->width / 2;
  int32_t left_index = middle - 1;
  int32_t right_index = middle + 1;
  uint32_t index = 1;
  board->col_order[0] = middle;
  while (left_index >= 0 || right_index < (int32_t)board->width) {
    if (left_index >= 0) {
      board->col_order[index] = left_index;
      left_index--;
      index++;
    }
    if (right_index < (int32_t)board->width) {
      board->col_order[index] = right_index;
      right_index++;
      index++;
    }
  }

  for (uint32_t y = 0; y < board->height; y++) {
    for (uint32_t x = 0; x < board->width; x++) {
      set_heuristic_factor(board, x, y, get_position_score(board, x, y));
    }
  }
  board->played_pawns = 0;
  board->max_pawns = width * height;
  board->next_play = rand() % 2 ? PLAYER : AI;
  board->is_finished = false;
  return 0;
}

void deinitialize_board(board_t *board) {
  free(board->grid);
  free(board->col_order);
  free(board->heuristic_factor);
  board->height = 0;
  board->width = 0;
  board->played_pawns = 0;
  board->max_pawns = 0;
  board->is_finished = false;
}
