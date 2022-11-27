#if !defined(CLUSTERING_H)
#define CLUSTERING_H

#include <vector>
#include <chrono>
#include <string>
#include "kdtree.h"

namespace Clustering
{
    std::vector<std::vector<int>> euclideanCluster(const std::vector<std::vector<float>>& points, KdTree* tree, float distanceTol);
} // namespace Clustering


#endif // CLUSTERING_H
