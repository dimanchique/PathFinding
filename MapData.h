#include "vector"

std::pair<int, int> StartPoint = {0,0};
std::pair<int, int> EndPoint = {14, 14};
const std::vector<int> MapData = {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,
                                  1,1,1,0,0,0,1,0,0,1,1,0,1,1,1,
                                  1,0,1,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,1,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,1,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,1,1,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,1,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1,
                                  1,0,0,1,1,0,1,0,0,1,1,0,1,1,1};

std::pair<int, int> MapDimensionsData = {15,15};