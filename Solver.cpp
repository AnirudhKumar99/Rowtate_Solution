#include "Solver.h"
#include "Grid.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

// Struct to keep track of the BFS path
struct ParentInfo {
  string parent;
  string move_from_parent;
  int dist; // distance from the respective start node
};

SolutionPath solve_puzzle(const string &start_state,
                          const string &target_state) {
  SolutionPath result;
  result.found = false;

  if (start_state == target_state) {
    result.found = true;
    return result;
  }

  auto available_moves = get_all_moves();

  // 5. The Solver (Bidirectional BFS)
  unordered_map<string, ParentInfo> f_visited;
  unordered_map<string, ParentInfo> b_visited;

  queue<string> f_q;
  queue<string> b_q;

  // Initialize forward search
  f_q.push(start_state);
  f_visited[start_state] = {"", "", 0};

  // Initialize backward search
  b_q.push(target_state);
  b_visited[target_state] = {"", "", 0};

  bool found = false;
  string best_intersection = "";
  int best_path_len = 1e9; // Keep track of best shortest path

  // Evaluate alternating levels, prioritizing the smaller queue frontier
  while (!f_q.empty() && !b_q.empty() && !found) {
    if (f_q.size() <= b_q.size()) {
      // Expand one complete level of forward BFS frontier
      int level_size = f_q.size();
      for (int i = 0; i < level_size; ++i) {
        string curr = f_q.front();
        f_q.pop();
        int curr_dist = f_visited[curr].dist;

        for (const auto &move : available_moves) {
          string next_state = apply_move(curr, move);

          // If intersection is found during forward propagation...
          if (b_visited.count(next_state)) {
            int path_len = curr_dist + 1 + b_visited[next_state].dist;
            if (path_len < best_path_len) {
              best_path_len = path_len;
              best_intersection = next_state;
            }
            if (!f_visited.count(next_state))
              f_visited[next_state] = {curr, move, curr_dist + 1};
            found = true;
          }

          if (!f_visited.count(next_state)) {
            f_visited[next_state] = {curr, move, curr_dist + 1};
            f_q.push(next_state);
          }
        }
      }
    } else {
      // Expand one complete level of backward BFS frontier
      int level_size = b_q.size();
      for (int i = 0; i < level_size; ++i) {
        string curr = b_q.front();
        b_q.pop();
        int curr_dist = b_visited[curr].dist;

        for (const auto &move : available_moves) {
          string next_state = apply_move(curr, move);

          // If intersection is found during backward propagation...
          if (f_visited.count(next_state)) {
            int path_len = curr_dist + 1 + f_visited[next_state].dist;
            if (path_len < best_path_len) {
              best_path_len = path_len;
              best_intersection = next_state;
            }
            if (!b_visited.count(next_state))
              b_visited[next_state] = {curr, move, curr_dist + 1};
            found = true;
          }

          if (!b_visited.count(next_state)) {
            b_visited[next_state] = {curr, move, curr_dist + 1};
            b_q.push(next_state);
          }
        }
      }
    }
  }

  if (!found) {
    return result; // returning empty result with found = false
  }

  result.found = true;

  // Trace backward from intersection to Start State using forward map
  vector<string> f_path_moves;
  vector<string> f_path_states;
  string curr = best_intersection;
  while (curr != start_state) {
    f_path_moves.push_back(f_visited[curr].move_from_parent);
    f_path_states.push_back(curr);
    curr = f_visited[curr].parent;
  }
  reverse(f_path_moves.begin(), f_path_moves.end());
  reverse(f_path_states.begin(), f_path_states.end());

  // Trace backward from intersection to Target State using backward map
  vector<string> b_path_moves;
  vector<string> b_path_states;
  curr = best_intersection;
  while (curr != target_state) {
    string move_to_curr = b_visited[curr].move_from_parent;
    // Revert the action to move closer towards the Target State
    string inv_move = get_inverse(move_to_curr);

    b_path_moves.push_back(inv_move);
    curr = b_visited[curr].parent;
    b_path_states.push_back(curr);
  }
  // Backward reconstruction naturally yields correct path order, no string
  // reversal needed

  // Combine reconstructed sequences
  result.moves.insert(result.moves.end(), f_path_moves.begin(),
                      f_path_moves.end());
  result.moves.insert(result.moves.end(), b_path_moves.begin(),
                      b_path_moves.end());

  result.states.insert(result.states.end(), f_path_states.begin(),
                       f_path_states.end());
  result.states.insert(result.states.end(), b_path_states.begin(),
                       b_path_states.end());

  return result;
}
