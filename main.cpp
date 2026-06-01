#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// ===== COLOR FUNCTION FOR WINDOWS =====
#ifdef _WIN32
#include <windows.h>
#endif

void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}
// ===== END COLOR FUNCTION =====

// Task class 
class Task
{
private:
    int id;
    string title;
    bool completed;

public:
    Task(int i, string t)
    {
        id = i;
        title = t;
        completed = false;
    }

    int getId() { return id; }
    string getTitle() { return title; }
    bool isCompleted() { return completed; }
    void markComplete() { completed = true; }
};

//Global variables
vector<Task> tasks;
int nextId = 1;

// Save tasks to file
void saveToFile() {
    ofstream file("tasks.txt");
    file << tasks.size() << endl;
    
    for(int i = 0; i < tasks.size(); i++) {
        file << tasks[i].getId() << endl;
        file << tasks[i].getTitle() << endl;
        file << tasks[i].isCompleted() << endl;
    }
    file.close();
}

// Load tasks from file
void loadFromFile() {
    ifstream file("tasks.txt");
    if(!file.is_open()) {
        return; 
    }
    
    int count;
    file >> count;
    
    for(int i = 0; i < count; i++) {
        int id;
        string title;
        bool completed;
        
        file >> id;
        file.ignore();
        getline(file, title);
        file >> completed;
        
        Task task(id, title);
        if(completed) {
            task.markComplete();
        }
        tasks.push_back(task);
        if(id >= nextId) {
            nextId = id + 1;
        }
    }
    file.close();
}

int main()
{
    int choice;
    string taskTitle;
    //Load saved tasks
    loadFromFile();

    do
    {
        // ===== ADD COLOR TO MENU =====
        setColor(3); //Cyan color
        cout << "\n=== TO-DO LIST MENU ===" << endl;
        setColor(7); //Reset to white
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task Complete" << endl; 
        cout << "4. Delete Task" << endl;               
        cout << "5. Exit" << endl;               
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter task title: ";
            cin.ignore();
            getline(cin, taskTitle);
            tasks.push_back(Task(nextId++, taskTitle));
            setColor(2);
            cout << "Task added successfully!" << endl;
            setColor(7);
        }
        else if(choice == 2) {
            setColor(3);  // Cyan
            cout << "\n=== YOUR TASKS ===" << endl;
            setColor(7);  // Reset
            
            for(int i = 0; i < tasks.size(); i++) {
                if(tasks[i].isCompleted()) {
                    setColor(2);  // Green for completed
                } else {
                    setColor(4);  // Red for pending
                }
                
                cout << tasks[i].getId() << ". " << tasks[i].getTitle();
                if(tasks[i].isCompleted()) {
                    cout << " [COMPLETED]";
                }
                cout << endl;
                setColor(7);  // Reset
            }
        }
        else if(choice == 3) {
            int id;
            cout << "Enter task ID to mark as complete: ";
            cin >> id;
            
            for(int i = 0; i < tasks.size(); i++) {
                if(tasks[i].getId() == id) {
                    tasks[i].markComplete();
                    setColor(2);  // Green
                    cout << "Task #" << id << " marked as completed!" << endl;
                    setColor(7);  // Reset
                    break;
                }
            }
        }
       else if(choice == 4) {
            int id;
            cout << "Enter task ID to delete: ";
            cin >> id;
            
            for(int i = 0; i < tasks.size(); i++) {
                if(tasks[i].getId() == id) {
                    tasks.erase(tasks.begin() + i);
                    setColor(2);  // Green
                    cout << "Task deleted successfully!" << endl;
                    setColor(7);  // Reset
                    break;
                }
            }
        }

    } while (choice != 5);

    saveToFile();
    setColor(3);
    cout << "Tasks saved to file!" << endl;
    return 0;
}