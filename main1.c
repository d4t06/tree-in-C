#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SPACE 5
struct TreeNode
{
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode *Tree;

int height(Tree r)
{
    if (r == NULL)
        return -1;
    else
    {
        // chạy cho tới khi tới cuối cùng
        // lheight = rheight = -1
        // +1 để thành không (nút lá độ cao là 0)
        // nút chứa hai nút là độ cao là 1 (0 + 1)
        // một link là độ cao bằng một

        int lHeight = height(r->left);
        int rHeight = height(r->right);
        if (lHeight > rHeight)
            return lHeight + 1;
        else
            // lheight <= rheight
            return rHeight + 1;
    }
}
int getBalanceFactor(Tree r)
{
    if (r == NULL)
        return -1;
    else
        return (height(r->left) - height(r->right));
}
Tree newNode(int value)
{
    Tree pRoot;
    pRoot = malloc(sizeof(struct TreeNode));
    pRoot->key = value;
    pRoot->left = NULL;
    pRoot->right = NULL;

    return pRoot;
}

void insertNode(int data, Tree *pRoot)
{
    if ((*pRoot == NULL))
    {
        (*pRoot) = newNode(data);
        return;
    }
    else if (data < (*pRoot)->key)
        insertNode(data, &((*pRoot)->left));
    else if (data > (*pRoot)->key)
        insertNode(data, &((*pRoot)->right));
    else
    {
        printf("Duplicate value ");
        return;
    }
}

Tree minValue(Tree node)
{
    // Tree temp = node;
    // while (temp->left != NULL)
    // {
    //     temp = temp->left;
    // }
    // return temp;
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}
void deleteNode(int x, Tree *r)
{
    if ((*r) == NULL)
        return;
    // find x
    if (x < (*r)->key)
        deleteNode(x, &((*r)->left));
    else if (x > (*r)->key)
        deleteNode(x, &((*r)->right));
    // matches
    else
    {
        // has only right child of is leaf
        if ((*r)->left == NULL)
        {
            Tree temp = (*r)->right;

            (*r) = temp;
        }
        // has only left child
        else if ((*r)->right == NULL)
        {
            Tree temp = (*r)->left;
            (*r) = temp;
        }
        else
        {
            Tree temp = minValue((*r)->right);
            // minValue (Tree r)
            (*r)->key = temp->key;
            deleteNode(temp->key, &((*r)->right));
        }
    }
}
Tree convertTree(Tree r)
{
    if (r == NULL)
        return 0;
    convertTree(r->left);
    convertTree(r->right);
    Tree temp;
    temp = r->left;
    r->left = r->right;
    r->right = temp;
    return r;
    // return temp;
}
int fodableHandle(Tree l, Tree r)
{
    if (l == NULL && r == NULL)
    {
        return 1;
    }
    if (l == NULL || r == NULL)
    {
        return 0;
    }
    return fodableHandle(l->left, r->right) && fodableHandle(l->right, r->left);
}
int isFoldable(Tree r)
{
    if (r == NULL)
        return 0;
    return fodableHandle(r->left, r->right);
}
int getLeaves(Tree r)
{
    if (r == NULL)
        return 0;
    if (r->left == NULL && r->right == NULL)
        return 1;
    return getLeaves(r->left) + getLeaves(r->right);
}
int countingNode2Child(Tree r)
{
    if (r == NULL)
        return 0;
    int couting = countingNode2Child(r->left) + countingNode2Child(r->right);

    if (r->left != NULL && r->right != NULL)
        couting++;
    return couting;
}
int countingNode1Child(Tree r)
{
    if (r == NULL)
        return 0;

    int counting = countingNode1Child(r->left) + countingNode1Child(r->right);

    if ((r->left == NULL && r->right != NULL) ||
        (r->right == NULL && r->left != NULL))
    {
        counting++;
    }
    return counting;
}

int identicalTrees(Tree r1, Tree r2)
{
    // both are empty
    if (r1 == NULL && r2 == NULL)
        return 1;
    // one empty
    if (r1 == NULL || r2 == NULL)
        return 0;
    // both are not empty
    return (r1->key == r2->key) && identicalTrees(r1->right, r2->right) && identicalTrees(r1->left, r2->left);
}
int sameStructureTrees(Tree r1, Tree r2)
{
    // both are empty
    if (r1 == NULL && r2 == NULL)
        return 1;
    // one empty
    if (r1 == NULL || r2 == NULL)
        return 0;
    // both are not empty
    return sameStructureTrees(r1->right, r2->right) && sameStructureTrees(r1->left, r2->left);
}
int hasPathSum(Tree r, int sum)
{
    if (r == NULL)
        return 0;
    int ans = 0;

    int subSum = sum - r->key;

    /* If we reach a leaf r
          and sum becomes 0 then
           * return true*/
    if (subSum == 0 && r->left == NULL && r->right == NULL)
        return 1;

    /* otherwise check both subtrees */
    if (r->left)
        ans = ans || hasPathSum(r->left, subSum);
    if (r->right)
        ans = ans || hasPathSum(r->right, subSum);

    return ans;
}

void print2D(Tree r, int space)
{
    if (r == NULL) // Base case  1
        return;
    space += SPACE;           // Increase distance between levels   2
    print2D(r->right, space); // Process right child first 3
    // printf("\n");
    for (int i = SPACE; i < space; i++) // 5
        printf(" ");                    // 5.1
    printf("%d\n", r->key);             // 6
    print2D(r->left, space);            // Process left child  7
}

int main()
{
    int option, value;
    Tree root = NULL;
    Tree root2 = NULL;
    // root = initTree();
    insertNode(5, &root);
    insertNode(8, &root);
    insertNode(2, &root);
    insertNode(4, &root);
    insertNode(7, &root);
    // insertNode(3, &root);
    // insertNode(5, &root);
    // insertNode(4, &root);

    // insertNode(33, &root2);
    // insertNode(22, &root2);
    // insertNode(77, &root2);
    // insertNode(62, &root2);
    // insertNode(26, &root2);

    print2D(root, 1);
    // print2D(root2, 1);
    // printf("isSameStructureTrees : %d\n", sameStructureTrees(root, root2));
    // printf("isIdentical: %d", identicalTrees(root, root2));
    printf("hasPathSum: %d", hasPathSum(root, 12));

    do
    {
        printf("\n");
        printf("1. Insert       ");
        printf("2. DeleteNode       ");
        printf("4. Check foldable\n");
        printf("5. couting leaf node     ");
        printf("6. couting Node 2 Child     ");
        printf("0. Exit");
        printf("Chose operand to perform...");
        // option = 0;
        scanf("%d", &option);
        switch (option)
        {

        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insertNode(value, &root);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            deleteNode(value, &root);
            break;
        case 4:
            printf("\nHeight of tree: %d\n", height(root));
            break;
        case 3:
            print2D(root, 1);
            break;

        default:
            printf("Exit");
            break;
        }
    } while (option != 0);

    return 0;
}
