#include "Grid.h"
#include "Solver.h"
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

// Load valid 5-letter uppercase words from the text file
vector<string> load_words(const string &filename) {
  vector<string> words;
  ifstream file(filename);
  string word;
  while (file >> word) {
    if (word.length() == 5) {
      for (char &c : word)
        c = toupper(c);
      words.push_back(word);
    }
  }
  return words;
}

int main() {
  // 1. Initialization & File I/O
  vector<string> words = load_words("words.txt");
  if (words.empty()) {
    cerr << "Warning: words.txt not found or empty. Using default dummy "
            "words.\n";
    words = {"APPLE", "BERRY", "CHERRY", "DIRTY", "EAGLE"};
  }

  // 2. User Input Setup
  int num_target_rows;
  cout << "How many target rows? ";
  cin >> num_target_rows;

  cout << "Which rows are the targets? (1-indexed, space-separated, e.g., '1 "
          "5' or '1 2 4'): ";
  vector<int> target_rows(num_target_rows);
  for (int i = 0; i < num_target_rows; ++i) {
    cin >> target_rows[i];
    target_rows[i]--; // Convert to 0-indexed internally
  }

  int scramble_depth;
  cout << "Enter scramble depth (number of random moves to apply, e.g., 5): ";
  cin >> scramble_depth;

  // 3. Grid Generation (Target State)
  string target_state(25, ' ');
  mt19937 rng(random_device{}());

  vector<bool> is_target_row(5, false);
  for (int r : target_rows) {
    if (r >= 0 && r < 5)
      is_target_row[r] = true;
  }

  uniform_int_distribution<int> word_dist(0, words.size() - 1);
  uniform_int_distribution<int> char_dist(0, 25); // 'A' (0) to 'Z' (25)

  for (int r = 0; r < 5; ++r) {
    if (is_target_row[r]) {
      string word = words[word_dist(rng)];
      for (int c = 0; c < 5; ++c) {
        target_state[r * 5 + c] = word[c];
      }
    } else {
      for (int c = 0; c < 5; ++c) {
        target_state[r * 5 + c] = 'A' + char_dist(rng);
      }
    }
  }

  cout << "\n============================================\n";
  cout << "Target State (Solved Grid):\n";
  print_grid(target_state);

  // 4. Scrambling to Generate Start State
  string start_state = target_state;
  auto available_moves = get_all_moves();
  uniform_int_distribution<int> move_dist(0, available_moves.size() - 1);

  int actual_scramble_moves = 0;
  cout << "\nScramble Moves: ";
  for (int i = 0; i < scramble_depth; ++i) {
    string m = available_moves[move_dist(rng)];
    cout << normalize_move_display(m) << (i == scramble_depth - 1 ? "" : ", ");
    actual_scramble_moves += get_move_cost(m);
    start_state = apply_move(start_state, m);
  }
  cout << "\n(Total scramble cost: " << actual_scramble_moves << " moves)";

  cout << "\n\nStart State (Scrambled Grid):\n";
  print_grid(start_state);
  cout << "============================================\n\n";

  if (start_state == target_state) {
    cout << "The grid is already solved!\n";
    return 0;
  }

  cout << "Solving using Bidirectional BFS...\n";

  SolutionPath result = solve_puzzle(start_state, target_state);

  if (!result.found) {
    cout << "Could not find a valid solution.\n";
    return 0;
  }

  int total_moves = 0;
  for (const string &m : result.moves) {
    total_moves += get_move_cost(m);
  }
  cout << "\nTotal Optimal Moves: " << total_moves << " (across "
       << result.moves.size() << " steps)\n\n";

  for (size_t i = 0; i < result.moves.size(); ++i) {
    cout << "Step " << i + 1 << ": Apply " << result.moves[i] << "\n";
    print_grid(result.states[i]);
    cout << "\n";
  }

  cout << "Puzzle solved optimally!\n";
  return 0;
}
