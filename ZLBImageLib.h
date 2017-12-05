/****************************************************************************
 * Copyright (C) 2004-2007  ZLB-its Co.,Ltd.  http://www.ZLB-its.com
 *
 * File      : ZLBImageLib.h  
 * Purpose   : Header file for ZLBImage library
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
#pragma once

#ifndef __ZLB_IMAGE_LIB_H__
#define __ZLB_IMAGE_LIB_H__

typedef struct ZLBImageStruct
{
    int width;
    int height;
    int depth;
	int channels;
	int widthstep;
    char* data;
}
ZLBImageStruct;

/*声明图象大小结构*/
typedef struct 
{
   int width;
   int height;
}
ZLBImageSize;

/*图像坐标结构*/
typedef struct
{
	int ix;
	int iy;
}
ZLBPoint;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
}
ZLBImageRect;

#ifdef __cplusplus
extern "C" {
#endif


///* 读取图像 */
//bool __stdcall ZLBLoadImage(LPSTR imageFileName);

/* 得到图像参数 */
//void __stdcall ZLBGetImage(char** imageData, int* width, int* height, int* depth, int* channels);

//* 释放图像内存 */
//void __stdcall ZLBReleaseImage();

/* 释放所有占用的内存资源 */
void __stdcall ZLBImageDllRelease();

/* 读取图像 */
ZLBImageStruct* __stdcall ZLBLoadImage(LPSTR imageFileName);

/*读取图像内存*/
ZLBImageStruct* __stdcall ZLBLoadMemImage(unsigned char *chJpegLength,int iJpegLength);

/*保存图像内存*/
bool __stdcall ZLBSaveMemImage(ZLBImageStruct *pImageStruct,unsigned char **chJpegChar,int *iJpegLength,int iJpegQuality);

/* 释放图像内存 */
void __stdcall ZLBReleaseImage(ZLBImageStruct** ppImage,int iReleaseMode);

/* 保存内存图像到文件 */
bool __stdcall ZLBSaveImage(LPSTR imageFileName, char* imageData, int width, int height, int depth, int channels,int iJpegQuality);

/*设置图像存储质量参数*/
void __stdcall ZLBSetImageQuality(float fQuality);

/*垂直翻转图像数据指针*/
void __stdcall ZLBFlipImage(char *imageData,int width,int height,int depth,int channels);

/* 得到图像坐标 x,y 所对应的数据指针 */
void __stdcall ZLBGetPixPointer(char *imageData, int width, int height, int depth, int channels, int x, int y, char **pxy);

/* 创建一个图像空间 */
ZLBImageStruct* __stdcall ZLBCreateImage(int width, int height, int depth, int channels);

/* 源图像拷贝到目的图像中去 */
/* 需要拷贝的源图像区域和目的图像区域分别由 sx,sy...dx,dy,... 指定 */
void __stdcall ZLBCopyImage(ZLBImageStruct* psourceImage, int sx, int sy, int swidth, int sheight, 
							ZLBImageStruct* pdestImage, int dx, int dy, int dwidth, int dheight);


/* 将文字叠加到图像中 */
/* x, y 为叠加位置 */
/* 所叠加文字颜色定义: 0 - 红色, 1 - 绿色, 2 - 蓝色 3 -白色 4 - 黑色 */
/* 所叠加字符透明度 0.0 - 1.0 */
/* size为 所叠加字符的字体的大小*/
/* fCharSpace字符间距*/
void __stdcall ZLBPutTextToImage(ZLBImageStruct* pImage, char* pText, int x, int y, int color, float size,float fCharSpace, float transparency);

/*绘制图象区域框*/
/*ZLBImageRect 绘制车牌区域*/
/*color: 0 - 红色, 1 - 绿色, 2 - 蓝色*/
/*thickness 车牌的粗细*/
void __stdcall ZLBDrawPlateRect(ZLBImageStruct *pImage,ZLBImageRect thisImageRect,LONG color,int thickness);

/*缩放图象区域大小*/
/*pSourceImage 源图象数据指针*/
/*pDestImage   缩放后图象数据指针*/
void __stdcall ZLBReSizeImage(ZLBImageStruct *pSourceImage,ZLBImageStruct *pdestImage); 

/*图像通道转换*/
/*pSourceImage 源图象数据指针*/
/*pDestImage   缩放后图象数据指针*/
/*iConvertMode 转换模式 0-表示彩色转换黑白 1-黑白转彩色*/
void __stdcall ZLBConvertImage(ZLBImageStruct *pSourceImage,ZLBImageStruct *pdestImage,int iConvertMode);

/*画图像直线*/
/*pSourceImage 源图象数据指针*/
/*startPoint 绘制的起始坐标*/
/*endPoint 绘制的结束坐标 */
/*color绘制直线的颜色  0 - 红色, 1 - 绿色, 2 - 蓝色 3-黑色 4-白色*/
/*fLineThickness 线段粗细*/
void __stdcall ZLBDrawLine(ZLBImageStruct *pSourceImage,ZLBPoint startPoint,ZLBPoint endPoint,int color,int iLineThickness);


/*将AVI文件头写入AVI文件中*/
/*pAviFileName 即将写入的文件名*/
/*iVideoFps    AVI的帧率*/
/*iVideoWidth  AVI的视频宽度*/
/*iVideoHeight  AVI的视频高度*/
/*iVideoType   AVI的视频格式 0-无压缩 1-MJpeg  -1选择编码器*/
void* __stdcall ZLBCreateAviHeader(const char* pAviFileName,int iVideoFps,int iVideoWidth,int iVideoHeight,int iVideoType);

/*将图像数据帧写入AVI文件中*/
/*pAviHandle   AVI句柄*/
/*pImageData   图像数据指针*/
/*iImageWidth  单帧宽度*/
/*iImageHeight 单帧高度*/
/*iImageSize   单帧图像大小*/
/*返回参数 1-插入成功 0-插入失败*/
bool __stdcall ZLBAddFrameToAvi(void *pAviHandle,unsigned char *pImageData,int iVideoWidth,int iVideoHeight,int iVideoSize);


/*关闭AVI文件*/
/*pAviHandle   AVI句柄*/
bool __stdcall ZLBCloseAvi(void *pAviHandle);

#ifdef __cplusplus
}
#endif

#endif 
