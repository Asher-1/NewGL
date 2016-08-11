// OpenGLDC.h: interface for the COpenGLDC class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OPENGLDC_H
#define _OPNEGLDC_H

#include "gl/gl.h"
#include "gl/glu.h"

#include "gl/glaux.h"
#pragma comment(lib, "glaux")// 必须加的声明，放置出现无法识别的外部符号
#pragma comment(lib, "legacy_stdio_definitions") // 强制兼容旧的代码，编译通过

#include "camera.h"

class COpenGLDC : public CObject  
{
public:
	// 构造和析构函数
	COpenGLDC(HWND hWnd);
	virtual ~COpenGLDC();

private:
	// 关联窗口的句柄
	HWND	m_hWnd;

	// 渲染场境句柄
	HGLRC	m_hRC;

	// 设备场境句柄
	HDC		m_hDC;

public:
	// 照相机，用于取景操作
	GCamera		m_Camera;

public:
	
	BOOL InitDC(); // initialize 初始化

	void GLResize(int cx,int cy); // 对应窗口尺寸变化

	void GLSetupRC(); // 设置渲染场境

	void Ready(); // 绘图前准备函数

	void Finish();// 结束绘图函数

	void GLRelease(); // 释放内存
};

#endif
