// PCL lib Functions for processing point clouds 

#include "processPointClouds.h"
#include <iostream>
#include <unordered_set>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>


//constructor:
template<typename PointT>
ProcessPointClouds<PointT>::ProcessPointClouds() {}


//de-constructor:
template<typename PointT>
ProcessPointClouds<PointT>::~ProcessPointClouds() {}


template<typename PointT>
void ProcessPointClouds<PointT>::numPoints(typename pcl::PointCloud<PointT>::Ptr cloud)
{
    std::cout << cloud->points.size() << std::endl;
}

template<typename PointT>
std::pair<typename pcl::PointCloud<PointT>::Ptr, typename pcl::PointCloud<PointT>::Ptr> ProcessPointClouds<PointT>::myRansacPlane(typename pcl::PointCloud<PointT>::Ptr cloud, int maxIterations, float distanceThreshold)
{
    // My implementation of RANSAC for segmenting planes. 

    typename pcl::PointCloud<PointT>::Ptr cloud_obstacle (new pcl::PointCloud<PointT> ());
    typename pcl::PointCloud<PointT>::Ptr cloud_road (new pcl::PointCloud<PointT> ());

    std::unordered_set<int> inliersResult;
	srand(time(NULL));
	
	// TODO: Fill in this function

	while(maxIterations-- >= 0) {
		std::unordered_set<int> inliers_set;

		while(inliers_set.size() < 3) 
			inliers_set.insert(rand() % (cloud->points.size()));

		float x1{}, x2{}, x3{}, y1{}, y2{}, y3{}, z1{}, z2{}, z3{}, a{}, b{}, c{}, d{};

		auto itr = inliers_set.begin();
		x1 = cloud->points[*itr].x;
		y1 = cloud->points[*itr].y;
		z1 = cloud->points[*itr].z;
		itr++;
		x2 = cloud->points[*itr].x;
		y2 = cloud->points[*itr].y;
		z2 = cloud->points[*itr].z;
		itr++;
		x3 = cloud->points[*itr].x;
		y3 = cloud->points[*itr].y;
		z3 = cloud->points[*itr].z;

		a = ((y2-y1)*(z3-z1)) - ((z2-z1)*(y3-y1));
		b = ((z2-z1)*(x3-x1)) - ((x2-x1)*(z3-z1));
		c = ((x2-x1)*(y3-y1)) - ((y2-y1)*(x3-x1));
		d = -(a*x1 + b*y1 + c*z1);

		for(int i=0; i < cloud->points.size(); i++) {
			if(inliers_set.count(i))
				continue;

			float x0{}, y0{}, z0{}, dist{};
			x0 = cloud->points[i].x;
			y0 = cloud->points[i].y;
			z0 = cloud->points[i].z;

			dist = fabs((a*x0)+(b*y0)+(c*z0)+d) / sqrt((a*a) + (b*b) + (c*c));

			if(dist <= distanceThreshold)
				inliers_set.insert(i);
		}

		if(inliers_set.size() > inliersResult.size())
			inliersResult = inliers_set;

	}

	for(int index = 0; index < cloud->points.size(); index++)
	{
		PointT point = cloud->points[index];
		if(inliersResult.count(index))
			cloud_road->points.push_back(point);
		else
			cloud_obstacle->points.push_back(point);
	}

    return std::pair<typename pcl::PointCloud<PointT>::Ptr, typename pcl::PointCloud<PointT>::Ptr>(cloud_obstacle, cloud_road);
}

template<typename PointT>
void ProcessPointClouds<PointT>::myclusterTemp(int id, std::vector<int> &cluster, typename pcl::PointCloud<PointT>::Ptr cloud, float distanceTol, KdTree* tree, std::vector<bool> points_processed) {

    // std::cout << "Entered helper clustering function" << std::endl;
	points_processed[id] = true;
	cluster.push_back(id);

	std::vector<int> clust_id = tree->search(cloud->points[id], distanceTol);

	for(auto &i:clust_id) {
		if(!points_processed[i]) {
			myclusterTemp(i, cluster, cloud, distanceTol, tree, points_processed);
		}
	}
}

template<typename PointT>
std::vector<typename pcl::PointCloud<PointT>::Ptr> ProcessPointClouds<PointT>::myeuclideanCluster(typename pcl::PointCloud<PointT>::Ptr cloud, float clusterTolerance, int minSize, int maxSize)
{

	// My implementation of Euclidean Clustering
    auto startTime = std::chrono::steady_clock::now();

    std::vector<typename pcl::PointCloud<PointT>::Ptr> clusters;
    std::vector<std::vector<float>> points;

    KdTree *tree = new KdTree;

    for(int i=0; i < cloud->points.size(); i++) {
        PointT point = cloud->points[i];
        points.push_back({point.x, point.y, point.z});
        tree->insert({point.x, point.y, point.z}, i);
    }

    std::vector<std::vector<int>> clustResult = euclideanCluster(points, tree, clusterTolerance);

    for(const auto &index: clustResult) {
        if(index.size() < minSize || index.size() > maxSize)
            continue;

        typename pcl::PointCloud<PointT>::Ptr cluster(new pcl::PointCloud<PointT> ());
        for(const auto &id:index) 
            cluster->points.push_back(cloud->points[id]);
    
        cluster->width = cluster->points.size();
        cluster->height = 1;
        cluster->is_dense = true;
        clusters.push_back(cluster);
    }

    auto endTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "clustering took " << elapsedTime.count() << " milliseconds and found " << clusters.size() << " clusters" << std::endl;
    
	return clusters;

}

template<typename PointT>
Box ProcessPointClouds<PointT>::BoundingBox(typename pcl::PointCloud<PointT>::Ptr cluster)
{

    // Find bounding box for one of the clusters
    PointT minPoint, maxPoint;
    pcl::getMinMax3D(*cluster, minPoint, maxPoint);

    Box box;
    box.x_min = minPoint.x;
    box.y_min = minPoint.y;
    box.z_min = minPoint.z;
    box.x_max = maxPoint.x;
    box.y_max = maxPoint.y;
    box.z_max = maxPoint.z;

    return box;
}

/*
template<typename PointT>
void ProcessPointClouds<PointT>::savePcd(typename pcl::PointCloud<PointT>::Ptr cloud, std::string file)
{
    pcl::io::savePCDFileASCII (file, *cloud);
    std::cerr << "Saved " << cloud->points.size () << " data points to "+file << std::endl;
}


template<typename PointT>
typename pcl::PointCloud<PointT>::Ptr ProcessPointClouds<PointT>::loadPcd(std::string file)
{

    typename pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);

    if (pcl::io::loadPCDFile<PointT> (file, *cloud) == -1) //* load the file
    {
        PCL_ERROR ("Couldn't read file \n");
    }
    std::cerr << "Loaded " << cloud->points.size () << " data points from "+file << std::endl;

    return cloud;
}


template<typename PointT>
std::vector<boost::filesystem::path> ProcessPointClouds<PointT>::streamPcd(std::string dataPath)
{

    std::vector<boost::filesystem::path> paths(boost::filesystem::directory_iterator{dataPath}, boost::filesystem::directory_iterator{});

    // sort files in accending order so playback is chronological
    sort(paths.begin(), paths.end());

    return paths;

}*/