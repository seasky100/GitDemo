/****************************************************************************
 * Copyright (C) 2004-2007  zte-its Co.,Ltd.  http://www.zte-its.com
 *
 * File      : ZTEImageLib.h  
 * Purpose   : Header file for ZTEImage library
 * Note      : 
 * ==========================================================================
 *
 *					Software License Agreement
 * 
 * Permission is granted to anyone to use this library, in source or object 
 * code form, and to modify, compile and redistribute it to anyone else, 
 * subject to the following restrictions:
 * 
 * 1. Redistribution's of source code must retain the above copyright notice,
 *
 * 2. The author makes no warranty of any kind, either expressed or implied, 
 *    about the suitability of this software for any purpose.
 *
 * 3. The author accepts no liability of any kind for damages or other 
 *    consequences of the use of this software, even if they arise from 
 *    defects in the software.
 *
 ****************************************************************************/
// 

#include <string>
#include <vector>
using namespace std;
#pragma once

#ifndef __ZLB_COMMON_LIB_H__
#define __ZTE_COMMON_LIB_H__

	/*打开文件夹*/
	extern "C" __declspec(dllexport) bool ZLBOpenFolder(char* chFloderPath,char* chDefaultDir);
	/*判断文件是否存在*/
	extern "C" __declspec(dllexport) bool ZLBIsPathExist(char* pPathName);
	/*获取当前程序的文件路径*/
	extern "C" __declspec(dllexport) char* ZLBGetCurrentPath();
	/*获取当前程序名*/
	extern "C" __declspec(dllexport) char* ZLBGetExeName();
	/*获取当前程序名以及文件路径*/
	extern "C" __declspec(dllexport) char* ZLBGetCurrentPathAndName();
	/*获取配置文件路径*/
	extern "C" __declspec(dllexport) char* ZLBGetConfigPath();
	//已知文件全路径获得不带文件名的路径
	extern "C" __declspec(dllexport) char* ZLBGetPath(char* sFileFullName);
	/*打开某个文件*/
	extern "C" __declspec(dllexport) void ZLBOpenFile(char* sFileName);
	/*打开文件夹*/
	extern "C" __declspec(dllexport) void ZLBCreateDirectory(char* sFileName);
	/*递归遍历获得最后一层文件夹*/
	extern "C" __declspec(dllexport) int ZLBFindLastDir(char * lpPath, vector<string>& aryLastPath);
	//获得文件夹目录的最后写时间
	extern "C" __declspec(dllexport) int ZLBDeleteDir(char*  sDirName);
	//递归遍历获得所有文件
	extern "C" __declspec(dllexport) int  ZLBFindAllFiles(char * lpPath, vector<string>& aryFilePath);
	/*重启软件*/
	extern "C" __declspec(dllexport) int  ZLBRestartSoftWare();
	/*计算两个系统时钟的差值*/
	extern "C" __declspec(dllexport) int   ZLBDiffMillionSeconds(SYSTEMTIME& tm1, SYSTEMTIME& tm2);

	/************************************文件读写API*******************************************************************************/
	/*文件读写类*/
	extern "C" __declspec(dllexport) void*  ZLBIniFile(char *chIniPath);
	/*读取文件中INT类型*/
	extern "C" __declspec(dllexport) int    ZLBIniReadInt(char* sSection,char* pFieldName,int iDefaultValue,void *pUserData);
	/*读取文件中字符串类型*/
	extern "C" __declspec(dllexport) char*    ZLBIniReadString(char* sSection,char* strFieldName,char* strDefaultValue,void *pUserData);
	/*读取文件中bool类型*/
	extern "C" __declspec(dllexport) bool   ZLBIniReadBool(char* sSection,char* strFieldName,bool bDefaultValue,void *pUserData);
	/*读取文件中的double类型*/
	extern "C" __declspec(dllexport) double  ZLBIniReadDouble(char* sSection,char* strFieldName,double dDefaultValue,void *pUserData);
	/*写入文件INT类型*/
	extern "C" __declspec(dllexport) bool    ZLBIniWriteInt(char* sSection,char* strFieldName,int iFieldValue,void *pUserData);
	/*写入文件字符串类型*/
	extern "C" __declspec(dllexport) bool    ZLBIniWriteString(char* sSection,char* strFieldName,char* strFieldValue,void *pUserData);
	/*写入文件bool类型*/
	extern "C" __declspec(dllexport) bool   ZLBIniWriteBool(char* sSection,char* strFieldName,bool bFieldValue,void *pUserData);
	/*写入文件double类型*/
	extern "C" __declspec(dllexport) bool   ZLBIniWriteDouble(char* sSection,char* strFieldName,double dFieldValue,void *pUserData);
	/*获取文件名以及扩展名*/
	extern "C" __declspec(dllexport) bool   ZLBGetFileNameAndFileType(char* chPathName,char* strFileName,char* strFileType);
	//获得文件夹目录的最后写时间
	extern "C" __declspec(dllexport) BOOL ZLBGetDirTime(char*   strDirName,   SYSTEMTIME   &stime);
	/*获取到时间类型的文件名*/
	extern "C" __declspec(dllexport) char* ZLBGetFormatTime(int iYear,int iMonth,int iDay,int iHour,int iMin,int iSecond,int iMillSecond);


	/************************************************************图像界面显示类********************************************************/
	//初始化显示控件
	extern "C" __declspec(dllexport) bool   ZLBInitPictureBox(unsigned char *ucPicBoxInfo,int iPicBoxWidth,int iPicHeight,int iPicDepth,int iPicChannels);
    //将图像绘制到界面上
	extern "C" __declspec(dllexport) void   ZLBDrawPicture(CDC *pDC,unsigned char *ucPicBoxInfo,unsigned char *pImageData,int iPicBoxWidth,int iPicBoxHeight);
    //全屏显示图像

#endif


