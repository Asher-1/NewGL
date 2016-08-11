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
	
	m_pGLDC = new COpenGLDC(GetSafeHwnd()); // 创建COpenGLDC的对象，并传入窗口句柄

	m_pGLDC->InitDC(); // 初始化COpenGLDC的对象

	// 该函数为系统设置一个序号为0的定时器
	SetTimer(0, 50, NULL); // 每隔50ms发出消息WM_TIMER

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
	glColor3ub(255,0,0);//red 绘制红色球
	auxSolidSphere(360); //0,0,0 球心位于（0,0,0）

	glColor3ub(0,0,255);//blue 绘制蓝色球
	glTranslatef(600,0,200);//600,0,200 球心位于（600,0,200）
	auxSolidSphere(120);

	glColor3ub(0,255,0);//green 绘制绿色球
	glTranslatef(-1200,600,0);//-600,600,200 球心位于（-600,600,200）
	auxSolidSphere(240);

	glPopMatrix();

}


void CGLView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate(FALSE);	// 刷新屏幕（每秒钟刷新屏幕20次）

	CView::OnTimer(nIDEvent);
}
