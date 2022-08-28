#include "MapData.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include "utility"
#include "vector"
#include <chrono>

#define NOT_VISITED -1
#define UNREACHABLE -999

struct Node {
    Node(int x, int y, int distance) : x(x), y(y), distance(distance) {};
    int x, y, distance;
};

class Grid {
public:
    Grid() {};

    Node *GetNodeAt(int x, int y) { return &_grid[y][x]; }

    void GetNeighboursOf(Node &n, std::vector<Node *> &neighbours) {
        neighbours.clear();
        if (n.x - 1 >= 0) {
            Node *node = GetNodeAt(n.x - 1, n.y);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
        if (n.x + 1 <= x_lim) {
            Node *node = GetNodeAt(n.x + 1, n.y);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
        if (n.y - 1 >= 0) {
            Node *node = GetNodeAt(n.x, n.y - 1);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
        if (n.y + 1 <= y_lim) {
            Node *node = GetNodeAt(n.x, n.y + 1);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
    }

    int ConvertFrom2Dto1D(Node &node) const { return node.x + node.y * (x_lim + 1); }

private:
    std::vector<std::vector<Node>> _grid;
    int x_lim, y_lim;

public:
    static Grid CreateGrid(std::pair<int, int> MapDimensions, const std::vector<int> &Map) {
        Grid grid;

        int index = 0;
        for (auto y = 0; y < MapDimensions.second; y++) {
            std::vector<Node> row;
            for (auto x = 0; x < MapDimensions.first; x++) {
                if (Map[index] == 0)
                    row.emplace_back(Node(x, y, UNREACHABLE));
                else
                    row.emplace_back(Node(x, y, NOT_VISITED));
                index++;
            }
            grid._grid.emplace_back(row);
        }

        grid.y_lim = grid._grid.size() - 1;
        grid.x_lim = grid._grid[0].size() - 1;
        return grid;
    }
};

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int> &Map,
              std::pair<int, int> MapDimensions,
              std::vector<int> &OutPath);

int main(int argc, char *argv[]) {
    std::vector<int> OutPath;

    std::chrono::high_resolution_clock::time_point start_time, stop_time;
    start_time = std::chrono::high_resolution_clock::now();
    bool c = FindPath(StartPoint, TargetPoint, MapData,MapDimensionsData, OutPath);
    stop_time = std::chrono::high_resolution_clock::now();

    printf("Target is %s\n", c ? "reachable" : "unreachable");
    std::chrono::duration<double, std::milli> ms_double = (stop_time - start_time) / 1000;
    printf("Time taken: %f s\n", ms_double.count());
}

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int> &Map,
              std::pair<int, int> MapDimensions,
              std::vector<int> &OutPath) {

    Grid grid = Grid::CreateGrid(MapDimensions, Map);
    Node *StartPoint = grid.GetNodeAt(Start.first, Start.second);
    Node *EndPoint = grid.GetNodeAt(Target.first, Target.second);

    EndPoint->distance = 0;

    std::vector<Node*> ToVisit;
    std::vector<Node*> neighbours;

    ToVisit.emplace_back(EndPoint);
    for (int i = 0; i < ToVisit.size(); i++) {
        grid.GetNeighboursOf(*ToVisit[i], neighbours);
        for (auto &n: neighbours) {
            if (n->distance == NOT_VISITED) {
                n->distance = ToVisit[i]->distance + 1;
                ToVisit.emplace_back(n);
            }
        }
    }

    for (auto y = 0; y < MapDimensions.second; y++) {
        std::cout << "|";
        for (auto x = 0; x < MapDimensions.first; x++) {
            if (grid.GetNodeAt(x, y)->distance == UNREACHABLE)
                std::cout << std::setw(3) << "xx" << "|";
            else
                std::cout << std::setw(3) << grid.GetNodeAt(x, y)->distance << "|";
        }
        printf("\n");
    }

    if (StartPoint->distance == NOT_VISITED)
        return false;

    while (StartPoint->distance != 0) {
        neighbours.clear();
        grid.GetNeighboursOf(*StartPoint, neighbours);
        for (auto &node: neighbours) {
            if (node->distance < StartPoint->distance) {
                OutPath.emplace_back(grid.ConvertFrom2Dto1D(*node));
                StartPoint = node;
                break;
            }
        }
    }
    return true;
}
