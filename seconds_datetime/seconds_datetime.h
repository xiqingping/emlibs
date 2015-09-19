#ifndef __SECOND_DATE_H__
#define __SECOND_DATE_H__

typedef struct {
    /// 年, 从1表示 2001年.
    unsigned char year;
    /// 月, 1-12.
    unsigned char month;
    /// 日, 1-31.
    unsigned char day;
    /// 星期, 0-6.
    unsigned char weekday;
    /// 时, 0-23.
    unsigned char hour;
    /// 分, 0-59.
    unsigned char minute;
    /// 秒, 0-59.
    unsigned char second;
} datetime_t;

typedef unsigned long seconds_t;

char seconds_to_datetime(datetime_t *datetime, seconds_t second);
char datetime_to_seconds(seconds_t *seconds, const datetime_t *datetime);
char datetime_is_valid(const datetime_t *datetime, char need_check_weekday);

#endif
