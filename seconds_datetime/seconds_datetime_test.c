#include "seconds_datetime.h"
#include "unity_fixture.h"

/* ipython code
In [1]: import datetime
In [2]: t0=datetime.datetime(2000,1,1,0,0,0)
In [3]: t1=datetime.datetime(2013,12,8,19,35,55)
In [4]: t1.weekday()
Out[4]: 6
In [5]: (t1-t0).total_seconds()
Out[5]: 439846555.0
*/


TEST_GROUP(seconds_datetime);

TEST_SETUP(seconds_datetime) {
}

TEST_TEAR_DOWN(seconds_datetime) {
}

TEST(seconds_datetime, from_seconds_to_datetime) {
    seconds_t seconds;
    datetime_t t;

    seconds = 439846555;
    TEST_ASSERT(seconds_to_datetime(&t, seconds));
    TEST_ASSERT_EQUAL(13, t.year);
    TEST_ASSERT_EQUAL(12, t.month);
    TEST_ASSERT_EQUAL(8, t.day);
    TEST_ASSERT_EQUAL(19, t.hour);
    TEST_ASSERT_EQUAL(35, t.minute);
    TEST_ASSERT_EQUAL(55, t.second);
    TEST_ASSERT_EQUAL(6, t.weekday);
}

TEST(seconds_datetime, from_datetime_to_seconds) {
    seconds_t seconds = 439846555;
    datetime_t t = {
        .year = 13,
        .month = 12,
        .day = 8,
        .hour = 19,
        .minute = 35,
        .second = 55,
        .weekday = 6,
    };
	
	TEST_ASSERT(datetime_to_seconds(&seconds, &t));
    TEST_ASSERT_EQUAL(439846555, seconds);
}

TEST(seconds_datetime, from_datetime_to_seconds_with_invalid_datetime) {
    seconds_t seconds = 439846555;
    datetime_t t = {
        .year = 13,
        .month = 12,
        .day = 8,
        .hour = 19,
        .minute = 35 - 1, // sub 1 minute
        .second = 55 + 60, // add 60 seconds
        .weekday = 6,
    };
	TEST_ASSERT_FALSE(datetime_to_seconds(&seconds, &t));
}

TEST(seconds_datetime, null_paramters) {
    seconds_t seconds = 439846555;
    datetime_t t = {
        .year = 13,
        .month = 12,
        .day = 8,
        .hour = 19,
        .minute = 35,
        .second = 55,
        .weekday = 6,
    };
	
	TEST_ASSERT_FALSE(datetime_to_seconds(0, 0));
	TEST_ASSERT_FALSE(datetime_to_seconds(&seconds, 0));
	TEST_ASSERT_FALSE(datetime_to_seconds(0, &t));
	TEST_ASSERT_FALSE(seconds_to_datetime(0, seconds));
}

TEST(seconds_datetime, datetime_is_valid) {
    seconds_t seconds;
    datetime_t t;

    seconds = 439846555;
    TEST_ASSERT(seconds_to_datetime(&t, seconds));
    TEST_ASSERT(datetime_is_valid(&t, 0));
    TEST_ASSERT(datetime_is_valid(&t, 1));

    TEST_ASSERT(seconds_to_datetime(&t, seconds));
    t.weekday = 7;
    TEST_ASSERT(datetime_is_valid(&t, 0));
    TEST_ASSERT_FALSE(datetime_is_valid(&t, 1));

    TEST_ASSERT(seconds_to_datetime(&t, seconds));
    t.hour = 24;
    TEST_ASSERT_FALSE(datetime_is_valid(&t, 0));
    TEST_ASSERT_FALSE(datetime_is_valid(&t, 1));
    
    TEST_ASSERT(seconds_to_datetime(&t, seconds));
    t.month = 13;
    TEST_ASSERT_FALSE(datetime_is_valid(&t, 0));
    TEST_ASSERT_FALSE(datetime_is_valid(&t, 2));
}


TEST_GROUP_RUNNER(seconds_datetime) {
    RUN_TEST_CASE(seconds_datetime, from_seconds_to_datetime);
    RUN_TEST_CASE(seconds_datetime, from_datetime_to_seconds);
    RUN_TEST_CASE(seconds_datetime, from_datetime_to_seconds_with_invalid_datetime);
    RUN_TEST_CASE(seconds_datetime, null_paramters);
}

