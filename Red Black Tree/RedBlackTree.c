#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *p;
	char color;
}*Node;

Node GetNode(int);


Node T;

void Tnill()
{
	T = GetNode(0);
	T->color = 'b';
	
}
Node GetNode(int data)
{
	Node nnode = (Node)malloc(sizeof(struct node));
	nnode->data = data;
	nnode->right = nnode->left = nnode->p = T;
	nnode->color = 'r';
	return nnode;
}	
Node RightRotate(Node root,Node x)
{
	Node y = T;
	y = x->left;
	x->left = y->right;

	if(y->right!=T)
		y->right->p = x;
	y->p = x->p;

	if(x->p == T)
		root = y;
	else if(x == x->p->right)
		x->p->right = y;
	else x->p->left = y;
	y->right = x;
	x->p = y;
	
	return root;

}

Node LeftRotate(Node root,Node x)
{
	Node y = T;

	y = x->right;
	x->right = y->left;

	if(y->left!=T)
		y->left->p = x;
	y->p = x->p;

	if(x->p == T)
		root = y;
	else if(x == x->p->left)
		x->p->left = y;
	else x->p->right = y;
	y->left = x;
	x->p = y;
	
	return root;
}


Node insert(Node root,Node nnode)
{
	if(root == T)
		return nnode;

	if(root->data > nnode->data)
	{
		root->left = insert(root->left,nnode);
		root->left->p = root;	
	}

	else 	
		if(root->data < nnode->data)
	 	{	
			root->right = insert(root->right,nnode);
			root->right->p = root;		
		}
	return root;
}


void inorder(Node root)
{
	if(root == T)
		return;

	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);
}


Node InsertFixup(Node root,Node z)
{
	Node y = T;
	while(z->p->color == 'r')
	{
		if(z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if(y != T && y->color == 'r')
			{
				z->p->color = 'b';
				y->color = 'b';
				z->p->p->color = 'r';
				z = z->p->p;
			}
			else if(z == z->p->right)
			{
				z = z->p;
				root = LeftRotate(root,z);
				z->p->color = 'b';
				z->p->p->color = 'r';
				root = RightRotate(root,z->p->p);
			}
			else if(z == z->p->left)
			{
				z->p->color = 'b';
				z->p->p->color = 'r';
				root = RightRotate(root,z->p->p);
			}
		}
		else
		{
			y = z->p->p->left;
			if(y != T && y->color == 'r')
			{
				z->p->color = 'b';
				y->color = 'b';
				z->p->p->color = 'r';
				z = z->p->p;
			}
			else if(z == z->p->left)
			{
				z = z->p;
				root = RightRotate(root,z);
				z->p->color = 'b';
				z->p->p->color = 'r';
				root = LeftRotate(root,z->p->p);
			}
			else if(z == z->p->right)
			{
				z->p->color = 'b';
				z->p->p->color = 'r';
				root = LeftRotate(root,z->p->p);
			}
		}
	}
	
	root->color = 'b';
	return root;
}

void preorderDotDump (Node root, FILE* outputFile)
{
	if (root != T) 
	{
		if(root->color == 'r')
			fprintf (outputFile, "%d [label=%d,color=red];\n",root->data, root->data);
		else
			fprintf (outputFile, "%d [label=%d,color=black];\n",root->data, root->data);
		
		if (root->left != T) 
		         fprintf (outputFile, "%d -> %d ;\n", root->data, (root->left->data));
		
        	if (root->right != T)
            	   fprintf (outputFile, "%d -> %d;\n", root->data, root->right->data);
            		
        	preorderDotDump (root->right, outputFile);
        	preorderDotDump (root->left, outputFile);
    	}
}

void dotDump(Node root, FILE *outFile)
{

	fprintf (outFile, "digraph RBT {\n");
	
	preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}


FILE *outputFile;

void main(int argc,char *argv[])
{
	int n,i,key;
	FILE *pipe;
	
	Tnill();
	
	if(argc!=2)
	{
		printf("2 arguments in command line!!!!");
		exit(0);
	}
	outputFile = fopen ("rbt.dot", "w");
	fclose (outputFile);
	n = atoi(argv[1]);
	Node root = T;

	for(i=0;i<n;i++)
	{
		Node nnode = GetNode(rand()%1000);
		root = insert(root,nnode);
		root = InsertFixup(root,nnode);
		
		outputFile = fopen ("rbt.dot", "a");
		if(outputFile != NULL) 
			dotDump (root,outputFile);
			
		fclose(outputFile);
	}

	
		
	pipe=popen("dot -Tps rbt.dot -o rbt.ps","w");
	pclose(pipe);	
	pipe=popen("evince rbt.ps","r"); 
	pclose(pipe);
}
