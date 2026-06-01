#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Task class to store each task
class Task {
private:
    int id;
    string title;
    bool completed;
    
public:
    Task(int i, string t) {
        id = i;
        title = t;
        completed = false;
    }
    
    int getId() { return id; }
    string getTitle() { return title; }
    bool isCompleted() { return completed; }
    void markComplete() { completed = true; }
};
vector<Task> tasks;
int nextId = 1;
int main() {
    int choice;
    string taskTitle;
    
    do {
        cout << "\n=== TO-DO LIST MENU ===" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if(choice == 1) {
            cout << "Enter task title: ";
            cin.ignore();
            getline(cin, taskTitle);
            tasks.push_back(Task(nextId++, taskTitle));
            cout << "Task added successfully!" << endl;
        }
        else if(choice == 2) {
            cout << "\n=== YOUR TASKS ===" << endl;
            for(int i = 0; i < tasks.size(); i++) {
                cout << tasks[i].getId() << ". " << tasks[i].getTitle();
                if(tasks[i].isCompleted()) {
                    cout << " [COMPLETED]";
                }
                cout << endl;
            }
        }
        
    } while(choice != 3);
    
    return 0;
}