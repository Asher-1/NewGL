/*************************************************************************
* This head file is for 3D scene script. We will define a scene class    *
* with some light and camera and models.                                 *
*************************************************************************/
#ifndef _CAMERA_H__
#define _CAMERA_H__

class GCamera	{

protected:
	//eye position �ӵ�λ�ú͹۲췽��
    double		m_eye[3];
	double		m_ref[3];
	double		m_vecUp[3];

	//viewing volume �Ӿ������
    double		m_far, m_near;
	double	 	m_width,m_height;

	//viewport �ӿڲ���
	double		m_screen[2];

public:
	// ��������������
    GCamera();
	~GCamera();

	void init(); // ��ʼ������
    
	void projection(); // ȡ������(ͶӰ��ʽ�����õ�)
	
	//set viewport acoording to window �����ӿڳߴ�
	void set_screen( int x, int y);

	//set eye coordinate �����ӵ�λ�úͷ���
	void set_eye(double eye_x,double eye_y,double eye_z);
	void set_ref(double ref_x,double ref_y,double ref_z);
	void set_vecUp(double up_dx,double up_dy,double up_dz);

	//set viewing volume �����Ӿ���
	void set_view_rect(double width,double height);
	void get_view_rect(double& width,double& height);
};
#endif 