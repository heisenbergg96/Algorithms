#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	int height;
}*Node;

Node GetNode(int data)
{
	Node nnode = (Node)malloc(sizeof(struct node));
	nnode->data = data;
	nnode->right = NULL;
	nnode->right = NULL;
	nnode->height = 0;

	return nnode;
}

Node RotateRight(Node r)
{
	Node p = NULL;

	p = r->right;
	r->right = p->left;
	p->left = r;
	r = p;

	return r;
}

Node RotateLeft(Node r)
{
	Node p = NULL;

	p = r->left;
	r->left = p->right;
	p->right = r;
	r = p;

	return r;
}

Node DoubleRightRotate(Node r)
{
	r->right = RotateLeft(r->right);
	r = RotateRight(r);

	return r;
}

Node DoubleLeftRotate(Node r)
{
	r->left = RotateRight(r->left);
	r = RotateLeft(r);
}

int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

int Height(Node r)
{
	if(r == NULL)
		return -1;
		
	return max(Height(r->right),Height(r->left))+1;
}

Node insert(Node root,Node nnode)
{
	if(root == NULL)
	return nnode;

	if(root->data > nnode->data)
	{
		root->left = insert(root->left,nnode);
		if(Height(root->left) - Height(root->right)==2)
		{
			if(root->left->data > nnode->data)
				root = RotateLeft(root);
			else
				root = DoubleLeftRotate(root);
		}
	}

	else 	
		if(root->data < nnode->data)
	 	{	
			root->right = insert(root->right,nnode);
			if(Height(root->right) - Height(root->left) == 2)
			{
				if(root->right->data < nnode->data)
					root = RotateRight(root);
				else
					root = DoubleRightRotate(root);
			}
		}

	root->height = Height(root);
	return root;
}

Node inorderSuccessor(Node root)
{
	if(root->right == NULL)
		return root;

	inorderSuccessor(root->left);
}

Node delete(Node root,int key)
{
	if(root == NULL)
	{
		printf("key not found:");
		return NULL;
	}

	if(root->data > key)
		root->left = delete(root->left,key);
	else
	if(root->data < key)
		root->right = delete(root->right,key);
	else
	{
		if(root->right == NULL)
		{
			Node temp = root->left;
			free(root);
			return temp;
		}

		else if(root->left == NULL)
		{
			Node temp = root->right;
			free(root);
			return temp;
		}

		Node temp = inorderSuccessor(root->right);
		root->data = temp->data;
		root->right = delete(root->right,root->data);
	}

	return root;
}

void inorder(Node root)
{
	if(root == NULL)
		return;

	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);
}

void postorder(Node root)
{
	if(root == NULL)
		return;

	postorder(root->left);
	postorder(root->right);
	printf("%d ",root->data);
}

void preorder(Node root)
{
	if(root == NULL)
		return;
	 	
	printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);
}



void preorderDotDump (Node root, FILE* outputFile)
{
	if (root != NULL) 
	{
		fprintf (outputFile, "%d [label=%d,color=black];\n",root->data, root->data);
		
		if (root->left != NULL) 
		         fprintf (outputFile, "%d -> %d ;\n", root->data, (root->left)->data);
		
        	if (root->right != NULL)
            	   fprintf (outputFile, "%d -> %d;\n", root->data, root->right->data);
            		
        	preorderDotDump (root->right, outputFile);
        	preorderDotDump (root->left, outputFile);
    	}
}

void dotDump(Node root, FILE *outFile)
{

	fprintf (outFile, "digraph BST {\n");
	
	preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}


FILE *outputFile;

void main(int argc,char *argv[])
{
	int n,i,key;
	FILE *pipe;

	if(argc!=2)
	{
		printf("2 arguments in command line!!!!");
		exit(0);
	}
	outputFile = fopen ("bst.dot", "w");
	fclose (outputFile);
	n = atoi(argv[1]);
	Node root = NULL;

	for(i=0;i<n;i++)
	{
		Node nnode = GetNode(rand()%1000);
		root = insert(root,nnode);
		
		outputFile = fopen ("bst.dot", "a");
		if(outputFile != NULL) 
			dotDump (root,outputFile);
			
		fclose(outputFile);
	}

	inorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	preorder(root);
	
		
		
	pipe=popen("dot -Tps bst.dot -o bst.ps","w");
	pclose(pipe);	
	pipe=popen("evince bst.ps","r"); 
	pclose(pipe);
}
