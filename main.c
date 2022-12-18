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

void preOrder(Tree root)
{
    if (root != NULL)
    {
        printf("%d ", root->key); // N
        preOrder(root->left);     // L
        preOrder(root->right);    // R
    }
}
Tree initTree()
{
    Tree pRoot;
    pRoot = malloc(sizeof(struct TreeNode));
    pRoot->left = NULL;
    pRoot->right = NULL;
    return pRoot;
}
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

void insertNode_While(int value, Tree r)
{
    if (!r->key)
    {
        r->key = value;
    }
    else
    {
        Tree temp, ptr = NULL;
        temp = newNode(value);
        ptr = r;
        while (ptr != NULL)
        {
            // duplicate
            if (temp->key == ptr->key)
                return;
            // khi toi cuoi cung ben trai
            if (temp->key < ptr->key && ptr->left == NULL)
            {
                ptr->left = temp;
                printf("Inserted on the left\n");
                break;
            }
            else if (temp->key < ptr->key)
            {
                ptr = ptr->left;
            }
            // khi toi cuoi cung ben phai
            else if (temp->key > ptr->key && ptr->right == NULL)
            {
                ptr->right = temp;
                printf("Inserted on the right\n");
                break;
            }
            else if (temp->key > ptr->key)
            {
                ptr = ptr->right;
            }
        }
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
Tree deleteNode_While(int x, Tree r)
{
    // base condition
    if (r == NULL)
        return r;
    // find x

    else if (x < r->key)
        r->left = deleteNode_While(x, r->left);
    else if (x > r->key)
        r->right = deleteNode_While(x, r->right);
    // matches
    else
    {
        // has only right child or is leaf
        if (r->left == NULL)
        {
            Tree temp = r->right;
            r == NULL;
            return temp;
        }
        // has only left child
        else if (r->right == NULL)
        {
            Tree temp = r->left;
            r == NULL;
            return temp;
        }
        // has two child
        else
        {
            // retrun smallest value on right sub tree
            Tree temp = minValue(r->right);
            // replace value;
            r->key = temp->key;
            // delete smallest value
            r->right = deleteNode_While(temp->key, r->right);
        }
    }

    return r;
}

void rightRotation(Tree *n1)
{
    //        n1                   n2
    //                           /    \
    //     n2                  n3      n1
    //                                /
    //  n3    NULL (sc)             NULL (sc)
    Tree n2 = (*n1)->left;
    Tree storageChild = n2->right; // store left child of n2
    // perform
    n2->right = (*n1);
    // sc less than n1
    (*n1)->left = storageChild; // link right child of n2 to n1
    (*n1) = n2;
    printf("right rotated ");
    // return (*n1);
}
void leftRotation(Tree *n1)
{
    //   n1                       n2
    //      \                   /    \
    //        n2               n1      rst
    //      /    \                \
    // NULL (sc)   rst             NULL (sc)

    Tree temp = (*n1);
    Tree n2 = temp->right;
    Tree storageChild = n2->left;
    // perform
    n2->left = (*n1);
    // sc is better than n1
    (*n1)->right = storageChild; // link right child of n2 to n1
    (*n1) = n2;
    printf("left rotated ");
}
void insertNodeAVL(int value, Tree *r)
{
    if ((*r == NULL))
    {
        (*r) = newNode(value);
        return;
    }
    else if (value < (*r)->key)
        insertNodeAVL(value, &((*r)->left));
    else if (value > (*r)->key)
        insertNodeAVL(value, &((*r)->right));
    else
    {
        printf("Duplicate value ");
        return;
    }
    // insertNode(value, r);

    int bf = getBalanceFactor((*r));
    //  left subtree - right subtree
    //  1 lệch trái
    // -1 lệch phải
    printf("bf: = %d ", bf);

    if ((bf > 1) && (value < (*r)->left->key))
    {
        rightRotation(r);
    }
    if ((bf < -1) && (value > (*r)->right->key))
    {
        leftRotation(r);
    }
    if ((bf > 1) && value > ((*r)->left->key))
    {
        //        n1  bf = 1 - - 1
        //      /    \ 
        //     n2
        //   /   \   
        //        n3 (new node)
        leftRotation(&((*r)->left));
        rightRotation(r);
    }
    if ((bf < -1) && value < ((*r)->right->key))
    {
        //       n1  bf = -1 -1
        //      /  \ 
        //           n2
        //          /  \ 
        //       n3 (new node)
        rightRotation(&(*r)->right);
        leftRotation(r);
    }
}
void deleteNodeAVL(int value, Tree *r)
{
    // deleteNode(value, r);
    if ((*r) == NULL)
        return;
    // find x
    if (value < (*r)->key)
        deleteNodeAVL(value, &((*r)->left));
    else if (value > (*r)->key)
        deleteNodeAVL(value, &((*r)->right));
    // matches
    else
    {
        // has only right child of is leaf
        if ((*r)->left == NULL)
        {
            Tree temp = (*r)->right;
            (*r) = temp;
            return;
        }
        // has only left child
        else if ((*r)->right == NULL)
        {
            Tree temp = (*r)->left;
            (*r) = temp;
            return;
        }
        else
        {
            // 1: tìm giá trị nhỏ nhất bên trái
            // 2: tìm giá trị lớn nhất bên phải
            Tree temp = minValue((*r)->right);
            // minValue (Tree r)
            (*r)->key = temp->key;
            deleteNode(temp->key, &((*r)->right));
            return;
        }
    }
    int bf = getBalanceFactor((*r));
    printf("bf: = %d ", bf);

    // right rotation
    if (bf == 2 && getBalanceFactor((*r)->left) >= 0)
    {
        rightRotation(r);
    }
    // left rotation
    if (bf == -2 && getBalanceFactor((*r)->right) <= 0)
    {
        leftRotation(r);
    }
    // left right rotation
    if (bf == 2 && getBalanceFactor((*r)->left) == -1)
    {
        leftRotation(&(*r)->left);
        rightRotation(r);
    }
    // right left rotation
    if (bf == 2 && getBalanceFactor((*r)->left) == 1)
    {
        rightRotation(&(*r)->right);
        leftRotation(r);
    }
}
int fodableHandle (Tree l, Tree r) {
    if (l == NULL && r == NULL) {
        return 1;
    }
    if (l == NULL || r == NULL) {
        return 0;
    }
    return fodableHandle(l -> left, r -> right) && fodableHandle(l -> right, r -> left);
}
int isFoldable (Tree r) {
    if (r == NULL) return 0;
    return fodableHandle (r -> left, r -> right);
}
int getLeaves (Tree r) {
    if (r == NULL) return 0;
    if (r -> left == NULL && r -> right == NULL) return 1;
    return getLeaves(r -> left) + getLeaves(r -> right);
}
int countingNode2Child (Tree r) {
    if (r == NULL) return 0;
        int couting = countingNode2Child(r -> left) + countingNode2Child(r -> right);
     
        if (r -> left != NULL && r -> right != NULL) couting ++;
    
    return couting;
}
int countingNode1Child (Tree r) {
    if (r == NULL) return 0;
        int counting = countingNode1Child(r -> left) + countingNode1Child(r -> right);
            
        if ((r -> left == NULL && r -> right != NULL) || (r -> right == NULL && r -> left != NULL)) {
                counting ++;
            
            // if (!(r -> left == NULL && r -> right == NULL)) {
            // }
        }
        
    
    return counting;
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
    // root = initTree();
    insertNodeAVL(33, &root);
    insertNodeAVL(22, &root);
    insertNodeAVL(77, &root);
    insertNodeAVL(66, &root);
    insertNodeAVL(25, &root);


    do
    {
        printf("\n");
        printf("1. InsertAVL       ");
        printf("2. Get Height       ");
        printf("3. Printf Tree\n");
        printf("4. DeleteNodeAVL       ");
        printf("5. DeleteNode_While     ");
        printf("6. Check foldable\n");
        printf("7. couting leaf node     ");
        printf("8. couting Node 2 Child     ");
        printf("10. couting Node 1 Child\n");

        printf("9. Clear screen     ");
        printf("0. Exit \n");
        printf("Chose operand to perform...");
        scanf("%d", &option);
        switch (option)
        {
            
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insertNodeAVL(value, &root);
            break;
        case 2:
            printf("\nHeight of tree: %d\n", height(root));
            break;
        case 3:
            print2D(root, 1);
            break;
        case 4:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            deleteNodeAVL(value, &root);
            break;
        case 5:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = deleteNode_While(value, root);
            break;
        case 6:
            printf("%d", isFoldable(root));
        break;
        case 7:
        printf("\nNumber of leaves node: %d\n", getLeaves(root));
            // printf("%d", isFoldable(root));
        break;
        case 8:
            printf("\nNumber of Nodes have 2 child: %d\n", countingNode2Child(root));
            // printf("%d", isFoldable(root));
        break;
        case 10:
            printf("\nNumber of Nodes have 1 child: %d\n", countingNode1Child(root));
            // printf("%d", isFoldable(root));
        break;
        case 9:
            system("clear");
            break;
        default:
            printf("Exit");
            break;
        }
    } while (option != 0);

    return 0;
}




