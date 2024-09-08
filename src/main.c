/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:47:00 by tdameros          #+#    #+#             */
/*   Updated: 2024/09/08 18:57:12 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "libft.h"

#include "connect4.h"

int main(int argc, char **argv) {
  board_t board = (board_t){0};
  
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
  display_winner(&board);
  deinitialize_board(&board);
  return 0;
}
