#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <math.h>


#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/search/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
 

#include "HPS3DUser_IF.h"
#include "processPointClouds.h"
#include "processPointClouds.cpp"
#include "render.h"
#include "environment.h"

#include <pthread.h>

#define DEVICE_BIND "/dev/ttyACM0"
#define MAX_RANSAC_ITERATIONS 50
#define RANSAC_THRESHOLD 10.0
#define CLUSTERING_THRESHOLD 100

int g_handle = -1;
int m_handle[8] = {-1};
static HPS3D_MeasureData_t g_measureData;

pthread_mutex_t lock;

static bool collisionDetected = false;

pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
CameraAngle setAngle = XY;
ProcessPointClouds<pcl::PointXYZ> *pointProcessorI = new ProcessPointClouds<pcl::PointXYZ>();
pcl::PointCloud<pcl::PointXYZ>::Ptr inputCloudI(new pcl::PointCloud<pcl::PointXYZ>);
std::pair<pcl::PointCloud<pcl::PointXYZ>::Ptr, pcl::PointCloud<pcl::PointXYZ>::Ptr> pair_cloud;
std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> cloudClusters;

/*pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
std::vector<pcl::PointIndices> cluster_indices;
pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

void* processPoints(void* args)
{
	while (1)
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZ>);
		std::cout << "PointCloud before filtering has: " << inputCloudI->size () << " data points." << std::endl; //*
		
		// Create the filtering object: downsample the dataset using a leaf size of 1cm
		pcl::VoxelGrid<pcl::PointXYZ> vg;
		
		vg.setInputCloud (inputCloudI);
		vg.setLeafSize (0.01f, 0.01f, 0.01f);
		vg.filter (*cloud_filtered);
		std::cout << "PointCloud after filtering has: " << cloud_filtered->size ()  << " data points." << std::endl; //*
		
		// Create the segmentation object for the planar model and set all the parameters
		pcl::SACSegmentation<pcl::PointXYZ> seg;
		pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
		pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane (new pcl::PointCloud<pcl::PointXYZ> ());
		seg.setOptimizeCoefficients (true);
		seg.setModelType (pcl::SACMODEL_PLANE);
		seg.setMethodType (pcl::SAC_RANSAC);
		seg.setMaxIterations (100);
		seg.setDistanceThreshold (0.02); // 2cm
		
		int nr_points = (int) cloud_filtered->size ();
		while (cloud_filtered->size () > 0.3 * nr_points)
		{
			// Segment the largest planar component from the remaining cloud
			seg.setInputCloud (cloud_filtered);
			seg.segment (*inliers, *coefficients);
			if (inliers->indices.size () == 0)
			{
			std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
			break;
			}
		
			// Extract the planar inliers from the input cloud
			pcl::ExtractIndices<pcl::PointXYZ> extract;
			extract.setInputCloud (cloud_filtered);
			extract.setIndices (inliers);
			extract.setNegative (false);
		
			// Get the points associated with the planar surface
			extract.filter (*cloud_plane);
			std::cout << "PointCloud representing the planar component: " << cloud_plane->size () << " data points." << std::endl;
		
			// Remove the planar inliers, extract the rest
			extract.setNegative (true);
			extract.filter (*cloud_f);
			*cloud_filtered = *cloud_f;
		}
		
		// Creating the KdTree object for the search method of the extraction
		pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
		tree->setInputCloud (cloud_filtered);
		
		
		pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
		ec.setClusterTolerance (0.05); // 5cm
		ec.setMinClusterSize (100);
		ec.setMaxClusterSize (9600/4);
		ec.setSearchMethod (tree);
		ec.setInputCloud (cloud_filtered);
		ec.extract (cluster_indices);
	}
}
*/
void handleInterrupt(HPS3D_PointCloudData_t cloud)
{
	pthread_mutex_lock(&lock);
	for (size_t i = 0; i < cloud.points; i++) {
		inputCloudI->points[i].x = cloud.point_data[i].x;
		inputCloudI->points[i].y = cloud.point_data[i].y;
		inputCloudI->points[i].z = cloud.point_data[i].z;
	}
	pthread_mutex_unlock(&lock);
	return;
}

static bool PrintResultData(HPS3D_EventType_t type, HPS3D_MeasureData_t data)
{
	int num = 0;
	int i = 0;
	switch (type)
	{
	case HPS3D_SIMPLE_ROI_EVEN: //简单ROI数据包  不含每个点的深度数据
		{
			break;
		}
	case HPS3D_FULL_ROI_EVEN: //完整ROI数据包
		{
			break;
		}
	case HPS3D_SIMPLE_DEPTH_EVEN: //简单深度数据包，不含每个点距离及点云数据
		{	
			break;
		}
	case HPS3D_FULL_DEPTH_EVEN: //完整深度图数据包，含点云数据
		{
			/*printf("*************  HPS3D_FULL_DEPTH_EVEN    ********************\n");
			printf("distance_average:%d\n", data.full_depth_data.distance_average);
			printf("distance_min    :%d\n", data.full_depth_data.distance_min);
			printf("saturation_count:%d\n", data.full_depth_data.saturation_count);


			for (size_t i = 0; i < data.full_depth_data.point_cloud_data.points; i++)
			{
				printf("distance[%d]     :%d\n", i, data.full_depth_data.distance[i]);
				printf("pointCloud[%d]   :(%f,%f.%f)\n", i, data.full_depth_data.point_cloud_data.point_data[i].x,
				data.full_depth_data.point_cloud_data.point_data[i].y, data.full_depth_data.point_cloud_data.point_data[i].z);
			}
			
			printf("distance[0]     :%d\n", data.full_depth_data.distance[0]);
			printf("pointCloud[0]   :(%f,%f.%f)\n", data.full_depth_data.point_cloud_data.point_data[0].x,
				data.full_depth_data.point_cloud_data.point_data[0].y, data.full_depth_data.point_cloud_data.point_data[0].z);

			printf("distance[1]     :%d\n", data.full_depth_data.distance[1]);
			printf("pointCloud[1]   :(%f,%f.%f)\n", data.full_depth_data.point_cloud_data.point_data[1].x,
				data.full_depth_data.point_cloud_data.point_data[1].y, data.full_depth_data.point_cloud_data.point_data[1].z);
			printf("Point amount: %d\n", data.full_depth_data.point_cloud_data.points);
			printf("width: %d\n", data.full_depth_data.point_cloud_data.width);
			printf("height: %d\n",
			data.full_depth_data.point_cloud_data.height);*/
			
			handleInterrupt(data.full_depth_data.point_cloud_data);
			// printf("==========================================================\n\n");
			break;
		}
	default:
		printf("hellohellohello\n");
		break;
	}

	return true;
}

static bool isReconnectEnable = true;
static bool isReconnect = false;
static void EventCallBackFunc(int handle, int eventType, uint8_t *data,int dataLen, void *userPara)
{
	switch ((HPS3D_EventType_t)eventType)
	{
		//测量数据通知事件
		case HPS3D_SIMPLE_ROI_EVEN:	
			//printf("hello\n");
		case HPS3D_FULL_ROI_EVEN:	
			//printf("hello\n");
		case HPS3D_FULL_DEPTH_EVEN:	
			//printf("hello\n");
		case HPS3D_SIMPLE_DEPTH_EVEN:
			//printf("handle:%d!\n", handle);
			HPS3D_ConvertToMeasureData(data,&g_measureData, (HPS3D_EventType_t)eventType);
			PrintResultData((HPS3D_EventType_t)eventType, g_measureData);
			break;
		case HPS3D_SYS_EXCEPTION_EVEN: /*系统异常通知事件*/
			//printf("SYS ERR :%s\n", data);

			break;
		case HPS3D_DISCONNECT_EVEN: /*连接异常断开通知事件*/
			printf("Device disconnected!\n");
			//sleep(10);
			//HPS3D_StopCapture(handle);
			//sleep(10);
			if(isReconnectEnable && isReconnect == false)
			{
				isReconnect = true;
			}
			break;
		case HPS3D_NULL_EVEN:  //空事件通知
		default:
			//printf("hello\n");
			break;	
	}
}

void signal_handler(int signo)
{
	HPS3D_StopCapture(g_handle);
	HPS3D_CloseDevice(g_handle);
	printf("Device disconnected!\n\n");
	exit(0);
}


int main()
{
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
	int handle = -1;
	HPS3D_StatusTypeDef ret = HPS3D_RET_OK;
	initCamera(setAngle, viewer);

	pthread_t thread_id;

	inputCloudI->is_dense = true;
	inputCloudI->width = 160;
	inputCloudI->height = 60;
	inputCloudI->points.resize(160*60);
    for (size_t i = 0; i < 60; i++) {
		for (size_t j = 0; j < 160; j++)
		{
        	inputCloudI->points[i].x = i;
			inputCloudI->points[i].y = j;
			inputCloudI->points[i].z = 0;
		}	
    }
	pointProcessorI->numPoints(inputCloudI);
	//pthread_create(&thread_id, NULL, processPoints, NULL);

	do
	{
		//初始化内存
		ret = HPS3D_MeasureDataInit(&g_measureData);
		if (ret != HPS3D_RET_OK)
		{
			printf("MeasureDataInit failed,Err:%d\n", ret);
			break;
		}

		ret = HPS3D_USBConnectDevice(DEVICE_BIND, &handle);

		if (ret != HPS3D_RET_OK)
		{
			printf("设备连接失败,Err:%d\n", ret);
			break;
		}
		printf("设备版本为:%s\n", HPS3D_GetDeviceVersion(0));
		printf("设备序列号:%s\n\n", HPS3D_GetSerialNumber(0));
		if (handle == 1)
		{
			printf("设备版本为:%s\n", HPS3D_GetDeviceVersion(1));
			printf("设备序列号:%s\n\n", HPS3D_GetSerialNumber(1));
		}

		//注册事件回调函数，用于接收连续返回数据包，及调用异常等;
		ret= HPS3D_RegisterEventCallback(EventCallBackFunc, NULL);
		if (ret != HPS3D_RET_OK)
		{
			printf("注册回调函数失败,Err:%d\n", ret);
			break;

		}

		HPS3D_DeviceSettings_t settings;
		ret = HPS3D_ExportSettings(handle, &settings);
		if (ret != HPS3D_RET_OK)
		{
			printf("导出设备参数失败,Err:%d\n", ret);
			break;
		}
		printf("分辨率为:%d X %d\n", settings.max_resolution_X, settings.max_resolution_Y);
		printf("支持最大ROI分组数量为:%d  当前ROI分组：%d\n", settings.max_roi_group_number, settings.cur_group_id);
		printf("支持最大ROI数量为:%d\n", settings.max_roi_number);
		printf("支持最大多机编号为:%d，当前设备多机编号:%d\n", settings.max_multiCamera_code, settings.cur_multiCamera_code);
		printf("当前设备用户ID为：%d\n", settings.user_id);
		printf("光路补偿是否开启: %d\n\n", settings.optical_path_calibration);
		srand(69);
		bool isContinuous = false;
		int count = 0;
		HPS3D_StartCapture(handle);
		size_t clusterID;
		do
		{
			if (isReconnect)
			{
				//sleep(5);
				ret = (HPS3D_StatusTypeDef)HPS3D_EthternetReconnection(handle);
				if (ret == HPS3D_RET_OK)
				{
					HPS3D_StartCapture(handle);
					printf("重连成功:设备 %d\n", handle);
					isReconnect = false;
				}
			}
			if (!viewer->wasStopped ())
			{   
				viewer->removeAllPointClouds();
				viewer->removeAllShapes();
				pthread_mutex_lock(&lock);
				// renderPointCloud(viewer, inputCloudI, "obstacle_road", Color(0,1,0));
				//renderPointCloud(viewer, pair_cloud.first, "obstacle_cloud", Color(1,0,0));

				//
				std::vector<pcl::PointIndices> cluster_indices;
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZ>);
				std::cout << "PointCloud before filtering has: " << inputCloudI->size () << " data points." << std::endl; //*
				
				// Create the filtering object: downsample the dataset using a leaf size of 1cm
				pcl::VoxelGrid<pcl::PointXYZ> vg;
				
				vg.setInputCloud (inputCloudI);
				vg.setLeafSize(5.0f, 5.0f, 5.0f); // ! COISA A MUDAR
				vg.filter (*cloud_filtered);
				pthread_mutex_unlock(&lock);
				std::cout << "PointCloud after filtering has: " << cloud_filtered->size ()  << " data points." << std::endl; //*
				
				// Create the segmentation object for the planar model and set all the parameters
				pcl::SACSegmentation<pcl::PointXYZ> seg;
				pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
				pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
				pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane (new pcl::PointCloud<pcl::PointXYZ> ());
				seg.setOptimizeCoefficients (true);
				seg.setModelType (pcl::SACMODEL_PLANE);
				seg.setMethodType (pcl::SAC_RANSAC);
				seg.setMaxIterations (400);
				seg.setDistanceThreshold (100); // 10cm // ! COISA A MUDAR
				
				int nr_points = (int) cloud_filtered->size ();
				
				/*while (cloud_filtered->size () > 0.99 * nr_points)
				{*/
				// Segment the largest planar component from the remaining cloud
				seg.setInputCloud (cloud_filtered);
				seg.segment (*inliers, *coefficients);
				if (inliers->indices.size () == 0)
				{
				std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
				break;
				}
			
				// Extract the planar inliers from the input cloud
				pcl::ExtractIndices<pcl::PointXYZ> extract;
				extract.setInputCloud (cloud_filtered);
				extract.setIndices (inliers);
				extract.setNegative (false);
			
				// Get the points associated with the planar surface
				extract.filter (*cloud_plane);
				std::cout << "PointCloud representing the planar component: " << cloud_plane->size () << " data points." << std::endl;
			
				// Remove the planar inliers, extract the rest
				extract.setNegative (true);
				extract.filter (*cloud_f);
				*cloud_filtered = *cloud_f;
				/*}*/
				renderPointCloud(viewer, cloud_plane, "plane", Color(0,1,0));
				// Creating the KdTree object for the search method of the extraction
				pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
				tree->setInputCloud (cloud_filtered);
				
				
				pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
				ec.setClusterTolerance (70); // 5cm // ! COISA A MUDAR
				ec.setMinClusterSize (20);
				ec.setMaxClusterSize (8000);
				ec.setSearchMethod (tree);
				ec.setInputCloud (cloud_filtered);
				ec.extract (cluster_indices);
				clusterID = 1;
				for (const auto& cluster : cluster_indices)
				{
					pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZ>);
					for (const auto& idx : cluster.indices) {
						cloud_cluster->push_back((*cloud_filtered)[idx]);
					} //*
					cloud_cluster->width = cloud_cluster->size ();
					cloud_cluster->height = 1;
					cloud_cluster->is_dense = true;
					renderPointCloud(viewer, cloud_cluster, "obstacle_cloud"+std::to_string(clusterID), Color(0,0,1));
					clusterID++;
				}
				std::cout << "Found: " << clusterID  << " clusters." << std::endl; //*
				/*for(pcl::PointCloud<pcl::PointXYZ>::Ptr cluster: cloudClusters) {
					std::cout << "cluster size";
					pointProcessorI->numPoints(cluster);
					renderPointCloud(viewer, cluster, "obstacle_cloud"+std::to_string(clusterID), Color(0,0,1));
					clusterID++;
				}*/
				//pthread_mutex_unlock(&lock);

				viewer->spinOnce ();
			}
		} while (1);
	} while (0);

	//pthread_join(thread_id, NULL);
	pthread_mutex_destroy(&lock);
	HPS3D_StopCapture(handle);
	HPS3D_CloseDevice(handle);
	HPS3D_MeasureDataFree(&g_measureData);
	system("pause");
}
