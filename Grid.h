#ifndef GRID_H
#define GRID_H

#include <string>
#include <vector>

// Applies a move (e.g., "R1+2", "C3+1") to the 1D string state
std::string apply_move(const std::string &state, const std::string &move);

// Generates all 40 possible valid moves for the 5x5 grid
std::vector<std::string> get_all_moves();

// Gets the inverse move for path reconstruction
std::string get_inverse(const std::string &move);

// Normalizes the move string so that +3 becomes -2, +4 becomes -1 for display
std::string normalize_move_display(const std::string &move);

// Helper to compute actual cost of a move
int get_move_cost(const std::string &move);

// Pretty prints the 5x5 grid to standard output
void print_grid(const std::string &state);

#endif // GRID_H
