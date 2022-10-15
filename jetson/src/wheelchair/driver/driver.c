#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "api.h"
#include <unistd.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <math.h>

HPS3D_HandleTypeDef handle[DEV_NUM];
AsyncIObserver_t My_Observer[DEV_NUM];
ObstacleConfigTypedef ObstacleConf;
uint8_t connect_number = 0;
/*
 * User processing function,Continuous measurement or asynchronous mode
 * in which the observer notifies the callback function
 * */
void* userFunction(HPS3D_HandleTypeDef *handle,AsyncIObserver_t *event)
{
    uint16_t distance_min = -1;
    FILE *f;
	f = fopen("data.txt","w");
    if(f == NULL)
    {
        printf("Error opening data file\n");
    }
	switch(event->RetPacketType)
	{
		case SIMPLE_ROI_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.simple_roi_data[0].distance_average);
            distance_min = event->ObserverID,event->MeasureData.simple_roi_data[0].distance_min;
			break;
		case FULL_ROI_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.full_roi_data[0].distance_average);
			distance_min = event->ObserverID,event->MeasureData.full_roi_data[0].distance_min;
            break;
		case FULL_DEPTH_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.full_depth_data->distance_average);
			//printf("observer id = %d,  point_cloud_data[0]:(%f,%f,%f)\n",event->ObserverID,event->MeasureData.point_cloud_data->point_data[0].x,
			//event->MeasureData.point_cloud_data->point_data[0].y,event->MeasureData.point_cloud_data->point_data[0].z);
            distance_min = event->ObserverID,event->MeasureData.full_depth_data->distance_min;
			break;
		case SIMPLE_DEPTH_PACKET:
			printf("observer id = %d, distance average:%d\n",event->ObserverID,event->MeasureData.simple_depth_data->distance_average);
			distance_min = event->ObserverID,event->MeasureData.simple_depth_data->distance_min;
            break;
		case OBSTACLE_PACKET:
			printf("observer id = %d\n",event->ObserverID);
			printf(" Obstacle ID：%d\n",event->MeasureData.Obstacle_data->Id);
			printf(" LeftPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->LeftPoint.x,event->MeasureData.Obstacle_data->LeftPoint.y,event->MeasureData.Obstacle_data->LeftPoint.z);
			printf(" RightPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->RightPoint.x,event->MeasureData.Obstacle_data->RightPoint.y,event->MeasureData.Obstacle_data->RightPoint.z);
			printf(" UpperPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->UpperPoint.x,event->MeasureData.Obstacle_data->UpperPoint.y,event->MeasureData.Obstacle_data->UpperPoint.z);
			printf(" UnderPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->UnderPoint.x,event->MeasureData.Obstacle_data->UnderPoint.y,event->MeasureData.Obstacle_data->UnderPoint.z);
			printf(" MinPoint:(%f,%f,%f)\n",event->MeasureData.Obstacle_data->MinPoint.x,event->MeasureData.Obstacle_data->MinPoint.y,event->MeasureData.Obstacle_data->MinPoint.z);
			printf(" DistanceAverage:%d\n\n",event->MeasureData.Obstacle_data->DistanceAverage);
            distance_min = event->MeasureData.Obstacle_data->DistanceAverage;
			break;
		case NULL_PACKET:
			printf(" packet is null\n");
			break;
		default:
			printf(" system error\n");
			break;
	}
    fprintf(f, "%d", distance_min);
    if(f != NULL)
    {
        fclose(f);
    }
    
}

/*
 * Debugging use
 * */
void userPrint(char *str)
{
	printf("%s\n",str);
}


void signalHandler(int signo)
{
	HPS3D_RemoveDevice(handle);
    exit(0);
}

int main()
{
	uint32_t i=0;
	uint32_t successfulSetup = 0;
	RET_StatusTypeDef ret;

	do
	{
		// Setup program signal handler
		if(signal(SIGINT,signalHandler) == SIG_ERR)
		{
			printf("Error assigning SIG_TERM to signal handler\n");
			break;
		}
		if(signal(SIGTERM,signalHandler) == SIG_ERR)
		{
			printf("Error assigning SIG_TERM to signal handler\n");
			break;
		}

		// Setup device debug
		HPS3D_SetDebugEnable(false);
		HPS3D_SetDebugFunc(&userPrint);

		// Connect to device (USB by default)
		connect_number = HPS3D_AutoConnectAndInitConfigDevice(handle);
		printf("connect_number = %d\n",connect_number);
		if(connect_number == 0)
		{
			break;
		}

		// Initialization of observers
		// One observer and handler per device connected
		// Ammount of connected devices is stored in "connect_number", returned by HPS3D_AutoConnectAndInitConfigDevice
		for(i = 0;i < connect_number;i++)
		{
			My_Observer[i].AsyncEvent = ISubject_Event_DataRecvd;
			My_Observer[i].NotifyEnable = true;
			My_Observer[i].ObserverID = i;
			My_Observer[i].RetPacketType = NULL_PACKET;
		}

		// Adding asynchronous observers, only valid in asynchronous or continuous measurement mode
		HPS3D_AddObserver(&userFunction,handle,My_Observer);

		// No idea what this
		HPS3D_SetPointCloudEn(true);
		
		// Set devices to continuous measurement mode
		for(i = 0;i<connect_number;i++)
		{
			HPS3D_SetOpticalEnable(&handle[i],true);
			handle[i].RunMode = RUN_CONTINUOUS;
			HPS3D_SetRunMode(&handle[i]);
		}

		successfulSetup = 1;
	}while(0);

	while(successfulSetup)
	{
		// While the main sleeps the observer functions will run on device events
		usleep(100000);
	}

	
	return 0;
}

