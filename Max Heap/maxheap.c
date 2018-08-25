#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node 
{
	int data;
	struct node *left;
	struct node *right;
	struct node *p;
}*Node;


typedef struct queue
{
	int r,f;
	Node a[100];
}Queue;

Queue create()
{
	Queue q;
	
	for(int i=0;i<100;i++)
		q.a[i] = NULL;
		
	q.r = -1;
	q.f = 0;
	
	return q;
}

void Enqueue(Node temp,Queue *q)
{
	q->a[++q->r] = temp;	
}

void Dequeue(Queue *q)
{
	q->a[q->f++];
}

Node getFront(Queue *q)
{
	return q->a[q->f];	
}

int isempty(Queue q)
{
	return q.f > q.r;
}

int hasBothChild(Node k)
{
	if(k->left!=NULL && k->right!=NULL)
		return 1;
	else
		return 0;
}

Node getNode(int data)
{
	Node nnode = NULL;
	nnode = (Node)malloc(sizeof(struct node));
	nnode->data = data;
	nnode->right = nnode->left = nnode->p = NULL;
	
	return nnode;
}


Node Heapify(Node temp)
{
	Node t = temp;
	int k;
	while(t->p!=NULL)
	{
		if(t->data > t->p->data)
		{
			k = t->data;
			t->data = t->p->data;
			t->p->data = k;
		}
		t = t->p;
	}
	
	return t;
}


Node insert(Node temp,Node root,Queue *q)
{
	
    if (!root)
    {
    	temp->p = NULL;
        root = temp;
        Enqueue(temp,q);

        return root;
    }
        
 
    else
    {
        Node front = getFront(q);

        if (!front->left)
        {
            temp->p = front;
            front->left = temp;
        }

        else if (!front->right)
        {
            temp->p = front;
            front->right = temp;
        }
 
        if (hasBothChild(front))
            Dequeue(q);
    }

    Enqueue(temp,q);
    root = Heapify(temp);
    
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

	fprintf (outFile, "digraph Heap {\n");
	
	preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}


FILE *outputFile;

void main(int argc,char *argv[])
{
	int num,i;
	FILE *pipe;
	Node root = NULL;
	Queue q;
	
	if(argc!=2)
	{
		printf("2 arguments in command line!!!!");
		exit(0);
	}

	num = atoi(argv[1]);
	q = create();
	
	outputFile = fopen ("heap.dot", "w");
	fclose (outputFile);
	
	srand(time(NULL)); 

	for(i=0;i<num;i++)
	{ 
		Node nnode = getNode(rand()%1000);
		root = insert(nnode,root,&q);
	}
	
	outputFile = fopen ("heap.dot", "a");
        if(outputFile != NULL) 
              dotDump (root,outputFile);
        fclose(outputFile);	inorder(root);
	
	pipe=popen("dot -Tps heap.dot -o heap.ps","w");
	pclose(pipe);	
	pipe=popen("evince heap.ps","r"); 
	pclose(pipe);
}












