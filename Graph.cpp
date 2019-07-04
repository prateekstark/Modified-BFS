#include<vector>
#include<math.h>
#include<cmath>
#include<map>

class vertex{
public:
    typedef pair<int, vertex*> typeVertex;
    vector<typeVertex> adjList;
    int vertexID;
    vertex(int id){
        this->vertexID = id;
    }
};

class FindAny{
public:
    int graphSize;
    int partitionSize;
    int *colorCode;
    int num_partition;
    typedef map<int, int> pListType;
    // This is pList, It has a tuple of (partitionID, numberOfVisited)
    pListType pList1, pList2;
    map<int, list<vertex*> > pAuxList1, pAuxList2;
    FindAny(int n){
        this->graphSize = n;
        this->colorCode = new int[n]{0};
        this->partitionSize = log2(n);
        this->num_partition = (float(n))/(float(this->partitionSize));
    }

    int calculatePartitionNumber(int i){
        return (i/partitionSize);
    }

    int calculateHeadElement(int partitionID){
        return (partitionID*partitionSize);
    }

    void printColorCode(){
        for(int i=0;i<this->graphSize;i++){
            cout<<this->colorCode[i]<<" ";
        }
        cout<<endl;
    }
};

class Graph{
public:
    typedef map<int, vertex*> vmap;
    vmap node;
    int numElements;
    Graph(int n){
        this->numElements = n;
        for(int i=0;i<n;i++){
            vertex* v;
            v = new vertex(i);
            node[i] = v;
        }
        // this->find_any = new FindAny();
    }

    void insertEdge(int a, int b){
        vertex* v1 = node.find(a)->second;
        vertex* v2 = node.find(b)->second;
        pair<int, vertex*> edge = make_pair(b, v2);
        v1->adjList.push_back(edge);
        pair<int, vertex*> edge1 = make_pair(a, v1);
        v2->adjList.push_back(edge1);
    }

    void displayGraph(){
        int n = this->numElements;
        for(int i=0;i<n;i++){
            vertex* v = node.find(i)->second;
            cout<<i<<": ";
            for(int j=0;j<v->adjList.size();j++){
                cout<<v->adjList.at(j).first<<" ";
            }
            cout<<endl;
        }

    }

    void displayAdjacencyList(int n){
        vertex* v = node.find(n)->second;
        for(int i=0;i<(v->adjList.size());i++){
            cout<<v->adjList.at(0).first<<endl;
        }
    }


    void classicalBFS(){
        vector<vertex*> sliding_queue;
        int color[this->numElements] = {};
        sliding_queue.push_back(node.find(0)->second);
        color[0] = 1;
        vertex* tempVertex;
        while(sliding_queue.size() != 0){
            tempVertex = sliding_queue.at(sliding_queue.size()-1);
            cout<<tempVertex->vertexID<<endl;
            for(int j=0;j<tempVertex->adjList.size();j++){
                if(color[tempVertex->adjList.at(j).first] == 0){
                    sliding_queue.insert(sliding_queue.begin(), tempVertex->adjList.at(j).second);
                    color[sliding_queue.begin(), tempVertex->adjList.at(j).first] = 1;
                }
            }
            sliding_queue.pop_back();
        }
    }

    void modifiedBFS(){
        FindAny *find_any = new FindAny(this->numElements);
        find_any->colorCode[0] = 3;
        vertex* tempVertex = node.find(0)->second;
        cout<<tempVertex->vertexID<<endl;
        int temp;
        int tempPartition;
        int coinToss;
        int partitionPresent;
        int tempNum;
        for(int i=0;i<tempVertex->adjList.size();i++){
            temp = tempVertex->adjList.at(i).first;
            find_any->colorCode[temp] = 1;
            coinToss = 1;
            tempPartition = find_any->calculatePartitionNumber(temp);
            if(find_any->pList1.count(tempPartition)){
                find_any->pList1.find(tempPartition)->second++;
                find_any->pAuxList1.find(tempPartition)->second.push_back(tempVertex->adjList.at(i).second);
            }
            else{
                list<vertex*> emptyList({});
                find_any->pList1.insert(make_pair(tempPartition, 1));
                emptyList.push_back(tempVertex->adjList.at(i).second);
                find_any->pAuxList1.insert(make_pair(tempPartition, emptyList));
            }
        }

        while(find_any->pList1.size() != 0 || find_any->pList2.size() != 0){

            if(find_any->pList1.size() == 0 && find_any->pList2.size() != 0){
                coinToss = 2;
            }
            if(find_any->pList1.size() != 0 && find_any->pList2.size() == 0){
                coinToss = 1;
            }
            if(find_any->pList1.size() != 0 && coinToss == 1){
                partitionPresent = find_any->pList1.begin()->first;
                tempNum = find_any->pList1.begin()->second;
                tempVertex = find_any->pAuxList1.begin()->second.back();
                cout<<tempVertex->vertexID<<endl;
                find_any->colorCode[tempVertex->vertexID] = 3;
                for(int i=0;i<tempVertex->adjList.size();i++){
                    temp = tempVertex->adjList.at(i).first;
                    if(find_any->colorCode[temp] == 0){
                        find_any->colorCode[temp] = 2;
                        tempPartition = find_any->calculatePartitionNumber(temp);
                        if(find_any->pList2.count(tempPartition)){
                            find_any->pList2.find(tempPartition)->second++;
                            find_any->pAuxList2.find(tempPartition)->second.push_back(tempVertex->adjList.at(i).second);
                        }
                        else{
                            list<vertex*> emptyList({});
                            find_any->pList2.insert(make_pair(tempPartition, 1));
                            emptyList.push_back(tempVertex->adjList.at(i).second);
                            find_any->pAuxList2.insert(make_pair(tempPartition, emptyList));
                        }
                    }
                }
                if(tempNum > 1){
                    find_any->pList1.begin()->second--;
                    find_any->pAuxList1.begin()->second.pop_back();
                }
                else{
                    find_any->pList1.erase(partitionPresent);
                    find_any->pAuxList1.erase(partitionPresent);
                }
            }
            if(find_any->pList1.size() == 0 && find_any->pList2.size() != 0 && coinToss == 2){
                partitionPresent = find_any->pList2.begin()->first;
                tempNum = find_any->pList2.begin()->second;
                tempVertex = find_any->pAuxList2.begin()->second.back();
                cout<<tempVertex->vertexID<<endl;
                find_any->colorCode[tempVertex->vertexID] = 3;
                for(int i=0;i<tempVertex->adjList.size();i++){
                    temp = tempVertex->adjList.at(i).first;
                    if(find_any->colorCode[temp] == 0){
                        find_any->colorCode[temp] = 1;
                        tempPartition = find_any->calculatePartitionNumber(temp);
                        if(find_any->pList1.count(tempPartition)){
                            find_any->pList1.find(tempPartition)->second++;
                            find_any->pAuxList1.find(tempPartition)->second.push_back(tempVertex->adjList.at(i).second);
                        }
                        else{
                            list<vertex*> emptyList({});
                            find_any->pList1.insert(make_pair(tempPartition, 1));
                            emptyList.push_back(tempVertex->adjList.at(i).second);
                            find_any->pAuxList1.insert(make_pair(tempPartition, emptyList));
                        }
                    }
                }
                if(tempNum > 1){
                    find_any->pList2.begin()->second--;
                    find_any->pAuxList2.begin()->second.pop_back();
                }
                else{
                    find_any->pList2.erase(partitionPresent);
                    find_any->pAuxList2.erase(partitionPresent);
                }
            }
        }
    }
};

int main(){
    int n;
    cin>>n;
    Graph g(n);
    g.insertEdge(3,0);
    g.insertEdge(2,3);
    g.insertEdge(1,2);
    g.insertEdge(3,1);
    g.displayGraph();
    g.modifiedBFS();
    return 0;
}
