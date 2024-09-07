/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:22:54 by ibertran          #+#    #+#             */
/*   Updated: 2024/09/07 13:42:02 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include "libft.h"

void display_grid(board_t *board) {
  static const char *str[] = {"  ", "🟡", "🔴"};

  // ft_printf("\033c");

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
}
