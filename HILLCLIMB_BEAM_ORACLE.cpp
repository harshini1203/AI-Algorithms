#include <iostream>
#include <vector>
#include<queue>
#include<algorithm>
#include<climits>
#include<utility>
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
struct ComparePairs {  //oracle
    bool operator()(const pair<int, Edge>& p1, const pair<int, Edge>& p2) const {
        // Compare based on the cumulative cost in the pair
        return p1.first > p2.first; //Min-heap
    }
};
struct ComparePairsLevel {   //branch and boundary
    bool operator()(const pair<pair<int,Edge>,int>& p1, const pair<pair<int,Edge>,int>& p2) const {
        // Compare based on the cumulative cost in the pair
        return p1.first.first > p2.first.first; //Min-heap
    }
};
struct ComparePairsLevelEH {   //branch and boundary with EH
    bool operator()(const pair<pair<int,Edge>,int>& p1, const pair<pair<int,Edge>,int>& p2) const {
        // Compare based on the cumulative cost in the pair
        return p1.first.first+p1.first.second.eh > p2.first.first+p2.first.second.eh; //Min-heap
    }
};
struct ComparePairsEH{  //oracle with eh
    bool operator()(const pair<int, Edge>& p1, const pair<int, Edge>& p2) const {
        // Compare based on the cumulative cost in the pair
        return p1.first+p1.second.eh > p2.first+p1.second.eh; //Min-heap
    }
};

struct comparator{
    bool operator()(const pair<vector<int>,int>& p1,const pair<vector<int>,int>& p2){
        return p1.second<p2.second;
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
    
    vector<pair<vector<int>,int>> bb(int goal){
        priority_queue <pair<pair<int,Edge>,int>,vector<pair<pair<int,Edge>,int>>, ComparePairsLevel> q;
        queue<pair<int,Edge>> temp;
        vector<pair<vector<int>,int>> ans;
         vector<vector<int>> parent( 100 , vector<int> (100, 0));
        // int visit[N]={0};
        // visit[0]=1;
         q.push(make_pair(make_pair(0,Edge(0,0,0)),0));
        //cout<<q.top().first.second.vertex<<endl;
        while(!q.empty()){
            int node=q.top().first.second.vertex;
            int cost=q.top().first.second.cost;
            int cumulativeCost=q.top().first.first;
            int level=q.top().second;
            q.pop();
            //cout<<"The level this node is on : "<<level<<endl;
            int vis[N]={0};
            for(Edge& edge:adjacencyList[node]){
                 for(int i=1;i<=level;i++){
                    vis[parent[i][node]]=1;
                }
                if(vis[edge.vertex]==0){
                  //  cout<<"now exploring "<<edge.vertex<<endl;
                    vis[edge.vertex]=1;
                    q.push(make_pair(make_pair(cumulativeCost+edge.cost,edge),level+1));
                  //  cout<<"pushed in queue : "<<cumulativeCost+edge.cost<<" "<<edge.vertex<<endl;
                    parent[level+1][edge.vertex] = node;
                  //  cout<<"Parent of "<<edge.vertex<<" is : "<<parent[level+1][edge.vertex]<<endl;
                    
                    //cout<<endl;
                    if(edge.vertex==goal){
                        vector<int> path;
                        int l=level+1;
                        //cout<<"goal is on level : "<<level<<endl;
                        int a=edge.vertex;
                        while (l != 0){
                            path.push_back(a);
                           // cout<<"in path : "<<a<<endl;
                            a = parent[l][a];
                            l=l-1;
                        }
                        path.push_back(0);
                        reverse(path.begin(), path.end());
                        ans.push_back(make_pair(path,cumulativeCost+edge.cost));
                        return ans;
                    }
                }
                
            }
          
            
            }
        return ans;
}
         vector<pair<vector<int>,int>> bbELEH(int goal){
        priority_queue <pair<pair<int,Edge>,int>,vector<pair<pair<int,Edge>,int>>, ComparePairsLevelEH> q;
        queue<pair<int,Edge>> temp;
        vector<pair<vector<int>,int>> ans;
         vector<vector<int>> parent( 100 , vector<int> (100, 0));
        // int visit[N]={0};
        // visit[0]=1;
        int EL[N]={0};
        EL[0]=1;
         q.push(make_pair(make_pair(0,Edge(0,0,0)),0));
        //cout<<q.top().first.second.vertex<<endl;
        while(!q.empty()){

            int node=q.top().first.second.vertex;
            int cost=q.top().first.second.cost;
            int cumulativeCost=q.top().first.first;
            int level=q.top().second;
            q.pop();
            cout<<"Now exploring : "<<node<<endl;
            //cout<<"The level this node is on : "<<level<<endl;
            //int vis[N]={0};
            for(Edge& edge:adjacencyList[node]){
                //  for(int i=1;i<=level;i++){
                //     vis[parent[i][node]]=1;
                // }
                if(EL[edge.vertex]==0){
                    //cout<<"now exploring "<<edge.vertex<<endl;
                    EL[edge.vertex]=1;
                    q.push(make_pair(make_pair(cumulativeCost+edge.cost,edge),level+1));
                  //  cout<<"pushed in queue : "<<cumulativeCost+edge.cost<<" "<<edge.vertex<<endl;
                    parent[level+1][edge.vertex] = node;
                  //  cout<<"Parent of "<<edge.vertex<<" is : "<<parent[level+1][edge.vertex]<<endl;
                    
                    //cout<<endl;
                    if(edge.vertex==goal){
                        vector<int> path;
                        int l=level+1;
                        //cout<<"goal is on level : "<<level<<endl;
                        int a=edge.vertex;
                        while (l != 0){
                            path.push_back(a);
                           // cout<<"in path : "<<a<<endl;
                            a = parent[l][a];
                            l=l-1;
                        }
                        path.push_back(0);
                        reverse(path.begin(), path.end());
                        ans.push_back(make_pair(path,cumulativeCost+edge.cost));
                        return ans;
                    }
                }
                
            }
          
            
            }
        return ans;
        }
        vector<pair<vector<int>,int>> bbEL(int goal){
        priority_queue <pair<pair<int,Edge>,int>,vector<pair<pair<int,Edge>,int>>, ComparePairsLevelEH> q;
        queue<pair<int,Edge>> temp;
        vector<pair<vector<int>,int>> ans;
         vector<vector<int>> parent( 100 , vector<int> (100, 0));
        // int visit[N]={0};
        // visit[0]=1;
        int EL[N]={0};
        EL[0]=1;
         q.push(make_pair(make_pair(0,Edge(0,0,0)),0));
        //cout<<q.top().first.second.vertex<<endl;
        while(!q.empty()){

            int node=q.top().first.second.vertex;
            int cost=q.top().first.second.cost;
            int cumulativeCost=q.top().first.first;
            int level=q.top().second;
            q.pop();
            //cout<<"Now exploring : "<<node<<endl;
            //cout<<"The level this node is on : "<<level<<endl;
            //int vis[N]={0};
            for(Edge& edge:adjacencyList[node]){
                //  for(int i=1;i<=level;i++){
                //     vis[parent[i][node]]=1;
                // }
                if(EL[edge.vertex]==0){
                    //cout<<"now exploring "<<edge.vertex<<endl;
                    EL[edge.vertex]=1;
                    q.push(make_pair(make_pair(cumulativeCost+edge.cost,edge),level+1));
                  //  cout<<"pushed in queue : "<<cumulativeCost+edge.cost<<" "<<edge.vertex<<endl;
                    parent[level+1][edge.vertex] = node;
                  //  cout<<"Parent of "<<edge.vertex<<" is : "<<parent[level+1][edge.vertex]<<endl;
                    
                    //cout<<endl;
                    if(edge.vertex==goal){
                        vector<int> path;
                        int l=level+1;
                        //cout<<"goal is on level : "<<level<<endl;
                        int a=edge.vertex;
                        while (l != 0){
                            path.push_back(a);
                           // cout<<"in path : "<<a<<endl;
                            a = parent[l][a];
                            l=l-1;
                        }
                        path.push_back(0);
                        reverse(path.begin(), path.end());
                        ans.push_back(make_pair(path,cumulativeCost+edge.cost));
                        return ans;
                    }
                }
                
            }
          
            
            }
        return ans;
        }

     vector<pair<vector<int>,int>> bbEH(int goal){
        priority_queue <pair<pair<int,Edge>,int>,vector<pair<pair<int,Edge>,int>>, ComparePairsLevelEH> q;
        queue<pair<int,Edge>> temp;
        vector<pair<vector<int>,int>> ans;
         vector<vector<int>> parent( 100 , vector<int> (100, 0));
        // int visit[N]={0};
        // visit[0]=1;
         q.push(make_pair(make_pair(0,Edge(0,0,0)),0));
        //cout<<q.top().first.second.vertex<<endl;
        while(!q.empty()){
            int node=q.top().first.second.vertex;
            int cost=q.top().first.second.cost;
            int cumulativeCost=q.top().first.first;
            int level=q.top().second;
            q.pop();
            //cout<<"The level this node is on : "<<level<<endl;
            int vis[N]={0};
            for(Edge& edge:adjacencyList[node]){
                 for(int i=1;i<=level;i++){
                    vis[parent[i][node]]=1;
                }
                if(vis[edge.vertex]==0){
                  //  cout<<"now exploring "<<edge.vertex<<endl;
                    vis[edge.vertex]=1;
                    q.push(make_pair(make_pair(cumulativeCost+edge.cost,edge),level+1));
                  //  cout<<"pushed in queue : "<<cumulativeCost+edge.cost<<" "<<edge.vertex<<endl;
                    parent[level+1][edge.vertex] = node;
                  //  cout<<"Parent of "<<edge.vertex<<" is : "<<parent[level+1][edge.vertex]<<endl;
                    
                    //cout<<endl;
                    if(edge.vertex==goal){
                        vector<int> path;
                        int l=level+1;
                        //cout<<"goal is on level : "<<level<<endl;
                        int a=edge.vertex;
                        while (l != 0){
                            path.push_back(a);
                           // cout<<"in path : "<<a<<endl;
                            a = parent[l][a];
                            l=l-1;
                        }
                        path.push_back(0);
                        reverse(path.begin(), path.end());
                        ans.push_back(make_pair(path,cumulativeCost+edge.cost));
                        return ans;
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
       // cout<<q.top().vertex<<endl;
        while(!q.empty()){
            priority_queue<Edge,vector<Edge>,CompareEdges> temp;
            int node=q.top().vertex;
            q.pop();
            
             if (node == goal) {
                vector<int> path;
                while (node != -1) {
                    path.push_back(node);
                    //cout<<"pushed in path : "<<node<<endl;
                    node = parent[node];
                }
                reverse(path.begin(), path.end());
               // cout<<"being returned "<<endl;
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
    vector<pair<vector<int>,int>> oracleEH(int goal){
        priority_queue<pair<int, Edge>,vector<pair<int, Edge>>, ComparePairs> q;
        queue<pair<int, Edge>> temp;
        vector<pair<vector<int>,int>> ans;
         vector<vector<int>> parent( 100 , vector<int> (100, 0));
         int level=1;
        // int visit[N]={0};
        // visit[0]=1;
        q.push(make_pair(0,Edge(0,0,0)));
        cout<<q.top().second.vertex<<endl;
        while(!q.empty()){
            int node=q.top().second.vertex;
            int cost=q.top().second.cost;
            int cumulativeCost=q.top().first;
            q.pop();
            
            int vis[N]={0};
            for(Edge& edge:adjacencyList[node]){
                 for(int i=1;i<level;i++){
                    vis[parent[i][node]]=1;
                }
                if(vis[edge.vertex]==0){
                    cout<<"now visiting "<<edge.vertex<<endl;
                    vis[edge.vertex]=1;
                    temp.push(make_pair(cumulativeCost+edge.cost,edge));
                    cout<<"pushed : "<<cumulativeCost+edge.cost<<" "<<edge.vertex<<endl;
                    parent[level][edge.vertex] = node;
                    cout<<"Parent of "<<edge.vertex<<" is : "<<parent[level][edge.vertex]<<endl;
                    
                    if(edge.vertex==goal){
                        vector<int> path;
                        int l=level;
                        int a=edge.vertex;
    
                        while (l != 0){
                            path.push_back(a);
                            a = parent[l][a];
                            l=l-1;
                        }
                        path.push_back(0);
                        reverse(path.begin(), path.end());
                        ans.push_back(make_pair(path,cumulativeCost+edge.cost));
                    }
                }
                
            }
          
            if(q.empty()){
                cout<<"Exploration of "<<level<<" level done "<<endl;
                level++;
                 while(!temp.empty()){
                     cout<<"TEMP SIZE : "<<temp.size()<<endl;
                    cout<<"adding now from temp for new level : "<<temp.front().second.vertex<<endl;
                    q.push(temp.front());   //level wise
                    temp.pop();
                }
            }
            }
        sort(ans.begin(),ans.end(),comparator());
        return ans;
}
     
       vector<pair<vector<int>,int>> oracle(int goal){
        priority_queue<pair<int, Edge>,vector<pair<int, Edge>>, ComparePairs> q;
        queue<pair<int, Edge>> temp;
        vector<pair<vector<int>,int>> ans;
         vector<vector<int>> parent( 100 , vector<int> (100, 0));
         int level=1;
        // int visit[N]={0};
        // visit[0]=1;
        q.push(make_pair(0,Edge(0,0,0)));
        cout<<q.top().second.vertex<<endl;
        while(!q.empty()){
            int node=q.top().second.vertex;
            int cost=q.top().second.cost;
            int cumulativeCost=q.top().first;
            q.pop();
            
            int vis[N]={0};
            for(Edge& edge:adjacencyList[node]){
                 for(int i=1;i<level;i++){
                    vis[parent[i][node]]=1;
                }
                if(vis[edge.vertex]==0){
                    cout<<"now visiting "<<edge.vertex<<endl;
                    vis[edge.vertex]=1;
                    temp.push(make_pair(cumulativeCost+edge.cost,edge));
                    cout<<"pushed : "<<cumulativeCost+edge.cost<<" "<<edge.vertex<<endl;
                    parent[level][edge.vertex] = node;
                    cout<<"Parent of "<<edge.vertex<<" is : "<<parent[level][edge.vertex]<<endl;
                    
                    if(edge.vertex==goal){
                        vector<int> path;
                        int l=level;
                        int a=edge.vertex;
        
                        while (l != 0){
                            path.push_back(a);
                            a = parent[l][a];
                            l=l-1;
                        }
                        path.push_back(0);
                        reverse(path.begin(), path.end());
                        ans.push_back(make_pair(path,cumulativeCost+edge.cost));
                    }
                }
                
            }
          
            if(q.empty()){
                cout<<"Exploration of "<<level<<" level done "<<endl;
                level++;
                 while(!temp.empty()){
                     cout<<"TEMP SIZE : "<<temp.size()<<endl;
                    cout<<"adding now from temp for new level : "<<temp.front().second.vertex<<endl;
                    q.push(temp.front());   //level wise
                    temp.pop();
                }
            }
            }
        sort(ans.begin(),ans.end(),comparator());
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

    void printOracle(vector<pair<vector<int>,int>> ans){
        int i=1;
        for(const auto& pair:ans){
            const vector<int>& vec=pair.first;
            cout<<"Path "<<i++<<": ";
            for(int num:vec){ 
                cout<<num<<" ";
            }
            cout<<endl;
            cout<<"Path cost :  "<<pair.second<<endl;
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
    vector<pair<vector<int>,int>> answer;
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
  cout << endl << "1. Beam Search" << endl << "2. Hill Climbing" << endl<<"3. Oracle search"<<endl<<"4. Branch and Boundary"<<endl<<"5. Oracle search with estimated heuristics and cost"<<endl<<"6. Branch and boundary with estimated heuristics and cost"<<endl<<"7. Branch and boundary with cost and extended list"<<endl<<"8. Branch and boundary with cost,estimated heuristics and extended list"<<endl;
    
    
cout<<endl<<endl;
  cout<<"Enter your choice of algorithm : ";
  cin>>choice;
  cout<<endl<<endl;
  cout << "The traversal for your desired algorithm is: "<<endl;
  switch(choice){
      case 1:
        cout<<"Enter beam width : ";
        cin>>width;
        ans=g.beamSearch(goal,width);
        g.printAnswerArray(ans);
      break;
      
      case 2:
      ans=g.dfsOfGraph(goal);
      g.printAnswerArray(ans);
      break;
      
      case 3:
      answer=g.oracle(goal);
      g.printOracle(answer);
      break;
      
      case 4:
      answer=g.bb(goal);
      g.printOracle(answer);
      break;
      
      case 5:
      answer=g.oracleEH(goal);
      g.printOracle(answer);
      break;
      
      case 6:
      answer=g.bbEH(goal);
      g.printOracle(answer);
      break;
      
      case 7:
      answer=g.bbEL(goal);
      g.printOracle(answer);
      break;
      
      case 8:
      answer=g.bbELEH(goal);
      g.printOracle(answer);
      break;
  }
    
 
   

    return 0;
}
