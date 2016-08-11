// OpenGLDC.cpp: implementation of the COpenGLDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGLDC.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGLDC::COpenGLDC(HWND hWnd):m_hWnd(hWnd)
{
	HWND	m_hWnd = NULL;
	// 渲染场境句柄
	HGLRC	m_hRC = NULL;
	// 设备场境句柄
	HDC		m_hDC = NULL;
}

COpenGLDC::~COpenGLDC()
{

}

BOOL COpenGLDC::InitDC()
{
	if (m_hWnd == NULL) return FALSE;
	
	m_Camera.init(); // 初始化照相机设置

	m_hDC = ::GetDC(m_hWnd);			// 获取设备场境

	// 像素格式结构体
	PIXELFORMATDESCRIPTOR pfdWnd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Structure size.
		1,                             // Structure version number.
		PFD_DRAW_TO_WINDOW |           // Property flags.
		PFD_SUPPORT_OPENGL |
 		PFD_DOUBLEBUFFER,              // 开启OPenGL的双缓冲
		PFD_TYPE_RGBA,                 // 启用RGBA绘图模式
		24,                            // 24-bit color.
		0, 0, 0, 0, 0, 0,              // Not concerned with these.
		0, 0, 0, 0, 0, 0, 0,           // No alpha or accum buffer.
		32,                            // 32-bit depth buffer.
		0, 0,                          // No stencil or aux buffer.
		PFD_MAIN_PLANE,                // Main layer type.
		0,                             // Reserved.
		0, 0, 0                        // Unsupported.
	};

	// 设置像素格式
	int pixelformat;
    if ( (pixelformat = ChoosePixelFormat(m_hDC, &pfdWnd)) == 0 )
	{
		AfxMessageBox(_T("ChoosePixelFormat to wnd failed"));
		return FALSE;
	}

    if (SetPixelFormat(m_hDC, pixelformat, &pfdWnd) == FALSE)
        AfxMessageBox(_T("SetPixelFormat failed"));

	m_hRC=wglCreateContext(m_hDC);		// 创建渲染场境

	VERIFY(wglMakeCurrent(m_hDC,m_hRC));// 当前化渲染场境

	GLSetupRC();                        // 初始化渲染场境

	wglMakeCurrent(NULL,NULL);          // 非当前化渲染场境

	return m_hRC!=0;

}


void COpenGLDC::GLResize(int w,int h)
{
	wglMakeCurrent(m_hDC,m_hRC);

	// Prevent a divide by zero
	if(h == 0) h = 1;
	if(w == 0) w = 1;
	m_Camera.set_screen(w,h); // 调用照相机类设置窗口尺寸

	wglMakeCurrent(NULL,NULL);
}

void COpenGLDC::GLSetupRC()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glEnable(GL_COLOR_MATERIAL);

	// Lighting components 设置光源
	GLfloat  ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat  diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat	 lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// 设置材料性质
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specular);
	glMateriali(GL_FRONT,GL_SHININESS,100);

	// 设置背景色（黑色）
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //background color

	// default color 设置材料的默认颜色
	glColor3ub(0, 0, 255);

}


void COpenGLDC::Ready()
{
	wglMakeCurrent(m_hDC,m_hRC); // 当前化渲染场境

	m_Camera.projection(); // 绘制图形之前的取景

	// 清除颜色缓存和深度缓存
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void COpenGLDC::Finish()
{
	glFlush(); // 刷新缓存

	SwapBuffers(m_hDC); // 交换帧存

	wglMakeCurrent(m_hDC,NULL); // 非当前化渲染场境

}

void COpenGLDC::GLRelease()
{
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}

