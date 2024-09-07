/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:14:58 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/07 13:34:04 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECT4_H
# define CONNECT4_H

# include <stdint.h>
# include <stdbool.h>

# define GRID_MIN_RAWS 6
# define GRID_MIN_COLS 7

typedef enum {
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
inline void set_pawn(board_t *board, uint32_t x, uint32_t y, pawn_t pawn);

void	display_grid(board_t *board);

#endif