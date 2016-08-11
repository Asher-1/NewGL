/*************************************************************************
* This head file is for 3D scene script. We will define a scene class    *
* with some light and camera and models.                                 *
*************************************************************************/
#ifndef _CAMERA_H__
#define _CAMERA_H__

class GCamera	{

protected:
	//eye position 视点位置和观察方向
    double		m_eye[3];
	double		m_ref[3];
	double		m_vecUp[3];

	//viewing volume 视景体参数
    double		m_far, m_near;
	double	 	m_width,m_height;

	//viewport 视口参数
	double		m_screen[2];

public:
	// 构造与析构函数
    GCamera();
	~GCamera();

	void init(); // 初始化函数
    
	void projection(); // 取景函数(投影方式的设置等)
	
	//set viewport acoording to window 设置视口尺寸
	void set_screen( int x, int y);

	//set eye coordinate 设置视点位置和方向
	void set_eye(double eye_x,double eye_y,double eye_z);
	void set_ref(double ref_x,double ref_y,double ref_z);
	void set_vecUp(double up_dx,double up_dy,double up_dz);

	//set viewing volume 设置视景体
	void set_view_rect(double width,double height);
	void get_view_rect(double& width,double& height);
};
#endif 
