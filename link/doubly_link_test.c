#include <string.h>

#include "doubly_link.h"
#include "unity_fixture.h"

TEST_GROUP(doubly_link);


static doubly_link_t head;
static doubly_link_t end;
static doubly_link_t m1;
static doubly_link_t m2;

TEST_SETUP(doubly_link) {
    memset(&head, 0, sizeof(doubly_link_t));
    memset(&end, 0, sizeof(doubly_link_t));
    memset(&m1, 0, sizeof(doubly_link_t));
    memset(&m2, 0, sizeof(doubly_link_t));
    doubly_link_init_head(&head);
}
TEST_TEAR_DOWN(doubly_link) {
}

TEST(doubly_link, init_head) {
    TEST_ASSERT_POINTERS_EQUAL(&head, head.next);
    TEST_ASSERT_POINTERS_EQUAL(&head, head.prev);
}

TEST(doubly_link, add) {
    doubly_link_add(&end, &head);
    TEST_ASSERT_POINTERS_EQUAL(&end, head.next);
    TEST_ASSERT_POINTERS_EQUAL(&end, head.prev);
    TEST_ASSERT_POINTERS_EQUAL(&head, end.next);
    TEST_ASSERT_POINTERS_EQUAL(&head, end.prev);
    
    doubly_link_add(&m1, &head);
    TEST_ASSERT_POINTERS_EQUAL(&m1, end.prev);
    TEST_ASSERT_POINTERS_EQUAL(&m1, head.next);
    TEST_ASSERT_POINTERS_EQUAL(&head, end.next);
    TEST_ASSERT_POINTERS_EQUAL(&head, m1.prev);
    TEST_ASSERT_POINTERS_EQUAL(&end, m1.next);
    TEST_ASSERT_POINTERS_EQUAL(&end, head.prev);
}

TEST(doubly_link, delete) {
    doubly_link_add(&end, &head);
    doubly_link_add(&m1, &head);
    doubly_link_add(&m2, &m1);

}


TEST_GROUP_RUNNER(doubly_link) {
    RUN_TEST_CASE(doubly_link, init_head);
    RUN_TEST_CASE(doubly_link, add);
    RUN_TEST_CASE(doubly_link, delete);
}

