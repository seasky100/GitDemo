#include "StdAfx.h"
#include "Cameras.h"


CCameras::CCameras(void)
{
}


CCameras::~CCameras(void)
{
}


int CCameras::GetCameraCount(void)
{
	int iCameraCount=0;
	int iServerCount=SapManager::GetServerCount();
	for(int i=0;i<iServerCount;i++)
	{
		int iAcqDeviceNum=SapManager::GetResourceCount(i,SapManager::ResourceAcqDevice);
		int iAcqNum=SapManager::GetResourceCount(i,SapManager::ResourceAcq);
		if(iAcqDeviceNum>0||iAcqNum>0)
		{
			SapManager::GetServerSerialNumber(i,dl[i].SN);
			dl[i].Index=i;
			iCameraCount++;
		}
	}

	return iCameraCount;
}
