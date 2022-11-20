/* \author Aaron Brown */
// Quiz on implementing simple RANSAC line fitting

//#include "HPS3DUser_IF.h"
#include "Ransac.h"
#include "time.h"

namespace Ransac
{
    

    std::unordered_set<int> ransac(const HPS3D_PointCloudData_t cloud, int maxIterations, float distanceTol) {
        std::unordered_set<int> inliersResult;
        srand(time(NULL));

        // For max iterations 
        for (int i = 0; i < maxIterations; i++) {
            // Randomly sample subset and fit line
            std::unordered_set<int> inliers;

            float x[2], y[2];
            int j = 0;
            // avoid picking the same point twice
            while(inliers.size() < 2) {
                auto index = rand() % (cloud.points);
                x[j] = cloud.point_data[index].x;
                y[j] = cloud.point_data[index].y;

                if (0 == inliers.count(index)) {
                    inliers.insert(index);
                    j++;
                }
            }

            float a = y[0] - y[1];
            float b = x[1] - x[0];
            float c = x[0] * y[1] - x[1] * y[0];
            // a constant number that will be used multiple times in following calculation
            float d2 = sqrt(a*a + b*b);

            // Measure distance between every point and fitted line
            for (size_t index = 0; index < cloud.points; index++) {
                if (inliers.count(index) > 0) {
                    continue;
                }

                auto point = cloud.point_data[index];
                float x = point.x;
                float y = point.y;

                float d = fabs(a*x + b*y + c) / d2;
                // If distance is smaller than threshold count it as inlier
                if (d <= distanceTol) {
                    inliers.insert(index);
                }
            }

            // Return indices of inliers from fitted line with most inliers
            if (inliers.size() > inliersResult.size()) {
                inliersResult = inliers;
            }
        }

        return inliersResult;
    }


    std::unordered_set<int> plane(const HPS3D_PointCloudData_t cloud, int maxIterations, float distanceTol) {
        std::unordered_set<int> inliersResult;
        srand(time(NULL));

        // For max iterations
        for (int i = 0; i < maxIterations; i++) {
            // Randomly sample subset and fit line
            std::unordered_set<int> inliers;

            constexpr int kDimension = 3;
            float x[kDimension], y[kDimension], z[kDimension];
            int j = 0;
            // avoid picking the same point twice
            while(inliers.size() < kDimension) {
                auto index = rand() % (cloud.points);
                x[j] = cloud.point_data[index].x;
                y[j] = cloud.point_data[index].y;
                z[j] = cloud.point_data[index].z;

                if (0 == inliers.count(index)) {
                    inliers.insert(index);
                    j++;
                }
            }

            float v0[3] = {x[1] - x[0], y[1] - y[0], z[1] - z[0]};
            float v1[3] = {x[2] - x[0], y[2] - y[0], z[2] - z[0]};

            float a = v0[1] * v1[2] - v0[2] * v1[1];
            float b = v0[2] * v1[0] - v0[0] * v1[2];
            float c = v0[0] * v1[1] - v0[1] * v1[0];
            float d = -(a * x[0] + b * y[0] + c * z[0]);
            // a constant number that will be used multiple times in following calculation
            float d2 = sqrt(a*a + b*b + c*c);

            // Measure distance between every point and fitted line
            for (size_t index = 0; index < cloud.points; index++) {
                if (inliers.count(index) > 0) {
                    continue;
                }

                auto point = cloud.point_data[index];
                float x = point.x;
                float y = point.y;
                float z = point.z;

                float distance = fabs(a*x + b*y + c*z + d) / d2;
                // If distance is smaller than threshold count it as inlier
                if (distance <= distanceTol) {
                    inliers.insert(index);
                }
            }

            // Return indices of inliers from fitted line with most inliers
            if (inliers.size() > inliersResult.size()) {
                inliersResult = inliers;
            }
        }

        return inliersResult;
    }
} // namespace Ransac



/*
int example() {

    HPS3D_PointCloudData_t cloud;
    cloud.points = 10;
    cloud.width = 2;
    cloud.height = 5;
    cloud.point_data = (HPS3D_PerPointCloudData_t*)malloc(sizeof(HPS3D_PerPointCloudData_t)*10);

    int k = 0;

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if (k < 8)
            {
                cloud.point_data[k].x = i;
                cloud.point_data[k].y = j;
                cloud.point_data[k].z = 1;
            }
            else
            {
                cloud.point_data[k].x = i;
                cloud.point_data[k].y = j;
                cloud.point_data[k].z = 2;
            }
            
            
            k++;
        }
    }
    

    std::unordered_set<int> inliers = RansacPlane(cloud, 50, 0.01);

    std::cout << inliers.size() << "\n";

    if (cloud.point_data)
    {
        free(cloud.point_data);
    }
    
	pcl::PointCloud<pcl::PointXYZ>::Ptr  cloudInliers(new pcl::PointCloud<pcl::PointXYZ>());
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloudOutliers(new pcl::PointCloud<pcl::PointXYZ>());

	for(int index = 0; index < cloud->points.size(); index++) {
		pcl::PointXYZ point = cloud->points[index];
		if(inliers.count(index))
			cloudInliers->points.push_back(point);
		else
			cloudOutliers->points.push_back(point);
	}
  	
}
*/