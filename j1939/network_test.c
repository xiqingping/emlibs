#include "network.h"
#include "unity_fixture.h"

TEST_GROUP(j1939_network);

TEST_SETUP(j1939_network) {
}
TEST_TEAR_DOWN(j1939_network) {
}

TEST(j1939_network, network_context) {
}

TEST_GROUP_RUNNER(j1939_network) {
    RUN_TEST_CASE(j1939_network, network_context);
}
