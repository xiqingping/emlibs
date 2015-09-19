#include "seconds_datetime.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#endif

#define SECONDS_PER_MINUTE 60
#define SECONDS_PER_HOUR (SECONDS_PER_MINUTE * 60)
#define SECONDS_PER_DAY (SECONDS_PER_HOUR * 24)
#define SECONDS_PER_WEEK (SECONDS_PER_DAY * 7)
#define SECONDS_PER_COM_YEAR (SECONDS_PER_DAY * 365)
#define SECONDS_PER_LEAP_YEAR (SECONDS_PER_DAY * 366)
#define SECONDS_PER_FOUR_YEARS (SECONDS_PER_LEAP_YEAR + SECONDS_PER_COM_YEAR*3)


static inline char __isLeapYear(const datetime_t *datetime) {
    return (datetime->year % 4) == 0;
}

static const seconds_t __fourYearSecondsTable[] = {
    0,
    SECONDS_PER_LEAP_YEAR,
    SECONDS_PER_LEAP_YEAR + SECONDS_PER_COM_YEAR * 1,
    SECONDS_PER_LEAP_YEAR + SECONDS_PER_COM_YEAR * 2,
};

static inline seconds_t __calYear(datetime_t *datetime, seconds_t second) {
    int i;

    datetime->year = (second / SECONDS_PER_FOUR_YEARS) * 4;
    second = second % SECONDS_PER_FOUR_YEARS; // seconds left for 4 year;
    for (i = 0; i < ARRAY_SIZE(__fourYearSecondsTable); ++i) {
        if (second < __fourYearSecondsTable[i])
            break;
    }
    --i;
    datetime->year += i;
    return second - __fourYearSecondsTable[i];
}



static inline seconds_t __yearToSeconds(const datetime_t *datetime) {
    return (datetime->year / 4) * SECONDS_PER_FOUR_YEARS + __fourYearSecondsTable[datetime->year % 4];
}


static const unsigned short __comYearMonthDaysNumAccTable[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};
static const unsigned short __leapYearMonthDaysNumAccTable[] = {
    0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335
};

static inline void __calMonthDate(datetime_t *datetime, int dayOffsetOfYear) {
    int i;
    const unsigned short *table;
    table = __isLeapYear(datetime) ? __leapYearMonthDaysNumAccTable : __comYearMonthDaysNumAccTable;

    for (i = 1; i < 12; ++i) {
        if (dayOffsetOfYear < table[i])
            break;
    }
    datetime->month = i;
    datetime->day = dayOffsetOfYear - table[i - 1] + 1;
}

static inline seconds_t __monthDateToSeconds(const datetime_t *datetime) {
    const unsigned short *table;
    table = __isLeapYear(datetime) ? __leapYearMonthDaysNumAccTable : __comYearMonthDaysNumAccTable;

    return (table[datetime->month - 1] + datetime->day - 1) * SECONDS_PER_DAY;
}


static inline void __calWeekDay(datetime_t *datetime, seconds_t second) {
    int day;
    second = (second % SECONDS_PER_WEEK);
    day = second / SECONDS_PER_DAY;
    day += 5; // 2000-1-1ÊÇÐÇÆÚÁù
    if (day > 6)
        datetime->weekday = day - 6; else
        datetime->weekday = day;
}

static inline void __calTime(datetime_t *datetime, seconds_t second) {
    second = second % SECONDS_PER_DAY;
    datetime->hour = second / SECONDS_PER_HOUR;
    second = second % SECONDS_PER_HOUR; // seconds left for one hour;
    datetime->minute = second / SECONDS_PER_MINUTE;
    datetime->second = second % SECONDS_PER_MINUTE;
}

static inline seconds_t __timeToSeconds(const datetime_t *datetime) {
    return datetime->hour * SECONDS_PER_HOUR + datetime->minute * SECONDS_PER_MINUTE + datetime->second;
}

static char __isValidDateTime(const datetime_t *datetime) {
    return (datetime->month > 0 &&
            datetime->month <= 12 &&
            datetime->day > 0 &&
            datetime->day <= 31 &&
            datetime->hour <= 24 &&
            datetime->minute <= 59 &&
            datetime->second <= 59);
}

static seconds_t __toSeconds(const datetime_t *datetime) {
    return __yearToSeconds(datetime) + __monthDateToSeconds(datetime) + __timeToSeconds(datetime);
}

char seconds_to_datetime(datetime_t *datetime, seconds_t second) {
    if (!datetime)
        return 0;
    __calWeekDay(datetime, second);
    second = __calYear(datetime, second);
    __calMonthDate(datetime, second / SECONDS_PER_DAY);
    __calTime(datetime, second);
    return 1;
}

char datetime_to_seconds(seconds_t *seconds, const datetime_t *datetime) {
    if (!seconds || !datetime)
        return 0;
    if (!__isValidDateTime(datetime))
        return 0;
    *seconds = __toSeconds(datetime);
    return 1;
}

char datetime_is_valid(const datetime_t *datetime, char need_check_weekday) {
    if (!__isValidDateTime(datetime)) return 0;

    if (!need_check_weekday) return 1;

    if (datetime->weekday > 6) return 0;

    {
        datetime_t t;
        seconds_to_datetime(&t, __toSeconds(datetime));
        return t.weekday == datetime->weekday;
    }
}

