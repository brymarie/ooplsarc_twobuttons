// ----------------------------
// projects/twobuttons/TwoButtons.c++
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <queue>
#include <utility>

#include "TwoButtons.h"

using namespace std;
typedef pair<int, int> Entry;

// ------------
// twobuttons_read
// ------------

std::pair<int, int> twobuttons_read (const std::string& s) {
  std::istringstream sin(s);
  int n = 0;
  int m = 0;
  sin >> n >> m;
  return std::make_pair(n, m);
}

// ------------
// twobuttons_eval
// ------------

int twobuttons_eval (int n, int m)
{
  // Declare a queue called "q" with elements of "Entry", a pair
  std::queue<Entry> q;

  // This is our visited array
  // For every calculated value the corresponding bit is set
  // If the value is encountered again the result is discarded since it already been queued or processed
  // This can get pretty big - 2*largest value of n (actually 2*n-2?)
  // The "{ }" causes it to be initialized to all false (0)
  // This better done using the c++ vector class - std::vector<bool> and using the built in functions
  bool visited[20000] = { };

  // Bounds check the input values - legals are 1 through 10000 inclusive
  // The problem statement doesn't say what to do for this, so we'll just return 0
  if ((n < 1) || (n > 10000)) {
    return 0;
  }
  if ((m < 1) || (m > 10000)) {
    return 0;
  }

  // Clear the visited array for each new set of input values 
  // How do I do this outside of iterating through it with a loop?
  for (int index = 0; index < 20000; ++index) {
    visited[index] = false;
  }

  // This is the starting point for the calculation
  // start with "n" (passed in from above) and an iteration count of 0
  q.push(std::make_pair(n, 0));

  while (!q.empty()) {

    // get the head of the queue and assign it to "val" (actually a FIFO the way we are using it)
    // we have to explicitly do a pop because grabbing the first entry doesn't do it automatically
    const Entry val = q.front();
    q.pop();

    // Check for termination condition and return the iteration count if we're done
    if (val.first == m) {
      return val.second;
    }

    // Red button - double and inc the interation count
    int red_val = 2 * val.first;
    int red_count = val.second + 1;

    // we only push the red result if the starting value for this iteration is LE to "m"
    // belief is that this is because you go up far faster than down, so it's a long path
    // we also only push if the value hasn't been encountered before
    Entry red_node (red_val, red_count);
    if ((val.first <= m) && (visited[red_val] == false)) {
      q.push(red_node);

      // update the visited array
      visited[red_val] = true;
    //   cout << "queueing red value\n";
    }
    // else {
    //   if (visited[red_val] == true) {
    //     cout << "already encountered red value\n";}
    // }
    
    // Blue button - subtract one and inc the iteration count
    int blue_val = val.first - 1;
    int blue_count = val.second + 1;

    // only push a result that is not negative - negatives break the goofy machine
    // also only push if the value hasn't been encountered before
    Entry blue_node (blue_val, blue_count);
    if ((blue_val >= 0) && (visited[blue_val] == false)) {
      q.push(blue_node);

      // update the visited array
      visited[blue_val] = true;
    //   cout << "queueing blue value\n";
    }
    // else {
    //   if (visited[blue_val] == true) {
    //     cout << "already encountered blue value\n";}
    // }

    // cout << "red_val " << red_val << " blue_val " << blue_val << "\n";
    
    // for (int index = 0; index < 20; ++index) {
    //   cout << "index " << index << " is " << visited[index] << "\n"; 
    // }

  }

  assert (false);
  return 0;
}

// -------------
// twobuttons_print
// -------------

void twobuttons_print (ostream& w, const int answer) {
  w << answer << std::endl;
}

// -------------
// twobuttons_solve
// -------------

void twobuttons_solve (istream& r, ostream& w) {
  std::string s;
  while (getline(r, s)) {
    const Entry val = twobuttons_read(s);
    const int answer = twobuttons_eval(val.first, val.second);
    twobuttons_print(w, answer);
  }
}
