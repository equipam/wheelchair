#if !defined(RANSAC_H)
#define RANSAC_H

#include <unordered_set>
//#include <iostream>
#include <math.h>
#include "HPS3DUser_IF.h"

namespace Ransac
{
    std::unordered_set<int> ransac(const HPS3D_PointCloudData_t cloud, int maxIterations, float distanceTol);
    std::unordered_set<int> plane(const HPS3D_PointCloudData_t cloud, int maxIterations, float distanceTol);
} // namespace Ransac



#endif // RANSAC_H
