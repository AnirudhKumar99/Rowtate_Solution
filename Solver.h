#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <vector>

struct SolutionPath {
  bool found;
  std::vector<std::string> moves;
  std::vector<std::string> states;
};

// Solves the Rowtate puzzle and returns the shortest sequence
// of moves (and states) to transition from start_state natively to target_state
SolutionPath solve_puzzle(const std::string &start_state,
                          const std::string &target_state);

#endif // SOLVER_H
