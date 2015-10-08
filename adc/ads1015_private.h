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
/// ADS1015底层接口.
struct ads1015_platform {
    void *__FAR platform_pdata;
    /// \brief 初始化用到的设备接口.
    void (*init)(const ads1015_platform_t *__FAR platform);

    /// \brief 通过I2C向ADS1015写入数据.
    ///
    /// \param dat 需要写入的数据.
    /// \param len 写入数据的长度.
    /// \return 实际写入的数据的长度.
    unsigned char (*i2c_write)(const ads1015_platform_t *__FAR platform, const unsigned char *__FAR dat, unsigned char len);

    /// \brief 通过I2C从ADS1015读取数据.
    ///
    /// \param dat 保存数据的指针.
    /// \param len 读取的数据的长度
    /// \return 实际读取到的数据的长度.
    unsigned char (*i2c_read)(const ads1015_platform_t *__FAR platform, unsigned char *__FAR dat, unsigned char len);

    /// \brief  ms延时函数.
    ///
    /// \param howmany 延时的毫秒数.
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
