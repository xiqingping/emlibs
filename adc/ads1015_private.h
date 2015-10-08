#ifndef __ADS1015_PRIVATE_H__
#define __ADS1015_PRIVATE_H__

#include "ads1015.h"

#ifndef ADS1015_CHECK
#define ADS1015_CHECK 1
#endif

#define ADS1015_CHECK_MAGIC (0x1234bc6fUL)

#ifndef __FAR
#define __FAR
#endif

typedef struct ads1015_platform ads1015_platform_t;
/// ADS1015�ײ�ӿ�.
struct ads1015_platform {
    void *__FAR platform_pdata;
    /// \brief ��ʼ���õ����豸�ӿ�.
    void (*init)(const ads1015_platform_t *__FAR platform);

    /// \brief ͨ��I2C��ADS1015д������.
    ///
    /// \param dat ��Ҫд�������.
    /// \param len д�����ݵĳ���.
    /// \return ʵ��д������ݵĳ���.
    unsigned char (*i2c_write)(const ads1015_platform_t *__FAR platform, const unsigned char *__FAR dat, unsigned char len);

    /// \brief ͨ��I2C��ADS1015��ȡ����.
    ///
    /// \param dat �������ݵ�ָ��.
    /// \param len ��ȡ�����ݵĳ���
    /// \return ʵ�ʶ�ȡ�������ݵĳ���.
    unsigned char (*i2c_read)(const ads1015_platform_t *__FAR platform, unsigned char *__FAR dat, unsigned char len);

    /// \brief  ms��ʱ����.
    ///
    /// \param howmany ��ʱ�ĺ�����.
    void (*delay_ms)(const ads1015_platform_t *__FAR platform, unsigned short howmany);

    char (*wait_interrupt_with_timeout)(const ads1015_platform_t *__FAR platform, unsigned short ms);
};


struct ads1015 {
#if ADS1015_CHECK != 0
    unsigned long magic;
#endif
    const struct ads1015_platform *__FAR platform;
};

#endif
