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
    int id; //process ID
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAround;
    int remainingTime;
    int priority;
};

//Queue for process IDs in Round Robin scheduling
int processQueue[MAX_PROCESSES];
int front = 0, rear = 0;

//Array to store information about each processes
struct CustomProcess processes[MAX_PROCESSES];

//Function to add a process to the queue
void enqueue(int id) {
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
void roundRobin(int n, int timeQuantum) {
    float totalWaitTime = 0.0, totalTurnaroundTime
    int time = 0;
    int remainingProcesses = n;
    int currentPosition = -1;
    int localTime = 0;

    //Loop to initialize the queue with processes ariving at time 0
    for (int j = 0; j < n; j++)
        if (processes[j].arrivalTime == time)
            enqueue(j);

    while (remainingProcesses) {
        if (localTime == 0) {
            if (currentPosition != -1)
                enqueue(currentPosition);
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
            if (processes[j].arrivalTime == time)
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
void priorityScheduling() {
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
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }

        //Displaying process details for priority scheduling
        cout << endl << endl;
        cout << setw(10) << "Process" << setw(15) << "Arrival Time" << setw(15) << "Burst Time" << setw(10) << "Priority" << setw(15) << "Finish Time" << setw(20) << "Turnaround Time" << setw(15) << "Waiting Time" << endl;

        for (i = 0; i < n; i++) {
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

        //Display average waiting time and average turnaround time
        cout << "\t\tAverage Waiting Time        : " << avgWaitingTime << endl;
        cout << "\t\tAverage Turn Around Time    : " << avgTurnaroundTime << endl;

        //Function for Shortest Remaining Time First (SRTF)
        void srtfScheduling(int n) {
            int currentTime = 0;
            int completed = 0;
            int shortestRemainingTime = -1;

            //Loop until all processes are completed
            while (completed != n) {
                shortestRemainingTime = -1;
                int minRemainingTime = numeric_limits < int > ::max();

                //Find the process with the shortest remaining time
                for (int i = 0; i < n; i++) {
                    if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < minRemainingTime && processes[i].remainingTime > 0) {
                        shortestRemainingTime = i;
                        minRemainingTime = processes[i].remainingTime;
                    }
                }

                //If no process is ready, move to the next time unit
                if (shortestRemainingTime == -1) {
                    currentTime++;
                } else {
                    //Execute the process for one time unit
                    processes[shortesRemainingTime].remainingTime--;
                    currentTime++;

                    //If the process is completed, update turnaround and waiting times
                    if (processes[shortestRemainingTime].remainingTime == 0) {
                        completed++;
                        processes[shortesReamainingTime].turnaround = currentTime - processes[shortestRemainingTime].arrivalTime;
                        processes[shortestRemainingTime].waitingTime = processes[shortestRemainingTime].turnaroundTime - processes[shortestRemainingTime].burstTime;
                    }
                }
            }

            //Display process details in tabular format outside the loop
            cout << "Process\t\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
            for (int i = 0; i < n; i++) {
                cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
            }

            //Calculate and display average waiting and turnaround times
            float avgWaitingTime = 0, abgturnaroundTime = 0;
            for (int i = 0; i < n; i++) {
                avgWaitingTime += processes[i].waitingTime;
                avgTurnaroundTime += processes[i].turnaroundTime;
            }
            avgWaitingTime /= n;
            avgTurnaroundTime /= n;
            cout << "\n\n"
            //Display average waiting time and average turnaround time
            cout << "\t\tAverage Waiting Time     : " << avgWaitingTime << endl;
            cout << "\t\tAverage Turn-Around Time : " << avgTurnaroundTime << endl << endl;
        }

        //Function for First Come First Served (FCFS) Scheduling
        void fcfsScheduling(int n) {
            //Sort processes based on arrival time for First Come First Serve Scheduling
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                        CustomProcess temp = processes[j];
                        processes[j] = processes[j + 1];
                        processes[j + 1] = temp;
                    }
                }
            }

            int currentTime = 0;

            //Display header for the process details table
            cout << "Process\t\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";

            for (int i = 0; i < n; i++) {
                //Wait for the arrival of the current process
                while (currentTime < processes[i].arrivalTime) {
                    currentTime++;
                }

                //Display process details in tabular format
                cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t";

                //Update waiting and turnaround times for the current process
                processes[i].waitingTime = currentTime - processes[i].arrivalTime;
                currentTime += processes[i].burstTime;
                processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                cout << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
            }

            //Calculate and display average waiting and turnaround times
            float avgWaitingTime = 0, avgTurnaroundTime = 0;
            for (int i = 0; i < n; i++) {
                avgWaitingTime += processes[i].waitingTime;
                avgTurnaroundTime += processes[i].turnaroundTime;
            }
            avgWaitingTime /= n;
            avgTurnaroundTime /= n;
            cout << "\n\n";
            //Display average waiting time and average turnaround time
            cout << "\t\tAverage Waiting Time    : " << avgWaitingTime << endl;
            cout << "\t\tAverage Turn-Around Time: " << avgTurnaroundTime << endl << endl;
        }

        int main() {
            //Variables for user input and control flow
            int choice;
            int timeQuantum;
            char tryAgain;
            system("Color 2"); //Set console text color to green

            do {
                //Display the main menu for scheduling algorithms
                cout << "\n";
                cout << "\t\t|+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++|\n";
                cout << "\t\t|          Welcome to the realm of ALGORITHM SCHEDULING!                      |\n";
                cout << "\t\t|  Kindly choose one of the subsequent approaches for ALGORITHM SCHEDULING.   |\n";
                cout << "\t\t|                                                                             |\n";
                cout << "\t\t|     1. Embark on an enchanting adventure with Round Robin Scheduling (R.R)  |\n";
                cout << "\t\t|     2. Delve into the realm of Non-Preemptive Priority                      |\n";
                cout << "\t\t|     3. Uncover the marvels of Shortest Remaining Time First (S.R.T.F)       |\n";
                cout << "\t\t|     4. Indulge in the elegance of First Come First Served (F.C.F.S)         |\n";
                cout << "\t\t|     5. Exit the program                                                     |\n";
                cout << "\t\t|+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++|\n";
                cout << "\n\n";

                //Prompt user for algorithm choice
                cout << "\t\tPlease indicate your preference by selecting a number from the options provided: ";

                //Validate and get user input for algorithm choice
                while (!(cin >> choice) || choice < 1 || choice > 5) {
                    cin.clear();
                    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                    cout << "\t\t\tApologies, but it seems that the input provided is not valid." << endl;
                    cout << "\t\t\t\tPlease enter a number between 1 and 5: ";
                }

                cout << endl;

                //Execute the chosen algorithm
                switch (choice) {
                case 1:
                    cout << endl << endl;
                    cout << "\t  ROUND ROBIN" << endl;
                    cout << "\t===============" << endl << endl;
                    for (int i = 0; i < 7; i++) {
                        cout << "\tEnter the arrival time for Process " << i + 1 << ": ";
                        while (!(cin >> processes[i].arrivalTime)) {
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            cout << "\tInvalid input. Please enter a valid integer for the arrival time: ";
                        }

                        cout << "\tEnter the burst time for process    " << i + 1 << ": ";
                        while (!(cin >> processes[i].burstTime)) {
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            cout << "\tInvalid input. Please enter a valid integer for the burst time: ";
                        }
                        processes[i].id = i + 1;
                        processes[i].waitingTime = 0;
                        processes[i].turnaroundTime = 0;
                        processes[i].remainingTime = processes[i].int burstTime;
                        cout << endl;
                    }

                    cout << "/tEnter the time quantum: "
                    while (!(cin >> timeQuantum) || timeQuantum <= 0) {
                        cin.clear();
                        cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                        cout << "\tInvalid input. Please enter a valid positive integer for the time quantum: ";
                    }
                    roundRobin(7, timeQuantum);
                    break;

                case 2:
                    cout << endl << endl;
                    cout << "\t   NON-PREEMPTIVE PRIORITY SCHEDULING" << endl;
                    cout << "\t========================================" << endl << endl;
                    priorityScheduling();
                    break;

                case 3:
                    cout << endl << endl;
                    cout << "\t   SHORTEST REMAINING TIME FIRST (SRTF) SCHEDULING" << endl;
                    cout << "\t=====================================================" << endl << endl;
                    for (int i = 0; i < 7; i++) {
                        cout << "\tEnter the arrival time for Process " << i + 1 << ": ";
                        while (!(cin >> processes[i].arrivalTime)) {
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            cout << "\tInvalid input. Please enter a valid integer for the arrival time: ";
                        }

                        cout << "\tEnter the burst time for Process   " << i + 1 << ": ";
                        while (!(cin >> processes[i].burstTime)) {
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            cout << "\tInvalid input. Please enter a valid integer for the burst time: ";
                        }

                        processes[i].id = i + 1;
                        processes[i].waitingTime = 0;
                        processes[i].turnaroundTime = 0;
                        processes[i].remainingTime = processes[i].burstTime;
                        cout << endl;
                    }
                    srtfScheduling(7);
                    break;

                case 4:
                    cout << endl << endl;
                    cout << "\t  FIRST COME FIRST SERVED (FCFS) SCHEDULING" << endl;
                    cout << "\t=============================================" << endl << endl;
                    for (int i = 0; i < 7; i++) {
                        cout << "\tEnter the arrival time for Process " << i + 1 << ": ";
                        while (!(cin >> processes[i].arrivalTime)) {
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            cout << "\tInvalid input. Please enter a valid integer for the arrival time: ";
                        }
                        cout << "\tEnter the burst time for Process   " << i + 1 << ": ";
                        while (!(cin >> processes[i].burstTime)) {
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            cout << "\tInvalid input. Please enter a valid integer for the burst time: ";
                        }
                        processes[i].id = i + 1;
                        processes[i].waitingTime = 0;
                        processes[i].turnaroundTime = 0;
                        processes[i].remainingTime = processes[i].burstTime;
                        cout << endl;
                    }
                    fcfsScheduling(7);
                    break;

                case 5: //Exit the program
                    cout << "\n\tConcluding the program with the utmost elegance. Gratitude is extended!!\n";
                    return 0;

                default:
                    cout << "\tInvalid choice" << endl;
                    break;
                }

                if (choice != 5) {
                    cout << "\tWould you like to give it another shot? (y/n): ";
                    cin >> tryAgain;

                    // Input validation for tryAgain
                    while (cin.fail() || (tryAgain != 'y' && tryAgain != 'Y' && tryAgain != 'n' && tryAgain != 'N')) {
                        cout << "\tInvalid input. Please enter 'y' or 'n': ";
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits < streamsize > ::max(), '\n'); // Discard invalid input
                        cin >> tryAgain;
                    }
                }

                if (tryAgain == 'y' || tryAgain == 'Y') {
                    // Clear screen (for Windows)
                    system("cls");
                }
            } while (tryAgain == 'y' || tryAgain == 'Y');

            while (tryAgain == 'y' || tryAgain == 'Y');

            cout << "\tProgram exiting. Thank you!" << endl;

            return 0;

        }