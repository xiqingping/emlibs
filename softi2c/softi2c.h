#ifndef __SOFT_I2C_H__
#define __SOFT_I2C_H__

typedef struct softi2c softi2c_t;

/// \brief softi2c_init 初始化总线.
/// 
/// \param i2c 底层接口.
void softi2c_init(const softi2c_t *i2c);

/// \brief softi2c_write 通过I2C总线写数据.
/// 
/// \param i2c 底层接口.
/// \param addr 从设备的地址, 最终在总线上的第一个字节为((addr << 1) + RW)
/// \param dat 需要写的数据.
/// \param len 需要写的数据的长度.
/// 
/// \return 从设备应答的数据长度.
unsigned char softi2c_write(const softi2c_t *i2c, unsigned char addr, const unsigned char *dat, unsigned char len);

/// \brief softi2c_read 通过I2C总线读数据.
/// 
/// \param i2c 底层接口.
/// \param addr 从设备的地址, 最终在总线上的第一个字节为((addr << 1) + RW)
/// \param dat 读到的数据保存的地址.
/// \param len 需要读的数据的长度.
/// 
/// \return 读取到的数据长度.
unsigned char softi2c_read(const softi2c_t *i2c, unsigned char addr, unsigned char *dat, unsigned char len);

#endif
