#ifndef __SOFTI2C_PRIVATE_H__
#define __SOFTI2C_PRIVATE_H__

#include "softi2c.h"

/// softi2c�ײ�Ӳ���ӿ�.
/// �ڰ弶֧������Ҫʵ������ӿڵĺ���.
struct softi2c {
    /// \brief �ײ�ӿڳ�ʼ��, �����������softi2c_init��ʱ�����.
    /// ��Ҫ�����õ���IO�ڳ�ʼ���ɸߵ�ƽ, ����Ϊ��©���.
	void (* init)(void);

    /// \brief ����SCL�ĵ�ƽ.
    /// \param b !=0 ����SCL�ĵ�ƽΪ��(����); ==0 ����SCL�ĵ�ƽΪ��.
	char (* scl)(char b);

    /// \brief ����SDA�ĵ�ƽ.
    /// \param b !=0 ����SDA�ĵ�ƽΪ��(����); ==0 ����SDA�ĵ�ƽΪ��.
	char (* sda)(char b);
};

#endif
