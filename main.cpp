#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Task class to store each task
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
        return; // No saved file yet
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
    loadFromFile();

    do
    {
        cout << "\n=== TO-DO LIST MENU ===" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task Complete" << endl; // NEW OPTION
        cout << "4. Exit" << endl;               // Changed from 3 to 4
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter task title: ";
            cin.ignore();
            getline(cin, taskTitle);
            tasks.push_back(Task(nextId++, taskTitle));
            cout << "Task added successfully!" << endl;
        }
        else if (choice == 2)
        {
            cout << "\n=== YOUR TASKS ===" << endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                cout << tasks[i].getId() << ". " << tasks[i].getTitle();
                if (tasks[i].isCompleted())
                {
                    cout << " [COMPLETED]";
                }
                cout << endl;
            }
        }
        else if(choice == 3) {
            int id;
            cout << "Enter task ID to mark complete: ";
            cin >> id;
            
            for(int i = 0; i < tasks.size(); i++) {
                if(tasks[i].getId() == id) {
                    tasks[i].markComplete();
                    cout << "Task marked as completed!" << endl;
                    break;
                }
            }
        }

    } while (choice != 3);

    saveToFile();
    cout << "Tasks saved to file!" << endl;
    return 0;
}