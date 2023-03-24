#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

const int INF = 1000000000;

void SetGraph(vector<vector<int>>& adj, int n) {
    for (int i = 0; i < n; i ++) {
        vector<int> row;
        for (int j = 0; j < n; j++) {
            string tmp;
            cin >> tmp;
            if (tmp == "-") {
                row.push_back(INF);
            } else {
                row.push_back(atoi(tmp.c_str()));
            }
        }
        adj.push_back(row);
    }
}

void PrintGraph(vector<vector<int>>& adj, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] == INF) {
                cout << '-' << ' ';
            } else {
                cout << adj[i][j] << ' ';
            }
        }
        cout << '\n';
    }
}

vector<vector<int>> FloydWarshallAlgorithm(vector<vector<int>>& adj, int n) {
    vector<vector<int>> dist;
    for (int i = 0; i < n; i++) {
        vector<int> tmp;
        for (int j = 0; j < n; j++) {
            tmp.push_back(adj[i][j]);
        }
        dist.push_back(tmp);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

vector<int> DijkstraAlgrorithm(vector<vector<int>>& adj, int n, int start) {
    vector<int> distances(n, INF);
    distances[start] = 0;
    vector<bool> coloured(n);
    int minDistance = 0, minVertex = start;
    while (minDistance < INF) {
        int i = minVertex;
        coloured[i] = 1;
        for (int j = 0; j < n; j++) {
            if (distances[i] + adj[i][j] < distances[j]) {
                distances[j] = distances[i] + adj[i][j];
            }
        }
        minDistance = INF;
        for (int j = 0; j < n; j++) {
            if (!coloured[j] and distances[j] < minDistance) {
                minDistance = distances[j];
                minVertex = j;
            }
        }
    }
    return distances;
}

vector<int> BellmanFord(vector<vector<int>>& adj, int n, int start) {
    vector<int> distances(n, INF);
    distances[start] = 0;
    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distances[j] + adj[j][i] < distances[i])
                    distances[i] = distances[j] + adj[j][i];
            }
        }
    }
    return distances;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj;
    SetGraph(adj, n); 
    cout << "---------------------------------------------------------" << '\n';

    vector<vector<int>> FloydWarshallResult;
    FloydWarshallResult = FloydWarshallAlgorithm(adj, n);
    PrintGraph(FloydWarshallResult, n);
    cout << "---------------------------------------------------------" << '\n';

    vector<int> DijkstraResult;
    DijkstraResult = DijkstraAlgrorithm(adj, n, 0);

    for (int i = 0; i < n; i++) {
        cout << DijkstraResult[i] << ' ';
    }
    cout << "\n---------------------------------------------------------\n";

    vector<int> BellmanFordResult;
    BellmanFordResult = BellmanFord(adj, n, 0);
    
    for (int i = 0; i < n; i++) {
        cout << BellmanFordResult[i] << ' ';
    }
    cout << "\n---------------------------------------------------------\n";
    return 0;
}