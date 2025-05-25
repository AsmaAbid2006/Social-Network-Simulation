#include <iostream>
#include <string>
#include <unordered_set>
#include<windows.h>
using namespace std;

class Node {
    public:
        int user_index;
        Node* next;
};

class User {
    public:
        string name;
};

class Graph {
    private:
        int no_of_users;
        User* users;
        Node** adjList;

        Node* createNode(int user_index) {
            Node* newNode = new Node;
            newNode->user_index = user_index;
            newNode->next = NULL;
            return newNode;
        }

    public:
        Graph(int total_users) {
            no_of_users = total_users;
            users = new User[no_of_users];
            adjList = new Node*[no_of_users];
            for (int i = 0; i < no_of_users; ++i) {
                adjList[i] = NULL;
            }
        }

        void setUser(int user_index, string name) {
            users[user_index].name = name;
        }

        void friendship(int user1, int user2) {
            Node* newNode = createNode(user2);
            newNode->next = adjList[user1];
            adjList[user1] = newNode;

            newNode = createNode(user1);
            newNode->next = adjList[user2];
            adjList[user2] = newNode;
        }

        //shortest path func
      void shortestpath(int start_user, int target_user) 
	{
	    int* queue = new int[no_of_users];
	    bool* visited = new bool[no_of_users];
	    int* predecessor = new int[no_of_users]; 
	    int front = 0, rear = 0;
	
	
	    for (int i = 0; i < no_of_users; ++i) {
	        visited[i] = false;
	        predecessor[i] = -1;
	    }
	
	    visited[start_user] = true;
	    queue[rear++] = start_user; 
	
	    while (front < rear) {
	        int current = queue[front++]; 
	
	        if (current == target_user) {
	            cout << "Shortest path: ";
	
	            //trace back from target_user to start_user using predecessor array
	            int path[no_of_users]; 
	            int path_length = 0;
	            int temp = target_user;
	            while (temp != -1) {
	                path[path_length++] = temp;  
	                temp = predecessor[temp];
	            }
	
	            //printing from target_user to start_user
	            for (int i = path_length - 1; i >= 0; --i) {
	                cout << users[path[i]].name << " "; 
	            }
	            cout << endl; 
	            return;
	        }
	
	        Node* temp = adjList[current];
	        while (temp) {
	            if (!visited[temp->user_index]) {
	                visited[temp->user_index] = true;
	                predecessor[temp->user_index] = current; 
	                queue[rear++] = temp->user_index;
	            }
	            temp = temp->next;
	        }
	    }
	
    	cout << "No path exists between " << users[start_user].name << " and " << users[target_user].name << endl;      
	}


        // recommendation func
        void recommendations(int start_user) 
        {
            bool* visited = new bool[no_of_users];
            for (int i = 0; i < no_of_users; ++i) {
                visited[i] = false;
            }

            int* stack = new int[no_of_users];
            int top = -1;
            stack[++top] = start_user;

            unordered_set<int> recommended; //track already recommended users

            cout << "Recommended connections for " << users[start_user].name << ": ";

            while (top != -1) {
                int user = stack[top--]; 

                if (!visited[user])
				{
                    visited[user] = true;
                    Node* temp = adjList[user];
                    while (temp) //traversal
					{ 
                        if (!visited[temp->user_index] //1. that friend has not been visited
						&& recommended.find(temp->user_index) == recommended.end())//2. that friend has not already been recommended
						{
                            cout << users[temp->user_index].name << " ";
                            recommended.insert(temp->user_index); 
                            stack[++top] = temp->user_index; //push
                        }
                        temp = temp->next;
                    }
                }
            }
            cout << endl;
            delete[] visited;
            delete[] stack;
        }

        //display graph
        void display_net() {
            for (int i = 0; i < no_of_users; ++i) {
                cout << i + 1 << ") " << users[i].name << "  friends: ";
                Node* temp = adjList[i];
                while (temp) {    
                    cout << users[temp->user_index].name << ", ";
                    temp = temp->next;
                }
                cout << endl;
            }
        }
};

//clear screen
void clearscreen() {
    char c;
    cout << "\n\nClear Screen?(y/n)"; 
    cin >> c;
    if (c == 'Y' || c == 'y')
        system("cls");    
}

//display menu
void displayMenu() {
    cout << "\nMenu Options:\n";
    cout << "1. Display Users and Friendships\n";
    cout << "2. Find Shortest Path Between Two Users\n";
    cout << "3. Get Friend Recommendations\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    system("Color E1");
    int total_users = 10, id1, id2;
    string name;
    Graph Net(total_users);

    Net.setUser(0, "Jameel");
    Net.setUser(1, "Asim");
    Net.setUser(2, "Kareem");
    Net.setUser(3, "Akram");
    Net.setUser(4, "Ahmed");
    Net.setUser(5, "Alia");
    Net.setUser(6, "Ilyas");
    Net.setUser(7, "Haleema");
    Net.setUser(8, "Mussab");
    Net.setUser(9, "Bakht");

    Net.friendship(0, 1);
    Net.friendship(0, 2);
    Net.friendship(2, 3);
    Net.friendship(3, 4);
    Net.friendship(1, 3);
    Net.friendship(2, 4);
    Net.friendship(4, 5);
    Net.friendship(8, 9);

    int choice;
    char cont = 'Y';
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nUsers and their friends:\n";
                Net.display_net();
                clearscreen();
                break;
            }
            case 2: {
                // shortest path 
                int start_user, target_user;
                cout << "Enter First User: ";
                cin >> start_user;
                cout << "Enter Second User: ";
                cin >> target_user;
                Net.shortestpath(start_user - 1, target_user - 1); 
                cout << endl;
                clearscreen();
                break;
            }
            case 3: {
                // recommendations
                int start_user;
                cout << "Enter User to get recommendations for: ";
                cin >> start_user;
                Net.recommendations(start_user - 1); 
                cout << endl;
                clearscreen();
                break;
            }

            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please select a valid option." << endl;
        }

    } while (choice != 0);

    return 0;
}
