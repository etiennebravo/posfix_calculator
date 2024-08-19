/// @file Stack-test.cxx
/// @author Kevin Mess <kevin.mess@csn.edu>
/// @date 2023-11-25
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This file contains unit tests for the Stack class. It covers tests
/// for all the public member functions of the Stack class, ensuring that they
/// work correctly under various scenarios, including edge cases. The tests
/// check the functionality of the Stack class with different data types and
/// validate the behavior of constructors, stack operations (push, pop, top),
/// and special cases like operating on an empty stack or swapping contents.

#include <string>
#include <stdexcept>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Stack.hpp"  // check include guard

// Test Default Constructor
TEST_CASE("Default Constructor", "[Stack]") {
    Stack<int> stack;
    CHECK(stack.empty());
}

// Test Push and Size
TEST_CASE("push and size", "[Stack]") {
    Stack<int> stack;

    SECTION("push increases size") {
        stack.push(1);
        CHECK(stack.size() == 1);
        stack.push(2);
        CHECK(stack.size() == 2);
    }

    SECTION("top returns last pushed element") {
        stack.push(1);
        stack.push(2);
        CHECK(stack.top() == 2);
    }

    SECTION("multiple elements are pushed in the correct order") {
        stack.push(1);
        stack.push(2);
        stack.push(3);
        CHECK(stack.top() == 3);
        stack.pop();
        CHECK(stack.top() == 2);
        stack.pop();
        CHECK(stack.top() == 1);
    }
}

// Test Pop
TEST_CASE("pop", "[Stack]") {
    Stack<int> stack;

    SECTION("pop decreases size and removes the top element") {
        stack.push(1);
        stack.push(2);
        stack.pop();
        CHECK(stack.size() == 1);
        CHECK(stack.top() == 1);
    }

    SECTION("pop on empty stack does not throw") {
        Stack<int> empty_stack;
        CHECK_NOTHROW(empty_stack.pop());
    }

    SECTION("state of the stack after multiple pops") {
        for (int i = 0; i < 3; ++i) {
            stack.push(i);
        }
        stack.pop();
        stack.pop();
        CHECK(stack.size() == 1);
        CHECK(stack.top() == 0);
    }
}

// Test Top
TEST_CASE("top", "[Stack]") {
    Stack<int> stack;

    SECTION("top on non-empty stack returns correct element") {
        stack.push(1);
        CHECK(stack.top() == 1);
    }

    SECTION("top on empty stack throws exception") {
        CHECK_THROWS(stack.top());
    }

    SECTION("consistency of top after a series of push and pop operations") {
        stack.push(1);
        stack.push(2);
        stack.pop();
        stack.push(3);
        CHECK(stack.top() == 3);
    }
}

// Test Copy Constructor
TEST_CASE("Copy Constructor", "[Stack]") {
    Stack<int> original;
    original.push(1);

    SECTION("creates an independent copy") {
        Stack<int> copy(original);
        copy.push(2);
        CHECK(original.size() == 1);
        CHECK(copy.size() == 2);
    }

    SECTION("modifying original does not affect the copied stack") {
        Stack<int> copy(original);
        original.push(3);
        CHECK(copy.size() == 1);
        CHECK(original.size() == 2);
    }
}

// Test Move Constructor
TEST_CASE("Move Constructor", "[Stack]") {
    Stack<int> original;
    original.push(1);

    SECTION("transfers ownership") {
        Stack<int> moved(std::move(original));
        CHECK(original.empty());
        CHECK(moved.size() == 1);
    }

    SECTION("moved-to stack correctly acquires elements") {
        Stack<int> moved(std::move(original));
        CHECK(moved.top() == 1);
    }
}

// Test Swap
TEST_CASE("swap", "[Stack]") {
    Stack<int> stack1, stack2;
    stack1.push(1);
    stack2.push(2);

    SECTION("exchanges contents of two stacks") {
        stack1.swap(stack2);
        CHECK(stack1.top() == 2);
        CHECK(stack2.top() == 1);
    }

    SECTION("swap functionality with empty stacks") {
        Stack<int> empty_stack;
        stack1.swap(empty_stack);
        CHECK(stack1.empty());
        CHECK(empty_stack.top() == 1);
    }

    SECTION("swap stacks with different sizes") {
        stack2.push(3);
        stack1.swap(stack2);
        CHECK(stack1.size() == 2);
        CHECK(stack2.size() == 1);
    }
}

// Test for multiple push/pop operations
TEST_CASE("Multiple push/pop operations", "[Stack]") {
    Stack<int> stack;

    SECTION("push and pop work correctly with multiple values") {
        for (int i = 0; i < 10; ++i) {
            stack.push(i);
        }
        for (int i = 9; i >= 0; --i) {
            CHECK(stack.top() == i);
            stack.pop();
        }
        CHECK(stack.empty());
    }

    SECTION("alternating push/pop sequences") {
        stack.push(1);
        stack.push(2);
        stack.pop();
        stack.push(3);
        CHECK(stack.size() == 2);
        CHECK(stack.top() == 3);
    }
}

// Test with different data types
TEST_CASE("Handling different data types", "[Stack]") {
    Stack<std::string> string_stack;

    SECTION("Works with string data type") {
        string_stack.push("hello");
        string_stack.push("world");
        CHECK(string_stack.top() == "world");
        string_stack.pop();
        CHECK(string_stack.top() == "hello");
    }

    SECTION("Works with user-defined types") {
        struct TestStruct {
            int value;
            TestStruct(int val) : value(val) {}
            bool operator==(const TestStruct& other) const {
                return value == other.value;
            }
        };

        Stack<TestStruct> custom_type_stack;
        custom_type_stack.push(TestStruct(10));
        custom_type_stack.push(TestStruct(20));
        CHECK(custom_type_stack.top() == TestStruct(20));
        custom_type_stack.pop();
        CHECK(custom_type_stack.top() == TestStruct(10));
    }
}

/* EOF */

