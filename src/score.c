#include <stdint.h>
#include "connect4.h"
static uint32_t calculate_score_horizontally(board_t *board, uint32_t x, uint32_t y);
static uint32_t calculate_score_vertically(board_t *board, uint32_t x, uint32_t y);
static uint32_t calculate_score_diagonally_right(board_t *board, uint32_t x, uint32_t y);
static uint32_t calculate_score_diagonally_left(board_t *board, uint32_t x, uint32_t y);

uint32_t get_position_score(board_t *board, uint32_t x, uint32_t y) {
    return (calculate_score_horizontally(board, x, y) + calculate_score_vertically(board, x, y) + calculate_score_diagonally_left(board, x, y) + calculate_score_diagonally_right(board, x, y));
}

static uint32_t calculate_score_horizontally(board_t *board, uint32_t x, uint32_t y) {
    uint32_t right = board->width - x - 1;
    uint32_t left = x;
    (void) y;

    if (right + left >= 3) {
        return (ft_min(right, left));
    }
    return 0;
}

static uint32_t calculate_score_vertically(board_t *board, uint32_t x, uint32_t y) {
    uint32_t down = board->height - y - 1;
    uint32_t up = y;
    (void) x;

    if (down + up >= 3) {
        return (ft_min(down, up));
    }
    return 0;
}

static uint32_t calculate_score_diagonally_left(board_t *board, uint32_t x, uint32_t y) {
    uint32_t right = board->width - x - 1;
    uint32_t left = x;
    uint32_t down = board->height - y - 1;
    uint32_t up = y;
    uint32_t up_left = ft_min(left, up);
    uint32_t down_right = ft_min(right, down);

    if (up_left + down_right >= 3) {
        return (ft_min(up_left, down_right));
    }
    return 0;
}

static uint32_t calculate_score_diagonally_right(board_t *board, uint32_t x, uint32_t y) {
    uint32_t right = board->width - x - 1;
    uint32_t left = x;
    uint32_t down = board->height - y - 1;
    uint32_t up = y;
    uint32_t up_right = ft_min(right, up);
    uint32_t down_left = ft_min(left, down);

    if (up_right + down_left >= 3) {
        return (ft_min(up_right, down_left));
    }
    return 0;
}