#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ���� Ʈ�� ��� ����ü
typedef struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ���� Ʈ�� ���� �Լ�
TreeNode* buildTree(char* preorder, char* inorder, int inorder_start, int inorder_end, int* preorder_index) {
    if (inorder_start > inorder_end) // ������ ����� NULL ��ȯ
        return NULL;

    // ���� ��� ����
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = preorder[(*preorder_index)++]; // preorder�� ���� ������ ��Ʈ ����

    // inorder���� ��Ʈ�� ��ġ ã��
    int inorder_index;
    for (int i = inorder_start; i <= inorder_end; ++i) {
        if (inorder[i] == root->val) {
            inorder_index = i;
            break;
        }
    }

    // inorder �������� ���� ����Ʈ���� ������ ����Ʈ�� ����
    root->left = buildTree(preorder, inorder, inorder_start, inorder_index - 1, preorder_index);
    root->right = buildTree(preorder, inorder, inorder_index + 1, inorder_end, preorder_index);

    return root;
}

// inorder ��ȸ �Լ�
void inorderTraversal(TreeNode* root, char* result, int* index) {
    if (root == NULL)
        return;

    inorderTraversal(root->left, result, index);
    result[(*index)++] = root->val; // ��� �迭�� ���� ��� �� �߰�
    inorderTraversal(root->right, result, index);
}

// ���� Ʈ���� �� ��忡 ���� complete binary tree�� ��� ��ȣ ��� �Լ�
void getNodeNumbers(TreeNode* root, int* node_numbers, int node_number) {
    if (root == NULL)
        return;

    node_numbers[root->val - 'A'] = node_number;
    getNodeNumbers(root->left, node_numbers, node_number * 2);
    getNodeNumbers(root->right, node_numbers, node_number * 2 + 1);
}

int main(int argc, char* argv[]) {
    char preorder_sequence[MAX];
    char inorder_sequence[MAX];

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");


    if (input == NULL) exit(1);

    fscanf(input, "preorder sequence : %s\n", preorder_sequence);
    fscanf(input, "inorder sequence : %s\n", inorder_sequence);

    fclose(input);


    // ���� Ʈ�� ����
    int preorder_index = 0;
    TreeNode* root = buildTree(preorder_sequence, inorder_sequence, 0, strlen(inorder_sequence) - 1, &preorder_index);

    // inorder ��ȸ ��� Ȯ��
    char inorder_result[strlen(inorder_sequence) + 1];
    int index = 0;
    inorderTraversal(root, inorder_result, &index);
    inorder_result[index] = '\0'; // ���ڿ� �������� NULL �߰�
    if (strcmp(inorder_sequence, inorder_result) != 0) {
        printf("Error: Invalid input sequences.\n");
        return 1;
    }

    // �� ��忡 ���� complete binary tree�� ��� ��ȣ ���
    int node_numbers[26] = { 0 }; // ��� ��ȣ�� ������ �迭, ���ĺ� �빮�� A���� Z����
    getNodeNumbers(root, node_numbers, 1);

    // ��� ���
    fprintf(output, "%d", node_numbers[preorder_sequence[0] - 'A']); // ��Ʈ ����� ��� ��ȣ ���
    for (int i = 1; i < strlen(preorder_sequence); ++i) {
        fprintf(output, ", %d", node_numbers[preorder_sequence[i] - 'A']); // ������ ����� ��� ��ȣ ���
    }
    printf("\n");

    return 0;
}
