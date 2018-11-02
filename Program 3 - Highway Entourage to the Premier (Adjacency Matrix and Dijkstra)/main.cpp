/*
Michael Mroczka
CIS 3501
Professor Elenbogan
Code: Highway_Entrourage to the Premier_Program 3
Last updated: 3:47pm 3/25/15 to add comments
Description: When this program runs an adjacency matrix and can calculate the shortest path
             in a directed graph from one node to another. It allows you to define a number of test cases,
             then proceeds to wait for you to input the number of intersections, the # of streets,
             and then the starting and stopping node. It then further waits for you to enter 'n' # number of streets
             with each street containing 3 variables - start, stop, weight. After all data has been correctly entered
             it builds an adjacency matrix and calculates the shortest path while considering primarily weights (times) and
             secondarily lexigraphical order. After the calculation it displays the cost and the shortest path.
*/



#include <iostream>
#include <string>
#include <vector>
const int infinity = INT_MAX;
const int NoPARENT = -1;
using namespace std;

struct vertex{
    vector<int> vertices;
};

class adjMatrix{
public:
    adjMatrix(int n=0, int sourceNode=0, int targetNode=0){
        SIZE = n;
        start = sourceNode;
        finish = targetNode;
        matrix.resize(SIZE);
        for (int i = 0; i < SIZE; i++){
            matrix[i].vertices.resize(SIZE);
        }
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                matrix[i].vertices[j] = 0;
    }
    vector<vertex> matrix;
    vector<int> dist, parents, path; //previous nodes
    vector<bool> known;
    int SIZE, start, finish;

    void shortestPath(){
        /*
        ????name?? : shortestPath()
        ????purpose: prints the cost value of going from node A to node B and then retraces
                     the path - printing out the trail to follow to achieve the shortest path
        ????pre????: assumes an adjMatrix class object has been built, and the dijkstras function
                     was successfully run, and the class now contains a vertex to be printed. It
                     additionally assumes the shortest path either exists in vertex or else will
                     print "unreachable"
        ????post?? : will always print something. It will either print the shortest path's cost and then
                     path itself, or it will print "unreachable" if it can't get to the vertex in question
        ????called
        ????by???? : dijkstras()
    ????*/
        bool impossible = false;
        int cur = finish;
        while (parents[cur] != NoPARENT){ //provided that the current node has a parent...
            path.push_back(cur); // add the current parent to the path...
            cur = parents[cur]; // and update the parent
        }
        path.push_back(cur);

        if (cur != start)
            impossible = true;

        //reverse the output order of vector!
        reverse(path.begin(), path.end());

        if (impossible == false){
            cout << dist[finish] << " ";
            for (int i = 0; i < path.size(); i++){
                cout << path[i] << " ";
            }
            path.clear();
        }

        else{
            cout << "unreachable";
        }
        cout << endl;
    }

    void dijkstras(){
        /*
????            name?? : dijkstras()
????            purpose: identifies and catalogs the shortest reachable path from one
                     vertex to another while considering weight and breaking ties
                     lexigraphically
????            pre????: assumes that infinity is defined as the largest integer value possible,
                     and that no nodes/vertices will contain weights/rows/columns of that size.
                     It alsoassumes SIZE is a non-negative number, assumes the workset only
                     contains nodes on the actual graph. If the result set contains a path
                     for a node, it is actually a path and uses vertices outside the workset.
                     It also assumes matrix was built correctly, no illegal input is in play
????            post?? : assumes shortest path has been found and stored in the vertex in the object class
                     it also assumes program will not modify the class variables before the shortest path
                     function is called and printed
????            called
????            by???? : main()
    ????*/
        int smallestIndex, smallestDistance;
        dist.resize(SIZE);
        parents.resize(SIZE);
        known.resize(SIZE);
        for (int i = 0; i < SIZE; i++){
            dist[i] = infinity;
            known[i] = false;
            parents[i] = NoPARENT;
        }
        //initialize distance to 0
        this->dist[start] = 0;

        for (int i = 0; i < SIZE; i++){  // go through all nodes
            smallestDistance = infinity; // smallestDistance starts at infinity
            for (int j = 0; j < SIZE; j++){ // run through all nodes in subroutine to find...
                if (dist[j] < smallestDistance && known[j] != true) { // whether or not the new distance is smaller than the old one
                    smallestIndex = j; //if it is smaller update both distance and index
                    smallestDistance = dist[j];
                }
            }
            known[smallestIndex] = true;
            //and we need to update the distance and parent as well
            for (int j = 0; j < SIZE; j++){
                if (known[j] == false){ //if the vertex is currently marked false
                    if (matrix[smallestIndex].vertices[j] > 0){ //and the weight is greater than 0
                        if (dist[smallestIndex] < infinity){  // and the distance is smaller than infinity
                            if ((dist[smallestIndex] + matrix[smallestIndex].vertices[j]) < dist[j]) {
                                dist[j] = dist[smallestIndex] + matrix[smallestIndex].vertices[j]; //replace distance
                                parents[j] = smallestIndex; //and update parent
                            }
                        }
                    }
                }
            }
        }
        shortestPath(); //call shortest path function to print final answer
    }
};

int main(){
    int testCases, intersections, streets, start, finish, stBegin, stEnd, time;
    cin >> testCases;
    for (int i = 0; i < testCases; i++){
        cin >> intersections >> streets >> start >> finish;
        adjMatrix V(intersections, start, finish);
            for (int j = 0; j < streets; j++){// add edge weights to 2d matrix
                cin >> stBegin >> stEnd >> time;
                V.matrix[stBegin].vertices[stEnd] = time; // store weight in row 'stBegin' and column 'stEnd' of adjMatrix's matrix
            }
            V.dijkstras();
        }
    return 0;
}

