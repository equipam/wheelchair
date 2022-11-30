/* \author Aaron Brown */
// Create simple 3d highway enviroment using PCL
// for exploring self-driving car sensors

#include "render.h"
#include "processPointClouds.h"
// using templates for processPointClouds so also include .cpp to help linker
#include "processPointClouds.cpp"
#include "HPS3DUser_IF.h"


void cityBlock(pcl::visualization::PCLVisualizer::Ptr& viewer, std::pair<pcl::PointCloud<pcl::PointXYZ>::Ptr, pcl::PointCloud<pcl::PointXYZ>::Ptr> pair_cloud, std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> cloudClusters) {
    
    // pcl::PointCloud<pcl::PointXYZI>::Ptr filterCloud = pointProcessorI->FilterCloud(inputCloud, 0.2f, Eigen::Vector4f (-10, -5, -2, 1), Eigen::Vector4f (25, 7, 2, 1));
    // pcl::PointCloud<pcl::PointXYZI>::Ptr filterCloud = pointProcessorI->FilterCloud(inputCloud, 0.3, Eigen::Vector4f (-20, -6, -3, 1), Eigen::Vector4f (30, 7, 2, 1));

    //renderPointCloud(viewer,inputCloud,"inputCloud");

    // std::pair<pcl::PointCloud<pcl::PointXYZI>::Ptr,
    // pcl::PointCloud<pcl::PointXYZI>::Ptr> pair_cloud =
    // pointProcessorI->SegmentPlane(filterCloud, 100, 0.2);
    
    renderPointCloud(viewer, pair_cloud.first, "obstacle_cloud", Color(1,0,0));
    renderPointCloud(viewer, pair_cloud.second, "obstacle_road", Color(0,1,0));

    int clusterID{};
    std::vector<Color> colors{Color(1,0,0), Color(0,1,0), Color(0,0,1)};
    for(pcl::PointCloud<pcl::PointXYZ>::Ptr cluster: cloudClusters) {
        std::cout << "cluster size";
        //pointProcessorI->numPoints(cluster);
        renderPointCloud(viewer, cluster, "obstacle_cloud", Color(0,0,1));
        //Box box = pointProcessorI->BoundingBox(cluster);
        //renderBox(viewer, box, clusterID);
        //++clusterID;
    }
}

//setAngle: SWITCH CAMERA ANGLE {XY, TopDown, Side, FPS}
void initCamera(CameraAngle setAngle, pcl::visualization::PCLVisualizer::Ptr& viewer)
{

    viewer->setBackgroundColor (0, 0, 0);
    
    // set camera position and angle
    viewer->initCameraParameters();
    // distance away in meters3
    int distance = 16;
    
    switch(setAngle)
    {
        case XY : viewer->setCameraPosition(-distance, -distance, distance, 1, 1, 0); break;
        case TopDown : viewer->setCameraPosition(0, 0, distance, 1, 0, 1); break;
        case Side : viewer->setCameraPosition(0, -distance, 0, 0, 0, 1); break;
        case FPS : viewer->setCameraPosition(-10, 0, 0, 0, 0, 1);
    }

    if(setAngle!=FPS)
        viewer->addCoordinateSystem (1.0);
}

/*
int main (int argc, char** argv)
{
    std::cout << "Checkpoint 0" << std::endl;
    HPS3D_PointCloudData_t cloud;
	cloud.height = 10;
	cloud.width = 10;
	cloud.points = 100;
    cloud.point_data = (HPS3D_PerPointCloudData_t*)malloc(sizeof(HPS3D_PerPointCloudData_t)*cloud.points);
	size_t k = 0;
    srand(time(NULL));
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			cloud.point_data[k].x = i;
			cloud.point_data[k].y = j;
			cloud.point_data[k].z = (float)(rand() % 100);
			k++;
            printf("%.2f\n", cloud.point_data[k].z);
		}
	}

    std::cout << "Checkpoint 1" << std::endl;

    pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    CameraAngle setAngle = XY;
    initCamera(setAngle, viewer);

    std::cout << "Checkpoint 2" << std::endl;

    ProcessPointClouds<pcl::PointXYZ> *pointProcessorI = new ProcessPointClouds<pcl::PointXYZ>();

    std::cout << "create processor" << std::endl;

    pcl::PointCloud<pcl::PointXYZ>::Ptr inputCloudI(new pcl::PointCloud<pcl::PointXYZ>);

    std::cout << "create inputCloudI" << std::endl;

    inputCloudI->is_dense = true;
    inputCloudI->width = cloud.width;
    inputCloudI->height = cloud.height;

    std::cout << "set width height" << std::endl;

    inputCloudI->points.resize(cloud.points);

    std::cout << "resize" << std::endl;
    for (size_t i = 0; i < cloud.points; i++) {
        inputCloudI->push_back(pcl::PointXYZ(cloud.point_data[i].x, cloud.point_data[i].y, cloud.point_data[i].z));
    }

    std::cout << "Checkpoint 3" << std::endl;

    while (!viewer->wasStopped ())
    {   
        k = 0;
        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                inputCloudI->points[k].x = i;
                inputCloudI->points[k].y = j;
                inputCloudI->points[k].z = (float)(rand() % 10);
                k++;
            }
        }
        viewer->removeAllPointClouds();
        viewer->removeAllShapes();
        cityBlock(viewer, pointProcessorI, inputCloudI);
        
        viewer->spinOnce ();
    } 
    free(cloud.point_data);
}
*/