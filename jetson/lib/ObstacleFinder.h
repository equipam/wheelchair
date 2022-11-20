#if !defined(OBSTACLE_FINDER_h)
#define OBSTACLE_FINDER_h

#include <vector>
#include <iostream>
#include <unordered_set>
#include "HPS3DUser_IF.h"

namespace ObstacleFinder
{
    std::vector<std::vector<int>> find(HPS3D_PointCloudData_t cloud, int maxRansacIterations, float ransacThreshold, float clusteringThreshold);
} // namespace ObstacleFinder


#endif // OBSTACLE_FINDER_h
