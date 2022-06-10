#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct treeNode 
{
    int data;
    struct treeNode *leftPtr; 
    struct treeNode *rightPtr; 
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

int numberOfElements = 9; // it is 9 beacuse of index. 0 1 . . . . 9

//prototypes
TreeNodePtr insertNode(TreeNodePtr treePtr, int value);
void preorder (TreeNodePtr treePtr);
void inorder (TreeNodePtr treePtr);
void postorder (TreeNodePtr treePtr);

TreeNodePtr insertNode(TreeNodePtr treePtr, int value)
{
    if(treePtr == NULL) {//if treePtr is null that means value is our first element.
	
        TreeNodePtr newNode = (TreeNodePtr)malloc(sizeof(TreeNode)); //creating a newNode and assign value as its data.
                                                                    //and make left and right null so our tree is ready for to load.

        newNode->data = value;

        newNode->leftPtr = NULL;
        newNode->rightPtr = NULL;
        return newNode;
	  
	} 
  else {
		TreeNodePtr temp;
		
		if(value <= treePtr->data) //if our treePtr's data is bigger than value we go left subtree and we add it there.
        {
            temp = insertNode(treePtr->leftPtr, value);
            treePtr->leftPtr = temp;
		} 
        else //if our treePtr's data is not bigger than value than we go right subtree and we add it there.
        {
            temp = insertNode(treePtr->rightPtr, value);
            treePtr->rightPtr = temp;
		}
	
		return treePtr;
	}
}

void preorder (TreeNodePtr treePtr)
{
    if(treePtr == NULL) 
    {
        return; //if treePtr is null then it has finished so finish the function
    }

    //check root then left subtree and left subtree
    printf("%d ",treePtr->data);

    preorder(treePtr->leftPtr);

    preorder(treePtr->rightPtr);
}

void inorder (TreeNodePtr treePtr)
{
    if(treePtr == NULL) 
    {
        return;//if treePtr is null then it has finished so finish the function
    }

    //check left subtree then root and right subtree
    inorder(treePtr->leftPtr);

    printf("%d ",treePtr->data);

    inorder(treePtr->rightPtr);
}

void postorder (TreeNodePtr treePtr)
{
    if(treePtr == NULL) 
    {
        return;//if treePtr is null then it has finished so finish the function
    }

    //check left subtree then right subtree and root
    postorder(treePtr->leftPtr);

    postorder(treePtr->rightPtr);

    printf("%d ",treePtr->data);
}

int main()
{
    TreeNodePtr root = NULL;

    int elements[10];
    srand(time(NULL));
    int i = 0;

    int arrLen = sizeof(elements) / sizeof(elements[0]);
    int isContain = 0;


    //taking element in binarytree 
    while(numberOfElements >= i)
    {
        int value = rand() % 25 + 1; //creating random numbers between 1-25

        //check for same numbers.
        for (int j = 0; j < arrLen; j++) {
            if (elements[j] == value) {
                isContain = 1;
                break;
            }
        }
        //if there is no same numbers then we can add it 
        if(isContain == 0)
        {
            elements[i] = value;//elements array is created for first look of our numbers.
            root = insertNode(root, value);
            i++;
        }
        isContain = 0;
    }

    i = 0;
    printf("\nThe numbers being placed in the tree are:\n");
    while(numberOfElements >= i)
    {
        printf("%d ",elements[i]);
        i++;
    }
    printf("\n");

    printf("\nThe preorder traversal is:\n");
    preorder(root); //preorder version
    printf("\n");

    printf("\nThe inorder traversal is:\n");
    inorder(root); //inorder version
    printf("\n");

    printf("\nThe postorder traversal is:\n");
    postorder(root); //postorder version
    printf("\n\n");

    return 0;
}
