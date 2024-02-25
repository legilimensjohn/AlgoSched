#include <iostream>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

//Maximum number of processes
const int MAX_PROCESSES = 7;

//Process structure to store information about each process
struct CustomProcess {
  int id;  //process ID
  int arrivalTime;   
  int burstTime;
  int waitingTime;
  int turnAround;
  int remainingTime;
  int priority;
};

//Queue for process IDs in Round Robin scheduling
int processQueue [MAX_PROCESSES];
int front = 0, rear = 0;

//Array to store information about each processes
struct CustomProcess processes[MAX_PROCESSES];

