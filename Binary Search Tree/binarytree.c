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


Node insert(Node root,Node nnode)
{
	if(root == NULL)
	return nnode;

	if(root->data > nnode->data)
		root->left = insert(root->left,nnode);
	else 	
		root->right = insert(root->right,nnode);
		
	return root;
}

Node verify(Node root)
{
	Node l,r;
	if(root->right == NULL || root->left == NULL)
		return root;

	l = verify(root->left);
	r = verify(root->right);

	if(l->data > r->data)
	{
		printf("FALSE\n");
		exit(0);
	}
}

void inorder(Node root)
{
	if(root == NULL)
		return;

	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);
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
	verify(root);
	printf("TRUE\n");
	
	pipe=popen("dot -Tps bst.dot -o bst.ps","w");
	pclose(pipe);	
	pipe=popen("evince bst.ps","r"); 
	pclose(pipe);
}
