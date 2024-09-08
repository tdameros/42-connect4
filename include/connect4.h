/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:14:58 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 19:03:19 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdint.h>
# include <stdbool.h>

# define GRID_MIN_HEIGHT (6) // 6
# define GRID_MIN_WIDTH (7) // 7
# define MIN_DEPTH (2)

# define RED "\e[41;1m"
# define YELLOW "\e[43;1m"
# define BLUE "\e[44;1m"
# define FLASHING "\033[5m"
# define RESET "\e[0;m"

#define TIME_TO_DROP (200000)

typedef enum __attribute__((__packed__)) {
  EMPTY = 0,
  PLAYER = 1,
  AI = 2,
  PLAYER_WIN = 3,
  AI_WIN = 4
} pawn_t;

typedef struct {
  pawn_t *grid;
  uint8_t *heuristic_factor;
  uint32_t height;
  uint32_t width;
  uint32_t played_pawns;
  uint32_t max_pawns;
  pawn_t next_play;
  bool is_finished;
  uint32_t *col_order;


} board_t;


uint32_t get_position_score(board_t *board, uint32_t x, uint32_t y);

pawn_t get_pawn(board_t *board, uint32_t x, uint32_t y);
void set_pawn(board_t *board, uint32_t x, uint32_t y, pawn_t pawn);
bool check_win(board_t *board, uint32_t x, uint32_t y, bool is_simulation);

int8_t parse_arguments(int argc, char **argv, board_t *board);
void deinitialize_board(board_t *board);
void display_grid(board_t *board);

void ai_play(board_t *board);
int8_t user_play(board_t *board);
int8_t drop_pawn(board_t *board, uint32_t x);
void display_winner(board_t *board);

int32_t get_heuristic_total_score(board_t *board, pawn_t pawn);

// UTILS
int32_t ft_max(int32_t a, int32_t b);
int32_t ft_min(int32_t a, int32_t b);
pawn_t get_pawn(board_t *board, uint32_t x, uint32_t y);
void set_pawn(board_t *board, uint32_t x, uint32_t y, pawn_t pawn);
uint32_t get_heuristic_factor(board_t *board, uint32_t x, uint32_t y);
void set_heuristic_factor(board_t *board, uint32_t x, uint32_t y, int8_t value);

#endif