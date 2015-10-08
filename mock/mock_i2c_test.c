#include "unity_fixture.h"
#include "mock_i2c.h"

TEST_GROUP(mock_i2c);

TEST_SETUP(mock_i2c) {

}

TEST_TEAR_DOWN(mock_i2c) {
}


TEST(mock_i2c, write) {
    RINGBUFFER_DEFINE_STATIC(rb, 100);
    MOCK_I2C_DEFINE_STATIC(i2c, &rb);\
    mock_i2c_init(&i2c);
    mock_i2c_expect_write(&i2c, 0x01, "1231", 5);
    mock_i2c_expect_write(&i2c, 0x02, "123456", 6);
    mock_i2c_write(&i2c, 0x01, "1231", 5);
    mock_i2c_write(&i2c, 0x02, "123456", 6);
    mock_i2c_assert_finished(&i2c);
}


TEST(mock_i2c, read) {
    unsigned char buf[10];
    RINGBUFFER_DEFINE_STATIC(rb, 100);
    MOCK_I2C_DEFINE_STATIC(i2c, &rb);\
    mock_i2c_init(&i2c);
    mock_i2c_expect_read(&i2c, 0x01, "1231", 5);
    mock_i2c_expect_read(&i2c, 0x02, "123456", 6);
    mock_i2c_read(&i2c, 0x01, buf, 5);
    TEST_ASSERT_EQUAL_INT8_ARRAY("1231", buf, 5);
    mock_i2c_read(&i2c, 0x02, buf, 6);
    TEST_ASSERT_EQUAL_INT8_ARRAY("123456", buf, 6);
    mock_i2c_assert_finished(&i2c);
}


TEST_GROUP_RUNNER(mock_i2c) {
    RUN_TEST_CASE(mock_i2c, write);
    RUN_TEST_CASE(mock_i2c, read);
}

