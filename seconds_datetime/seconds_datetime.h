#ifndef __SECOND_DATE_H__
#define __SECOND_DATE_H__

typedef struct {
    /// ��, ��1��ʾ 2001��.
    unsigned char year;
    /// ��, 1-12.
    unsigned char month;
    /// ��, 1-31.
    unsigned char day;
    /// ����, 0-6.
    unsigned char weekday;
    /// ʱ, 0-23.
    unsigned char hour;
    /// ��, 0-59.
    unsigned char minute;
    /// ��, 0-59.
    unsigned char second;
} datetime_t;

typedef unsigned long seconds_t;

char seconds_to_datetime(datetime_t *datetime, seconds_t second);
char datetime_to_seconds(seconds_t *seconds, const datetime_t *datetime);
char datetime_is_valid(const datetime_t *datetime, char need_check_weekday);

#endif
