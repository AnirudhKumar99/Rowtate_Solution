#include "Grid.h"
#include <iostream>

using namespace std;

string apply_move(const string &state, const string &move) {
  char type = move[0];
  int idx = move[1] - '1'; // Convert '1'-'5' to 0-4
  int shift = move[3] - '0';

  string res = state;
  if (type == 'R') {
    // Shift a row
    for (int c = 0; c < 5; ++c) {
      res[idx * 5 + ((c + shift) % 5)] = state[idx * 5 + c];
    }
  } else {
    // Shift a column
    for (int r = 0; r < 5; ++r) {
      res[((r + shift) % 5) * 5 + idx] = state[r * 5 + idx];
    }
  }
  return res;
}

vector<string> get_all_moves() {
  vector<string> moves;
  for (char type : {'R', 'C'}) {
    for (int i = 1; i <= 5; ++i) {   // Index 1 to 5
      for (int k = 1; k <= 4; ++k) { // Shift 1 to 4
        moves.push_back(string(1, type) + to_string(i) + "+" + to_string(k));
      }
    }
  }
  return moves;
}

string get_inverse(const string &move) {
  char type = move[0];
  char index = move[1];
  int shift = move[3] - '0';
  int inv_shift = 5 - shift; // e.g., shift of 1 is inverted by a shift of 4
  return string(1, type) + index + "+" + to_string(inv_shift);
}

void print_grid(const string &state) {
  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 5; ++c) {
      cout << state[r * 5 + c] << ' ';
    }
    cout << '\n';
  }
}
