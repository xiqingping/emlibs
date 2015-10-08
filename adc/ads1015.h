/// \file ads1015.h
/// \brief ads1015��������.
/// \author Xi Qingping, qingping.xi@ligoo.cn
/// \version
/// \date 2015-09-06
#ifndef __ADS1015_H__
#define __ADS1015_H__

/// \name ads1015 ads1015�������
/// @{

typedef struct ads1015 ads1015_t;


#ifndef __FAR
#define __FAR
#endif

/// ADS1015֧�ֵ�ͨ����.
typedef enum {
    ADS1015_CHANNEL_0 = 4,
    ADS1015_CHANNEL_1 = 5,
    ADS1015_CHANNEL_2 = 6,
    ADS1015_CHANNEL_3 = 7,
} ADS1015_Channel;

/// ADS1015�����̶�Ӧ�ĵ�ѹ(mV).
typedef enum {
    ADS1015_FULL_SCALE_6144_MV = 0,
    ADS1015_FULL_SCALE_4096_MV = 1,
    ADS1015_FULL_SCALE_2048_MV = 2,
    ADS1015_FULL_SCALE_1024_MV = 3,
    ADS1015_FULL_SCALE_512_MV = 4,
    ADS1015_FULL_SCALE_256_MV = 5,
} ADS1015_FullScaleVoltage;

/// \brief ADS1015_Init ��ʼ��
///
/// \param iface �ײ�ӿ�.
void ads1015_init(ads1015_t *__FAR ads1015);

/// ת������ʱ����ֵ.
#define ADS1015_RESULT_ERROR 32767

/// \brief ADS1015_SingleConvert ��ʼһ��ת����ȡ��ת�����.
///
/// \param iface �ײ�ӿ�.
/// \param channel ת����ͨ��.
/// \param fullScaleVol �����̶�Ӧ�ĵ�ѹ.
///
/// \return ת���õ��Ľ��, ���� [-4096, 4095], ����ʱ���� ADS1015_RESULT_ERROR.
/// \note ���������û�мӻ�����, ���̵߳�����������ȷ������.
signed short ads1015_single_convert(ads1015_t *__FAR ads1015, ADS1015_Channel channel, ADS1015_FullScaleVoltage fullScaleVol);
///  @}

#endif
