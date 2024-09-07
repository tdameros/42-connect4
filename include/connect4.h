/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:14:58 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/07 16:00:06 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdint.h>
# include <stdbool.h>

# define GRID_MIN_HEIGHT (6)
# define GRID_MIN_WIDTH (7)

#define TIME_TO_DROP (300000)

typedef enum __attribute__((__packed__)) {
    EMPTY = 0,
    PLAYER = 1,
    IA = 2,
} pawn_t;

typedef struct
{
	pawn_t		*grid;
    uint32_t	height;
    uint32_t	width;
    uint32_t	played_pawns;
	pawn_t		next_play;
	bool		is_finished;
}	board_t;

pawn_t get_pawn(board_t *board, uint32_t x, uint32_t y);
void set_pawn(board_t *board, uint32_t x, uint32_t y, pawn_t pawn);

int8_t	parse_arguments(int argc, char **argv, board_t *board);
void    deinitialize_board(board_t *board);
void	display_grid(board_t *board);

#endif