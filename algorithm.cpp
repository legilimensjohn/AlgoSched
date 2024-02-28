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

//Function to add a process to the queue
void enqueue (int id) {
    processQueue[rear] = id;
    rear = (rear + 1) % MAX_PROCESSES;
}

//Function to remove and return a process from the queue
int dequeue() {
    if (front == rear)
        return -1;
    int returnPosition = processQueue[front];
    front = (front + 1) % MAX_PROCESSES;
    return returnPosition;
}

//Function to perform Round Robin scheduling
void roundRobin (int n, int timeQuantum) {
    float totalWaitTime = 0.0, totalTurnaroundTime
    int time = 0;
    int remainingProcesses = n;
    int currentPosition = -1;
    int localTime = 0; 
  
  //Loop to initialize the queue with processes ariving at time 0
  for (int j = 0; j < n; j++)
    if (processes[j].arrivalTime == time)
      enqueue (j);

  while (remainingProcesses) {
    if (localTime == 0) {
      if (currentPosition != -1)
        enqueue (currentPosition);
      currentPosition = dequeue();
    }

    //Loop through processes and update waiting and turnaround times
    for (int i = 0; i < n; i++) {
       if (processes[i].arrivalTime > time)
                continue;
            if (i == currentPosition)
                continue;
            if (processes[i].remainingTime == 0)
                continue;
            processes[i].waitingTime++;
            processes[i].turnaroundTime++;
    }

    //Execution of the current process
    if (currentPosition != -1) {
      processes[currentPosition].remainingTime--;
      processes[currentPosition].turnaroundTime++;
      if (processes[currentPosition].remainingTime == 0) {
        remainingProcesses--;
        localTime = -1;
        currentPosition = -1;
      }
    } else
      localTime = -1;

    time++;
    localTime = (localTime + 1) % timeQuantum;

    //Loop for enqueue processes arriving at the current time
    for (int j = 0; j < n; j++)
      if (processes [j].arrivalTime == time)
        enqueue(j);
  }

  //Displaying process details after completion of all processes
}










