# Rowtate Solver

This is a standalone C++ solver for the grid-based word puzzle game **[Rowtate](https://rowtate.app)**.

## Game Mechanics
The board is a 5x5 grid of uppercase characters. A "Move" consists of shifting an entire row horizontally or an entire column vertically. When letters fall off one edge, they wrap around to the opposite edge.

There are 5 rows and 5 columns. Each can be shifted by 1, 2, 3, or 4 positions.

## Solver
The solver uses a Bidirectional Breadth-First Search (Bi-BFS) algorithm to find the optimal (minimum moves) solution to return a scrambled grid back to its target state.

## Building and Running
To build the solver, run:
```bash
make
```

To run the solver:
```bash
./rowtate_solver
```
