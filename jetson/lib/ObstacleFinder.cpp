#include "ObstacleFinder.h"
#include "Clustering.h"
#include "Ransac.h"
#include "kdtree.h"

#define MAX_RANSAC_ITERATIONS 50
#define RANSAC_THRESHOLD 0.1
#define EUCLIDEAN_CLUSTER_DISTANCE_TOL 3.0

namespace ObstacleFinder
{

    /// @brief Find obstacles within point cloud data from SSLidar
    /// @param cloud Point cloud data
    /// @param maxRansacIterations 
    /// @param ransacThreshold 
    /// @param clusteringThreshold 
    /// @return Array of clusters, represented by an array of indexes each
    std::vector<std::vector<int>> find(HPS3D_PointCloudData_t cloud, int maxRansacIterations, float ransacThreshold, float clusteringThreshold)
    {
        
        // First find the base plane of the scene (the road, or pavement, etc.)
        // The ransac returns inliers, so we have fewer points of interest to
        // search obstacles
        std::unordered_set<int> inliers = Ransac::plane(cloud, maxRansacIterations, ransacThreshold);

        int outlierAmmount = inliers.size() - cloud.points;

        // Save the outlier points in a different variable
        std::vector<std::vector<float>> cloudOutliers(outlierAmmount);

        size_t outlierIndex = 0;
        for(size_t i = 0; i < cloud.points; i++) {
            if(inliers.count(i) == 0)
            {
                cloudOutliers[outlierIndex] = {cloud.point_data[i].x,cloud.point_data[i].y,cloud.point_data[i].z};
            }
        }

        // Save cloud data in a KdTree <https://en.wikipedia.org//wiki/K-d_tree>
        KdTree* tree = new KdTree;

        for (size_t i=0; i<cloudOutliers.size(); i++)
        {
            tree->insert(cloudOutliers[i],i); 
        }

        // Apply euclidean clustering to find objects within the outliers
        std::vector<std::vector<int>> clusters = Clustering::euclideanCluster(cloudOutliers, tree, clusteringThreshold);

        std::cout << "clustering found " << clusters.size() << std::endl;

        return clusters;
    }
    
} // namespace ObstacleFinder


