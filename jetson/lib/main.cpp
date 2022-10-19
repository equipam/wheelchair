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
#include <JetsonGPIO.h>

#include "HPS3DUser_IF.h"

#define DEVICE_BIND "/dev/ttyACM0"
#define INTERRUPT_PIN 11 // TODO figure out the pin
#define COLLISION_DISTANCE_THRESHOLD 1 // TODO figure out the units

int gHandle = -1;
static HPS3D_MeasureData_t gMeasureData;

static bool collisionDetected = false;

void handleInterrupt(uint16_t distanceMin)
{
	if (distanceMin < COLLISION_DISTANCE_THRESHOLD && !collisionDetected)
	{
		GPIO::output(INTERRUPT_PIN, GPIO::HIGH);
		collisionDetected = true;
		return;
	}
	GPIO::output(INTERRUPT_PIN, GPIO::LOW);
	collisionDetected = false;
}

static bool handleDataReceive(HPS3D_EventType_t type, HPS3D_MeasureData_t data)
{
	int num = 0;
	int i = 0;
	uint16_t distanceMin = 0;
	switch (type)
	{
	case HPS3D_SIMPLE_ROI_EVEN: // Simple ROI data packets do not contain the depth of each point
		//printf("*************  HPS3D_SIMPLE_ROI_EVEN  ********************\n");
		{
			num = data.simple_roi_data[0].roi_num;
			int i = 0;
			for (i = 0; i < num; i++)
			{
				distanceMin += data.simple_roi_data[i].distance_min * 1/num;
			}
			break;
		}
	case HPS3D_FULL_ROI_EVEN: // Complete ROI packets
		//printf("*************  HPS3D_FULL_ROI_EVEN  ********************\n");
		{
			num = data.full_roi_data[0].roi_num;
			for (i = 0; i < num; i++)
			{
				distanceMin += data.full_roi_data[i].distance_min * 1/num;
			}
			break;
		}
	case HPS3D_SIMPLE_DEPTH_EVEN:
		distanceMin = data.simple_depth_data.distance_min;
		break;
	case HPS3D_FULL_DEPTH_EVEN: // Full depth map data packets, containing the point cloud data
		distanceMin = data.full_depth_data.distance_min;
		break;
	default:
		break;
	}

	printf("min distance: %d\n", distanceMin);

	handleInterrupt(distanceMin);

	return true;
}

static bool isReconnectEnable = true;
static bool isReconnect = false;
static void eventCallbackFunction(int handle, int eventType, uint8_t *data, int dataLen, void *userPara)
{
	switch ((HPS3D_EventType_t)eventType)
	{
	// Measurement data notification events
	case HPS3D_SIMPLE_ROI_EVEN:
		// printf("HPS3D_SIMPLE_ROI_EVEN\n");
		break;
	case HPS3D_FULL_ROI_EVEN:
		// printf("HPS3D_FULL_ROI_EVEN\n");
		break;
	case HPS3D_FULL_DEPTH_EVEN:
		// printf("HPS3D_FULL_DEPTH_EVEN\n");
		break;
	case HPS3D_SIMPLE_DEPTH_EVEN:
		printf("handle:%d!\n", handle);
		HPS3D_ConvertToMeasureData(data, &gMeasureData, (HPS3D_EventType_t)eventType);
		handleDataReceive((HPS3D_EventType_t)eventType, gMeasureData);
		break;
	case HPS3D_SYS_EXCEPTION_EVEN:
		printf("SYS ERR :%s\n", data);
		break;
	case HPS3D_DISCONNECT_EVEN:
		printf("Device disconnected!\n");
		if (isReconnectEnable && isReconnect == false)
		{
			isReconnect = true;
		}
		break;
	case HPS3D_NULL_EVEN:
		printf("HPS3D_NULL_EVEN\n");
		break;
	default:
		printf("Not known event\n");
		break;
	}
}

void signalHandler(int signo)
{
	HPS3D_StopCapture(gHandle);
	HPS3D_CloseDevice(gHandle);
	printf("Device disconnected!\n\n");
	GPIO::cleanup(INTERRUPT_PIN);
	exit(0);
}

void gpioSetup()
{
	GPIO::setmode(GPIO::BOARD);
	GPIO::setwarnings(false);
	GPIO::setup(INTERRUPT_PIN, GPIO::OUT, GPIO::LOW);
}


int main()
{
	gpioSetup();

	printf("SDK Ver:%s\n", HPS3D_GetSDKVersion());
	
	int handle = -1;
	HPS3D_StatusTypeDef ret = HPS3D_RET_OK;
	do
	{
		// Initializes the memory
		ret = HPS3D_MeasureDataInit(&gMeasureData);´
		if (ret != HPS3D_RET_OK)
		{
			printf("MeasureDataInit failed, Err:%d\n", ret);
			break;
		}

		ret = HPS3D_USBConnectDevice((char *) DEVICE_BIND, &handle);

		if (ret != HPS3D_RET_OK)
		{
			printf("Equipment connection failed, Err:%d\n", ret);
			break;
		}
		printf("Equipment version for:%s\n", HPS3D_GetDeviceVersion(handle));
		printf("Equipment serial number:%s\n\n", HPS3D_GetSerialNumber(handle));

		gHandle = handle;

		// Register event callback function, used to receive continuous return packets, and invoke exception, etc;
		ret = HPS3D_RegisterEventCallback(eventCallbackFunction, NULL);
		if (ret != HPS3D_RET_OK)
		{
			printf("Register callback function failure,Err:%d\n", ret);
			break;
		}

		HPS3D_DeviceSettings_t settings;
		ret = HPS3D_ExportSettings(handle, &settings);
		if (ret != HPS3D_RET_OK)
		{
			printf("Export equipment failure parameters,Err:%d\n", ret);
			break;
		}
		printf("A resolution of:%d X %d\n", settings.max_resolution_X, settings.max_resolution_Y);
		printf("Support for maximum ROI group number:%d  The current ROI group：%d\n", settings.max_roi_group_number, settings.cur_group_id);
		printf("Support for maximum ROI quantity:%d\n", settings.max_roi_number);
		printf("Most support the machine number:%d，The current equipment more machine number:%d\n", settings.max_multiCamera_code, settings.cur_multiCamera_code);
		printf("The current user ID for the equipment：%d\n", settings.user_id);
		printf("Optical path compensation is open: %d\n\n", settings.optical_path_calibration);

		HPS3D_StartCapture(handle);
		do
		{
			if (isReconnect)
			{
				ret = HPS3D_USBConnectDevice((char *)DEVICE_BIND, &handle);
				if (ret == HPS3D_RET_OK)
				{
					HPS3D_StartCapture(handle);
					printf("Reconnection successful: equipment %d\n", handle);
					isReconnect = false;
				}
			}
			sleep(1);

		} while (1);

	} while (0);

	HPS3D_StopCapture(handle);
	HPS3D_CloseDevice(handle);
	HPS3D_MeasureDataFree(&gMeasureData);
	GPIO::cleanup(INTERRUPT_PIN);
	system("pause");
}
