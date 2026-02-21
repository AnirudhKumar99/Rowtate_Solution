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

  int shift = 0;
  char sign = move[2];
  if (sign == '+') {
    shift = move[3] - '0';
  } else if (sign == '-') {
    shift = -(move[3] - '0');
  }

  // To invert a move, simply negate its shift
  int inv_shift = -shift;

  string res_sign = inv_shift > 0 ? "+" : "-";
  return string(1, type) + index + res_sign + to_string(abs(inv_shift));
}

// Helper to normalize the move string so that +3 becomes -2, +4 becomes -1 for
// display
string normalize_move_display(const string &move) {
  char type = move[0];
  char index = move[1];
  int shift = move[3] - '0';
  if (move[2] == '-')
    shift = -shift;

  // Convert positive shifts > 2 to equivalent negative shifts
  // e.g. a shift of +4 is equal to -1
  // e.g. a shift of +3 is equal to -2
  // Modulo math to get it into the range [-2, 2]
  int norm_shift = shift % 5;
  if (norm_shift > 2)
    norm_shift -= 5;
  if (norm_shift < -2)
    norm_shift += 5;

  string sign = norm_shift > 0 ? "+" : "-";
  return string(1, type) + index + sign + to_string(abs(norm_shift));
}

// Helper to compute actual cost of a move
int get_move_cost(const string &move) {
  int shift = move[3] - '0';
  if (move[2] == '-')
    shift = -shift;

  int norm_shift = shift % 5;
  if (norm_shift > 2)
    norm_shift -= 5;
  if (norm_shift < -2)
    norm_shift += 5;

  return std::abs(norm_shift);
}

void print_grid(const string &state) {
  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 5; ++c) {
      cout << state[r * 5 + c] << ' ';
    }
    cout << '\n';
  }
}
