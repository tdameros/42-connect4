# Connect4

Connect4 is a two-player strategy board game where players take turns dropping colored discs into a grid. The goal is to be the first to connect four discs in a row, either horizontally, vertically, or diagonally. In this project, the goal is to implement an AI to play against a human player using the **Minimax algorithm** combined with an **heuristic evaluation function**.

The AI evaluates possible moves and uses the Minimax algorithm to choose the best move, aiming to either win or block the opponent from winning.

## Project Objectives

- Develop an AI capable of playing the Connect4 game against a human player.
- Implement the Minimax algorithm to simulate the AI's decision-making process.
- Create a heuristic evaluation function to assess the quality of a given board state.
- Allow two modes of play: human vs human and human vs AI.
- Implement game mechanics such as alternating turns, move validation, and detecting a winner.

## Getting Started

Compile with: 

```
make animation
```

Run:

```
./connect4
```

Run the game by specifying the grid size (rows x columns):

```
./connect4 <rows> <columns>
```


https://github.com/user-attachments/assets/c24e2c23-b079-4300-b85a-9fead943e726

