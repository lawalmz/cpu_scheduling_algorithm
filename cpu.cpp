/*

Note that to compile the project you have to use  "g++ -std=c++11 cpu.cpp -o cpu" because the
compiler is configured to use an older version of C++ (pre-C++11) where range-based for loops are not supported


*/

#include <iostream>
#include <fstream>
#include <limits>
#include <string>

using namespace std;

struct Job
{
    int burstTime;
    int arrivalTime;
    int priority;
    int waiting_time;
    Job *next;
};

void addJob(Job *&head, int burstTime, int arrivalTime, int priority)
{

    Job *newJob = new Job{burstTime, arrivalTime, priority, 0, nullptr};

    if (head == nullptr)
    {
        head = newJob;
    }
    else
    {
        Job *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newJob;
    }
}

// Function to print the linked list to test if is working
void printLinkedList(const Job *head)
{
    const Job *current = head;
    while (current != nullptr)
    {
        cout << "Burst Time: " << current->burstTime
             << ", Arrival Time: " << current->arrivalTime
             << ", Priority: " << current->priority << endl;
        current = current->next;
    }
}

// freeLinkedList Function to free the memory allocated for the linked list
void freeLinkedList(Job *&head)
{
    while (head != nullptr)
    {
        Job *temp = head;
        head = head->next;
        delete temp;
    }
}

// Function to load jobs from a file into a linked list
void loadJobsFromFile(const char *inputFile, Job *&head)
{
    ifstream inputFileStream(inputFile);
    if (inputFileStream.is_open())
    {
        int burst, arrival, priority;
        char delimiter;
        while (inputFileStream >> burst >> delimiter >> arrival >> delimiter >> priority)
        {
            addJob(head, burst, arrival, priority);
        }

        inputFileStream.close();
    }
    else
    {
        cerr << "Unable to open input file." << endl;
    }
}

void FCFS(Job *head, const char *outputFile)
{
    float totalWaitingTime = 0;
    int processCount = 0;
    ofstream myfile(outputFile, ios_base::app);
    myfile << "\n==============================================\n"
           << endl;
    myfile << "Scheduling Method: First Come First Serve" << endl;
    myfile << "Process Waiting Times:\n"
           << endl;

    int currentTime = 0;
    Job *current = head;

    while (current != nullptr)
    {
        current->waiting_time = max(0, currentTime - current->arrivalTime);
        totalWaitingTime += current->waiting_time;
        processCount++;

        myfile << "P" << processCount << ": " << current->waiting_time << " ms" << endl;

        currentTime += current->burstTime;
        current = current->next;
    }

    myfile << "\nAverage Waiting Time: " << totalWaitingTime / processCount << " ms" << endl;

    cout << "FCFS is Successfully calculated :)" << endl;
}

void ShowResult(const char *outputFile)
{
    ifstream file(outputFile);

    if (file.is_open())
    {
        string line;
        cout << "\nBelow are the result:\n"
             << endl;

        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
    else
    {
        cerr << "Unable to open output file." << endl;
    }
}

Job *sortJobsByArrivalAndBurstTime(Job *head)
{
    if (head == nullptr || head->next == nullptr)
    {

        return head;
    }

    for (Job *i = head; i != nullptr; i = i->next)
    {

        Job *lastSorted = nullptr;

        for (Job *j = head; j != lastSorted && j->next != nullptr; j = j->next)
        {

            if (j->next != nullptr &&
                (j->arrivalTime > j->next->arrivalTime ||
                 (j->arrivalTime == j->next->arrivalTime && j->burstTime > j->next->burstTime)))
            {

                if (j == head)
                {

                    head = j->next;
                    j->next = head->next;
                    head->next = j;
                }
                else
                {

                    Job *temp = j->next;
                    j->next = temp->next;
                    temp->next = j;
                    lastSorted->next = temp;
                }
            }
            lastSorted = j;
        }
    }

    return head;
}

void SJFNonPreemptive(Job *head, const char *outputFile)
{
    float totalWaitingTime = 0;
    int processCount = 0;
    ofstream myfile(outputFile, ios_base::app);
    myfile << "\n==============================================\n"
           << endl;
    myfile << "Scheduling Method: Shortest Job First - Non-Preemptive" << endl;
    myfile << "Process Waiting Times:\n"
           << endl;

    // Sort the jobs by burst time
    head = sortJobsByArrivalAndBurstTime(head);
    // head = sortJobsByBurstTime(head);

    int currentTime = 0;
    Job *current = head;

    while (current != nullptr)
    {
        current->waiting_time = max(0, currentTime - current->arrivalTime);
        totalWaitingTime += current->waiting_time;
        processCount++;

        myfile << "P" << processCount << ": " << current->waiting_time << " ms" << endl;

        currentTime += current->burstTime;
        current = current->next;
    }

    myfile << "\nAverage Waiting Time: " << totalWaitingTime / processCount << " ms" << endl;

    cout << "Shortest Job First - Non-Preemptive is Successfully calculated :)" << endl;
}

Job *sortByPriority(Job *head)
{
    Job *sorted = nullptr;

    for (Job *i = head; i != nullptr; i = i->next)
    {
        Job *lastSorted = nullptr;
        for (Job *j = head; j != lastSorted && j->next != nullptr; j = j->next)
        {
            if (j->next != nullptr && j->priority > j->next->priority)
            {
                if (j == head)
                {
                    head = j->next;
                    j->next = head->next;
                    head->next = j;
                }
                else
                {
                    Job *temp = j->next;
                    j->next = temp->next;
                    temp->next = j;
                    lastSorted->next = temp;
                }
            }
            lastSorted = j;
        }
    }

    return sorted;
}



int main(int argc, char *argv[])
{
    int choice;
    int option;
    int p_choose;
    string p = "OFF";

    if (argc != 5)
    {
        cerr << "Usage: " << argv[0] << " -f input.txt -o output.txt" << endl;
        return 1;
    }

    const char *inputFile = nullptr;
    const char *outputFile = nullptr;

    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "-f" && i + 1 < argc)
        {
            inputFile = argv[i + 1];
        }
        else if (string(argv[i]) == "-o" && i + 1 < argc)
        {
            outputFile = argv[i + 1];
        }
    }

    if (!inputFile || !outputFile)
    {
        cerr << "Input and output files are required." << endl;
        return 1;
    }

    Job *jobs = nullptr;
    do
    {
        string text = "CPU Scheduler Simulator";
        int totalWidth = 80;
        int padding = (totalWidth - text.length()) / 2;

        cout << "\n"
             << endl;
        cout << setw(padding + text.length()) << text << endl;
        cout << "1) Scheduling Method (None)" << endl;
        cout << "2) Preemptive Mode (" + p + ")" << endl;
        cout << "3) Show Result" << endl;
        cout << "4) End Program" << endl;
        cout << "Option > ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\n"
                 << endl;
            cout << " 1) First Come, First Served Scheduling" << endl;
            cout << " 2) Shortest-Job-First Scheduling " << endl;
            cout << " 3) Priority Scheduling " << endl;
            cout << " 4) Round-Robin Scheduling\n"
                 << endl;
            cout << "\n"
                 << endl;
            cout << "Option> ";
            cin >> option;

            while (cin.fail() || (option < 1 || option > 4))
            {
                cout << "Invalid input. Please enter a valid option (1-4): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> option;
            }

            if (option == 1)
            {
                loadJobsFromFile(inputFile, jobs);
                FCFS(jobs, outputFile);
                freeLinkedList(jobs);
            }
            else if (option == 2)
            {
                if (p == "OFF")
                {
                    loadJobsFromFile(inputFile, jobs);
                    SJFNonPreemptive(jobs, outputFile);
                    freeLinkedList(jobs);
                }
            }
            else if (option == 3)
            {
                cout << "Priority Scheduling " << endl;
            }
            else if (option == 4)
            {
                cout << "Round-Robin Scheduling " << endl;
            }
            else
            {
                cout << "Invalid sub-menu option. Please try again." << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "\n"
                 << endl;
            cout << "1)ON" << endl;
            cout << "2)OFF" << endl;
            cout << "\n"
                 << endl;
            cout << "Option> ";
            cin >> p_choose;
            if (p_choose < 1 || p_choose > 2 || cin.fail())
            {
                cout << "Invalid input. Please enter a valid option (1-2): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> p_choose;
            }

            if (p_choose == 1)
            {
                p = "ON";
            }
            else if (p_choose == 2)
            {
                p = "OFF";
            }
            else
            {
                cout << "Invalid sub-menu option. Please try again." << endl;
            }
        }
        else if (choice == 3)
        {
            ShowResult(outputFile);
        }
        else if (choice == 4)
        {
            cout << "Thank you program end" << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}