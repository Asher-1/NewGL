// OpenGLDC.h: interface for the COpenGLDC class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OPENGLDC_H
#define _OPNEGLDC_H

#include "gl/gl.h"
#include "gl/glu.h"

#include "gl/glaux.h"
#pragma comment(lib, "glaux")// ����ӵ����������ó����޷�ʶ����ⲿ����
#pragma comment(lib, "legacy_stdio_definitions") // ǿ�Ƽ��ݾɵĴ��룬����ͨ��

#include "camera.h"

class COpenGLDC : public CObject  
{
public:
	// �������������
	COpenGLDC(HWND hWnd);
	virtual ~COpenGLDC();

private:
	// �������ڵľ��
	HWND	m_hWnd;

	// ��Ⱦ�������
	HGLRC	m_hRC;

	// �豸�������
	HDC		m_hDC;

public:
	// �����������ȡ������
	GCamera		m_Camera;

public:
	
	BOOL InitDC(); // initialize ��ʼ��

	void GLResize(int cx,int cy); // ��Ӧ���ڳߴ�仯

	void GLSetupRC(); // ������Ⱦ����

	void Ready(); // ��ͼǰ׼������

	void Finish();// ������ͼ����

	void GLRelease(); // �ͷ��ڴ�
};

#endif
