#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    int choice;
    int option;
    int p_choose;
    string p = "OFF";

    if (argc != 5)
    {
        cerr << "Usage: " << argv[0] << " -f input.txt -o output.txt" << std::endl;
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


//   Added input validation for 'option' and 'p_choose' to ensure they are within the valid range and handle invalid input.

    do
    {
        string text = "CPU Scheduler Simulator";
        int totalWidth = 80; 
        int padding = (totalWidth - text.length()) / 2;

        cout << "\n"<< endl;
        cout << setw(padding + text.length()) << text << endl;
        cout << "1) Scheduling Method (None)" << endl;
        cout << "2) Preemptive Mode (" + p + ")" << endl;
        cout << "3) Show Result" << endl;
        cout << "4) End Program" << endl;
        cout << "Option > ";
        cin >> choice;

       
        if (choice == 1)
        {
            cout << "\n"<< endl;
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
                
            }
            else if (option == 2)
            {
               
            }
            else if (option == 3)
            {
                
            }
            else if (option == 4)
            {
                
            }
            else
            {
                cout << "Invalid sub-menu option. Please try again." << std::endl;
            }
        }
        else if (choice == 2)
        {
            cout << "\n"<< endl;
            cout << "1)ON" << endl;
            cout << "2)OFF" << endl;
            cout << "\n"<< endl;
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
                p ="ON";
            }
            else if (p_choose == 2)
            {
                p = "OFF";
            }
            else
            {
                cout << "Invalid sub-menu option. Please try again." << std::endl;
            }
        }
        else if (choice == 3)
        {
            cout << "show result is choosed " << endl;
           
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
