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
	// ��Ⱦ�������
	HGLRC	m_hRC = NULL;
	// �豸�������
	HDC		m_hDC = NULL;
}

COpenGLDC::~COpenGLDC()
{

}

BOOL COpenGLDC::InitDC()
{
	if (m_hWnd == NULL) return FALSE;
	
	m_Camera.init(); // ��ʼ�����������

	m_hDC = ::GetDC(m_hWnd);			// ��ȡ�豸����

	// ���ظ�ʽ�ṹ��
	PIXELFORMATDESCRIPTOR pfdWnd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Structure size.
		1,                             // Structure version number.
		PFD_DRAW_TO_WINDOW |           // Property flags.
		PFD_SUPPORT_OPENGL |
 		PFD_DOUBLEBUFFER,              // ����OPenGL��˫����
		PFD_TYPE_RGBA,                 // ����RGBA��ͼģʽ
		24,                            // 24-bit color.
		0, 0, 0, 0, 0, 0,              // Not concerned with these.
		0, 0, 0, 0, 0, 0, 0,           // No alpha or accum buffer.
		32,                            // 32-bit depth buffer.
		0, 0,                          // No stencil or aux buffer.
		PFD_MAIN_PLANE,                // Main layer type.
		0,                             // Reserved.
		0, 0, 0                        // Unsupported.
	};

	// �������ظ�ʽ
	int pixelformat;
    if ( (pixelformat = ChoosePixelFormat(m_hDC, &pfdWnd)) == 0 )
	{
		AfxMessageBox(_T("ChoosePixelFormat to wnd failed"));
		return FALSE;
	}

    if (SetPixelFormat(m_hDC, pixelformat, &pfdWnd) == FALSE)
        AfxMessageBox(_T("SetPixelFormat failed"));

	m_hRC=wglCreateContext(m_hDC);		// ������Ⱦ����

	VERIFY(wglMakeCurrent(m_hDC,m_hRC));// ��ǰ����Ⱦ����

	GLSetupRC();                        // ��ʼ����Ⱦ����

	wglMakeCurrent(NULL,NULL);          // �ǵ�ǰ����Ⱦ����

	return m_hRC!=0;

}


void COpenGLDC::GLResize(int w,int h)
{
	wglMakeCurrent(m_hDC,m_hRC);

	// Prevent a divide by zero
	if(h == 0) h = 1;
	if(w == 0) w = 1;
	m_Camera.set_screen(w,h); // ��������������ô��ڳߴ�

	wglMakeCurrent(NULL,NULL);
}

void COpenGLDC::GLSetupRC()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glEnable(GL_COLOR_MATERIAL);

	// Lighting components ���ù�Դ
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

	// ���ò�������
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR,specular);
	glMateriali(GL_FRONT,GL_SHININESS,100);

	// ���ñ���ɫ����ɫ��
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f ); //background color

	// default color ���ò��ϵ�Ĭ����ɫ
	glColor3ub(0, 0, 255);

}


void COpenGLDC::Ready()
{
	wglMakeCurrent(m_hDC,m_hRC); // ��ǰ����Ⱦ����

	m_Camera.projection(); // ����ͼ��֮ǰ��ȡ��

	// �����ɫ�������Ȼ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void COpenGLDC::Finish()
{
	glFlush(); // ˢ�»���

	SwapBuffers(m_hDC); // ����֡��

	wglMakeCurrent(m_hDC,NULL); // �ǵ�ǰ����Ⱦ����

}

void COpenGLDC::GLRelease()
{
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}

