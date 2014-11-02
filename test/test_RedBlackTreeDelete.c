#include "unity.h"
#include "Node.h"
#include "Rotation.h"
#include "InitNode.h"
#include "RedBlackTree.h"
#include "CustomAssertion.h"
#include "ErrorCode.h"
#include <stdio.h>
#include <CException.h>

Node node1, node5, node10, node15, node20, node25, node30, node35, node40, node45;

void setUp(void){
  resetNode(&node1, 1);
	resetNode(&node5, 5);
	resetNode(&node10, 10);
	resetNode(&node15, 15);
	resetNode(&node20, 20);
	resetNode(&node25, 25);
	resetNode(&node30, 30);
	resetNode(&node35, 35);
	resetNode(&node40, 40);
	resetNode(&node45, 45);
}
void tearDown(void){}

/**
 *      root              root
 *       |    remove 10    |
 *       V   ---------->   V
 *      10                NULL
 */
void test_delRedBlackTree_should_delete_the_root(void){
  setNode(&node10, NULL, NULL,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node10);
  TEST_ASSERT_EQUAL_PTR(NULL, root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
}
/**
 *      root              root
 *       |    remove 5     |
 *       V   ---------->   V
 *      10                NULL
 */
void test_delRedBlackTree_should_throw_if_not_found(void){
  setNode(&node10, NULL, NULL,'b');
  setNode(&node5, NULL, NULL,'b');
	Node *root = &node10;

  ErrorCode e;
  Try{
    delRedBlackTree(&root, &node5);
    TEST_FAIL_MESSAGE("Error, expected to be throw, But receive none");
  }
  Catch(e){
    TEST_ASSERT_EQUAL_PTR(root, &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', root);
  }
}
/**
 *      root           root
 *       |    rmv 5     |
 *       V   ------->   V
 *      10b            10b
 *      /              /
 *    5r             NULL
 */
void test_delRedBlackTree_delete_5_from_tree_with_root_10(void){
  setNode(&node5,NULL,NULL,'r');
  setNode(&node10,&node5,NULL,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
}
/**
 *      root           root
 *       |    rmv 15    |
 *       V   ------->   V
 *      10b            10b
 *        \              \
 *        15r            NULL
 */
void test_delRedBlackTree_delete_15_from_tree_with_root_10(void){
  setNode(&node15,NULL,NULL,'r');
  setNode(&node10,NULL,&node15,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node15);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', root);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
}
/**
 *      root           root
 *       |    rmv 5     |
 *       V   ------->   V
 *      10b            10b
 *     /  \           /  \
 *    5r  15r      NULL  15r
 */
void test_delRedBlackTree_delete_5_from_tree_with_root_10_and_right_with_15(void){
  setNode(&node15,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}
/**
 *      root           root
 *       |    rmv 15    |
 *       V   ------->   V
 *      10b            10b
 *     /  \            /  \
 *    5r  15r        5r   NULL
 */
void test_delRedBlackTree_delete_15_from_tree_with_root_10_and_left_with_5(void){
  setNode(&node15,NULL,NULL,'r');
  setNode(&node5,NULL,NULL,'r');
  setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node15);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}
/**
 *      root           root
 *       |    rmv 5     |
 *       V   ------->   V
 *      10b            10b
 *     /  \           /  \
 *    5r  15r      NULL  15r
 */
void test_delRedBlackTree_delete_5_with_color_flipping(void){
  setNode(&node15,NULL,NULL,'b');
  setNode(&node5,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}
/////////////////
//  3 NODE RBT //
/////////////////
/**
 *      root           root
 *       |    rmv 5     |
 *       V   ------->   V
 *      10b            20b
 *     /   \          /   \
 *    5b   20r      10b   30b
 *        /  \        \
 *     15b   30b      15r
 */
void test_delRedBlackTree_delete_5_from_tree_should_rotateLeft_and_flip_colour(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node20,&node15,&node30,'r');
  setNode(&node10,&node5,&node20,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node20);
  TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}
/**
 *       root           root
 *        |    rmv 30    |
 *        V   ------->   V
 *       20b            10b
 *      /   \          /   \
 *    10r   30b      5b    20b
 *   /  \                 /
 *  5b  15b             15r
 */
void test_delRedBlackTree_delete_5_from_tree_should_rotateRight_and_flip_colour(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'r');
  setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;

  delRedBlackTree(&root, &node30);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}
/**
 *      root           root
 *       |    rmv 30    |
 *       V   ------->   V
 *      10b            10b
 *     /   \          /   \
 *    5b   20r      5b   20b
 *        /  \           /
 *     15b   30b       15r
 */
void test_delRedBlackTree_delete_30_from_tree_should_not_rotate_and_flip_colour(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node20,&node15,&node30,'r');
  setNode(&node10,&node5,&node20,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node30);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(&node15, NULL, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}
/**
 *       root           root
 *        |    rmv 5     |
 *        V   ------->   V
 *       20b            20b
 *      /   \          /   \
 *    10r   30b      10b   30b
 *   /  \              \
 *  5b  15b            15r
 */
void test_delRedBlackTree_delete_5_from_tree_should_not_rotate_and_flip_colour(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'r');
  setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;

  delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node20);
  TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}
/**
 *      root           root
 *       |    rmv 15    |
 *       V   ------->   V
 *      10b            10b
 *     /   \          /   \
 *    5b   20r      5b   20b
 *        /  \              \
 *     15b   30b            30r
 */
void test_delRedBlackTree_delete_15_from_tree_should_not_rotate_and_flip_colour_right_case(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node20,&node15,&node30,'r');
  setNode(&node10,&node5,&node20,'b');
	Node *root = &node10;

  delRedBlackTree(&root, &node15);
  TEST_ASSERT_EQUAL_PTR(root, &node10);
  TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node30);
}
/**
 *       root           root
 *        |    rmv 15     |
 *        V   ------->   V
 *       20b            20b
 *      /   \          /   \
 *    10r   30b      10b   30b
 *   /  \           /
 *  5b  15b       5r
 */
void test_delRedBlackTree_delete_15_from_tree_should_not_rotate_and_flip_colour_left_case(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'r');
  setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;

  delRedBlackTree(&root, &node15);
  TEST_ASSERT_EQUAL_PTR(root, &node20);
  TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}

/////////////////
//  4 NODE  RBT//
/////////////////
/**
 *         root               root
 *          |      rmv 5       |
 *          V   --------->     V
 *         20b                20b
 *      /      \           /      \
 *    10r      30r       10b      30r
 *   /  \     /  \      /  \     /  \
 *  5b  15b 25b  35b  NULL 15r 25b  35b
 */
void test_delRedBlackTree_delete_5_from_tree_should_not_rotate_and_flip_colour_case_1_leftleft_remove(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node25,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'r');
  setNode(&node30,&node25,&node35,'r');
  setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;

  delRedBlackTree(&root, &node5);
  TEST_ASSERT_EQUAL_PTR(root, &node20);
  TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(&node25, &node35, 'r', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node25);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node35);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}
/**
 *         root               root
 *          |      rmv 15      |
 *          V   --------->     V
 *         20b                20b
 *      /      \           /      \
 *    10r      30r       10b      30r
 *   /  \     /  \      /  \     /  \
 *  5b  15b 25b  35b  5r  NULL 25b  35b
 */
void test_delRedBlackTree_delete_15_from_tree_should_not_rotate_and_flip_colour_case_2_leftright_remove(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node25,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'r');
  setNode(&node30,&node25,&node35,'r');
  setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;

  delRedBlackTree(&root, &node15);
  TEST_ASSERT_EQUAL_PTR(root, &node20);
  TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
  TEST_ASSERT_EQUAL_NODE(&node25, &node35, 'r', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node25);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node35);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}
/**
 *         root               root
 *          |      rmv 25      |
 *          V   --------->     V
 *         20b                20b
 *      /      \           /      \
 *    10r      30r       10r      30b
 *   /  \     /  \      /  \     /  \
 *  5b  15b 25b  35b  5b  15b NULL  35r
 */
void test_delRedBlackTree_delete_25_from_tree_should_not_rotate_and_flip_colour_case_3_rightleft_remove(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node25,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'r');
  setNode(&node30,&node25,&node35,'r');
  setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;

  delRedBlackTree(&root, &node25);
  TEST_ASSERT_EQUAL_PTR(root, &node20);
  TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
  TEST_ASSERT_EQUAL_NODE(NULL, &node35, 'b', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node35);
}
/**
 *         root               root
 *          |      rmv 35      |
 *          V   --------->     V
 *         20b                20b
 *      /      \           /      \
 *    10r      30r       10r      30b
 *   /  \     /  \      /  \     /  \
 *  5b  15b 25b  35b  5b   15b 25r  NULL
 */
void test_delRedBlackTree_delete_35_from_tree_should_not_rotate_and_flip_colour_case_4_rightright_remove(void){
  setNode(&node5,NULL,NULL,'b');
  setNode(&node15,NULL,NULL,'b');
  setNode(&node25,NULL,NULL,'b');
  setNode(&node30,NULL,NULL,'b');
  setNode(&node10,&node5,&node15,'r');
  setNode(&node30,&node25,&node35,'r');
  setNode(&node20,&node10,&node30,'b');
	Node *root = &node20;

  delRedBlackTree(&root, &node35);
  TEST_ASSERT_EQUAL_PTR(root, &node20);
  TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
  TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
  TEST_ASSERT_EQUAL_NODE(&node25, NULL, 'b', &node30);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
  TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node25);
}