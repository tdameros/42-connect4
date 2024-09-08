/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:22:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 19:11:31 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "connect4.h"

void display_grid(board_t *board) {
  static const char *str[] = {"  ", "🔴", "🟡", "\033[5m🔴\033[0m", "\033[5m🟡\033[0m"};

  ft_printf("\033c");

  ft_printf(" ");
  for (uint32_t x = 0; x < board->width; x++) {
    if (get_pawn(board, x, 0) != EMPTY) {
      ft_printf("   ", x % 10);
    } else {
      ft_printf("↓%d ", x % 10);
    }
  }
  ft_printf("\n");
  ft_printf("┌");
  for (uint32_t x = 0; x < board->width * 3 - 1; x++) {
    ft_printf("─");
  }
  ft_printf("┐\n");
  for (uint32_t y = 0; y < board->height; y++) {
    ft_printf("│");
    for (uint32_t x = 0; x < board->width; x++) {
      if (x != board->width - 1) {
        ft_printf("%s ", str[get_pawn(board, x, y)]);
      } else {
        ft_printf("%s", str[get_pawn(board, x, y)]);
      }
    }
    ft_printf("│");
    ft_printf("\n");
  }
  ft_printf("└");
  for (uint32_t x = 0; x < board->width * 3 - 1; x++) {
    ft_printf("─");
  }
  ft_printf("┘");
  ft_printf("\n");
}

void display_winner(board_t *board) {
  if (board->is_finished) {
    if (board->next_play == PLAYER) {
      ft_printf("🟡 %s YELLOW WINS! %s 🟡\n", YELLOW, RESET);
    } else {
      ft_printf("🔴 %s RED WINS! %s 🔴\n", RED, RESET);
    }
  } else {
    ft_printf("🏳️  %s DRAW GAME %s 🏳️\n", BLUE, RESET);
  }

}
