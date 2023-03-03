#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>

using namespace std;

// Standard Node class for the graph that store a key value to the next node in both address and name
struct GraphNode
{
    int key;
    GraphNode *next;
    GraphNode(int value = 0)
    {
        this->key = value;
        next = NULL;
    }
};

class Graph
{
private:
    // Declaring the necessary variables
    int num_vertex;
    vector<GraphNode *> Adjlist;
    vector<int> visited;    // visited nodes
    vector<int> Parents;    // parents nodes of visited nodes
    vector<int> input_list; // the graph's copy of the user's input

public:
    // Graph constructor
    Graph(vector<int> user_input)
    {
        int i = 0;
        input_list.clear();

        // copying the user's input list
        while (user_input[i] != -1)
        {
            this->input_list.push_back(user_input[i]);
            i++;
        }
        // putting end point into the list
        input_list.push_back(-1);

        // Grabing V from input list
        num_vertex = input_list[0];
        i = 0;
        // initializing all the necessary values
        for (i; i < num_vertex; i++)
        {
            visited.push_back(0);
            Parents.push_back(-1);
            Adjlist.push_back(new GraphNode);
            Adjlist[i]->next = NULL;
        }

        //Initialize all the arrays of the graph class
        Initialize_cond();
        // Adding the inputed edge as pairs
        i = 1;
        while (input_list[i] != -1)
        {
            addEdge(input_list[i], input_list[i + 1]);
            i += 2;
        }
    }

    // Graph destructor
    ~Graph()
    {
        GraphNode *edge = new GraphNode;
        GraphNode *temp = new GraphNode;
        for (int i = 0; i < num_vertex; i++)
        {
            edge = Adjlist[i];
            while (edge != NULL)
            {
                temp = edge;
                edge = edge->next;
                delete temp;
                temp = NULL;
            }
        }
        Adjlist.clear();
    }

    // A function to initialize all the conditions for visit and neighbours
    void Initialize_cond()
    {
        int i = 0;
        for (i; i < num_vertex; i++)
        {
            visited[i] = 0;
            Parents[i] = -1;
        }
    }

    // Function to add edge to the graph
    void addEdge(int begin, int end)
    {
        GraphNode *newEdge = new GraphNode(end); // Header node
        newEdge->next = Adjlist[begin];          // Adjacency list
        Adjlist[begin] = newEdge;

        newEdge = new GraphNode(begin);
        newEdge->next = Adjlist[end];
        Adjlist[end] = newEdge;
    }

    // Function to remove an edge from the graph (unfinished)
    void removeEdge(int begin, int end)
    {
        
    }

    // Printing the Graph by vertices and their respective edges
    void printGraph()
    {
        GraphNode *curr_edge = new GraphNode;
        for (int v = 0; v < num_vertex; v++)
        {
            cout << "Vertex: " << v << endl;
            curr_edge = Adjlist[v];
            cout << v << "->";
            while (curr_edge->next != NULL)
            {
                cout << curr_edge->key << "->";
                curr_edge = curr_edge->next;
            }
            cout << endl;
        }
    }

    // Depth first search function
    // DFS is similar to BFS with the difference being the order in which vertices are explored
    // main difference is that DFS uses a stack instead of a queue
    // is solved iteratively
    vector<int> DFS(int start_v)
    {
        stack<int> vert_stack; // Vertex stack to keep track of visited nodes
        vector<int> output;    // output the set of connected vertices
        GraphNode *temp = new GraphNode;
        Initialize_cond();
        int flag; // Variable to check for disconnected vertex
        visited[start_v] = 1;
        vert_stack.push(start_v);

        while (!vert_stack.empty())
        {
            flag = 0;
            temp = Adjlist[start_v];
            while (temp->next != NULL)
            {
                if (visited[temp->key] == 0)
                {

                    visited[temp->key] = 1;
                    vert_stack.push(temp->key);
                    output.push_back(temp->key);
                    start_v = temp->key;
                    flag = 1;
                    break;
                }

                temp = temp->next;
            }

            // Edge case for isolated vertex
            if (!vert_stack.empty() && flag == 0)
            {
                start_v = vert_stack.top();
                vert_stack.pop();
            }
        }

        return output;
    }

    void printDFSset(int user_input)
    {
        vector<int> print_output = DFS(user_input);
        cout << "The DFS result for " << user_input << " is: \n"<< user_input << " -> ";
        for(int i = 0; i < num_vertex - 1; i++)
            cout << print_output[i] << " -> ";
        cout << endl;
    }

    // Function to compute all the
    vector<vector<int>> Components()
    {
        vector<vector<int>> vertex_sets;
        int i = 0;
        cout << "{";
        //Creating the sets of all connected vertices per vertex
        for (i; i < num_vertex; i++)
        {
            vertex_sets.push_back(DFS(i));
        }

        i = 0;
        //Outputting the result
        for (i; i < num_vertex; i++)
        {
            cout << "{" << i << "->";
            for (int j = 0; j < vertex_sets[i].size(); j++)
            {
                cout << vertex_sets[i][j] << "->";
            }
            cout << "}, ";
        }
        cout << "}";
        return vertex_sets;
    }
};

int num_vertices = 0;

vector<int> takeGraphinput()
{
    vector<int> user_input;
    int input_num, i;
    int num_vertex;
    cout << "How many vertices do you want in your graph? ";
    cin >> num_vertex;
    num_vertices = num_vertex;
    cout << "Your vertices are: ";
    for (i = 0; i < num_vertex; i++)
        cout << i << " ";
    user_input.push_back(num_vertex);
    cout << "\nEnter your edges in pairs(You can stop by inputting -1:\nPair 1: ";
    int count = 1;
    i = 0;
    while (input_num != -1)
    {
        cin >> input_num;
        if (input_num == -1)
            break;
        user_input.push_back(input_num);
        i++;
        cin >> input_num;
        user_input.push_back(input_num);
        if (input_num == -1)
            break;
        cout << "\nPair " << count + 1 << ": ";
        count++;
        i++;
    }

    if (i % 2 != 0)
    {
        cout << "Pair " << i - 1 << " is incomplete";
        user_input.clear();
        user_input.push_back(num_vertex);
    }
    cout << "Your final input: ";
    for (i = 0; i < user_input.size(); i++)
        cout << user_input[i] << " ";
    user_input.push_back(-1);

    return user_input;
}

void makeMenu()
{
    vector<int> user_input;
    string name;
    int options = 0;
    string YorN;
    vector<int> testing = {5, 0, 1, 1, 4, 2, 3, 1, 3, 3, 4, -1};
    num_vertices = testing[0];
    Graph* gph = new Graph(testing);
    int find_vertex = -1;
    cout << "Please enter your name: ";
    cin >> name;
    cout << "Welcome " << name << "!!!" << endl;
    cout << "-------------Getting connected components from graph-------------------\n";
    while (options != 5)
    {
        cout << "--------------------------------------------------------Menu------------------------------------------------------------------\n";
        cout << "\nPick your options!\n1.Create new a graph \n2.Do DFS on graph\n3.Find the connected components\n4.Get current graph\n5.Exit\n";
        cout << "Your choice: ";
        cin >> options;
        switch (options)
        {
        case (1):
            while (YorN != "y" && YorN != "Y")
            {
                user_input = takeGraphinput();
                cout << "Are you satisfied? Y/N: ";
                cin >> YorN;
            }
            num_vertices = user_input[0];
            gph = new Graph(user_input);
            break;

        case (2):
            while(find_vertex < 0 || find_vertex > num_vertices -1)
            {
                cout << "Which vertex do you want to do DFS on: ";
                cin >> find_vertex;

            }

            gph->printDFSset(find_vertex);
            break;

        case (3):
            gph->Components();
            break;

        case (4):
            cout << "Your current graph:\n";
            gph->printGraph();
            break;
        }
    }
}

int main()
{

    makeMenu();

    return 0;
}
