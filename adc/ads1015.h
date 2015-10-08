/// \file ads1015.h
/// \brief ads1015驱动声明.
/// \author Xi Qingping, qingping.xi@ligoo.cn
/// \version
/// \date 2015-09-06
#ifndef __ADS1015_H__
#define __ADS1015_H__

/// \name ads1015 ads1015驱动相关
/// @{

typedef struct ads1015 ads1015_t;


#ifndef __FAR
#define __FAR
#endif

/// ADS1015支持的通道数.
typedef enum {
    ADS1015_CHANNEL_0 = 4,
    ADS1015_CHANNEL_1 = 5,
    ADS1015_CHANNEL_2 = 6,
    ADS1015_CHANNEL_3 = 7,
} ADS1015_Channel;

/// ADS1015满量程对应的电压(mV).
typedef enum {
    ADS1015_FULL_SCALE_6144_MV = 0,
    ADS1015_FULL_SCALE_4096_MV = 1,
    ADS1015_FULL_SCALE_2048_MV = 2,
    ADS1015_FULL_SCALE_1024_MV = 3,
    ADS1015_FULL_SCALE_512_MV = 4,
    ADS1015_FULL_SCALE_256_MV = 5,
} ADS1015_FullScaleVoltage;

/// \brief ADS1015_Init 初始化
///
/// \param iface 底层接口.
void ads1015_init(ads1015_t *__FAR ads1015);

/// 转换错误时返回值.
#define ADS1015_RESULT_ERROR 32767

/// \brief ADS1015_SingleConvert 开始一次转换并取得转换结果.
///
/// \param iface 底层接口.
/// \param channel 转换的通道.
/// \param fullScaleVol 满量程对应的电压.
///
/// \return 转换得到的结果, 正常 [-4096, 4095], 错误时返回 ADS1015_RESULT_ERROR.
/// \note 这个函数中没有加互斥锁, 多线程调用请额外加锁确保互斥.
signed short ads1015_single_convert(ads1015_t *__FAR ads1015, ADS1015_Channel channel, ADS1015_FullScaleVoltage fullScaleVol);
///  @}

#endif
