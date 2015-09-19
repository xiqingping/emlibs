#ifndef __SOFT_I2C_H__
#define __SOFT_I2C_H__

typedef struct softi2c softi2c_t;

/// \brief softi2c_init ��ʼ������.
/// 
/// \param i2c �ײ�ӿ�.
void softi2c_init(const softi2c_t *i2c);

/// \brief softi2c_write ͨ��I2C����д����.
/// 
/// \param i2c �ײ�ӿ�.
/// \param addr ���豸�ĵ�ַ, �����������ϵĵ�һ���ֽ�Ϊ((addr << 1) + RW)
/// \param dat ��Ҫд������.
/// \param len ��Ҫд�����ݵĳ���.
/// 
/// \return ���豸Ӧ������ݳ���.
unsigned char softi2c_write(const softi2c_t *i2c, unsigned char addr, const unsigned char *dat, unsigned char len);

/// \brief softi2c_read ͨ��I2C���߶�����.
/// 
/// \param i2c �ײ�ӿ�.
/// \param addr ���豸�ĵ�ַ, �����������ϵĵ�һ���ֽ�Ϊ((addr << 1) + RW)
/// \param dat ���������ݱ���ĵ�ַ.
/// \param len ��Ҫ�������ݵĳ���.
/// 
/// \return ��ȡ�������ݳ���.
unsigned char softi2c_read(const softi2c_t *i2c, unsigned char addr, unsigned char *dat, unsigned char len);

#endif
