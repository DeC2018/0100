#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 1000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to check if two trees are the same
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL && q == NULL) return true;
    if (p == NULL || q == NULL) return false;
    if (p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// Helper function to create a new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to parse input string like "[1,2,3]"
int parseInput(const char* s, char arr[][16], int* n) {
    int idx = 0, arr_idx = 0;
    char buf[16];
    int buf_idx = 0;
    while (s[idx]) {
        if (s[idx] == '[' || s[idx] == ']' || s[idx] == ' ' || s[idx] == '\n') {
            idx++;
            continue;
        }
        if (s[idx] == ',') {
            if (buf_idx > 0) {
                buf[buf_idx] = '\0';
                strcpy(arr[arr_idx++], buf);
                buf_idx = 0;
            }
            idx++;
            continue;
        }
        buf[buf_idx++] = s[idx++];
    }
    if (buf_idx > 0) {
        buf[buf_idx] = '\0';
        strcpy(arr[arr_idx++], buf);
    }
    *n = arr_idx;
    return arr_idx;
}

// Helper function to build a binary tree from an array of strings (level order, "null" for NULL)
struct TreeNode* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct TreeNode* nodes[MAX_NODES] = {0};
    int i, j = 1;
    nodes[0] = newNode(atoi(arr[0]));
    int front = 0, rear = 1;
    while (front < rear && j < n) {
        struct TreeNode* curr = nodes[front++];
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->left = newNode(atoi(arr[j]));
            nodes[rear++] = curr->left;
        }
        j++;
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->right = newNode(atoi(arr[j]));
            nodes[rear++] = curr->right;
        }
        j++;
    }
    return nodes[0];
}

// Helper function to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main() {
    const char* inputs[][2] = {
        {"[1,2,3]", "[1,2,3]"},
        {"[1,2]", "[1,null,2]"},
        {"[1,2,1]", "[1,1,2]"}
    };
    int num_cases = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: p = %s, q = %s\n", inputs[i][0], inputs[i][1]);

        char arrP[MAX_NODES][16], arrQ[MAX_NODES][16];
        int nP = 0, nQ = 0;

        parseInput(inputs[i][0], arrP, &nP);
        parseInput(inputs[i][1], arrQ, &nQ);

        struct TreeNode* p = buildTree(arrP, nP);
        struct TreeNode* q = buildTree(arrQ, nQ);

        printf("Output: %s\n", isSameTree(p, q) ? "true" : "false");

        deleteTree(p);
        deleteTree(q);
    }

    return 0;
}
