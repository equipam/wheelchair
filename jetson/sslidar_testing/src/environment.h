#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

void cityBlock(pcl::visualization::PCLVisualizer::Ptr& viewer, ProcessPointClouds<pcl::PointXYZ> *pointProcessorI, const pcl::PointCloud<pcl::PointXYZ>::Ptr &inputCloud);
void initCamera(CameraAngle setAngle, pcl::visualization::PCLVisualizer::Ptr& viewer);

#endif // ENVIRONMENT_H
