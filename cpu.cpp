#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



int main(int argc, char *argv[]) {
    int choice;
    int option;
    string p = "OFF";

    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " -f input.txt -o output.txt" << std::endl;
        return 1;
    }


    const char* inputFile = nullptr;
    const char* outputFile = nullptr;

    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-f" && i + 1 < argc) {
            inputFile = argv[i + 1];
        } else if (string(argv[i]) == "-o" && i + 1 < argc) {
            outputFile = argv[i + 1];
        }
    }

    if (!inputFile || !outputFile) {
        cerr << "Input and output files are required." << endl;
        return 1;
    }

   
    
    do {
       
        cout << "CPU Scheduler Simulator" <<endl;
        cout << "1) Scheduling Method (None)" << endl;
        cout << "2) Preemptive Mode ("+p+")" << endl;
        cout << "3) Show Result" << endl;
        cout << "4) End Program" << endl;
        cout << "Option > ";
        cin >> choice;

       
        switch (choice) {
            case 1:
                
                cout << "\n 1) First Come, First Served Scheduling" << std::endl;
                cout << "\n 2) Shortest-Job-First Scheduling " << std::endl;
                cout << "\n 3) Priority Scheduling " << std::endl;
                cout << "\n 4) Round-Robin Scheduling\n" << std::endl;

                cout << "Option> ";
                cin >> option;

                
                switch (option) {
                    case 1:
                      
                        break;
                    case 2:
                        
                        break;
                    case 3:
                        
                        break;
                    case 4:
                       
                        break;
                    default:
                        cout << "Invalid sub-menu option. Please try again." << std::endl;
                }
                break;
               
            case 2:
                cout<<"ON"<<endl;
                cout<<"OFF"<<endl;
                int p_choose;
                 switch (p_choose) {
                    case 1:
                      
                        p = "ON";
                    case 2:
                        
                        p ="OFF";
                    default:
                         cout << "Invalid sub-menu option. Please try again." << std::endl;

                 }


               
            case 3:
                 cout<<"show result is choosed "<<endl;
        
            case 4:
                cout<<"Thank you progam end"<<endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 4);

    

    return 0;
}
