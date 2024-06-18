#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// 이진 트리 노드 구조체
typedef struct TreeNode {
    char val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 이진 트리 생성 함수
TreeNode* buildTree(char* preorder, char* inorder, int inorder_start, int inorder_end, int* preorder_index) {
    if (inorder_start > inorder_end) // 범위를 벗어나면 NULL 반환
        return NULL;

    // 현재 노드 생성
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = preorder[(*preorder_index)++]; // preorder의 다음 값으로 루트 설정

    // inorder에서 루트의 위치 찾기
    int inorder_index;
    for (int i = inorder_start; i <= inorder_end; ++i) {
        if (inorder[i] == root->val) {
            inorder_index = i;
            break;
        }
    }

    // inorder 기준으로 왼쪽 서브트리와 오른쪽 서브트리 생성
    root->left = buildTree(preorder, inorder, inorder_start, inorder_index - 1, preorder_index);
    root->right = buildTree(preorder, inorder, inorder_index + 1, inorder_end, preorder_index);

    return root;
}

// inorder 순회 함수
void inorderTraversal(TreeNode* root, char* result, int* index) {
    if (root == NULL)
        return;

    inorderTraversal(root->left, result, index);
    result[(*index)++] = root->val; // 결과 배열에 현재 노드 값 추가
    inorderTraversal(root->right, result, index);
}

// 이진 트리의 각 노드에 대한 complete binary tree의 노드 번호 계산 함수
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


    // 이진 트리 생성
    int preorder_index = 0;
    TreeNode* root = buildTree(preorder_sequence, inorder_sequence, 0, strlen(inorder_sequence) - 1, &preorder_index);

    // inorder 순회 결과 확인
    char inorder_result[strlen(inorder_sequence) + 1];
    int index = 0;
    inorderTraversal(root, inorder_result, &index);
    inorder_result[index] = '\0'; // 문자열 마지막에 NULL 추가
    if (strcmp(inorder_sequence, inorder_result) != 0) {
        printf("Error: Invalid input sequences.\n");
        return 1;
    }

    // 각 노드에 대한 complete binary tree의 노드 번호 계산
    int node_numbers[26] = { 0 }; // 노드 번호를 저장할 배열, 알파벳 대문자 A부터 Z까지
    getNodeNumbers(root, node_numbers, 1);

    // 결과 출력
    fprintf(output, "%d", node_numbers[preorder_sequence[0] - 'A']); // 루트 노드의 노드 번호 출력
    for (int i = 1; i < strlen(preorder_sequence); ++i) {
        fprintf(output, ", %d", node_numbers[preorder_sequence[i] - 'A']); // 나머지 노드의 노드 번호 출력
    }
    printf("\n");

    return 0;
}
