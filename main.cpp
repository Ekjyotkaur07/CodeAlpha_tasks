#include <iostream>
using namespace std;

int main() {
    int choice;
    
    do {
        cout << "\n=== TO-DO LIST MENU ===" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if(choice == 1) {
            cout << "Add task feature coming soon!" << endl;
        }
        else if(choice == 2) {
            cout << "View tasks feature coming soon!" << endl;
        }
        
    } while(choice != 3);
    
    return 0;
}