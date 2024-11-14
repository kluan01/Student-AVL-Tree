#include <string>
#include <vector>
using namespace std;

// Node & Tree Classes
class TreeNode {
public:
    int ID;
    string NAME;
    int height;
    TreeNode *left;
    TreeNode *right;

    // Constructor
    TreeNode(int studentID, string studentName) : ID(studentID), NAME(studentName), height(1), left(nullptr), right (nullptr) {}
};

class AVLTree {
public:
    TreeNode* root;
    AVLTree() : root(nullptr) {}

    // Helper Functions
    void updateHeight(TreeNode *root);
    int getBalance(TreeNode *root);
    TreeNode* rightRotate(TreeNode *root);
    TreeNode* leftRotate(TreeNode *root);
    TreeNode* getSuccessor(TreeNode *root);
    TreeNode* getPredecessor(TreeNode *root);
    void printInorderID(TreeNode *root, vector<int> &list);
    void printResponses(vector<string> &response_list);

    // Necessary Functions
    TreeNode* insert(TreeNode *root, int ID, string NAME, vector<string> &response_list);
    TreeNode* remove(TreeNode *root, int ID, vector<string> &response_list);
    bool search_ID(TreeNode *root, int ID, vector<string> &response_list);
    bool search_NAME(TreeNode *root, string NAME, vector<string> &response_list);
    void printInorder(TreeNode *root, vector<string> &list);
    void printPreorder(TreeNode *root,vector<string> &list);
    void printPostorder(TreeNode *root,vector<string> &list);
    void printLevelCount(TreeNode *root, vector<string> &response_list);
};