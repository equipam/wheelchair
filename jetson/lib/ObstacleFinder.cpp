#include "ObstacleFinder.h"
#include "Clustering.h"
#include "Ransac.h"
#include "kdtree.h"

#define MAX_RANSAC_ITERATIONS 50
#define RANSAC_THRESHOLD 0.1
#define EUCLIDEAN_CLUSTER_DISTANCE_TOL 3.0

namespace ObstacleFinder
{

    std::vector<std::vector<int>> find(HPS3D_PointCloudData_t cloud, int maxRansacIterations, float ransacThreshold, float clusteringThreshold)
    {

        std::unordered_set<int> inliers = Ransac::plane(cloud, maxRansacIterations, ransacThreshold);

        int outlierAmmount = inliers.size() - cloud.points;

        std::vector<std::vector<float>> cloudOutliers(outlierAmmount);

        size_t outlierIndex = 0;
        for(size_t i = 0; i < cloud.points; i++) {
            if(inliers.count(i) == 0)
            {
                cloudOutliers[outlierIndex] = {cloud.point_data[i].x,cloud.point_data[i].y,cloud.point_data[i].z};
            }
        }

        // Create data
        //std::vector<std::vector<float>> points = { {-6.2,7,1}, {-6.3,8.4,1}, {-5.2,7.1,1}, {-5.7,6.3,1}, {7.2,6.1,1}, {8.0,5.3,1}, {7.2,7.1,1}, {0.2,-7.1,1}, {1.7,-6.9,1}, {-1.2,-7.2,1}, {2.2,-8.9,1}};

        KdTree* tree = new KdTree;

        for (int i=0; i<cloudOutliers.size(); i++) 
            tree->insert(cloudOutliers[i],i); 

        std::vector<std::vector<int>> clusters = Clustering::euclideanCluster(cloudOutliers, tree, clusteringThreshold);

        std::cout << "clustering found " << clusters.size() << std::endl;

        return clusters;
    }
    
} // namespace ObstacleFinder


