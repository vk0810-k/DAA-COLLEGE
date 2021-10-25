#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct node
{
    struct node *left;
    int data;
    struct node *right;
};

struct node *tree=NULL;

struct node* insertelement(struct node *tree,int n)
{
    struct node *newnode,*nodeptr,*parentptr;
    newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data=n;
    newnode->left=NULL;
    newnode->right=NULL;
    if(tree==NULL)
    {
        tree=newnode;
    }
    else
    {
        parentptr=NULL;
        nodeptr=tree;
        while(nodeptr!=NULL)
        {
        parentptr=nodeptr;
        if(n<nodeptr->data)
            nodeptr=nodeptr->left;
        else
            nodeptr = nodeptr->right;
        }
        if(n<parentptr->data)
            parentptr->left=newnode;
        else
            parentptr->right=newnode;
    }
    return tree;
}
int inorder(struct node *tree)
{
    while(tree!=NULL)
    {
        inorder(tree->left);
        printf("\t%d",tree->data);
        inorder(tree->right);
        return tree;
    }
}

int postorder(struct node *tree)
{
    while(tree!=NULL)
    {
        preorder(tree->left);
        preorder(tree->right);
        printf("\t%d",tree->data);
        return tree;
    }
}

int preorder(struct node *tree)
{
    while(tree!=NULL)
    {
        printf("\t%d",tree->data);
        preorder(tree->left);
        preorder(tree->right);
        return tree;
    }
}

int main()
{
    int n,ch;
    printf("\tBinary Search Tree Traversal\n");
    printf("\n\tMenu:\n");
    printf("1.Insert Elements\n2.In-Order\n3.Pre-Order\n4.Post-Order\n5.Exit");
    while(ch!=5)
    {
        printf("\n\nEnter your Choice :: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("\nEnter the Element :: ");
                    scanf("%d",&n);
                    tree=insertelement(tree,n);
                    break;

            case 2: printf("\tThe In-Order sequence for the given string is as follows::\n");
                    n=inorder(tree);
                    break;

            case 3: printf("\tThe Pre-Order sequence for the given string is as follows::\n");
                    n=preorder(tree);
                    break;

            case 4: printf("\tThe Post-Order sequence for the given string is as follows::\n");
                    n=postorder(tree);
                    break;

            case 5: printf("\tSure Boss Exiting!!\n\tGood Bye\n\n");
                    break;
        }
    }
    return 0;
}
