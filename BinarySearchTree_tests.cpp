// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

TEST(empty) {
    BinarySearchTree<int> a;
    ASSERT_TRUE(a.empty());
}

TEST(insert) {
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(12);
    a.insert(-1);
    ASSERT_FALSE(a.empty());
}

TEST(size) {
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(12);
    a.insert(-1);
    a.insert(20);
    a.insert(3);
    ASSERT_EQUAL(a.size(), 5);
}

TEST(height) {
    BinarySearchTree<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    ASSERT_EQUAL(a.height(), 5);
}

TEST(height_and_size_empty) {
    BinarySearchTree<int> a;
    ASSERT_EQUAL(a.height(), 0);
    ASSERT_EQUAL(a.size(), 0)
}

TEST(copy_ctor) {
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(12);
    a.insert(-1);
    BinarySearchTree<int> b(a);
    ASSERT_FALSE(b.empty());
    ASSERT_EQUAL(a.size(), b.size());
}

TEST(copy_op) {
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(12);
    a.insert(-1);
    BinarySearchTree<int> b = a;
    ASSERT_FALSE(b.empty());
    ASSERT_EQUAL(a.size(), b.size());
}

TEST(max_elem) {
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(12);
    a.insert(-1);
    ASSERT_EQUAL(*a.max_element(), 12)
}

TEST(min_elem) {
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(12);
    a.insert(-1);
    ASSERT_EQUAL(*a.min_element(), -1)
}

TEST(check_sort) {
    BinarySearchTree<int> a;
    a.insert(5);
    ASSERT_TRUE(a.check_sorting_invariant());
}

TEST(check_sort2) {
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(0);
    a.insert(23);
    a.insert(-12);
    a.insert(15);
    a.insert(10);
    a.insert(101);
    ASSERT_TRUE(a.check_sorting_invariant());
}

TEST(check_preorder)
{
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(23);
    a.insert(-23);

    ostringstream oss_preorder;
    a.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "5 -23 23 ");
}

TEST(check_inorder)
{
    BinarySearchTree<int> a;
    a.insert(5);
    a.insert(23);
    a.insert(-23);

    ostringstream oss_inorder;
    a.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "-23 5 23 ");
}



TEST_MAIN()
