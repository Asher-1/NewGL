#include "stdafx.h"

#include <gl/gl.h>
#include <gl/glu.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <gl\glut.h>
#include "camera.h"

//-------------------------------------------------------------
// For Camera class
//-------------------------------------------------------------
GCamera::GCamera(void)
{
}

GCamera::~GCamera()
{
}

void GCamera::projection() 
{
	//switch to projection 
   	glMatrixMode(GL_PROJECTION); // 切换到投影变换矩阵设置
   	glLoadIdentity(); // 初始化投影矩阵

	glRenderMode(GL_RENDER); // 设置渲染模式

	//apply projective matrix 创建投影矩阵
	double left		=  - m_width/2.0;
	double right	=  m_width/2.0;
	double bottom	=  - m_height/2.0;
	double top		=  m_height/2.0;

	glOrtho(left,right,bottom,top,m_near,m_far); // 正交直角投影方式

	glMatrixMode(GL_MODELVIEW); // 切换到视图变换矩阵设置
	glLoadIdentity( );// 初始化视图变换矩阵

	// 设置视点位置和观察方向
	gluLookAt(m_eye[0],m_eye[1],m_eye[2],
			  m_ref[0],m_ref[1],m_ref[2],
		      m_vecUp[0], m_vecUp[1], m_vecUp[2]);	

}

void GCamera::init()
{
	m_eye[0] = 0;// 视点位置（0,0,1000）
	m_eye[1] = 0;
	m_eye[2] = 1000.0;

	m_ref[0] = 0.0;// 参考点位置（0,0,0）
	m_ref[1] = 0.0;
	m_ref[2] = 0.0;

	m_far = 10000;
	m_near= 1;

	m_width = 2400.0;
	m_height = 2400.0;

	m_vecUp[0] = 0.0; // 视线向上的方向（0,1，0）
	m_vecUp[1] = 1.0;
	m_vecUp[2] = 0.0;

	m_screen[0] = 400;
	m_screen[1] = 400;
}

void GCamera::set_screen( int x, int y) 
{ 
	glViewport(0,0,x,y);  // 设置视口
	if(y==0) y=1;
	double ratio = (double)x/(double)y;
	m_width *= (double)x/m_screen[0]; // 根据窗口尺寸变化更新视景体的宽和高
	m_height *= (double)y/m_screen[1];
	m_width =  m_height*ratio; // 保持视景体宽与高的比率与窗口一致
	m_screen[0] = x;
	m_screen[1] = y; // 缓存窗口尺寸当前尺寸参考，用于下次视景体的尺寸调节

}

void GCamera::set_eye(double eye_x,double eye_y,double eye_z)
{
	m_eye[0] = eye_x;
	m_eye[1] = eye_y;
	m_eye[2] = eye_z;
}

void GCamera::set_ref(double ref_x,double ref_y,double ref_z)
{
	m_ref[0] = ref_x;
	m_ref[1] = ref_y;
	m_ref[2] = ref_z;
}

void GCamera::set_vecUp(double up_dx,double up_dy,double up_dz)
{
	m_vecUp[0] = up_dx;
	m_vecUp[1] = up_dy;
	m_vecUp[2] = up_dz;
}

void GCamera::set_view_rect(double width,double height)
{
	m_width = width;
	m_height = height;
	double aspect = m_screen[0]/m_screen[1];
	m_width =  m_height*aspect;
}

void GCamera::get_view_rect(double& width,double& height)
{
	width = m_width;
	height = m_height;
}
