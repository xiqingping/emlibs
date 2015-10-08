/// \file ads1015.c
/// \brief ads1015����ʵ��.
/// \author Xi Qingping, qingping.xi@ligoo.cn
/// \version
/// \date 2015-09-06

#include "ads1015_private.h"

/// \name ads1015 ads1015�������
/// @{

#if ADS1015_CHECK != 0
#define ADS1015_INTERFACE_IS_VALID(iface) ((0 != (iface)) && ((iface)->magic == ADS1015_CHECK_MAGIC))
#define ADS1015_IS_VALID(ads1015) ((0 != (ads1015)) && ((ads1015)->magic == ADS1015_CHECK_MAGIC))
#else
#define ADS1015_INTERFACE_IS_VALID(iface) (0 != (iface))
#define ADS1015_IS_VALID(ads1015) (0 != (ads1015))
#endif

/// \brief write_register дADS1015�ļĴ���.
///
/// \param ads1015
/// \param reg �Ĵ�����ַ.
/// \param value д���ֵ.
///
/// \return ==0 д�����; !=0 д����ȷ.
static char write_register(ads1015_t *__FAR ads1015, unsigned char reg, unsigned short value) {
    unsigned char dat[3];

    dat[0] = reg;
    dat[1] = (value >> 8);
    dat[2] = (value & 0xFF);

    return ads1015->platform->i2c_write(ads1015->platform, dat, sizeof(dat)) == sizeof(dat);
}

/// \brief read_register ��ȡADS1015�ļĴ���.
///
/// \param ads1015
/// \param reg �Ĵ�����ַ.
/// \param pvalue ���ڱ���Ĵ���ֵ�õ�ַ.
///
/// \return ==0 ��ȡ����; !=0 ��ȡ��ȷ.
static char read_register(ads1015_t *__FAR ads1015, unsigned char reg, unsigned short *pval) {
    unsigned char dat[2];

    if (!pval) {
        return 0;
    }

    dat[0] = reg;

    if (1 != ads1015->platform->i2c_write(ads1015->platform, dat, 1)) {
        return 0;
    }
    if (2 != ads1015->platform->i2c_read(ads1015->platform, dat, 2)) {
        return 0;
    }
    *pval = ((dat[0] << 8) | dat[1]);
    return 1;
}

void ads1015_init(ads1015_t *__FAR ads1015) {
    if (!ADS1015_IS_VALID(ads1015)) {
        return;
    }

    ads1015->platform->init(ads1015->platform);
}

signed short ads1015_single_convert(ads1015_t *__FAR ads1015, ADS1015_Channel channel, ADS1015_FullScaleVoltage fullScaleVol) {
    unsigned short tmp;
    if (!ADS1015_IS_VALID(ads1015)) {
        return ADS1015_RESULT_ERROR;
    }

    // bit[15]  Operational status / single-shot convertion start.
    // bit[14:12] Input multiplexer configuration.
    // bit[11:9] Programmable gain.
    // bit[8] Device operating mode.
    // bit[7:5] Data rate.
    // bit[1:0] Comparator queue and disable.
    tmp = (0 << 15) |
          (((unsigned short)channel) << 12) |
          (((unsigned short)fullScaleVol) << 9) |
          (1 << 8) |
          (0 << 5) |
          (3 << 0);

    if (!write_register(ads1015, 0x01, tmp)) {
        return ADS1015_RESULT_ERROR;
    }
    if (!write_register(ads1015, 0x01, tmp | (1 << 15))) {
        return ADS1015_RESULT_ERROR;
    }

    if (ads1015->platform->wait_interrupt_with_timeout) {
        if (!ads1015->platform->wait_interrupt_with_timeout(ads1015->platform, 200)) {
            return ADS1015_RESULT_ERROR;
        }
    } else {
        unsigned char i = 0;
        do {
            ads1015->platform->delay_ms(ads1015->platform, 1);
            if (++i > 20) {
                return ADS1015_RESULT_ERROR;
            }
            if (!read_register(ads1015, 0x01, &tmp)) {
                return ADS1015_RESULT_ERROR;
            }
        } while ((tmp & (1 << 15)) == 0);
    }

    if (!read_register(ads1015, 0x00, &tmp)) {
        return ADS1015_RESULT_ERROR;
    }
    return tmp;
}

/// @}

