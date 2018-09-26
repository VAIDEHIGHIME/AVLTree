#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define INT_MAX 10000
typedef struct nodeTag
{
    char student_name[MAX], subject_code[MAX], department_name[MAX];
    int roll_number, semester_number,balance,isVisited;
    float marks;
    struct nodeTag * left,* right;
}node;
node * minValueNode(node * );
node * BSTDelete(node * ,int ,char *);
node * createNode();
void visitNode(node *);
void preOrder(node *);
int max(int , int );
void inOrder(node * );
void setBalance(node *);
node * avlInsertRecord(node * ,node *);
node * find_prev( node * , node *);
node * checkBalance(node *, node *);
node * rightRotate(node *);
node * leftRotate(node *);
void get_max_marks_print(node * ,float );
node * InsertBST(node *,node *);
//node * deleteRecord(node *,int ,char *);
//void deleteNode(node ** );
node * search(node *,int ,char *);
int getNumRecords(node *  root);
int height(node *);
void RangeSearch(node *,int ,int);
void printDatabase(node *);
int getMax(node * , char * );
void getListofFailures(node *,char *,float );
int main()
{
    node * root , * newNode, * deletedNode,* searchedNode;
    int option,rollno, records, heightTree,k1,k2, continueOperation=0;
    char subject[MAX];
    float max_marks_subject,passing_marks;
    root=NULL;
    do
    {
            printf("1:Insertion\n");
            printf("2:deletion\n");
            printf("3:search\n");
            printf("4:no of records\n");
            printf("5:height of the tree\n");
            printf("6:range search\n");
            printf("7:print database\n");
            printf("8:max marks in subject\n");
            printf("9:list of failures in a subject\n");
            printf("your choice:");
            scanf("%d",&option);
            switch(option)
            {

                case 1:
                    {
                         newNode=createNode();
                         root=avlInsertRecord(root,newNode);
                         preOrder(root);
                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;
                    }

               case 2:
                    {
                         printf("enter roll no:");
                         scanf("%d",&rollno);
                         printf("enter subject:");
                         scanf("%s",subject);
                         deletedNode=BSTDelete(root,rollno,subject);
                         visitNode(deletedNode);//
                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;
                    }
                case 3:
                    {
                        printf("\n enter roll no:");
                        scanf("%d",&rollno);
                        printf("\n enter subject code:");
                        scanf("%s",subject);
                        searchedNode= search(root,rollno,subject);
                        if(searchedNode!=NULL)
                        {
                            visitNode(searchedNode);
                        }
                        else
                        {
                                printf("record not found\n");
                        }

                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;

                    }
                case 4:
                    {
                            records=getNumRecords(root);
                            printf("no of records in the database:%d\n",records);
                             printf("1:continue | 0:exit:");
                            scanf("%d",&continueOperation);
                            break;

                    }
                case 5:
                    {
                        heightTree=height(root);
                        printf("height of the tree:%d\n",heightTree);
                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;
                    }
                case 6:
                    {
                        printf("\n lower bound :");
                        scanf("%d",&k1);
                        printf("\n upper bound:");
                        scanf("%d",&k2);
                        RangeSearch(root,k1 ,k2);
                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;
                    }
                case 7:
                    {
                        inOrder(root);
                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;
                    }
                case 8:
                    {
                        printf("\n enter the subject code:");
                        scanf("%s",subject);
                        max_marks_subject=getMax(root,subject);
                        get_max_marks_print(root,max_marks_subject);
                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;

                    }
                case 9:
                    {
                        printf("enter the subject code:");
                        scanf("%s",subject);
                        printf("enter the passing marks:");
                        scanf("%f",&passing_marks);
                        getListofFailures(root,subject,passing_marks);
                         printf("1:continue | 0:exit:");
                         scanf("%d",&continueOperation);
                         break;
                    }
            }
    }
    while(continueOperation==1);
    return(0);
}

node * InsertBST(node * root, node * newNode)
{
    if(newNode!=NULL)
    {
            if(root==NULL)
            {
                return(newNode);
            }
            else
            {
                if(root->roll_number < newNode->roll_number)
                {
                    root->right=InsertBST(root->right,newNode);
                }
                else if(root->roll_number > newNode->roll_number)
                {
                    root->left=InsertBST(root->left,newNode);
                }
                else
                {
                    if(strcmp(newNode->subject_code,root->subject_code)>0)
                    {
                        root->right=InsertBST(root->right,newNode);
                    }
                    else if(strcmp(newNode->subject_code,root->subject_code)<0)
                    {
                        root->left=InsertBST(root->left,newNode);
                    }
                    else
                    {
                        strcpy(root->student_name,newNode->student_name);
                        root->roll_number=newNode->roll_number;
                        root->semester_number=newNode->semester_number;
                        strcpy(root->department_name,newNode->department_name);
                        strcpy(root->subject_code,newNode->subject_code);
                        root->marks=newNode->marks;
                    }
                }
                return(root);
            }

    }
    else
    {
        printf("no space\n");
        return(newNode);
    }

}
void visitNode(node *root)
{
   if(root!=NULL)
   {
        printf("****************************************************************************************************\n");
        printf("Name:%s\n",root->student_name);
        printf("Roll no:%d\n",root->roll_number);
      	printf("Department name:%s\n",root->department_name);
        printf("semester no:%d\n",root->semester_number);
        printf("subject code:%s\n",root->subject_code);
        printf("marks obtained:%f\n",root->marks);
        printf("****************************************************************************************************\n");
    }
}
void preOrder(node * root)
{
    if(root != NULL)
    {
        visitNode(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}
node * createNode()
{
	node * new_node;
	int roll,semester;
	float marks;
	char subject[50],name[50],department[50];
	new_node=(node*)malloc(sizeof(node));
	if(new_node!=NULL)
	{
	    printf("Enter Roll_Number: ");
		scanf("%d",&roll);
		printf("Enter Subject Code: ");
		scanf("%s",subject);
		printf("Enter Marks: ");
		scanf("%f",&marks);
		printf("Enter Student Name: ");
		scanf("%s",name);
        printf("Enter Department Name: ");
		scanf("%s",department);
		printf("Enter Semester Number: ");
		scanf("%d",&semester);
		new_node->roll_number=roll;
		strcpy(new_node->student_name,name);
		strcpy(new_node->subject_code,subject);
		strcpy(new_node->department_name,department);
		new_node->semester_number=semester;
		new_node->marks=marks;
		new_node->balance=3;
		new_node->isVisited=0;
		new_node->left=NULL;
		new_node->right=NULL;
	}
    else
    {
             printf("no space\n");

    }
	return(new_node);
}
int getNumRecords(node * root)
{
	if(root==NULL)
	{
		return(0);
	}
	else
	{
		return(1+getNumRecords(root->left)+getNumRecords(root->right));
	}
}
int height(node * root)
{
	int heightTree;
	if(root==NULL)
	{
		return(-1);
	}
	else if(root->right==NULL && root->left==NULL)
	{
		return(0);
	}
	else
	{
		heightTree=1+max(height(root->right),height(root->left));
		return(heightTree);
	}

}
int max(int a, int b)
{
    if(a>b)
    {
        return(a);
    }
    else
    {
        return(b);
    }
}
node * search(node * root,int roll_number,char * subject)
{
    node * retRoot;
    if(root==NULL)
    {
        retRoot=NULL;
    }
    else
    {
        if(roll_number<root->roll_number)
        {
            retRoot=search(root->left,roll_number,subject);
        }
        else if(roll_number>root->roll_number)
        {
            retRoot=search(root->right,roll_number,subject);
        }
        else
        {
            if(strcmp(subject,root->subject_code)<0)
            {
                    retRoot=search(root->left,roll_number,subject);
            }
            else if(strcmp(subject,root->subject_code)>0)
            {
                    retRoot=search(root->right,roll_number,subject);
            }
            else
            {
                    retRoot=root;
            }
        }
    }
    return(retRoot);
}
void RangeSearch(node * root, int start, int end)
{
	if(root!=NULL)
	{
		if(root->roll_number >=start&&root->roll_number<=end)
		{
			visitNode(root);
			RangeSearch(root->left,start,end);
			RangeSearch(root->right,start,end);
		}
       else if(root->roll_number<start&&root->roll_number<end)
		{
			RangeSearch(root->right,start,end);
		}
       else if(root->roll_number>start&&root->roll_number>end)
		{
			RangeSearch(root->left,start,end);
		}
    }
}
int getMax(node * root, char * subject)
{
    int root_marks,right_tree_marks,left_tree_marks;
    if(root==NULL)
    {
        return(INT_MAX);
    }
    else
    {
        if(strcmp(subject,root->subject_code)==0)
        {
            root_marks=root->marks;
            left_tree_marks=getMax(root->left,subject);
            right_tree_marks=getMax(root->right,subject);
            if(left_tree_marks>root_marks)
            {
                return(left_tree_marks);
            }
            else if (right_tree_marks>root_marks)
            {
                return(right_tree_marks);
            }
            else
            {
                return(root_marks);
            }
        }
    }
}
void get_max_marks_print(node * root,float max_marks)
{
    if(root!=NULL)
    {
        if(root->marks==max_marks)
        {
            printf("Name:%s\n",root->student_name);
            printf("Roll no:%d\n",root->roll_number);
            printf("Department name:%s\n",root->department_name);
            printf("semester no:%d\n",root->semester_number);
            printf("subject code:%s\n",root->subject_code);
            printf("marks obtained:%f\n",root->marks);
        }
        get_max_marks_print(root->left,max_marks);
        get_max_marks_print(root->right,max_marks);
    }
}
void getListofFailures(node * root,char * subject,float passing_marks)
{
    if(root!=NULL)
    {
        if(strcmp(subject,root->subject_code)==0 && root->marks<passing_marks)
        {
            printf("Name:%s\n",root->student_name);
            printf("Roll no:%d\n",root->roll_number);
            printf("Department name:%s\n",root->department_name);
            printf("semester no:%d\n",root->semester_number);
            printf("subject code:%s\n",root->subject_code);
            printf("marks obtained:%f\n",root->marks);
        }
        getListofFailures(root->right,subject,passing_marks);
        getListofFailures(root->left,subject,passing_marks);
    }

}
void inOrder(node * root)
{
    if(root!=NULL)
    {
        inOrder(root->left);
        visitNode(root);
        inOrder(root->right);
    }
}
node * avlInsertRecord(node * root,node * newNode)
{
    node * isBalancedNode,* justBstInsert,* balanced,* prev,* semirotate;
    justBstInsert=InsertBST(root,newNode);
    setBalance(justBstInsert);
    isBalancedNode=checkBalance(justBstInsert,NULL);
    if(isBalancedNode==NULL)
    {
            printf("BST INSERTION DONE\n");
            return(justBstInsert);
    }
    else
    {
        prev=find_prev(justBstInsert,isBalancedNode);
        visitNode(prev);
        if(isBalancedNode->balance==-2 && isBalancedNode->right->balance==-1)
        {
            printf("right right problem\n");
            balanced=leftRotate(isBalancedNode);
            if(prev==NULL)
            {
                justBstInsert=balanced;
            }
            if(balanced->roll_number < prev->roll_number)
            {
                prev->left=balanced;
            }
            else
            {
                prev->right=balanced;
            }
        }
        if(isBalancedNode->balance==2 && isBalancedNode->left->balance==1)
        {

            printf("left left problem\n");
            balanced=rightRotate(isBalancedNode);
            if(prev==NULL)
            {
                justBstInsert=balanced;
            }
            if(balanced->roll_number <  prev->roll_number)
            {
                prev->left=balanced;
            }
            else
            {
                prev->right=balanced;
            }
        }

        if(isBalancedNode->balance==-2 && isBalancedNode->right->balance==1)
        {
            printf("left right  problem\n");
            semirotate=rightRotate(isBalancedNode->right);
            isBalancedNode->right=semirotate;
            balanced=leftRotate(isBalancedNode);
            if(prev==NULL)
            {
                justBstInsert=balanced;
            }

            if(balanced->roll_number <  prev->roll_number)
            {
                prev->left=balanced;
            }
            else
            {
                prev->right=balanced;
            }

        }
        if(isBalancedNode->balance==2 && isBalancedNode->left->balance==-1)
        {
            printf(" right left problem\n");
            semirotate=leftRotate(isBalancedNode->left);
            isBalancedNode->left=semirotate;
            balanced=rightRotate(isBalancedNode);
            if(prev==NULL)
            {
                justBstInsert=balanced;
            }
            if(balanced->roll_number <  prev->roll_number)
            {
                prev->left=balanced;
            }
            else
            {
                prev->right=balanced;
            }
        }
        return(justBstInsert);
    }
}
node * find_prev(node * root, node *unbalanced)
{
    node * find_ret;

	if(root!=NULL)
	{
	    if(root==unbalanced)
        {
            printf("this is the root\n");
            visitNode(root);
            printf("this is the unbalanced\n");
            visitNode(unbalanced);
            find_ret=NULL;
        }
        else
        {
             printf("finding prev\n");
            if(root->left==unbalanced||root->right==unbalanced)
            {
                find_ret=root;
                printf("this is the prev node\n");
                visitNode(find_ret);
            }
            find_ret=find_prev(root->left,unbalanced);
            find_ret=find_prev(root->right,unbalanced);

        }

	}
	return(find_ret);
}
void setBalance(node * root)
{

    if(root!=NULL)
	{
	    printf("setting balance\n");
		root->balance=height(root->left)-height(root->right);
		setBalance(root->left);
		setBalance(root->right);
	}
}
node * checkBalance(node * root, node * ret_val)
{

    if(root!=NULL)
	{
	    printf("checking for the not balaned node\n");
		if(root->balance==2||root->balance==-2)
		{
			ret_val=root;
		}
		ret_val=checkBalance(root->left,ret_val);
		ret_val=checkBalance(root->right,ret_val);
	}
	return(ret_val);
}
node * rightRotate(node * unbalanced)
{
   /* printf("rotating right\n");
    node * leftUnbalanced,* leftUnbalancedRight;
    leftUnbalanced=unbalanced->left;
    leftUnbalancedRight=leftUnbalanced->right;
    leftUnbalanced->right=unbalanced;
    unbalanced->left=leftUnbalancedRight;
    unbalanced->balance=height(unbalanced->left)-height(unbalanced->right);
    leftUnbalanced->balance=height(leftUnbalanced->left)-height(leftUnbalanced->right);
    visitNode(leftUnbalanced);
    return(leftUnbalanced);*/
    node * temp=NULL;
    if(unbalanced==NULL)
    {
        printf("cannot rotate\n");
    }
    else if (unbalanced->left==NULL)
    {
        printf("cannot rotate there is no left\n");
    }
    else
    {
        temp=unbalanced->left;
        unbalanced->left=temp->right;
        temp->right=unbalanced;
    }
    return(temp);
   /* node *prev,*ptr,*intr_ret,*store,*ret;
	store=root;
	prev=root;
	ptr=root->left;
	prev->left=NULL;
	intr_ret=leftRotate(ptr);
	prev->left=intr_ret;
	ret=rightRotate(root);
	return(ret);*/

}
node * leftRotate(node * unbalanced)
{
    /*printf("rotating left\n");
    node * rightUnbalanced, * rightUnbalancedLeft;
    rightUnbalanced=unbalanced->right;
    rightUnbalancedLeft=rightUnbalanced->left;
    rightUnbalanced->left=unbalanced;
    unbalanced->right=rightUnbalancedLeft;
    unbalanced->balance=height(unbalanced->left)-height(unbalanced->right);
    rightUnbalanced->balance=height(rightUnbalanced->left)-height(rightUnbalanced->right);
    return(rightUnbalanced);*/
    node * temp=NULL;
    if(unbalanced==NULL)
    {
        printf("cannot rotate\n");
    }
    else if (unbalanced->right==NULL)
    {
        printf("cannot rotate there is no left\n");
    }
    else
    {
        temp=unbalanced->right;
        unbalanced->right=temp->left;
        temp->left=unbalanced;
    }
    return(temp);
}
/*node * deleteRecord(node * root,int roll_number,char * subject)
{
    printf("entry in the delete record\n");
    node * storeRoot,* prev;
    prev=NULL;
    storeRoot=root;
    while(storeRoot!=NULL && storeRoot->roll_number!=roll_number && strcmp(storeRoot->subject_code,subject)!=0)
    {
        if(storeRoot->roll_number< roll_number && strcmp(storeRoot->subject_code,subject)<0)
        {
            prev=storeRoot;
            storeRoot=storeRoot->right;
        }
        else
        {
            prev=storeRoot;
            storeRoot=storeRoot->left;
        }
    }
    if(storeRoot!=NULL)
    {
        if(prev!=NULL)
        {
            if(prev->left=storeRoot)
            {
                deleteNode(&(prev->left));
            }
            else if (prev->right=storeRoot)
            {
            deleteNode(&(prev->right));
            }
        }
        else
        {

        }
    }
    return(root);
}
void deleteNode(node **root)
{
    printf("entry in delete node\n");
    node * q,* r;
    if((* root)==NULL)
    {
        printf("error\n");
    }
    else if((*root)->right==NULL)
    {
        (*root)=(*root)->left;
    }
    else if((*root)->left==NULL)
    {
        (*root)=(*root)->right;
    }
    else
    {
        for(q=(*root)->left;q->right!=NULL; )
        {
            q=q->right;
        }
        q->right=(*root)->right;
        q=(*root);
        (*root)=(*root)->left;
        free(q);
        printf("node deleted\n");
    }
}*/
node * BSTDelete(node * root,int roll_no,char * sub)
{
    node * temp;
    if(root==NULL)
    {
        printf("empty database\n");
    }
    else if(roll_no < root->roll_number)
    {
        root->left=BSTDelete(root->left,roll_no,sub);
    }
    else if(roll_no > root->roll_number)
    {
        root->right=BSTDelete(root->left,roll_no,sub);
    }
    else
    {
        if(strcmp(sub,root->subject_code)<0)
        {
                root->left=BSTDelete(root->left,roll_no,sub);
        }
        else if(strcmp(sub,root->subject_code)>0)
        {
                root->right=BSTDelete(root->left,roll_no,sub);
        }
        else
        {
                if(root->left == NULL)
                {
                        temp=root->right;
                        free(root);
                        return(temp);
                }
                else if(root->right ==NULL)
                {
                    temp=root->left;
                    free(root);
                    return(temp);
                }
                else
                {
                    temp=minValueNode(root->right);
                    root->roll_number=temp->roll_number;
                    strcpy(root->student_name,temp->roll_number);
                    strcpy(root->subject_code,temp->subject_code);
                    strcpy(root->department_name,temp->department_name);
                    root->semester_number=temp->semester_number;
                    root->marks=temp->marks;
                    root->right=BSTDelete(root->right,roll_no,sub);

                }
        }
    }
    return(root);
}
node * minValueNode(node * root)
{
    node * current;
    current=root;
    while(current->left!=NULL)
    {
        current=current->left;
    }
    return(current);
}
