//Databse Using b tree
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 4 
#define MIN 2 

typedef enum{FALSE,TRUE} Boolean;

typedef struct accomodation
{
	char firstname[50];
	char lastname[50];
	char accommodation_type[20];
	int idtype;
	struct idnum
	{
		char aadhaar[15];
		char passport[15];
		char empcode[15];
	}id;
	char address[100];
}Employee_record;

typedef struct node_tag {
    int count;
    Employee_record value[MAX];
    struct node_tag *branch[MAX+ 1];
} Node_type; 

typedef struct index_tree
{
    int index_count;
    Employee_record *index_ptr[MAX];
    struct index_tree *index_branch[MAX + 1];
}index;


void assign_null(Employee_record* nptr)
{
	nptr->firstname[0]='\0';
	nptr->lastname[0]='\0';
	nptr->accommodation_type[0]='\0';
	nptr->id.aadhaar[0]='\0';
	nptr->id.passport[0]='\0';
	nptr->id.empcode[0]='\0';
	nptr->address[0]='\0';
}

Employee_record* create_record()
{
    // creating record in heap
    Employee_record *nptr=(Employee_record*)malloc(sizeof(Employee_record));
    if(nptr!=NULL)
    {
        // initiating all id's to NULL
        nptr->id.aadhaar[0] = '\0' ;
        nptr->id.empcode[0] = '\0' ;
        nptr->id.passport[0] = '\0' ;

        printf("Enter data:");
	    scanf(" %s",nptr->firstname) ; // firstname

	    scanf(" %s",nptr->lastname) ; // last name

	    scanf(" %s",nptr->accommodation_type) ; // accomodation type

	    // update_count(nptr,1);
	    scanf("%d",&nptr->idtype);

	    if(nptr->idtype==0)
	    {
	    	scanf(" %s ",&nptr->id.aadhaar);
	    }
	    else if(nptr->idtype==1)
	    {
	    	scanf(" %s ",&nptr->id.passport);
	    }
	    else // if user enters other than 0 and 1 to avoid invalid entries
	    {
	    	scanf(" %s ",&nptr->id.empcode);
	    }
	   fgets(nptr->address,100,stdin);
    }
    return nptr;
}

index* create_index()
{
	index *nptr = (index*)malloc(sizeof(index));
	nptr->index_count = 0;
	int i;
	for(i=0;i<MAX;i++)
	{
		nptr->index_ptr[i] = NULL;
		nptr->index_branch[i] = NULL;
	}
	nptr->index_branch[i] = NULL;
	return nptr;
}

Node_type* create_node()
{
	Node_type* ptr = (Node_type*)malloc(sizeof(Node_type));
	ptr->count=0;
	int i;
	for(i=0;i<MAX;i++)
	{
		assign_null(&ptr->value[i]);
		ptr->branch[i] = NULL;
	}
	ptr->branch[i] = NULL;
	return ptr;
}

int compare_name(Employee_record *nptr,Employee_record *ptr)
{
    int i=strcmp(nptr->firstname,ptr->firstname);
    if(i==0)
    {
        i=strcmp(nptr->lastname,ptr->lastname);
    }
    return i;
}

void print_Employee_record(Employee_record *ptr)
{
	printf("\n%s      ",ptr->firstname);
	printf("\t%s       ",ptr->lastname);
	printf("\t\t%s       ",ptr->accommodation_type);
	printf("\t%d       ",ptr->idtype);
	printf("\t%s",ptr->id.aadhaar);
	printf("%s",ptr->id.passport);
	printf("%s       ",ptr->id.empcode);
	printf("%s\n",ptr->address);
}

int compare_id(Employee_record *rec1,Employee_record *rec2)
{
    int ret_val;
    if(rec1->idtype > rec2->idtype)
    {
        ret_val = 1;
    }
    else if(rec1->idtype < rec2->idtype)
    {
        ret_val = -1;
    }
    else if(rec1->idtype == rec2->idtype)
    {
        if(rec1->idtype == 0 )
        {
            ret_val = strcmp(rec1->id.aadhaar,rec2->id.aadhaar);
        }
        else if(rec1->idtype == 1 )
        {
            ret_val = strcmp(rec1->id.passport,rec2->id.passport);
        }
        else if(rec1->idtype == 2 )
        {
            ret_val = strcmp(rec1->id.empcode,rec2->id.empcode);
        }
    }
    return ret_val;
}

void copy_record_data(Employee_record *temp_ptr,Employee_record *rec)
{
    strcpy(temp_ptr->firstname,rec->firstname);
	strcpy(temp_ptr->lastname,rec->lastname);
	strcpy(temp_ptr->accommodation_type,rec->accommodation_type);
    temp_ptr->idtype = rec->idtype;
	strcpy(temp_ptr->id.aadhaar,rec->id.aadhaar);
	strcpy(temp_ptr->id.passport,rec->id.passport);
	strcpy(temp_ptr->id.empcode,rec->id.empcode);
	strcpy(temp_ptr->address,rec->address);
}

void copy_record(Employee_record *rec1,Employee_record *rec2)
{
    assign_null(rec1);
    *rec1 = *rec2;
}

Boolean SearchNode(Employee_record *target, Node_type *root, int *k)
{
    Boolean ret_val = FALSE;
    if(compare_id(target,&root->value[0]) < 0 ) 
    {   
        (*k) = 0;
    }
    else
    {
        *k =root->count;
        while ((compare_id(target,&root->value[(*k)-1]) < 0 ) &&  *k > 1  ) 
        {   
            (*k)-- ;
        }
        if(compare_id(target,&root->value[(*k)-1]) == 0)
        {
            ret_val = TRUE;
        }
    }
    return ret_val;
}

Node_type* Search(Employee_record *target, Node_type *root, int *targetpos)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if(SearchNode(target, root,targetpos))
    {
        return root;
    }
    else
    {
        return  Search(target,root->branch[*targetpos], targetpos);
    }
}

void PushIn(Employee_record *x, Node_type * Xr, Node_type * p, int k) 
{ 
    int i;
    for (i = p->count-1; i >= k; i--) 
    { 
        copy_record(&p->value[i + 1] ,&p->value[i]); 
        p->branch [i + 2] = p->branch[i+1] ; 
        p->branch[i+1] = NULL;
    } 
    copy_record(&p->value[k] ,x); 
    p->branch [k + 1 ] = Xr; 
    p->count++; 
}

void Split(Employee_record *x, Node_type *Right_ptr, Node_type *p, int k, Node_type **Right_pptr) 
{ 
    int i;
    int median; 
    if (k <=MIN)
    { 
        median = MIN - 1;
    } 
    else 
    {
        median = MIN;
    } 
    *Right_pptr = create_node(); 
    for (i = median + 1; i < MAX; i++) 
    { 
        (*Right_pptr)->value[i - median -1] = p->value[i]; 
        (*Right_pptr)->branch [i - median] = p->branch [i+1] ; 
         p->branch[i+1] = NULL;
    } 
    (*Right_pptr)->count = MAX - median - 1; 
    p->count = median + 1; 
    if ( k <= MIN)
    {
        PushIn(x, Right_ptr, p, k);
    } 
    else 
    {
        PushIn(x, Right_ptr, *Right_pptr, k - median-1);
    } 
    copy_record(x,&p->value[p->count-1] ); 
    ( *Right_pptr) ->branch [0] = p->branch[p->count] ; 
    p->branch[p->count] = NULL;
    p->count--;
}

Boolean PushDown(Employee_record *new_value ,Node_type *p, Employee_record **X,Node_type **Right_pptr) 
{
    int k;
    Boolean ret_val = FALSE;
    if (p == NULL)
    { 
        *X = new_value ;
        *Right_pptr = NULL; 
        ret_val = TRUE; 
    } 
    else
    {
        if(SearchNode(new_value, p, &k) == FALSE)
        {
            if (PushDown (new_value ,p->branch[k] , X, Right_pptr)) 
            {
                if (p->count < MAX) 
                { 
                    PushIn( *X, *Right_pptr, p, k);
                } 
                else 
                { 
                    Split( *X, *Right_pptr, p, k, Right_pptr) ; 
                    ret_val = TRUE; 
                } 
            }
        }
    }
    return ret_val;
}

Node_type* Insert(Employee_record *new_value, Node_type *root) 
{
    Employee_record *x;
    Node_type *xr; 
    Node_type *p; 
    Boolean pushup;
    pushup = PushDown(new_value, root,&x, &xr); 
    if(pushup)
    {
        p=(Node_type*)malloc(sizeof(Node_type));//Make a new root. 
        p->count = 1;
        copy_record(&p->value[0], x);
        p->branch [0] = root; 
        p->branch [1] = xr;
        return p;
    }
    return root; 
}

// Qc-->Records printed in the order whose Aadhar numbers are listed first 
// all those who have provided Passport number are listed next
// and all those who have provided Employee code are listed at the end
void traversal(Node_type *root) {
  int i;
  if (root) {
    for (i = 0; i < root->count; i++) {
      traversal(root->branch[i]);
      print_Employee_record(&root->value[i]);
    }
    traversal(root->branch[i]);
  }
}

//Qd-->Index tree creation
Boolean SearchNode_in_index(Employee_record *target, index *root, int *k)
{
    Boolean ret_val = FALSE;
    if(compare_name(target,root->index_ptr[0]) < 0 ) 
    {   
        (*k) = 0;
    }
    else
    {
        *k =root->index_count;
        while ((compare_name(target,root->index_ptr[(*k)-1]) < 0 ) &&  *k > 1  ) 
        {   
            (*k)-- ;
        }
        if(compare_name(target,root->index_ptr[(*k)-1]) == 0)
        {
            ret_val = TRUE;
        }
    }
    return ret_val;
}

index* Search_in_index(Employee_record *target, index *root, int *targetpos)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if(SearchNode_in_index(target, root,targetpos))
    {
        return root;
    }
    else
    {
        return  Search_in_index(target,root->index_branch[*targetpos], targetpos);
    }
}

void PushIn_in_index(Employee_record *x, index * Xr, index * p, int k) 
{ 
    int i;
    for (i = p->index_count-1; i >= k; i--) 
    { 
        p->index_ptr[i + 1] = p->index_ptr[i]; 
        p->index_branch [i + 2] = p->index_branch[i+1] ; 
        p->index_branch[i+1] = NULL;
    } 
    p->index_ptr[k] = x; 
    p->index_branch [k + 1 ] = Xr; 
    p->index_count++;  
}

void Split_in_index(Employee_record **x, index *Right_ptr, index *p, int k, index **Right_pptr) 
{ 
    int i;
    int median; 
    if (k <=MIN)
    { 
        median = MIN - 1;
    } 
    else 
    {
        median = MIN;
    } 
    *Right_pptr = create_index(); 
    for (i = median + 1; i < MAX; i++) 
    { 
        (*Right_pptr)->index_ptr[i - median -1] = p->index_ptr[i]; 
        (*Right_pptr)->index_branch [i - median] = p->index_branch [i+1] ; 
         p->index_branch[i+1] = NULL;
    } 
    (*Right_pptr)->index_count = MAX - median - 1; 
    p->index_count = median + 1; 
    if ( k <= MIN)
    {
        PushIn_in_index(*x, Right_ptr, p, k);
    } 
    else 
    {
        PushIn_in_index(*x, Right_ptr, *Right_pptr, k - median-1);
    } 
    *x = p->index_ptr[p->index_count-1] ;
    print_Employee_record(*x);
    ( *Right_pptr)->index_branch [0] = p->index_branch[p->index_count] ; 
    p->index_branch[p->index_count] = NULL;
    p->index_count--;
}

Boolean PushDown_in_index(Employee_record *new_value, index *p, Employee_record **X,index **Right_pptr) 
{
    int k;
    Boolean ret_val = FALSE;
    if (p == NULL)
    { 
        *X = new_value ;
        *Right_pptr = NULL; 
        ret_val = TRUE; 
    } 
    else
    {
        if(SearchNode_in_index(new_value ,p, &k) == FALSE)
        {
            if (PushDown_in_index(new_value, p->index_branch[k] , X, Right_pptr)) 
            {
                if (p->index_count < MAX) 
                { 
                    PushIn_in_index( *X, *Right_pptr, p, k);
                } 
                else 
                { 
                    Split_in_index( X, *Right_pptr, p, k, Right_pptr) ; 
                    ret_val = TRUE; 
                } 
            }
        }
    }
    return ret_val;
}

void Insert_in_index(Employee_record *new_value,index **i_pptr) 
{
    Employee_record *x=NULL;
    index *xr=NULL; 
    index *p=NULL; 
    Boolean pushup;
    pushup = PushDown_in_index(new_value,*i_pptr,&x, &xr); 
    if(pushup)
    {
        p=create_index();
        p->index_count = 1;
        p->index_ptr[0] = x;
        p->index_branch [0] = *i_pptr; 
        p->index_branch [1] = xr;
        *i_pptr  = p;
    } 
}

void create_index_tree(Node_type *root,index **i_pptr) {
  int i;
  if (root) {
    for (i = 0; i < root->count; i++) {
      create_index_tree(root->branch[i],i_pptr);
      Insert_in_index(&root->value[i],i_pptr);
    }
    create_index_tree(root->branch[i],i_pptr);
  }
}

//Qd-->PrintSortedRecords
void printSortedRecords(index *i_ptr) {
  int i;
  if (i_ptr) 
  {
    for (i = 0; i < i_ptr->index_count; i++) 
    {
      printSortedRecords(i_ptr->index_branch[i]);
      print_Employee_record(i_ptr->index_ptr[i]);
    }
    printSortedRecords(i_ptr->index_branch[i]);
  }
}

//Qe-->Searching a employee record for given name

Boolean Search_record(Employee_record *temp,Employee_record *target,index *p) 
{ 
    int k; 
    Boolean ret_val;
    if (p == NULL) 
    {
        ret_val = FALSE;
    }
    else 
    { 
        if (SearchNode_in_index(target,p, &k))
        {
            ret_val = TRUE;
            copy_record_data(temp,p->index_ptr[k-1]);
        }
        else 
        {
            ret_val = Search_record(temp,target, p->index_branch[k]);
        }
    }
    return ret_val;
}

Boolean Search_name( Employee_record *temp,Employee_record *target,Node_type *p) 
{ 
    int k; 
    Boolean ret_val;
    if (p == NULL) 
    {
        ret_val = FALSE;
    }
    else 
    { 
        if (SearchNode(target, p, &k))
        {
            ret_val = TRUE;
            copy_record_data(temp,&p->value[k-1]);
        }
        else 
        {
            ret_val = Search_name(temp,target, p->branch[k]);
        }
    }
    return ret_val;
}
//Qf-->Delete record from database
void Merge(Node_type *p, int k) 
{ 
    int c; 
    Node_type *q;
    Node_type *t; 
    q = p->branch [k]; 
    t = p->branch [k - 1];
    t->count++;
    t->value[t->count-1] = p->value[k-1]; 
    t->branch [t->count] = q->branch[0]; 
    for (c= 0; c < q->count; c++ ) 
    {
        t->count++; 
        copy_record(&t->value[t->count-1] ,&q->value[c]) ; 
        t->branch [t->count] = q->branch [c+1] ;
        q->branch[c+1] = NULL;
    } 
    for (c= k; c < p->count; c++) 
    { 
        copy_record(&p->value[c-1], &p->value[c]) ; 
        p->branch [c] = p->branch [c + 1] ;
        p->branch[c+1] =NULL;
    }
    p->count--; 
    free(q);
} 

void MoveRight(Node_type *p, int k) 
{ 
    int c; 
    Node_type *t; 
    t = p->branch[k]; 
    for (c = t->count; c > 0; c-- ) 
    { 
        copy_record(&t->value[c + 1 ],&t->value[c]) ; 
        t->branch [c + 1 ] = t->branch[c] ; 
    } 
    t->branch [1] = t->branch [0] ;
    t->count++; 
    copy_record(&t->value[0],&p->value[k]); 
    t = p->branch [k- 1 ];
    copy_record(&p->value[k] ,&t->value[t->count]); 
    p->branch[k]->branch [0] = t->branch [t->count]; 
    t->count-- ; 
}

void MoveLeft(Node_type *p, int k) 
{ 
    int c; 
    Node_type *t; 
    t = p->branch[k-1] ; 
    t->count++; 
    copy_record(&t->value[t->count],&p->value[k]) ; 
    t->branch [t->count] = p->branch[ k]->branch[0] ;
    t = p->branch [k] ; 
    copy_record(&p->value[ k], &t->value[0]); 
    t->branch [0] = t->branch[1]; 
    t->count-- ; 
    for (c = 1; c <= t->count; c++) 
    { 
        copy_record(&t->value[c],&t->value[c + 1]); 
        t->branch [c] = t->branch [c + 1] ; 
    } 
}

void Restore(Node_type * p, int k) 
{
    if (k == 0)
    {
        if (p->branch[1]->count > MIN)
        { 
            MoveLeft(p, 1);
        } 
        else
        { 
            Merge(p, 1) ;
        }
    } 
    else if(k == p->count)
    {    
        if(p->branch [k - 1]->count > MIN) 
        {    
            MoveRight(p, k);
        } 
        else 
        {
            Merge(p, k);
        }
    } 
    else if (p->branch[ k- 1]->count > MIN)
    {
        MoveRight(p, k);
    } 
    else if (p->branch [ k + 1]->count > MIN) 
    {
        MoveLeft(p, k + 1);
    }
    else 
    {
        Merge(p, k);
    } 
}

void Remove(Node_type *p, int k) 
{
    int i;
    for (i = k + 1; i <= p->count; i++) 
    { 
        copy_record(&p->value[i- 1],&p->value[i]) ; 
        p->branch [i - 1] = p->branch[i]; 
    } 
    p->count--; 
}

void Successor(Node_type *p, int k) 
{ 
    Node_type *q; 
    q = p->branch [k] ;
    while(q->branch[0]!=NULL)
    {
        q = q->branch [0] ;
    }
    copy_record(&p->value[ k],&q->value[0]) ;
}

Boolean RecDelete( Employee_record *temp,Employee_record *target, Node_type *p) 
{ 
    int k; 
    Boolean ret_val;
    if (p == NULL) 
    {
        ret_val = FALSE;
    }
    else 
    { 
        if (SearchNode(target, p, &k))
        {
        	copy_record_data(temp,&p->value[k-1]);
            ret_val = TRUE;
            if (p->branch[k-1]!=NULL) 
            { 
                Successor(p, k);
                if (!(RecDelete(temp,&p->value[k-1], p->branch[k])))
                {
                    ret_val = FALSE;
                }
            } 
            else
            { 
                Remove(p, k) ;
            }
        }
        else 
        {
            ret_val = RecDelete(temp,target, p->branch [k]);
        }
        if(p->branch[k] != NULL)
        { 
            if (p->branch[k]->count < MIN) 
            {
                Restore( p, k) ;
            }
        } 
    }
    return ret_val;
}

Node_type* Delete(Employee_record *temp,Employee_record *target, Node_type *root) 
{ 
    Node_type* p;
    if ( ! RecDelete ( temp,target, root) ) 
    {
        printf("\nRecord not found") ; 
    }
    else 
    {
        if (root->count == 0) 
        {
            p = root; 
            root = root->branch [0] ; 
            free (p);
        }
    }
    return root; 
}

//Qf-->deleting record from index tree
void Merge_index(index *p, int k) 
{ 
    int c; 
    index *q;
    index *t; 
    q = p->index_branch [k]; 
    t = p->index_branch [k - 1];
    t->index_count++;
    t->index_ptr[t->index_count-1] = p->index_ptr[k-1]; 
    t->index_branch [t->index_count] = q->index_branch[0]; 
    for (c= 0; c < q->index_count; c++ ) 
    {
        t->index_count++; 
        t->index_ptr[t->index_count-1]  = q->index_ptr[c] ; 
        t->index_branch [t->index_count] = q->index_branch [c+1] ;
        q->index_branch[c+1] = NULL;
    } 
    for (c= k; c < p->index_count; c++) 
    { 
        p->index_ptr[c-1] = p->index_ptr[c] ; 
        p->index_branch [c] = p->index_branch [c + 1] ;
        p->index_branch[c+1] =NULL;
    }
    p->index_count--; 
    free(q);
} 

void MoveRight_index(index *p, int k) 
{ 
    int c; 
    index *t; 
    t = p->index_branch[k]; 
    for (c = t->index_count; c > 0; c-- ) 
    { 
        t->index_ptr[c + 1 ] = t->index_ptr[c] ; 
        t->index_branch [c + 1 ] = t->index_branch[c] ; 
    } 
    t->index_branch [1] = t->index_branch [0] ;
    t->index_count++; 
    t->index_ptr[0] = p->index_ptr[k]; 
    t = p->index_branch [k- 1 ];
    p->index_ptr[k]  = t->index_ptr[t->index_count]; 
    p->index_branch[k]->index_branch [0] = t->index_branch [t->index_count]; 
    t->index_count-- ; 
}

void MoveLeft_index(index *p, int k) 
{ 
    int c; 
    index *t; 
    t = p->index_branch[k-1] ; 
    t->index_count++; 
    t->index_ptr[t->index_count] = p->index_ptr[k] ; 
    t->index_branch [t->index_count] = p->index_branch[ k]->index_branch[0] ;
    t = p->index_branch [k] ; 
    p->index_ptr[ k]= t->index_ptr[0]; 
    t->index_branch [0] = t->index_branch[1]; 
    t->index_count-- ; 
    for (c = 1; c <= t->index_count; c++) 
    { 
        t->index_ptr[c] = t->index_ptr[c + 1]; 
        t->index_branch [c] = t->index_branch [c + 1] ; 
    } 
}

void Restore_index(index * p, int k) 
{
    if (k == 0)
    {
        if (p->index_branch[1]->index_count > MIN)
        { 
            MoveLeft_index(p, 1);
        } 
        else
        { 
            Merge_index(p, 1) ;
        }
    } 
    else if(k == p->index_count)
    {    
        if(p->index_branch [k - 1]->index_count > MIN) 
        {    
            MoveRight_index(p, k);
        } 
        else 
        {
            Merge_index(p, k);
        }
    } 
    else if (p->index_branch[ k- 1]->index_count > MIN)
    {
        MoveRight_index(p, k);
    } 
    else if (p->index_branch [ k + 1]->index_count > MIN) 
    {
        MoveLeft_index(p, k + 1);
    }
    else 
    {
        Merge_index(p, k);
    }
}

void Remove_index(index *p, int k) 
{
    int i;
    for (i = k + 1; i <= p->index_count; i++) 
    { 
        p->index_ptr[i- 1] = p->index_ptr[i] ; 
        p->index_branch [i - 1] = p->index_branch[i]; 
    } 
    p->index_count--; 
}

void Successor_index(index *p, int k) 
{ 
    index *q; 
    q = p->index_branch [k] ;
    while(q->index_branch[0]!=NULL)
    {
        q = q->index_branch [0] ;
    }
    p->index_ptr[ k] = q->index_ptr[0] ;
}

Boolean RecDelete_index(Employee_record *target,index *p) 
{ 
    int k; 
    Boolean ret_val;
    if (p == NULL) 
    {
        ret_val = FALSE;
    }
    else 
    { 
        if (SearchNode_in_index(target, p, &k))
        {
            ret_val = TRUE;
            if (p->index_branch[k-1]!=NULL) 
            { 
                Successor_index(p, k);
                if (!(RecDelete_index(p->index_ptr[k-1], p->index_branch[k])))
                {
                    ret_val = FALSE;
                }
            } 
            else
            { 
                Remove_index(p, k) ;
            }
        }
        else 
        {
            ret_val = RecDelete_index(target, p->index_branch [k]);
        }
        if(p->index_branch[k] != NULL)
        { 
            if (p->index_branch[k]->index_count < MIN) 
            {
                Restore_index( p, k) ;
            }
        } 
    }
    return ret_val;
}

index* Delete_index(Employee_record *target,index *root) 
{ 
    index* p;
    if ( ! RecDelete_index( target, root) ) 
    {
        printf("\nRecord not found") ; 
    }
    else 
    {
        if (root->index_count == 0) 
        {
            p = root; 
            root = root->index_branch [0] ; 
            free (p);
        }
    }
    return root; 
}

Employee_record* input_record()
{
    Employee_record* nptr=(Employee_record*)(malloc(sizeof(Employee_record)));
    if(nptr!=NULL)
    {
        assign_null(nptr);
        printf("Enter Employee id type:");
        scanf("%d",&nptr->idtype);
        if(nptr->idtype==0)
	    {
            printf("Enter aadhar no:");
	    	scanf(" %s",nptr->id.aadhaar);
	    }
	    else if(nptr->idtype==1)
	    {
            printf("Enter passport no:");
	    	scanf(" %s",nptr->id.passport);
	    }
	    else if(nptr->idtype==2)
	    {
            printf("Enter employee code:");
	    	scanf(" %s",nptr->id.empcode);
	    }
    }
    else
    {
        printf("No memory in heap!\n");
    }
    return nptr;
}

Employee_record* input_record_name()
{
    Employee_record* nptr=(Employee_record*)(malloc(sizeof(Employee_record)));
    if(nptr!=NULL)
    {
        assign_null(nptr);
        printf("Enter first name:");
        scanf(" %s",nptr->firstname);
        printf("Enter last name:");
        scanf(" %s",nptr->lastname);
    }
    else
    {
        printf("No memory in heap!\n");
    }
    return nptr;
}

//Qg-->updating record

Employee_record* Search_employee(Employee_record *target,Node_type *p) 
{ 
    int k; 
    Employee_record *ret_val;
    if (p == NULL) 
    {
        ret_val = NULL;
    }
    else 
    { 
        if (SearchNode(target, p, &k))
        {
            ret_val = &p->value[k-1];
        }
        else 
        {
            ret_val = Search_employee(target, p->branch[k]);
        }
    }
    return ret_val;
}

void update_record(index **i_pptr,Node_type **root_ptr)
{
	Employee_record *ptr = input_record();
	
	print_Employee_record(ptr);
	
    Employee_record *search_ptr ,*name_ptr;
    name_ptr = (Employee_record*)malloc(sizeof(Employee_record));

    int field_type,flag=0;
    Employee_record *nptr=(Employee_record*)malloc(sizeof(Employee_record));

    if(ptr!=NULL)
    {
    	search_ptr = Search_employee(ptr,*root_ptr);
        copy_record_data(nptr,search_ptr);

		printf("Enter the field to be changed:");
		printf("\n0-name\n1-idtype\n2-Address\n");
		scanf("%d",&field_type);
		switch(field_type)
		{
			case 0:
				printf("Enter firstname:");
				scanf(" %s",nptr->firstname);
				printf("Enter  lastname:");
				scanf(" %s",nptr->lastname);
                flag=1;
				break;
			case 1:
				printf("Enter new id_type:");
	            scanf("%d",&nptr->idtype);
	            printf("Enter changed id");
	            switch(nptr->idtype)
	            {
	            	case 0:scanf(" %s",nptr->id.aadhaar);
	            		break;
	            	case 1:scanf(" %s",nptr->id.passport);
	            		break;
	            	case 2:scanf(" %s",nptr->id.empcode);
	            	    break;
                }
                flag = 1;
				break;
			case 2:
				printf("Enter new address:");
				scanf("\n%[^\n]%*c",search_ptr->address);
				break;
			default :printf("You have selected wrong option");
				break;
		}
		if(flag)
		{
			if(Search_name(name_ptr,ptr,*root_ptr))
            {
                *i_pptr = Delete_index(name_ptr,*i_pptr);
                *root_ptr = Delete(name_ptr,ptr,*root_ptr);
                print_Employee_record(ptr);
                Insert(nptr,*root_ptr);
                Insert_in_index(nptr,i_pptr);
            }
		}
	}
	else
	{
		printf("No record found regarding the entered data");
	}

}

int main()
{
  Node_type *root=NULL;
  Employee_record temp,*record_ptr =NULL,*delete_record = NULL,*ptr ,*search_ptr;
  ptr = (Employee_record*)malloc(sizeof(Employee_record));
  search_ptr = (Employee_record*)malloc(sizeof(Employee_record));
  index *i_ptr = NULL;
  int field_type=1;
  printf("Insert atleast one record to the data base\nPlease select once option 4 before going to options above 4 to create index linked list\n");
  while(field_type)
  {
      switch(field_type)
      {
          case 1:
            record_ptr=create_record();
  	        root = Insert(record_ptr,root);
  	        if(i_ptr!=NULL)
            {
                Insert_in_index(record_ptr,&i_ptr);
            }
            break;
          case 2:
            //Qb-->remove_duplicates
            //assuming no duplicates are present in given records
            printf("\nAssuming no duplicate entries are present");
            break;
          case 3:
            //Qc-->print records
	      	traversal(root);
	      	break;
          case 4:
            // Qd-->create index tree
            if(i_ptr == NULL)
            {
                create_index_tree(root,&i_ptr);
            }
	        printf("Sorted records:");
            printSortedRecords(i_ptr);
	      	break;
	      case 5:
	      	assign_null(ptr);
	      	assign_null(search_ptr);
	      	if(i_ptr == NULL)
            {
                create_index_tree(root,&i_ptr);
            }
	      	search_ptr = input_record_name();
	      	if(Search_record(ptr,search_ptr,i_ptr))
	      	{
	      		print_Employee_record(ptr);	
			}
			else
			{
				printf("\nNo record found");
			}
            break;
          case 6:
          	assign_null(ptr);
          	assign_null(search_ptr);
            delete_record = input_record();
            if(i_ptr == NULL)
            {
                create_index_tree(root,&i_ptr);
            }
            if(Search_name(ptr,delete_record,root))
            {
            	i_ptr = Delete_index(ptr,i_ptr);
            	root = Delete(search_ptr,delete_record,root);
            	print_Employee_record(search_ptr);
			}
			else
			{
				printf("\nRecord not found!");
			}
            
            break;
          case 7:
          	update_record(&i_ptr,&root);
          	break;
	      default :printf("You have selected wrong option");
	      	break;
        }
    printf("Select one option of the following:");
    printf("\n0-To quit\n1->Insert new record\n2->removeDuplicates\n3->printrecord\n4->printsortedrecords\n5->searchrecord\n6->deleterecord\n7->updaterecord\n");
    scanf("%d",&field_type);
  }
  return 0;
}

