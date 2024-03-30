//===- MinSpanningTree.cpp --------------------------------------------------===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===-----------------------------------------------------------------------------------===//
//
// This file implements the benchmark for the naive implementation of Minimum Spanning Tree.
//
//===-----------------------------------------------------------------------------------===//

#include <benchmark/benchmark.h>
#include <cstring>
#include <iostream>

using namespace std;

#define VERTICES 10
# define INF 1000

namespace {
int input[VERTICES][VERTICES];
int output[VERTICES];
} // namespace

void minSpanningTree(int graph[][VERTICES], int parent[VERTICES]) {
    float key[VERTICES];
    bool visited[VERTICES];

    for (int i = 0; i < VERTICES; i++) {
        key[i] = INF;
        visited[i] = false;
    }

    key[0] = 0;
    parent[0] = 0;

    for (int count = 0; count < VERTICES-1; count++) {
        int min_index = -1;
        float min_cost = INF;
        int min_index_temp = -1;
        for (int i = 0; i < VERTICES; i++) {
            min_index_temp = min_index;
            if (visited[i] == false && key[i] < min_cost) {
                min_cost = key[i];
                min_index = i;
            }
            else {
                min_index = min_index_temp;
            }
        }
        visited[min_index] = true;

        for (int v = 0; v < VERTICES; v++) {
            if (graph[min_index][v] && visited[v] == false && graph[min_index][v] < key[v]) {
                parent[v] = min_index;
                key[v] = graph[min_index][v];
            }
        }
    }    
}

void initializeMinSpanningTree() {
  int MAX_EDGES = VERTICES * (VERTICES - 1) / 2;
  for (int i = 0; i < MAX_EDGES; i++) {
    int u = rand() % VERTICES;
    int v = rand() % VERTICES;
    int d = rand() % 1000;
    input[u][v] = d;
  }
  memset(output, 0, sizeof(output));
}

// Benchmarking function.
static void MinSpanningTree(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      minSpanningTree(input, output);
    }
  }
}

// Register benchmarking function.
BENCHMARK(MinSpanningTree)->Arg(1);

void generateResultMinSpanningTree() {
    initializeMinSpanningTree();
    std::cout << "-------------------------------------------------------\n";
    std::cout << "[Minimum Spanning Tree Result Information ]\n";

    minSpanningTree(input, output);

    for (int i = 0; i < VERTICES; i++) {
        std::cout << "p[" << i << "] = " << output[i] << ", ";
    }
    std::cout << "\nMinimum Spanning Tree operation finished!\n";
}
