#include <iostream>
#include <vector>
#include<queue>
#include<algorithm>
using namespace std;


class Graph{
    int N,E; //Number of nodes/vertices
    vector<int> *adjacencyList; //Array of lists

    public:  
    Graph(int N,int E){
        this->N=N; //setting the number of vertices to variable V
        this->E=E;
        adjacencyList=new vector<int>[N]; //initialising an array of lists of size V
    }
    void addEdge(int v1,int v2){
        adjacencyList[v1].push_back(v2); //pushing node v2 to adjacency list of node 2
        adjacencyList[v2].push_back(v1);
    }
    
     vector<vector<int>> bms(int goal) {
        vector<vector<int>> paths; // Vector to store all the paths to goal 
        vector<bool> visited(N, false); 
        queue<int> q; 
        vector<int> parent(N, -1);
        q.push(0); 
        visited[0] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : adjacencyList[node]) {
                if (!visited[neighbor] || neighbor==goal) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    parent[neighbor] = node; //setting parent of goal if found else just update parent of neighbor node
                    
                    if(neighbor==goal){
                        vector<int> path;
                        int a=neighbor;
                        while (a != -1) {
                            path.push_back(a);
                            a = parent[a];
                        }
                        reverse(path.begin(), path.end());
                        paths.push_back(path);
                    }
                }
            }
        }
        return paths;
    }
    vector<int> bfs(int goal) {
    
        vector<int> ans;
        vector<int> parent(N, -1);
        int visit[N]={0};
        visit[0]=1;
        queue<int> q;
        q.push(0);
        
        while(!q.empty()){
            int node=q.front();
            q.pop();
            
             if (node == goal) {
                vector<int> path;
                while (node != -1) {
                    path.push_back(node);
                    node = parent[node];
                }
                reverse(path.begin(), path.end());
                return path;
            }
           
            for(auto it:adjacencyList[node]){
                if(!visit[it]){
                    visit[it]=1;
                    q.push(it);
                    parent[it] = node;
                }
            }
        }
        return ans;
    }
    void dfs(int node,int visited[],vector<int> &answer,int goal){
      visited[node]=1;
      answer.push_back(node);
      if (node == goal) {
            return;
        }
      for(auto it : adjacencyList[node]){
          if(!visited[it]){
              dfs(it,visited,answer,goal);
              if (answer.back() == goal) {
                    return;
               }
               answer.pop_back();

          }
      }
  }
    vector<int> dfsOfGraph(int goal) {
        int visited[N]={0};
        int source=0;
        vector<int> answer;
        dfs(source,visited,answer,goal);
        return answer;
        
    }
    void printAdjacencyList(){
        cout<<endl;
        cout<<"The adjacency list is :"<<endl;
        for(int i=0;i<N;i++){
            cout<<"Node "<<i<<"->";
            for(int num:adjacencyList[i]){
                cout<<num<<",";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void printAnswerArray(vector<int> ans){
        for(int i=0;i<ans.size();i++){
            cout<<ans[i]<<" ";
        }
    }
    void printNestedArray(vector<vector<int>> ans){
        for(int i=0;i<ans.size();i++){
            cout<<"Path "<<i+1<<" : ";
            for(int j=0;j<ans[i].size();j++){
                cout<<ans[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

int main() {
    int N, E, choice, goal;
    vector<int> ans;
    vector<vector<int>> answer;
    cout << "Enter the number of nodes/vertices: ";
    cin >> N;
    cout << "Enter the number of edges: ";
    cin >> E;
    Graph g(N, E);
    cout << "Enter the source and destination vertices for each edge:" << endl;
    for (int i = 0; i < E; i++) {
        int v1, v2;
        cout << "V1 V2: ";
        cin >> v1 >> v2;
        g.addEdge(v1, v2);
    }
    g.printAdjacencyList();
    cout << endl << "Enter the goal node: ";
    cin >> goal;
    cout << endl;
    cout << "The following are the algorithms that can be performed on your graph: " << endl;
    cout << endl << "1. BFS" << endl << "2. DFS" << endl << "3. British Museum Search" << endl;
    cout << endl << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case (1):
            ans = g.bfs(goal);
            break;
        case (2):
            ans = g.dfsOfGraph(goal);
            break;
        case (3):
            answer = g.bms(goal);
            break;
    }
  
    cout << "The traversal for your desired algorithm is: "<<endl;
    if (choice == 3) {
        g.printNestedArray(answer); // Print BMS paths
    } else {
        g.printAnswerArray(ans); // Print BFS or DFS path
    }
    return 0;
}

