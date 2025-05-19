/// @file tests.cpp
/// @date March 17, 2023
/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

// Catch 1.0 Framework Testing
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "priorityqueue.h"
#include "map"
#include "vector"
#include "random"

using namespace std;

TEST_CASE("Constructor and Size")
{
    SECTION("Default Constructor") {
        priorityqueue<int> pq;
        REQUIRE(pq.Size() == 0);
    }
}

TEST_CASE("Enqueue and Size")
{
    SECTION("Enqueue single element") {
        priorityqueue<int> pq;
        pq.enqueue(1, 1);
        REQUIRE(pq.Size() == 1);
    }
    SECTION("Enqueue multiple elements") {
        priorityqueue<string> pq;
        pq.enqueue("hello", 2);
        pq.enqueue("world", 1);
        pq.enqueue("!", 3);
        REQUIRE(pq.Size() == 3);
    }
    SECTION("Enqueue duplicate elements") {
        priorityqueue<char> pq;
        pq.enqueue('a', 1);
        pq.enqueue('b', 2);
        pq.enqueue('c', 2);
        pq.enqueue('d', 3);
        pq.enqueue('e', 3);
        REQUIRE(pq.Size() == 5);
    }
}

TEST_CASE("Enqueue and Size for all primitive types")
{
    SECTION("Enqueue and Size for int") {
        priorityqueue<int> pq;
        pq.enqueue(1, 1);
        pq.enqueue(2, 2);
        pq.enqueue(3, 2);
        pq.enqueue(4, 3);
        pq.enqueue(5, 3);

        REQUIRE(pq.Size() == 5);

    }

    SECTION("Enqueue and Size for Random Integers") {

        srand(1);
        priorityqueue<int> pq;
        map<int, vector<int> > map;
        for (int i = 0; i < 33; i++) {
            int val = rand() % 999;
            int pr = rand() % 999;
            pq.enqueue(val, pr);
            map[pr].push_back(val);
            REQUIRE(pq.Size() == i + 1);
        }
    }

    SECTION("Enqueue and Size for float") {
        priorityqueue<float> pq;
        pq.enqueue(1.1f, 1);
        pq.enqueue(2.2f, 2);
        pq.enqueue(3.3f, 2);
        pq.enqueue(4.4f, 3);
        pq.enqueue(5.5f, 3);
        REQUIRE(pq.Size() == 5);

        SECTION("Enqueue and Size for Random floats") {
            srand(1);
            priorityqueue<float> pq;
            for (int i = 0; i < 21; i++) {
                float val = (rand() % 100) / 100.0;
                int pr = (rand() % 100);
                pq.enqueue(val, pr);
                REQUIRE(pq.Size() == i + 1);
            }

        }
    }
    SECTION("Enqueue and Size for double") {
        priorityqueue<double> pq;
        pq.enqueue(1.1, 1);
        pq.enqueue(2.2, 2);
        pq.enqueue(3.3, 2);
        pq.enqueue(4.4, 3);
        pq.enqueue(5.5, 3);
        REQUIRE(pq.Size() == 5);


        SECTION("Enqueue and Size for Random doubles") {
            srand(1);
            priorityqueue<double> pq;
            for (int i = 0; i < 17; i++) {
                double val = (rand() % 100) / 0.3;
                int pr = (rand() % 100);
                pq.enqueue(val, pr);
                REQUIRE(pq.Size() == i + 1);
            }

        }
    }
    SECTION("Enqueue and Size for bool") {
        priorityqueue<bool> pq;
        pq.enqueue(true, 1);
        pq.enqueue(false, 2);
        pq.enqueue(true, 2);
        pq.enqueue(true, 3);
        pq.enqueue(false, 3);
        REQUIRE(pq.Size() == 5);
    }
    SECTION("Enqueue and Size for char") {
        priorityqueue<char> pq;
        pq.enqueue('a', 1);
        pq.enqueue('b', 1);
        pq.enqueue('c', 2);
        pq.enqueue('d', 2);
        pq.enqueue('e', 2);
        pq.enqueue('f', 3);
        pq.enqueue('g', 3);
        pq.enqueue('h', 3);
        pq.enqueue('i', 3);
        SECTION("Size returns correct value") {
            REQUIRE(pq.Size() == 9);
        }
        SECTION("Enqueue and Size for Random chars") {
            srand(1);
            priorityqueue<char> pq;
            for (int i = 0; i < 30; i++) {
                char val = 'a' + rand() % 99;
                int pr = rand() % 99;
                pq.enqueue(val, pr);
                REQUIRE(pq.Size() == i + 1);
            }

        }
    }

    SECTION("Enqueue and Size for int") {
        priorityqueue<int> pq;
        pq.enqueue(1, 1);
        pq.enqueue(2, 1);
        pq.enqueue(3, 2);
        pq.enqueue(4, 2);
        pq.enqueue(5, 2);
        pq.enqueue(6, 3);
        pq.enqueue(7, 3);
        pq.enqueue(8, 3);
        pq.enqueue(9, 3);

        SECTION("Size returns correct value") {
            REQUIRE(pq.Size() == 9);
        }
    }

    SECTION("Enqueue and Size for double") {
        priorityqueue<double> pq;
        pq.enqueue(1.1, 1);
        pq.enqueue(2.2, 1);
        pq.enqueue(3.3, 2);
        pq.enqueue(4.4, 2);
        pq.enqueue(5.5, 2);
        pq.enqueue(6.6, 3);
        pq.enqueue(7.7, 3);
        pq.enqueue(8.8, 3);
        pq.enqueue(9.9, 3);

        SECTION("Size returns correct value") {
            REQUIRE(pq.Size() == 9);
        }
    }

    SECTION("Enqueue and Size for string") {
        priorityqueue<string> pq;
        pq.enqueue("one", 1);
        pq.enqueue("two", 1);
        pq.enqueue("three", 2);
        pq.enqueue("four", 2);
        pq.enqueue("five", 2);
        pq.enqueue("six", 3);
        pq.enqueue("seven", 3);
        pq.enqueue("eight", 3);
        pq.enqueue("nine", 3);

        SECTION("Size returns correct value") {
            REQUIRE(pq.Size() == 9);
        }
        SECTION("Enqueue and Size for Random Strings") {
            srand(1);
            priorityqueue<string> pq;

            for (int i = 0; i < 15; i++) {
                string val = "a" + to_string(rand() % 999);
                int pr = rand() % 999;
                pq.enqueue(val, pr);
                REQUIRE(pq.Size() == i + 1);
            }

        }
    }
}
TEST_CASE("Clear") {
    SECTION("Clear an empty queue") {
        priorityqueue<int> pq;
        pq.clear();
        REQUIRE(pq.Size() == 0);
    }
    SECTION("Clear a non-empty queue") {
        priorityqueue<string> pq;
        pq.enqueue("hello", 2);
        pq.enqueue("world", 1);
        pq.enqueue("!", 3);
        pq.clear();
        REQUIRE(pq.Size() == 0);
    }
}
TEST_CASE("Operator==") {
    SECTION("Equal queues") {
        priorityqueue<int> pq1, pq2;
        pq1.enqueue(1, 1);
        pq1.enqueue(2, 2);
        pq1.enqueue(3, 3);
        pq2.enqueue(1, 1);
        pq2.enqueue(2, 2);
        pq2.enqueue(3, 3);
        REQUIRE(pq1 == pq2);
    }
    SECTION("Different element order") {
        priorityqueue<string> pq1, pq2;
        pq1.enqueue("hello", 2);
        pq1.enqueue("world", 1);
        pq1.enqueue("!", 3);
        pq2.enqueue("world", 1);
        pq2.enqueue("hello", 2);
        pq2.enqueue("!", 3);
        REQUIRE_FALSE(pq1 == pq2);
    }
    SECTION("Different element priorities") {
        priorityqueue<char> pq1, pq2;
        pq1.enqueue('a', 1);
        pq1.enqueue('b', 2);
        pq2.enqueue('a', 2);
        pq2.enqueue('b', 1);
        REQUIRE_FALSE(pq1 == pq2);
    }
    SECTION("Different queue sizes") {
        priorityqueue<double> pq1, pq2;
        pq1.enqueue(1.1, 1);
        pq1.enqueue(2.2, 2);
        pq2.enqueue(1.1, 1);
        REQUIRE_FALSE(pq1 == pq2);
    }
}
TEST_CASE("priorityqueue<int> dequeue() removes and returns the minimum element", "[priorityqueue][dequeue][int]") {
    priorityqueue<int> pq;

    pq.enqueue(3,1);
    pq.enqueue(1,2);
    pq.enqueue(4,2);
    pq.enqueue(1,4);
    pq.enqueue(5,5);
    pq.enqueue(9,7);

    SECTION("Removing the minimum element with no duplicates") {
        int valueOut = pq.dequeue();
        REQUIRE(valueOut == 3);
        REQUIRE(pq.Size() == 5);
    }

    SECTION("Removing the minimum element with duplicates") {
        pq.dequeue(); // remove the first 1
        int valueOut = pq.dequeue(); // remove the second 1
        REQUIRE(valueOut == 1);
        REQUIRE(pq.Size() == 4);
    }

    SECTION("Removing the minimum element from an empty priorityqueue<int>") {
        priorityqueue<int> emptyPq;
        int valueOut = emptyPq.dequeue();
        REQUIRE(valueOut == int());
        REQUIRE(emptyPq.Size() == 0);
    }
}
TEST_CASE("Test peek and dequeue on int priority queue") {
    priorityqueue<int> pq;

    SECTION("Test with one element") {
        pq.enqueue(1, 0);
        REQUIRE(pq.peek() == 1);
        REQUIRE(pq.dequeue() == 1);
        REQUIRE(pq.Size() == 0);
    }

    SECTION("Test with multiple elements") {
        pq.enqueue(2, 1);
        pq.enqueue(1, 0);
        pq.enqueue(3, 2);

        REQUIRE(pq.peek() == 1);
        REQUIRE(pq.dequeue() == 1);
        REQUIRE(pq.peek() == 2);
        REQUIRE(pq.dequeue() == 2);
        REQUIRE(pq.peek() == 3);
        REQUIRE(pq.dequeue() == 3);
        REQUIRE(pq.Size() == 0);
    }

    SECTION("Test with duplicate priorities") {
        pq.enqueue(1, 1);
        pq.enqueue(2, 1);
        pq.enqueue(3, 1);

        REQUIRE(pq.peek() == 1);
        REQUIRE(pq.dequeue() == 1);
        REQUIRE(pq.peek() == 2);
        REQUIRE(pq.dequeue() == 2);
        REQUIRE(pq.peek() == 3);
        REQUIRE(pq.dequeue() == 3);
        REQUIRE(pq.Size() == 0);
    }
}

TEST_CASE("Test peek and dequeue on string priority queue") {
    priorityqueue<string> pq;

    SECTION("Test with one element") {
        pq.enqueue("hello", 0);
        REQUIRE(pq.peek() == "hello");
        REQUIRE(pq.dequeue() == "hello");
        REQUIRE(pq.Size() == 0);
    }

    SECTION("Test with multiple elements") {
        pq.enqueue("world", 1);
        pq.enqueue("hello", 0);
        pq.enqueue("!", 2);

        REQUIRE(pq.peek() == "hello");
        REQUIRE(pq.dequeue() == "hello");
        REQUIRE(pq.peek() == "world");
        REQUIRE(pq.dequeue() == "world");
        REQUIRE(pq.peek() == "!");
        REQUIRE(pq.dequeue() == "!");
        REQUIRE(pq.Size() == 0);
    }

    SECTION("Test with duplicate priorities") {
        pq.enqueue("hello", 1);
        pq.enqueue("world", 1);
        pq.enqueue("!", 1);

        REQUIRE(pq.peek() == "hello");
        REQUIRE(pq.dequeue() == "hello");
        REQUIRE(pq.peek() == "world");
        REQUIRE(pq.dequeue() == "world");
        REQUIRE(pq.peek() == "!");
        REQUIRE(pq.dequeue() == "!");
        REQUIRE(pq.Size() == 0);
    }
}
TEST_CASE("Equality operator", "[priorityqueue]") {
    // Create two identical priority queues
    priorityqueue<int> pq1;
    pq1.enqueue(1, 1);
    pq1.enqueue(2, 2);
    pq1.enqueue(3, 3);
    priorityqueue<int> pq2;
    pq2.enqueue(1, 1);
    pq2.enqueue(2, 2);
    pq2.enqueue(3, 3);

    // Test that two identical priority queues are equal
    REQUIRE(pq1 == pq2);

    // Create two non-identical priority queues
    priorityqueue<int> pq3;
    pq3.enqueue(1, 1);
    pq3.enqueue(2, 2);
    pq3.enqueue(3, 3);
    priorityqueue<int> pq4;
    pq4.enqueue(1, 1);
    pq4.enqueue(3, 3);
    pq4.enqueue(2, 2);

    // Test that two non-identical priority queues are not equal
    REQUIRE_FALSE(pq3 == pq4);
}







