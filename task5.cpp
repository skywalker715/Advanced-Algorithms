#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

struct TreeNode {
    string data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val) : data(val), left(nullptr), right(nullptr) {}
};

int compute(TreeNode* node) {
    if (!node) return 0;
    if (!node->left && !node->right) return stoi(node->data);
    int leftResult = compute(node->left);
    int rightResult = compute(node->right);

    if (node->data == "+") return leftResult + rightResult;
    if (node->data == "-") return leftResult - rightResult;
    if (node->data == "*") return leftResult * rightResult;
    if (node->data == "/") return leftResult / rightResult;
    return 0;
}

void display(TreeNode* node) {
    if (!node) return;
    display(node->left);
    cout << node->data << " ";
    display(node->right);
}

TreeNode* buildTree(const string& expr) {
    stack<TreeNode*> nodes;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') continue;

        if (isdigit(expr[i])) {
            string number;
            while (i < expr.length() && isdigit(expr[i])) {
                number += expr[i++];
            }
            i--;
            nodes.push(new TreeNode(number));
        } else if (expr[i] == '(') {
            ops.push(expr[i]);
        } else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                TreeNode* operatorNode = new TreeNode(string(1, ops.top()));
                ops.pop();

                operatorNode->right = nodes.top();
                nodes.pop();
                operatorNode->left = nodes.top();
                nodes.pop();
                nodes.push(operatorNode);
            }
            ops.pop();
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            ops.push(expr[i]);
        }
    }

    return nodes.top();
}

int main() {
    string expression = "((9-1)/(4-2))";
    TreeNode* root = buildTree(expression);
    display(root);
    cout << "\nValue at the root of tree: " << compute(root) << endl;
    return 0;
}
