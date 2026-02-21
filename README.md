# Rowtate Solver

This is a standalone C++ solver for the grid-based word puzzle game **[Rowtate](https://rowtate.app)**.

## Game Mechanics
The board is a 5x5 grid of uppercase characters. A "Move" consists of shifting an entire row horizontally or an entire column vertically. When letters fall off one edge, they wrap around to the opposite edge.

There are 5 rows and 5 columns. Each can be shifted by 1, 2, 3, or 4 positions.

## Solver
The solver uses a Bidirectional Breadth-First Search (Bi-BFS) algorithm to find the optimal (minimum moves) solution to return a scrambled grid back to its target state.

### Seeking Better Solutions!
While the Bi-BFS algorithm guarantees finding the optimal shortest path for any scramble, the 5x5 grid's branching factor is quite large (40 possible moves per state). If you're an algorithmic wizard and have ideas for an *A\** heuristic, pattern databases, optimizations, or an entirely different approach that can solve deep scrambles faster or with less memory footprint, **Pull Requests are highly encouraged!**

## Building and Running
To build the solver, run:
```bash
make
```

To run the solver:
```bash
./rowtate_solver
```
