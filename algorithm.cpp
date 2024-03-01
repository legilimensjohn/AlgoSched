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
  cout << endl;
  cout << "Process    Arrival Time      Burst Time      Waiting Time     Turnaround Time      " << endl;

  for (int i = 0; i < n; i++) {
     cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t";
     cout << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
     totalTurnaroundTime += processes[i].turnaroundTime;
     totalWaitTime += processes[i].waitingTime;
  }

  //Calculate average waiting time and average turnaround time
  totalTurnaroundTime /= (1.0 * n);
  totalWaitTime /= (1.0 * n);

  //Display average waiting time and turnaround time
  cout << endl << endl;
  cout << "\t\tAverage Waiting Time     : " << totalWaitTime << endl;
  cout << "\t\tAverage Turn-Around Time : " << totalTurnaroundTime << endl << endl;
}

//Function for Non-Preemptive Priority Scheduling
void priorityScheduling () {
  int i, j, currentTime = 0;
  int n = 7;
  CustomProcess processes[7];

  //Input process details
  for (i = 0; i < n; i++) {
    cout << "\tEnter the arrival time for Process " << i + 1 << ": ";
        while (!(cin >> processes[i].arrivalTime)) {
            cout << "\tInvalid input. Please enter a valid integer for arrival time: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
    }

    cout << "\tEnter burst time for Process " << i + 1 << "      : ";
        while (!(cin >> processes[i].burstTime)) {
            cout << "\tInvalid input. Please enter a valid integer for burst time: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
    }

    cout << "\Enter priority for Process (Lower # = higher priority) " << i + 1 << ": ";
        while (!(cin >> processes[i].priority)) {
            cout << "\tInvalid input. Please enter a valid integer for priority: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
    }

    processes[i].id = i + 1;
    processes[i].waitingTime = 0;
    processes[i].turnaroundTime = 0;
    cout << endl;
}

//Sort processe based on priority
for (i = 0; i < n - 1; i++) {
  for (j = 0; j < n - i - 1; j++) {
    if (processes[j].priority > processes[j + 1].priority) {
      CustomProcess temp = processes[j];
      processes[j] = processes[j+1];
      processes[j+1] = temp;
    }
  }
}

//Displaying process details for priority scheduling
cout << endl << endl;
cout << setw(10) << "Process" << setw(15) << "Arrival Time" << setw(15) << "Burst Time" << setw(10) << "Priority" << setw(15) << "Finish Time" << setw(20) << "Turnaround Time" << setw(15) << "Waiting Time" << endl;

for(i = 0; i < n; i++) {
  //Waiting for the arrival of the current process
  while (currentTime < processes[i].arrivalTime) {
    currentTime++;
  }

  cout << setw(10) << processes[i].id << setw(15) << processes[i].arrivalTime << setw(15) << processes[i].burstTime << setw(10) << processes[i].priority;
  //Updating waiting and turnaround times for the current process
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;

        cout << setw(15) << currentTime << setw(20) << processes[i].turnaroundTime << setw(15) << processes[i].waitingTime << endl;
}

//Calculating average waiting and turnaround times
float avgWaitingTime = 0, avgTurnaroundTime = 0;
for (i = 0; i < n; i++) {
  avgWaitingTime += processes[i].waitingTime;
  avgTurnaroundTime += processes[i].turnaroundTime;
}
avgWaitingTime /= n;
avgTurnaroundTime /= n;
cout << endl << endl;







