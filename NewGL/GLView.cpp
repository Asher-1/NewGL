// GLView.cpp : implementation of the CGLView class
//

#include "stdafx.h"
#include "NewGL.h"

#include "GLDoc.h"
#include "GLView.h"

#include "OpenGLDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

IMPLEMENT_DYNCREATE(CGLView, CView)

BEGIN_MESSAGE_MAP(CGLView, CView)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLView construction/destruction

CGLView::CGLView()
{
	m_pGLDC = NULL;	
}

CGLView::~CGLView()
{
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs)
{

	//  Add Window style required for OpenGL before window is created
	cs.style |= WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLView drawing

void CGLView::OnDraw(CDC* pDC)
{
	if(m_pGLDC){

		m_pGLDC->Ready();

		RenderScene(m_pGLDC);

		m_pGLDC->Finish();

	}
}

/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pGLDC = new COpenGLDC(GetSafeHwnd()); // ����COpenGLDC�Ķ��󣬲����봰�ھ��

	m_pGLDC->InitDC(); // ��ʼ��COpenGLDC�Ķ���

	// �ú���Ϊϵͳ����һ�����Ϊ0�Ķ�ʱ��
	SetTimer(0, 50, NULL); // ÿ��50ms������ϢWM_TIMER

	return 0;
}

void CGLView::OnDestroy() 
{
	
	if (m_pGLDC) {

		m_pGLDC->GLRelease();
		delete m_pGLDC;
	}

	CView::OnDestroy();

}

BOOL CGLView::OnEraseBkgnd(CDC* pDC) 
{
	//return CView::OnEraseBkgnd(pDC);
	return FALSE;
}

void CGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if(m_pGLDC)	
		m_pGLDC->GLResize(cx,cy);
}


void CGLView::RenderScene(COpenGLDC* pDC)
{
	// Rotate
	glRotatef(3.0f,0.0f, 0.0f, 1.0f); // Rock Z
	glRotatef(3.0f,1.0f, 0.0f, 0.0f); // Roll X

	glPushMatrix();
	glColor3ub(255,0,0);//red ���ƺ�ɫ��
	auxSolidSphere(360); //0,0,0 ����λ�ڣ�0,0,0��

	glColor3ub(0,0,255);//blue ������ɫ��
	glTranslatef(600,0,200);//600,0,200 ����λ�ڣ�600,0,200��
	auxSolidSphere(120);

	glColor3ub(0,255,0);//green ������ɫ��
	glTranslatef(-1200,600,0);//-600,600,200 ����λ�ڣ�-600,600,200��
	auxSolidSphere(240);

	glPopMatrix();

}


void CGLView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Invalidate(FALSE);	// ˢ����Ļ��ÿ����ˢ����Ļ20�Σ�

	CView::OnTimer(nIDEvent);
}
