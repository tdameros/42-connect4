/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:22:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/08 20:42:18 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "connect4.h"

void display_grid(board_t *board) {
  static const char *border[] = {"", FG_RED, FG_YELLOW};
  static const char *str[] = {"  ", "🔴", "🟡", "\033[5m🔴\033[0m", "\033[5m🟡\033[0m"};
  char *fg_color[] = {"\e[0m", "🔴 \e[31;1m", "🟡 \e[33;1m"};

  const char  *color = border[board->next_play];

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
  ft_printf("%s┌", color);
  for (uint32_t x = 0; x < board->width * 3 - 1; x++) {
    ft_printf("─");
  }
  ft_printf("┐%s\n", RESET);
  for (uint32_t y = 0; y < board->height; y++) {
    ft_printf("%s│%s", color, RESET);
    for (uint32_t x = 0; x < board->width; x++) {
      if (x != board->width - 1) {
        ft_printf("%s ", str[get_pawn(board, x, y)]);
      } else {
        ft_printf("%s", str[get_pawn(board, x, y)]);
      }
    }
    ft_printf("%s│%s", color, RESET);
    ft_printf("\n");
  }
  ft_printf("%s└", color);
  for (uint32_t x = 0; x < board->width * 3 - 1; x++) {
    ft_printf("─");
  }
  ft_printf("┘%s", RESET);
  ft_printf("\n");
  if (AI == board->next_play) {
    ft_printf("%s IA is thinking...\n", fg_color[board->next_play]);
  }
}

void display_winner(board_t *board) {
  const int32_t len[] = {20, 17};

  if (board->is_finished) {
    if (board->next_play == PLAYER) {
      for (int32_t i = 0; i < ((int32_t)board->width * 2 + (int32_t)board->width - 1 + 2 - len[0]) / 2; i++) {
        ft_printf(" ");
      }
      ft_printf("🟡 %s YELLOW WINS! %s 🟡\n", YELLOW, RESET);
    } else {
      for (int32_t i = 0; i < ((int32_t)board->width * 2 + (int32_t)board->width - 1 + 2 - len[1]) / 2; i++) {
        ft_printf(" ");
      }
      ft_printf("🔴 %s RED WINS! %s 🔴\n", RED, RESET);
    }
  } else {
    ft_printf("🏳️  %s DRAW GAME %s 🏳️\n", BLUE, RESET);
  }
}
