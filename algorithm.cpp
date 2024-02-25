#include <iostream>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_PROCESSES = 7;

struct CustomProcess {
  int id;
  int arrivalTime;
  int burstTime;
  int waitingTime;
  int turnAround;
  int remainingTime;
  int priority;
}
