#include <iostream>
#include "AVL.h"
#include <algorithm>
#include <string>
#include <sstream>
#include <regex>
using namespace std;

// Helper Functions - self-explanatory
void AVLTree::updateHeight(TreeNode *root) {
    if (root == nullptr) { // FIX
        return;
    }
    root->height = 1 + max(root->left == nullptr? 0:root->left->height, root->right == nullptr? 0:root->right->height);
}

int AVLTree::getBalance(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    }
    return (root->left == nullptr? 0:root->left->height) - (root->right == nullptr? 0:root->right->height);
}

TreeNode* AVLTree::leftRotate(TreeNode *root) {
    TreeNode *grandchild = root->right->left;
    TreeNode* newParent = root->right;
    newParent->left = root;
    root->right = grandchild;

    updateHeight(root);
    updateHeight(newParent);
    return newParent;
}

TreeNode* AVLTree::rightRotate(TreeNode *root) {
    TreeNode *grandchild = root->left->right;
    TreeNode* newParent = root->left;
    newParent->right = root;
    root->left = grandchild;

    updateHeight(root);
    updateHeight(newParent);
    return newParent;
}

TreeNode* AVLTree::getSuccessor(TreeNode *root) {
    if (root->left == nullptr)
        return root;
    return getSuccessor(root->left);
}

TreeNode* AVLTree::getPredecessor(TreeNode *root) {
    if (root->right == nullptr)
        return root;
    return getPredecessor(root->right);
}

void AVLTree::printResponses(vector<std::string> &response_list) {
    for (const auto & j : response_list) {
        cout << j << endl;
    }
}

// Main Functions
TreeNode *AVLTree::insert(TreeNode *root, int ID, string NAME, vector<string> &response_list) {
    // Standard BST insertion
    if (root == nullptr) {
        response_list.emplace_back("successful");
        return new TreeNode(ID, NAME);
    } else if (ID < root->ID) {
        root->left = insert(root->left, ID, NAME, response_list);
    } else if (ID > root->ID) {
        root->right = insert(root->right, ID, NAME, response_list);
    }
    else {
        response_list.emplace_back("unsuccessful");
        return root;
    }

    // Update height
    updateHeight(root);
    // Rotations for AVL Balancing
    int parentBalance = getBalance(root);
    // Right heavy tree
    if (parentBalance < -1) {
        int childBalance = getBalance(root->right);
        // Left heavy subtree (right left rotation)
        if (childBalance > 0) {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
        // Right heavy subtree (left rotation)
        else {
            root = leftRotate(root);
        }
    }

    // Left heavy tree
    else if (parentBalance > 1) {
        int childBalance = getBalance(root->left);
        // Right heavy subtree (left right rotation)
        if(childBalance < 0) {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
        // Left heavy subtree (right rotation)
        else {
            root = rightRotate(root);
        }
    }
    // Update root height & return
    updateHeight(root);
    return root;
}

TreeNode* AVLTree::remove(TreeNode *root, int ID, vector<string> &response_list) {
    // Standard BST deletion
    if (root == nullptr) {
        response_list.emplace_back("unsuccessful");
    } else if (ID < root->ID) {
        root->left = remove(root->left, ID, response_list);
    } else if (ID > root->ID) {
        root->right = remove(root->right, ID, response_list);
    } else {
        // 0 Children
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            response_list.emplace_back("successful");
            return nullptr;
        }
            // 1 Child
        else if (root->left == nullptr) {
            TreeNode *temp = root->right;
            delete root;
            response_list.emplace_back("successful");
            return temp;
        } else if (root->right == nullptr) {
            TreeNode *temp = root->left;
            delete root;
            response_list.emplace_back("successful");
            return temp;
        }
            // 2 Children (YAY)
        else {
            TreeNode *temp;
            // Inorder Successor
            if (root->right != nullptr) {
                if (root->right->left != nullptr) {
                    temp = getSuccessor(root->right);
                } else {
                    temp = root->right;
                }
                root->ID = temp->ID;
                root->NAME = temp->NAME;
                root->right = remove(root->right, temp->ID, response_list); // Might cause issue later
            }
        }
    }

    // Update height
    updateHeight(root);
    // Rotations for AVL Balancing
    int parentBalance = getBalance(root);
    // Right heavy tree
    if (parentBalance < -1) {
        int childBalance = getBalance(root->right);
        // Left heavy subtree (right left rotation)
        if (childBalance > 0) {
            root->right = rightRotate(root->right);
            root = leftRotate(root);
        }
            // Right heavy subtree (left rotation)
        else {
            root = leftRotate(root);
        }
    }

        // Left heavy tree
    else if (parentBalance > 1) {
        int childBalance = getBalance(root->left);
        // Right heavy subtree (left right rotation)
        if (childBalance < 0) {
            root->left = leftRotate(root->left);
            root = rightRotate(root);
        }
            // Left heavy subtree (right rotation)
        else {
            root = rightRotate(root);
        }
    }
    // Update root height & return
    updateHeight(root);
    return root;
}

// Search Tree by ID
bool AVLTree::search_ID(TreeNode *root, int ID, vector<string> &response_list) {
    if (root == nullptr) {
        return false;
    } else if (root->ID == ID) {
        response_list.emplace_back(root->NAME);
        return true;
    } else if (ID < root->ID) {
        return search_ID(root->left, ID, response_list);
    } else {
        return search_ID(root->right, ID, response_list);
    }
}

// Search Tree by Name
bool AVLTree::search_NAME(TreeNode *root, string NAME, vector<string> &response_list) {
    if (root == nullptr) {
        return false;
    }
    bool found = false;

    bool found_in_left = search_NAME(root->left, NAME, response_list);

    if (root->NAME == NAME) {
        response_list.emplace_back(to_string(root->ID));
        found = true;
    }

    bool found_in_right = search_NAME(root->right, NAME, response_list);

    return found || found_in_left || found_in_right;
}

// Traversal Functions
void AVLTree::printInorder(TreeNode *root, vector<string> &list) {
    if (root == nullptr)
        return;
    else {
        printInorder(root->left, list);
        list.push_back(root->NAME);
        printInorder(root->right, list);
    }
}

void AVLTree::printInorderID(TreeNode *root, vector<int> &list_id) {
    if (root == nullptr)
        return;
    else {
        printInorderID(root->left, list_id);
        list_id.push_back(root->ID);
        printInorderID(root->right, list_id);
    }
}

void AVLTree::printPreorder(TreeNode *root, vector<string> &list) {
    if (root == nullptr)
        return;
    else {
        list.push_back(root->NAME);
        printPreorder(root->left, list);
        printPreorder(root->right, list);
    }
}

void AVLTree::printPostorder(TreeNode *root, vector<string> &list) {
    if (root == nullptr)
        return;
    else {
        printPostorder(root->left, list);
        printPostorder(root->right, list);
        list.push_back(root->NAME);
    }
}

void AVLTree::printLevelCount(TreeNode *root, vector<string> &response_list) {
    if (root == nullptr) {
        response_list.emplace_back("0");
    } else {
        response_list.emplace_back(std::to_string(root->height));
    }
}

int main() {
    // Initialize Class & Variables
    AVLTree tree;
    string name, str_id;
    vector<string> name_list;
    vector<int> id_list;
    vector<string> response_list;

    // Parse # of commands
    int num_command;
    cin >> num_command;
    cin.ignore();

    // Loop until entire input is read
    while (num_command--) {
        // Clear up vectors
        name_list.clear();
        id_list.clear();
        // Read entire line by line
        string full_line;
        getline(cin, full_line);

        // Empty command edge case
        if (full_line.empty()) {
            response_list.emplace_back("unsuccessful");
            continue;
        }

        // Create extractable string stream from fullLine
        string operation;
        stringstream streamed_line(full_line);
        streamed_line >> operation;

        // Insert Operation
        if (operation == "insert") {
            // Slice quotation and ensure name is present with quotation marks
            char quotation;
            streamed_line >> quotation;
            if (quotation != '"') {
                response_list.emplace_back("unsuccessful");
                continue;
            }

            // Slice the rest of name & id
            getline(streamed_line, name, '"');
            streamed_line >> str_id;

            // Ensure name is not empty
            if (name.empty()) {
                response_list.emplace_back("unsuccessful");
                continue;
            }

            // Ensure name is only characters
            regex char_obj = regex("[A-Za-z ]+");
            bool char_check = regex_match(name, char_obj);
            if (!char_check) {
                response_list.emplace_back("unsuccessful");
                continue;
            }

            // Ensure ID is 8 digits long
            int str_length = str_id.length();
            if (str_length < 8 || str_length > 8) {
                response_list.emplace_back("unsuccessful");
                continue;
            }

            // Ensure ID is only digits
            regex int_obj = regex("[0-9]{8,8}");
            bool int_check = regex_match(str_id, int_obj);
            if (!int_check) {
                response_list.emplace_back("unsuccessful");
                continue;
            }

            // Insert Node into AVL Tree?
            int int_id = stoi(str_id);
            tree.root = tree.insert(tree.root, int_id, name, response_list);
        }

        // Remove & Search Operations
        else if (operation == "remove" || operation == "search") {
            // Either streams the ID or a quotation mark -> check which one
            streamed_line >> str_id;
            regex str_obj = regex("^\".*\"$"); // Might have to create edge case surrounding empty remove/search
            bool string_check = regex_match(str_id, str_obj);

            // Search is a name
            if (string_check) {
                // Get rid of quotations
                name = str_id.substr(1, str_id.length() - 2);

                // Ensure name is not empty
                if (name.empty()) {
                    response_list.emplace_back("unsuccessful");
                    continue;
                }

                // Ensure name is only characters
                regex char_obj = regex("[A-Za-z ]+");
                bool char_check = regex_match(name, char_obj);
                if (!char_check) {
                    response_list.emplace_back("unsuccessful");
                    continue;
                }
                bool found = tree.search_NAME(tree.root, name, response_list); // FIX
                if (!found) {
                    response_list.emplace_back("unsuccessful");
                }
            }

            // Search is an ID or a Remove Operation
            else {
                // Ensure ID is only digits
                regex int_obj = regex("[0-9]{8,8}");
                bool int_check = regex_match(str_id, int_obj);
                if (!int_check) {
                    response_list.emplace_back("unsuccessful");
                    continue;
                }

                // Ensure ID is 8 digits long
                int str_length = str_id.length();
                if (str_length < 8 || str_length > 8) {
                    response_list.emplace_back("unsuccessful");
                    continue;
                }

                // String -> Int
                int int_id = stoi(str_id);

                // Remove ID
                if (operation == "remove") {
                    tree.remove(tree.root, int_id, response_list);
                } else {
                    // Search ID
                    bool found = tree.search_ID(tree.root, int_id, response_list);
                    if (!found) {
                        response_list.emplace_back("unsuccessful");
                    }
                }
            }
        }

        // Print Inorder Traversal
        else if (operation == "printInorder") {
            tree.printInorder(tree.root, name_list);
            string output;
            for (size_t i = 0; i < name_list.size(); ++i) {
                output += name_list[i];
                if (i < name_list.size() - 1)
                    output += ", ";
            }
            response_list.emplace_back(output);
        }

        // Print Preorder Traversal
        else if (operation == "printPreorder") {
            tree.printPreorder(tree.root, name_list);
            string output;
            for (size_t i = 0; i < name_list.size(); ++i) {
                output += name_list[i];
                if (i < name_list.size() - 1)
                    output += ", ";
            }
            response_list.emplace_back(output);
        }

        // Print Postorder traversal
        else if (operation == "printPostorder") {
            tree.printPostorder(tree.root, name_list);
            string output;
            for (size_t i = 0; i < name_list.size(); ++i) {
                output += name_list[i];
                if (i < name_list.size() - 1)
                    output += ", ";
            }
            response_list.emplace_back(output);
        }

        // Print levels in tree
        else if (operation == "printLevelCount") {
            tree.printLevelCount(tree.root, response_list);
        }

        // Remove Inorder ID based off user input "n"
        else if (operation == "removeInorder") {
            int n;
            streamed_line >> n;

            // Invalid input for n
            if (streamed_line.fail() || n < 0) {
                response_list.emplace_back("unsuccessful");
                continue;
            }

            // Traverse tree via inorder
            tree.printInorderID(tree.root, id_list);
            if (n >= id_list.size()) { // Invalid input for n
                response_list.emplace_back("unsuccessful");
                continue;
            } else {
                // Remove nth ID
                tree.root = tree.remove(tree.root, id_list[n], response_list);
            }
        }

        // Missing/error in command
        else {
            response_list.emplace_back("unsuccessful");
        }
    }

    // Print out all results from user command input
    tree.printResponses(response_list);
    return 0;
}
