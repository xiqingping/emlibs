#ifndef __SOFTI2C_PRIVATE_H__
#define __SOFTI2C_PRIVATE_H__

#include "softi2c.h"

/// softi2c底层硬件接口.
/// 在板级支持上需要实现这个接口的函数.
struct softi2c {
    /// \brief 底层接口初始化, 这个函数会在softi2c_init的时候调用.
    /// 需要把所用到的IO口初始化成高电平, 并且为开漏输出.
	void (* init)(void);

    /// \brief 设置SCL的电平.
    /// \param b !=0 设置SCL的电平为高(高阻); ==0 设置SCL的电平为低.
	char (* scl)(char b);

    /// \brief 设置SDA的电平.
    /// \param b !=0 设置SDA的电平为高(高阻); ==0 设置SDA的电平为低.
	char (* sda)(char b);
};

#endif
