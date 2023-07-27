#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char* data;
    struct node *left, *right;
} node;

node *newnode(char *word)
{
    node *n = malloc(sizeof(node));
    n->left = n->right = NULL;
    n->data = malloc(sizeof(word+1));
    strcpy(n->data, word);
    return n;
}

node* insert(node* node, char *word)
{
    if(node == NULL)
        return newnode(word);
    if(strcasecmp(word,node->data) < 0)
        node->left = insert(node->left,word);
    else if(strcasecmp(word,node->data) > 0)
        node->right = insert(node->right,word);
    return node;
}


node* search(node*root, char*key)
{
    if(root == NULL)
        return -1;
    else if(strcasecmp(root->data , key)==0)
        return 1;
    else if(strcasecmp(key, root->data)<0)
        return search(root->left, key);
    else if(strcasecmp(key, root->data)>0)
        return search(root->right, key);
}
int count(node* root)
{

    if(root == NULL)
        return 0;
    else
        return 1 + count(root->left) + count(root->right);

}

int max(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

int height(node* root)
{
    if(root == NULL)
        return -1;
    else
        return 1 + max(height(root->left),height(root->right));
}

node * findmin(node *root)
{
    if(root== NULL)
        return NULL;
    else if (root->left ==NULL)
        return root;
    else return findmin(root->left);
}

node * findmax(node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->right== NULL)
    return root;
    else return findmax(root->right);
}
node *nearest(node *root, char *word)
{
    node*  nearest;
    while(root != NULL)
    {
        nearest = root;
        if(strcasecmp(word,root->data) > 0)
            root=root->right;
        else if(strcasecmp(word,root->data) < 0)
            root=root->left;
    }
    return nearest;
}

node* successor(node* root, char *word)
{
    node* successor = newnode("Successor does not exist.");


    if(root==NULL)
        return NULL;
    else
        while(strcasecmp(word,root->data) != 0)
        {
            if(strcasecmp(word,root->data) > 0)
            {
                root=root->right;
            }
            else if (strcasecmp(word,root->data) < 0)
            {
                successor = root;
                root=root->left;
            }
        }
    if(root->right!=NULL)
        return findmin(root->right);
    else if(root->right==NULL)
        return successor;
}

node* predecessor(node* root, char *word)
{
    node* predecessor = newnode("Predecessor does not exist.");

    if(root==NULL)
        return NULL;
    else
        while(strcasecmp(word,root->data) != 0)
        {
            if(strcasecmp(word,root->data) > 0)
            {
                predecessor = root;
                root=root->right;
            }
            else if (strcasecmp(word,root->data) < 0)
            {

                root=root->left;
            }
        }
    if(root->left!=NULL)
        return findmax(root->left);
    else if(root->left==NULL)
        return predecessor;
}

void correction(node* dictionary, char *sentence)
{
    char* token = strtok(sentence, " ");
    while(token != NULL)
    {
        if(search(dictionary, token) == 1)
             printf("%s - Correct\n",token);
        else
        {
            printf("%s - Incorrect, Suggestions : %s %s %s\n",token,
                                                              nearest(dictionary,token)->data,
                                                              successor(dictionary,nearest(dictionary,token)->data)->data,
                                                              predecessor(dictionary,nearest(dictionary,token)->data)->data);
        }
        token=strtok(NULL," ");
    }
}

int main()
{
    int flag =0;
    node*dictionary = NULL;
    FILE*f=fopen("EN-US-Dictionary.txt","r");
    if (f != NULL)
    {
    char x[30];
    while(!feof(f))
    {
        fscanf(f,"%s",x);
        dictionary=insert(dictionary,x);
    }
    flag = 1;
    }
    if(flag)
    {
      printf("Dictionary Loaded Successfully...!\n");
      printf("..................................\n");
      printf("Size = %d\n",count(dictionary));
      printf("..................................\n");
      printf("Height = %d\n",height(dictionary));
      printf("Enter a sentence :\n");
    char *sentence = malloc(150);
    gets(sentence);
    correction(dictionary,sentence);
    }else printf("Failed Loading file.");
    return 0;
}
