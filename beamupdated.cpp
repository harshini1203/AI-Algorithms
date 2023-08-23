#include <iostream>
#include <vector>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;

struct Edge {
    int vertex;
    int cost;
    int eh;

    Edge(int v, int c,int h) {
        vertex=v;
        cost=c;
        eh=h;
    }
};
struct CompareEdges {
    bool operator()(const Edge& a, const Edge& b) {
        return a.eh>b.eh; // Min-heap 
    }
};
struct ComparePairs {
    bool operator()(const pair<int, Edge>& p1, const pair<int, Edge>& p2) const {
        // Compare based on the cumulative cost in the pair
        return p1.first > p2.first; //Min-heap
    }
};

class Graph {

    int N,E;
    vector<Edge>* adjacencyList ;// The vector to hold the edges

public:
    
    Graph(int N,int E)
    {
    this->N = N;
    this->E=E;
    adjacencyList = new vector<Edge>[N];
    }
    
     void addEdge(int v1, int v2, int cost,int eh) {
        adjacencyList[v1].push_back(Edge(v2, cost,eh)); // Pushing edge with destination vertex and cost to adjacency list of node v1
        adjacencyList[v2].push_back(Edge(v1, cost,eh)); // For undirected graph, add an edge in both directions
    }
    vector<int> oracle(int goal){
        priority_queue<pair<int, Edge>,vector<pair<int, Edge>>, ComparePairs> q;
        vector<pair<vector<int>,int>> ans;
        vector<int> parent(N, -1);
        int visit[N]={0};
        visit[0]=1;
     
        q.push(Edge(0,0,0));
        cout<<q.top().vertex<<endl;
        while(!q.empty()){
           priority_queue<pair<int, Edge>,vector<pair<int, Edge>>, ComparePairs> temp;
            int node=q.top().second.vertex;
            int cost=q.top().second.cost;
            int cumulativeCost=q.top().first;
            q.pop();
            
             if (node == goal) {
                vector<int> path;
                while (node != -1) {
                    path.push_back(node);
                    cout<<"pushed in path : "<<node<<endl;
                    node = parent[node];
                }
                reverse(path.begin(),path.end());
                ans.push_back()
            }
            for(Edge& edge:adjacencyList[node]){
                
                if(!visit[edge.vertex]){
                    cout<<"now visiting "<<edge.vertex<<endl;
                    visit[edge.vertex]=1;
                    temp.push(make_pair(cumulativeCost+cost,edge));
                    parent[edge.vertex] = node;
                }
            }
            if(q.empty()){
                 while(!temp.empty()){
                    cout<<"adding now from temp : "<<temp.top().vertex<<endl;
                    q.push(temp.top());   //level wise
                    temp.pop();
                }
            }
            }
        }
        return ans;
        
    }
    vector<int> beamSearch(int goal,int width){
        priority_queue<Edge, vector<Edge>, CompareEdges> q;
        vector<int> ans;
        vector<int> parent(N, -1);
        int visit[N]={0};
        visit[0]=1;
     
        q.push(Edge(0,0,0));
        cout<<q.top().vertex<<endl;
        while(!q.empty()){
            priority_queue<Edge,vector<Edge>,CompareEdges> temp;
            int node=q.top().vertex;
            q.pop();
            
             if (node == goal) {
                vector<int> path;
                while (node != -1) {
                    path.push_back(node);
                    cout<<"pushed in path : "<<node<<endl;

                    node = parent[node];
                }
                reverse(path.begin(), path.end());
                cout<<"being returned "<<endl;
                return path;
            }
            for(Edge& edge:adjacencyList[node]){
                
                if(!visit[edge.vertex]){
                    cout<<"now visiting "<<edge.vertex<<endl;
                    if(edge.vertex!=goal) visit[edge.vertex]=1;
                    temp.push(Edge(edge.vertex,edge.cost,edge.eh));
                    parent[edge.vertex] = node;
                    cout<<"parent of "<<edge.vertex<<" is"<<node<<endl;
                }
            }
            if(q.empty()){
                if(temp.size()>width){
                for(int i=0;i<width;i++){
                    cout<<"adding now from temp : "<<temp.top().vertex<<endl;
                    q.push(temp.top());   //adding only the first two nodes with least heuristic value to the queue to explore further
                    temp.pop();
                }
                }
                else{
                    while(!temp.empty()){
                    cout<<"adding now from temp : "<<temp.top().vertex<<endl;
                    q.push(temp.top());
                    temp.pop();
                }
                }
                while(!temp.empty()) temp.pop();  //clearing out the temp array to store the nodes at next level
                
                
            }
        }
        return ans;
    }

    void hillclimbing(int node,int visited[],vector<int> &answer,int goal){
      visited[node]=1;
      int chosen=-1;
      int mini=INT_MAX;
      answer.push_back(node);
      if (node == goal) {
            return;
        }
      for(Edge& edge : adjacencyList[node]){
          if(!visited[edge.vertex] && edge.cost<=mini){
              mini=edge.cost;
              chosen=edge.vertex;
          }
      }
      if (chosen != -1) { // If there's a valid neighbor to move to
        hillclimbing(chosen, visited, answer, goal);
        if (answer.back() == goal) {
                    return;
            }
        } 
        else {
        answer.clear(); // Clear the answer if no goal is reached
        }
  }
    vector<int> dfsOfGraph(int goal) {
        int visited[N]={0};
        int source=0;
        vector<int> answer;
        hillclimbing(source,visited,answer,goal);
        return answer;
        
    }
    void printAnswerArray(vector<int> ans){
        for(int i=0;i<ans.size();i++){
            cout<<ans[i]<<" ";
        }
    }
     void printAdjacencyList(){
        cout<<endl;
        cout<<"The adjacency list is :"<<endl;
    
        for (int i = 0; i < N; i++) {
            cout << "Node " << i << " -> ";
            for (const Edge& edge : adjacencyList[i]) {
                cout << "(" << edge.vertex << ", " << edge.cost << " , " << edge.eh << ") ";
            }
            cout << endl;
        }
    

        cout<<endl;
    }
};

int main() {
    int N, E, choice, goal,cost,width;
    vector<int> ans;
    vector<vector<int>> answer;
    cout << "Enter the number of nodes/vertices: ";
    cin >> N;
    cout << "Enter the number of edges: ";
    cin >> E;
    Graph g(N, E);
    cout << "Enter the source and destination vertices for each edge and their cost and their estimated heuristics :" << endl;
    for (int i = 0; i < E; i++) {
        int v1, v2,eh;
        cout << "V1 V2 cost heuristics : ";
        cin >> v1 >> v2 >>cost>>eh;
        g.addEdge(v1, v2,cost,eh);
    }
    g.printAdjacencyList();
    cout << endl << "Enter the goal node: ";
    cin >> goal;
    cout << endl;
    
  cout << "The following are the algorithms that can be performed on your graph: " << endl;
    cout << endl << "1. Beam Search" << endl << "2. Hill Climbing" << endl;
    
  cout<<"Enter your choice of algorithm : ";
  cin>>choice;
  switch(choice){
      case 1:
        cout<<"Enter beam width : ";
        cin>>width;
        ans=g.beamSearch(goal,width);
      break;
      
      case 2:
      ans=g.dfsOfGraph(goal);
      break;
  }
    cout << "The traversal for your desired algorithm is: "<<endl;
 
    g.printAnswerArray(ans); 

    return 0;
}
