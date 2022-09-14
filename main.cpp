#include "MapData.h"
#include <cstdio>
#include "utility"
#include "vector"
#include <chrono>

#define NOT_VISITED (-1)
#define UNREACHABLE (-999)

struct Node {
    Node(int x, int y, int distance) : x(x), y(y), distance(distance) {};
    Node(std::pair<int,int> xy, int distance) : x(xy.first), y(xy.second), distance(distance) {};

    int x, y, distance;
};

class Grid {
public:
    Grid(std::pair<int, int> MapDimensions, const std::vector<int> &Map) {
        x_lim = MapDimensions.first - 1;
        y_lim = MapDimensions.second - 1;

        for (int i = 0; i < Map.size(); i++)
        {
            auto Position = ConvertFrom1Dto2D(i);
            if (Map[i] == 0)
                _grid.emplace_back(Node(Position, UNREACHABLE));
            else
                _grid.emplace_back(Node(Position, NOT_VISITED));
        }
    };

    Node *GetNodeAt(int x, int y) { return &_grid[ConvertFrom2Dto1D(x, y)]; }

    void GetNeighboursOf(Node &n, std::vector<Node *> &neighbours) {
        Node* node;
        neighbours.clear();
        if (n.x - 1 >= 0) {
            node = GetNodeAt(n.x - 1, n.y);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
        if (n.x + 1 <= x_lim) {
            node = GetNodeAt(n.x + 1, n.y);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
        if (n.y - 1 >= 0) {
            node = GetNodeAt(n.x, n.y - 1);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
        if (n.y + 1 <= y_lim) {
            node = GetNodeAt(n.x, n.y + 1);
            if (node->distance != UNREACHABLE)
                neighbours.emplace_back(node);
        }
    }

    void Show()
    {
        for (auto y = 0; y < y_lim+1; y++) {
            printf("|");
            for (auto x = 0; x < x_lim+1; x++) {
                auto value = GetNodeAt(x, y)->distance;
                if (value == UNREACHABLE)
                {
                    printf(" xx |");
                }
                else
                    printf("%3d |", value);
            }
            printf("\n");
        }
    }

    int ConvertFrom2Dto1D(int x, int y) const {
        return x + y * (x_lim + 1);
    }

    int ConvertFrom2Dto1D(Node& n) const {
        return n.x + n.y * (x_lim + 1);
    }

    std::pair<int, int> ConvertFrom1Dto2D(int index) const {
        return { index % (x_lim+1), index / (x_lim+1) };
    }

private:
    std::vector<Node> _grid;
    int x_lim, y_lim;
};

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int> &Map,
              std::pair<int, int> MapDimensions,
              std::vector<int> &OutPath);

int main() {
    std::vector<int> OutPath;

    std::chrono::high_resolution_clock::time_point start_time, stop_time;
    start_time = std::chrono::high_resolution_clock::now();
    bool c = FindPath(StartPoint, EndPoint, MapData, MapDimensionsData, OutPath);
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

    Grid grid(MapDimensions, Map);
    Node *start_point = grid.GetNodeAt(Start.first, Start.second);
    Node *end_point = grid.GetNodeAt(Target.first, Target.second);

    end_point->distance = 0;

    std::vector<Node*> ToVisit;
    std::vector<Node*> neighbours;

    ToVisit.emplace_back(end_point);
    for (int i = 0; i < ToVisit.size(); i++) {
        if (start_point->distance != NOT_VISITED)
            break;
        grid.GetNeighboursOf(*ToVisit[i], neighbours);
        for (auto &n: neighbours) {
            if (n->distance == NOT_VISITED) {
                n->distance = ToVisit[i]->distance + 1;
                ToVisit.emplace_back(n);
            }
        }
    }

    grid.Show();

    if (start_point->distance == NOT_VISITED)
        return false;

    while (start_point->distance != 0) {
        neighbours.clear();
        grid.GetNeighboursOf(*start_point, neighbours);
        for (auto &node: neighbours) {
            if (node->distance < start_point->distance) {
                OutPath.emplace_back(grid.ConvertFrom2Dto1D(*node));
                start_point = node;
                break;
            }
        }
    }
    return true;
}
