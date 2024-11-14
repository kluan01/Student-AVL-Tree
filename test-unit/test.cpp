//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//#include "../AVL.h"
//#include <sstream>
//
//// Basic Test Cases
//TEST_CASE("Basic Insert", "[basic_insert]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//    std::istringstream input("insert \"a\" 1001\ninsert \"b\" 1002\ninsert \"c\" 1003");
//    std::string line;
//
//    while (std::getline(input, line)) {
//        std::istringstream streamed_line(line);
//        std::string operation;
//        streamed_line >> operation;
//        if (operation == "insert") {
//            std::string name;
//            int id;
//            streamed_line >> std::quoted(name) >> id;
//            tree.root = tree.insert(tree.root, id, name, response_list);
//        }
//    }
//
//    REQUIRE(response_list.size() == 3);
//    REQUIRE(response_list[0] == "successful");
//    REQUIRE(response_list[1] == "successful");
//    REQUIRE(response_list[2] == "successful");
//    cout << "Well done Kaden" << endl;
//}
//
//TEST_CASE("Basic Remove & Balancing", "[basic_remove]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    tree.root = tree.insert(tree.root, 50, "a", response_list);
//    tree.root = tree.insert(tree.root, 30, "b", response_list);
//    tree.root = tree.insert(tree.root, 70, "c", response_list);
//    tree.root = tree.insert(tree.root, 60, "d", response_list);
//    tree.root = tree.insert(tree.root, 80, "e", response_list);
//
//    response_list.clear();
//    tree.root = tree.remove(tree.root, 30, response_list);
//
//    REQUIRE(response_list.size() == 1);
//    REQUIRE(response_list[0] == "successful");
//
//    std::vector<std::string> inorder_list;
//    tree.printInorder(tree.root, inorder_list);
//
//    REQUIRE(inorder_list.size() == 4);
//    REQUIRE(inorder_list[0] == "a");
//    REQUIRE(inorder_list[1] == "d");
//    REQUIRE(inorder_list[2] == "c");
//    REQUIRE(inorder_list[3] == "e");
//    cout << "Well done Kaden" << endl;
//}
//
//TEST_CASE("Basic Bulk Insertions", "[basic_bulk_insert]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    for (int i = 1; i <= 100; ++i) {
//        tree.root = tree.insert(tree.root, i * 10, "node" + std::to_string(i), response_list);
//    }
//
//    REQUIRE(response_list.size() == 100);
//    for (auto& response : response_list) {
//        REQUIRE(response == "successful");
//    }
//
//    int balance = tree.getBalance(tree.root);
//    REQUIRE(balance >= -1);
//    REQUIRE(balance <= 1);
//    cout << "Well done Kaden" << endl;
//}
//
//TEST_CASE("Basic Mixed Operations", "[basic_mixed_operations]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    tree.root = tree.insert(tree.root, 500, "x", response_list);
//    tree.root = tree.insert(tree.root, 200, "y", response_list);
//    tree.root = tree.insert(tree.root, 800, "z", response_list);
//
//    response_list.clear();
//    bool found = tree.search_ID(tree.root, 200, response_list);
//    REQUIRE(found == true);
//    REQUIRE(response_list[0] == "y");
//
//    response_list.clear();
//    tree.root = tree.remove(tree.root, 800, response_list);
//    REQUIRE(response_list.size() == 1);
//    REQUIRE(response_list[0] == "successful");
//
//    response_list.clear();
//    found = tree.search_ID(tree.root, 800, response_list);
//    REQUIRE(found == false);
//    cout << "Well done Kaden" << endl;
//}
//
//TEST_CASE("Simple Duplicate and Edge Cases", "[simple_duplicate_and_edges]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    tree.root = tree.insert(tree.root, 1001, "a", response_list);
//    REQUIRE(response_list[0] == "successful");
//
//    response_list.clear();
//    tree.root = tree.insert(tree.root, 1001, "a_duplicate", response_list);
//    REQUIRE(response_list.size() == 1);
//    REQUIRE(response_list[0] == "unsuccessful");
//
//    response_list.clear();
//    tree.root = tree.insert(tree.root, INT_MAX, "max", response_list);
//    tree.root = tree.insert(tree.root, INT_MIN, "min", response_list);
//    REQUIRE(response_list.size() == 2);
//    REQUIRE(response_list[0] == "successful");
//    REQUIRE(response_list[1] == "successful");
//
//    response_list.clear();
//    bool found = tree.search_ID(tree.root, INT_MAX, response_list);
//    REQUIRE(found == true);
//    REQUIRE(response_list[0] == "max");
//
//    response_list.clear();
//    found = tree.search_ID(tree.root, INT_MIN, response_list);
//    REQUIRE(found == true);
//    REQUIRE(response_list[0] == "min");
//    cout << "Well done Kaden" << endl;
//}
//
//// Extensive Test Cases
//TEST_CASE("Extensive Insertions and Deletions", "[extensive_insert_delete]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    for (int i = 1; i <= 1000; ++i) {
//        tree.root = tree.insert(tree.root, i, "node" + std::to_string(i), response_list);
//        REQUIRE(response_list.back() == "successful");
//    }
//
//    std::vector<int> heights;
//    std::function<void(TreeNode*)> checkBalance = [&](TreeNode* node) {
//        if (node == nullptr) return;
//        checkBalance(node->left);
//        checkBalance(node->right);
//        int leftHeight = node->left ? node->left->height : 0;
//        int rightHeight = node->right ? node->right->height : 0;
//        int balanceFactor = std::abs(leftHeight - rightHeight);
//        REQUIRE(balanceFactor <= 1);
//    };
//    checkBalance(tree.root);
//
//    // Remove (every 10th element) from the tree
//    for (int i = 10; i <= 1000; i += 10) {
//        response_list.clear();
//        tree.root = tree.remove(tree.root, i, response_list);
//        REQUIRE(response_list.back() == "successful");
//    }
//
//    checkBalance(tree.root);
//
//    std::vector<int> inorder_list;
//    std::function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node) {
//        if (node == nullptr) return;
//        inorderTraversal(node->left);
//        inorder_list.push_back(node->ID);
//        inorderTraversal(node->right);
//    };
//    inorderTraversal(tree.root);
//
//    REQUIRE(std::is_sorted(inorder_list.begin(), inorder_list.end()));
//    cout << "Well done Kaden" << endl;
//}
//
//TEST_CASE("Randomized Data Insertions", "[random_insertions]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    // Seed for random number generation
//    std::mt19937 rng(42);
//    std::uniform_int_distribution<int> dist(1, 10000);
//
//    std::set<int> inserted_ids;
//    for (int i = 0; i < 500; ++i) {
//        int random_id = dist(rng);
//        if (inserted_ids.find(random_id) == inserted_ids.end()) {
//            inserted_ids.insert(random_id);
//            tree.root = tree.insert(tree.root, random_id, "random_node", response_list);
//            REQUIRE(response_list.back() == "successful");
//        }
//    }
//
//    std::function<void(TreeNode*)> checkBalance = [&](TreeNode* node) {
//        if (node == nullptr)
//            return;
//        checkBalance(node->left);
//        checkBalance(node->right);
//        int leftHeight = node->left ? node->left->height : 0;
//        int rightHeight = node->right ? node->right->height : 0;
//        int balanceFactor = std::abs(leftHeight - rightHeight);
//        REQUIRE(balanceFactor <= 1);
//    };
//    checkBalance(tree.root);
//
//    std::vector<int> inorder_list;
//    std::function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node) {
//        if (node == nullptr)
//            return;
//        inorderTraversal(node->left);
//        inorder_list.push_back(node->ID);
//        inorderTraversal(node->right);
//    };
//    inorderTraversal(tree.root);
//
//    REQUIRE(std::is_sorted(inorder_list.begin(), inorder_list.end()));
//    cout << "Well done Kaden" << endl;
//}
//
//TEST_CASE("Edge Cases and Extreme Values", "[edge_cases]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    tree.root = tree.insert(tree.root, INT_MAX, "max_value", response_list);
//    tree.root = tree.insert(tree.root, INT_MIN, "min_value", response_list);
//
//    REQUIRE(response_list.size() == 2);
//    REQUIRE(response_list[0] == "successful");
//    REQUIRE(response_list[1] == "successful");
//
//    response_list.clear();
//    bool found = tree.search_ID(tree.root, INT_MAX, response_list);
//    REQUIRE(found == true);
//    REQUIRE(response_list[0] == "max_value");
//
//    response_list.clear();
//    found = tree.search_ID(tree.root, INT_MIN, response_list);
//    REQUIRE(found == true);
//    REQUIRE(response_list[0] == "min_value");
//
//    response_list.clear();
//    tree.root = tree.remove(tree.root, INT_MAX, response_list);
//    REQUIRE(response_list.size() == 1);
//    REQUIRE(response_list[0] == "successful");
//
//    response_list.clear();
//    tree.root = tree.remove(tree.root, INT_MIN, response_list);
//    REQUIRE(response_list.size() == 1);
//    REQUIRE(response_list[0] == "successful");
//    cout << "Well done Kaden" << endl;
//}
//
//TEST_CASE("Complex Deletion Patterns", "[complex_deletions]") {
//    AVLTree tree;
//    std::vector<std::string> response_list;
//
//    for (int i = 50; i >= 1; --i) {
//        tree.root = tree.insert(tree.root, i, "node" + std::to_string(i), response_list);
//    }
//
//    // Remove every third element
//    for (int i = 3; i <= 50; i += 3) {
//        response_list.clear();
//        tree.root = tree.remove(tree.root, i, response_list);
//        REQUIRE(response_list.back() == "successful");
//    }
//
//    std::function<void(TreeNode*)> checkBalance = [&](TreeNode* node) {
//        if (node == nullptr)
//            return;
//        checkBalance(node->left);
//        checkBalance(node->right);
//        int leftHeight = node->left ? node->left->height : 0;
//        int rightHeight = node->right ? node->right->height : 0;
//        int balanceFactor = std::abs(leftHeight - rightHeight);
//        REQUIRE(balanceFactor <= 1);
//    };
//    checkBalance(tree.root);
//
//    std::vector<int> inorder_list;
//    std::function<void(TreeNode*)> inorderTraversal = [&](TreeNode* node) {
//        if (node == nullptr)
//            return;
//        inorderTraversal(node->left);
//        inorder_list.push_back(node->ID);
//        inorderTraversal(node->right);
//    };
//    inorderTraversal(tree.root);
//
//    REQUIRE(std::is_sorted(inorder_list.begin(), inorder_list.end()));
//    cout << "Well done Kaden" << endl;
//}