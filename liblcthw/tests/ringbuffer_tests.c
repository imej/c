#include "minunit.h"
#include <assert.h>
#include <string.h>
#include <lcthw/ringbuffer.h>

static RingBuffer *rb = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3

char *test_create()
{
    rb = RingBuffer_create(35);
    mu_assert(rb != NULL, "Failed to create RingBuffer.")
    mu_assert(RingBuffer_empty(rb) == 1, "Newly create RingBuffer should be empty.")

    return NULL;
}

char *test_destroy()
{
    RingBuffer_destroy(rb);

    return NULL;
}

char *test_read_write()
{
    char *test = calloc(1, 35);

    int rc = 0;
    rc = RingBuffer_write(rb, tests[0], 10);
    mu_assert(rc == 10, "Should write 10 characters.");

    rc = RingBuffer_write(rb, tests[1], 10);
    mu_assert(rc == 10, "Should write 10 characters.");

    rc = RingBuffer_write(rb, tests[2], 10);
    mu_assert(rc == 10, "Should write 10 characters.");

    rc = RingBuffer_read(rb, test, 7);
    mu_assert(rc == 7, "Should read 7 characters.");
    mu_assert(strcmp(test, "test1 d") == 0, "Failed to read correctly.");

    free(test);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
