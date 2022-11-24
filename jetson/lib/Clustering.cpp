/* \author Aaron Brown */
// Quiz on implementing simple RANSAC line fitting

#include "Clustering.h"

namespace Clustering
{

    void clusterHelper(int index, const std::vector<std::vector<float>> points, std::vector<int>& cluster, std::vector<bool>& processed, KdTree* tree, float distanceTol) {
        processed[index] = true;
        cluster.push_back(index);

        std::vector<int> nearest = tree->search(points[index], distanceTol);

        for (int id : nearest) {
            if (!processed[id]) {
                clusterHelper(id, points, cluster, processed, tree, distanceTol);
            }
        }
    }

    std::vector<std::vector<int>> euclideanCluster(const std::vector<std::vector<float>>& points, KdTree* tree, float distanceTol) {

        std::vector<std::vector<int>> clusters;

        std::vector<bool> processed(points.size(), false);

        int i = 0;
        while (i < points.size()) {
            if (processed[i]) {
                i++;
                continue;
            }

            std::vector<int> cluster;
            clusterHelper(i, points, cluster, processed, tree, distanceTol);
            clusters.push_back(cluster);
            i++;
        }

        // Return list of indices for each cluster
        return clusters;
    }
    
} // namespace Clustering



/*
int main () {

	// Create data
	std::vector<std::vector<float>> points = { {-6.2,7,1}, {-6.3,8.4,1}, {-5.2,7.1,1}, {-5.7,6.3,1}, {7.2,6.1,1}, {8.0,5.3,1}, {7.2,7.1,1}, {0.2,-7.1,1}, {1.7,-6.9,1}, {-1.2,-7.2,1}, {2.2,-8.9,1} };

	KdTree* tree = new KdTree;
  
    for (int i=0; i<points.size(); i++) 
    	tree->insert(points[i],i); 
  
  	std::cout << "Test Search" << std::endl;
  	std::vector<int> nearby = tree->search({-6, 7}, 3.0);
  	for(int index : nearby)
      std::cout << index << ",";
  	std::cout << std::endl;

  	// Time segmentation process
  	auto startTime = std::chrono::steady_clock::now();
  	//
  	std::vector<std::vector<int>> clusters = euclideanCluster(points, tree, 3.0);
  	//
  	auto endTime = std::chrono::steady_clock::now();
  	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
  	std::cout << "clustering found " << clusters.size() << " and took " << elapsedTime.count() << " milliseconds" << std::endl;

}
*/