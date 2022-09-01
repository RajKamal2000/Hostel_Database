#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum{FAILURE,SUCCESS} status_code;//for deleting a record

typedef enum{NO,YES} allocated;
//doubly linked list
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
	struct accomodation *prev;
	struct accomodation *next;
}Employee_record;

// linked list index for storing database sorted in alaphabetical order
typedef struct index_linked_list
{
    Employee_record *index_ptr;
    struct index_linked_list *prev;
    struct index_linked_list *next;
}index;

typedef struct type_of_accomodation
{
    allocated a;
    struct type_of_accomodation *prev;
    struct type_of_accomodation *next;
}acc_type;

acc_type *type1,*type2,*type3,*type4;

void create_node_acc_type()
{
    int i,j;
    acc_type *lptr;
    for(i=0;i<4;i++)
    {
        lptr=NULL;
        for(j=1;j<=10;j++)
        {
            acc_type *nptr=(acc_type*)malloc(sizeof(acc_type));
            nptr->a=NO;
	        nptr->prev=NULL;
	        nptr->next=NULL;
            if(lptr==NULL)
	        {
		        lptr=nptr;
	        }
	        else
	        {
		        (lptr)->prev=nptr;
		        nptr->next=lptr;
		        lptr=nptr;
	        }
        }
	    switch(i)
		{
			case 0:
				type1=lptr;
				break;
			case 1:
				type2=lptr;
				break;
			case 2:
				type3=lptr;
				break;
			case 3:
                type4=lptr;
				break;
		}
    }
}

void allocate_acc_type(Employee_record *ptr)
{
    int i,flag=1;
    if(ptr->accommodation_type[7]=='I')
	{
		i=2;
	}
	else if(ptr->accommodation_type[6]=='I')
	{
		i=1;
	}
	else if(ptr->accommodation_type[5]=='I')
	{
		i=0;
	}
	else if(ptr->accommodation_type[6]=='V')
	{
		i=3;
	}
    switch(i)
	{
		case 0:
			if(!type1->a)
            {
                type1->a=YES;
                if(type1->next!=NULL)
                {
                    type1=type1->next;
                }
                strcpy(ptr->accommodation_type,"type-I");
                flag=0;
            }
		case 1:
			if(!type2->a&&flag)
            {
                type2->a=YES;
                if(type2->next!=NULL)
                {
                    type2=type2->next;
                }
                strcpy(ptr->accommodation_type,"type-II");
                flag=0;
            }
		case 2:
			if(!type3->a&&flag)
            {
                type3->a=YES;
                if(type3->next!=NULL)
                {
                    type3=type3->next;
                }
                strcpy(ptr->accommodation_type,"type-III");
                flag=0;
            }
		case 3:
            if(!type4->a&&flag)
            {
                type4->a=YES;
                if(type4->next!=NULL)
                {
                    type4=type4->next;
                }
                strcpy(ptr->accommodation_type,"type-IV");
                flag=0;
            }
        default:
            if(flag)
            {
                printf("No space for accomodation");
            }
            break;
    }
}
void delete_allocation(Employee_record *ptr)
{
    int i,flag=1;
    if(ptr->accommodation_type[7]=='I')
	{
		i=2;
	}
	else if(ptr->accommodation_type[6]=='I')
	{
		i=1;
	}
	else if(ptr->accommodation_type[5]=='I')
	{
		i=0;
	}
	else if(ptr->accommodation_type[6]=='V')
	{
		i=3;
	}
    switch(i)
	{
		case 0:
			type1=type1->prev;
            type1->a=NO;
            break;
		case 1:
			type2=type2->prev;
            type2->a=NO;
            break;
		case 2:
			type3=type3->prev;
            type3->a=NO;
            break;
		case 3:
            type4=type4->prev;
            type4->a=NO;
            break;
    }
}
// for assigning null and zero values to elemnts of given linked list
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

// Qc-->Records printed in the order whose Aadhar numbers are listed first 
// all those who have provided Passport number are listed next
// and all those who have provided Employee code are listed at the end.
void printRecords(Employee_record *tptr) // PRINTING Employee DATA
{
	printf("FIRSTNAME	");
	printf("LASTNAME	");
	printf("Accommodation_type");
	printf("\tIdtype	");
	printf("\tIdno");
	printf("        \tAddress");
    while(tptr!=NULL)
    {
        print_Employee_record(tptr);
        tptr=tptr->next;
    }
}

// Qd-->printing sorted records (sorted in alphabetical order using index Linked list)
void printSortedRecords(index *tptr)
{
    printf("FIRSTNAME	");
	printf("LASTNAME	");
	printf("Accommodation_type");
	printf("\tIdtype	");
	printf("\tIdno");
	printf("        \tAddress");
    while(tptr!=NULL)
    {
        print_Employee_record(tptr->index_ptr);
        tptr=tptr->next;
    }
}
int name_compare(Employee_record* nptr,Employee_record *ptr)
{
    int i=strcmp(nptr->firstname,ptr->firstname);
    if(i==0)
    {
        i=strcmp(nptr->lastname,ptr->lastname);
    }
    return i;
}

index* divide_index(index* ptr)
{
	index *slow_ptr=ptr;
	index *fast_ptr=ptr->next;
	if(fast_ptr!=NULL)
	{
		fast_ptr=fast_ptr->next;
	}
	while(fast_ptr!=NULL)
	{
		slow_ptr=slow_ptr->next;
		fast_ptr=fast_ptr->next;
		if(fast_ptr!=NULL)
		{
			fast_ptr=fast_ptr->next;
		}
	}
	ptr=slow_ptr->next;
	ptr->prev=NULL;
	slow_ptr->next=NULL;
	return ptr;
}
index* merge_name(index* nptr,index *ptr)
{
	index *result,*tail,*temp;
    int i=name_compare(nptr->index_ptr,ptr->index_ptr);
	if(i==1)
	{
		result=ptr;
		ptr=ptr->next;
	}
	else
	{
		result=nptr;
		nptr=nptr->next;
	}
	tail=result;
	tail->next=NULL;
	while(ptr!=NULL&&nptr!=NULL)
	{
        i=name_compare(nptr->index_ptr,ptr->index_ptr);
		if(i==1)
		{
			tail->next=ptr;
			ptr->prev=tail;
			tail=tail->next;
			ptr=ptr->next;
		}
		else
		{
			tail->next=nptr;
			nptr->prev=tail;
			tail=tail->next;
			nptr=nptr->next;
		}
		tail->next=NULL;
	}
	if(ptr!=NULL)
	{
		tail->next=ptr;
		ptr->prev=tail;
	}
	if(nptr!=NULL)
	{
        tail->next=nptr;
		nptr->prev=tail;
	}
	return result;
}
index* merge_sort_name(index* nptr)
{
	index *ptr;
	if(nptr!=NULL&&nptr->next!=NULL)
	{
		ptr=divide_index(nptr);
		nptr=merge_sort_name(nptr);
		ptr=merge_sort_name(ptr);
		nptr=merge_name(nptr,ptr);
	}
	return nptr;
}

int id_compare(Employee_record* nptr,Employee_record *ptr)
{
    int i,idType_to_cmp=nptr->idtype;
    if(idType_to_cmp==0)
    {
        i=strcmp(nptr->id.aadhaar,ptr->id.aadhaar);
    }
    else if(idType_to_cmp==1)
    {
        i=strcmp(nptr->id.passport,ptr->id.passport);
    }
    else if(idType_to_cmp==2)
    {
        i=strcmp(nptr->id.empcode,ptr->id.empcode);
    }
    return i;
}

Employee_record* divide(Employee_record* ptr)
{
	Employee_record *slow_ptr=ptr;
	Employee_record *fast_ptr=ptr->next;
	if(fast_ptr!=NULL)
	{
		fast_ptr=fast_ptr->next;
	}
	while(fast_ptr!=NULL)
	{
		slow_ptr=slow_ptr->next;
		fast_ptr=fast_ptr->next;
		if(fast_ptr!=NULL)
		{
			fast_ptr=fast_ptr->next;
		}
	}
	ptr=slow_ptr->next;
	ptr->prev=NULL;
	slow_ptr->next=NULL;
	return ptr;
}
Employee_record* merge(Employee_record* nptr,Employee_record *ptr,Employee_record **last_pptr)
{
	Employee_record *result,*tail,*temp;
    int i=id_compare(nptr,ptr);
	if(i==1)
	{
		result=ptr;
		ptr=ptr->next;
	}
	else
	{
		result=nptr;
		if(i==0)
		{
			temp=ptr;
			ptr=ptr->next;
            delete_allocation(temp);
			free(temp);
		}
		nptr=nptr->next;
	}
	tail=result;
	tail->next=NULL;
	while(ptr!=NULL&&nptr!=NULL)
	{
        i=id_compare(nptr,ptr);
		if(i==1)
		{
			tail->next=ptr;
			ptr->prev=tail;
			tail=tail->next;
			ptr=ptr->next;
		}
		else if(i==-1)
		{
			tail->next=nptr;
			nptr->prev=tail;
			tail=tail->next;
			nptr=nptr->next;
		}
		else
		{
			temp=nptr;
			nptr=nptr->next;
			free(temp);
		}
		tail->next=NULL;
	}
	while(ptr!=NULL)
	{
        i=id_compare(ptr,tail);
		if(i==0)
		{
			temp=ptr;
			ptr=ptr->next;
			free(temp);
		}
		else
		{
			tail->next=ptr;
			ptr->prev=tail;
			ptr=ptr->next;
			tail=tail->next;
			tail->next=NULL;
		}
	}
	while(nptr!=NULL)
	{
        i=id_compare(nptr,tail);
		if(i==0)
		{
			temp=nptr;
			nptr=nptr->next;
			free(temp);
		}
		else
		{
			tail->next=nptr;
			nptr->prev=tail;
			nptr=nptr->next;
			tail=tail->next;
			tail->next=NULL;
		}
	}
    *last_pptr=tail;
	return result;
}
Employee_record* merge_sort(Employee_record* nptr,Employee_record **last_pptr)
{
	Employee_record *ptr;
	if(nptr!=NULL&&nptr->next!=NULL)
	{
		ptr=divide(nptr);
		nptr=merge_sort(nptr,last_pptr);
		ptr=merge_sort(ptr,last_pptr);
		nptr=merge(nptr,ptr,last_pptr);
	}
	return nptr;
}

// Qb-->removing duplicates
void remove_duplicates(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr)
{
    Employee_record *head_ptr=NULL,*tail_ptr=NULL;
    if(*E0_pptr!=NULL)
    {
        (*E0_pptr)->next=NULL;
        *S0_pptr=merge_sort(*S0_pptr,E0_pptr);
        head_ptr=*S0_pptr;
        tail_ptr=*E0_pptr;
    }
    if(*E1_pptr!=NULL)
    {
        (*S1_pptr)->prev=NULL;
        (*E1_pptr)->next=NULL;
        *S1_pptr=merge_sort(*S1_pptr,E1_pptr);
        if(head_ptr==NULL)
        {
            head_ptr=*S1_pptr;
        }
        else
        {
            tail_ptr->next=*S1_pptr;
            (*S1_pptr)->prev=tail_ptr;
        }
        tail_ptr=*E1_pptr;
    }
    if(*E2_pptr!=NULL)
    {
        (*S2_pptr)->prev=NULL;
        (*E2_pptr)->next=NULL;
        *S2_pptr=merge_sort(*S2_pptr,E2_pptr);
        if(head_ptr==NULL)
        {
            head_ptr=*S2_pptr;
        }
        else
        {
            tail_ptr->next=*S2_pptr;
            (*S2_pptr)->prev=tail_ptr;
        }
        tail_ptr=*E2_pptr;
    }
    *fpptr=head_ptr;
    *tpptr=tail_ptr;
}

Employee_record* create_record()
{
    // craeting record in heap
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
        // initializing both prev and next to NULL 
        nptr->prev=NULL;
        nptr->next=NULL;
        allocate_acc_type(nptr);
    }
    return nptr;
}

// Qa-->The records with idtype 0 are stored first, followed by records with idtype 1 and 2
void insert_record(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr,Employee_record *ptr)
{
    // *tpptr-->traverse poniter
    Employee_record *next_ptr,*prev_ptr;
    if(ptr!=NULL)
    {
        if(*tpptr==NULL)
        {
            if( ptr->idtype == 0 )
            {
                *S0_pptr=ptr;
                *E0_pptr=ptr;
            }
            else if( ptr->idtype == 1 )
            {
                *S1_pptr=ptr;
                *E1_pptr=ptr;
            }
            else if( ptr->idtype == 2 )
            {
                *S2_pptr=ptr;
                *E2_pptr=ptr;
            }
            *fpptr=ptr;
            *tpptr=ptr;
        }
        else if( ptr->idtype == 0 )
        {
            if(*E0_pptr==NULL)
            {
                if( *S1_pptr != NULL )
                {
                    ptr->next = *S1_pptr;
                    (*S1_pptr)->prev=ptr;
                }
                else
                {
                    ptr->next = *S2_pptr;
                    (*S2_pptr)->prev=ptr;
                }
                *fpptr=ptr;
                *S0_pptr=ptr;
                *E0_pptr=ptr;
            }
            else
            {
                ptr->prev=*E0_pptr;
                ptr->next=(*E0_pptr)->next;
                (*E0_pptr)->next=ptr;
                if(ptr->next!=NULL)
                {
                    next_ptr=ptr->next;
                    next_ptr->prev=ptr;
                    next_ptr=NULL;// making next_ptr NULL if any further freeing memory will not effect it
                }
                else
                {
                    *tpptr=ptr;
                }
                *E0_pptr = (*E0_pptr)->next;
            }
        }
        else if( ptr->idtype == 1 )
        {
            if( *E1_pptr == NULL )
            {
                if(*E0_pptr != NULL )
                {
                    ptr->prev = *E0_pptr;
                    ptr->next = (*E0_pptr)->next;
                    (*E0_pptr)->next=ptr;
                    if(ptr->next!=NULL)
                    {
                        next_ptr=ptr->next;
                        next_ptr->prev=ptr;
                        next_ptr=NULL;// making next_ptr NULL if any further freeing memory will not effect it
                    }
                    else
                    {
                        *tpptr=ptr;
                    }
                }
                else
                {
                    ptr->next = *S2_pptr;
                    (*S2_pptr)->prev=ptr;
                    *fpptr=ptr;
                }
                *S1_pptr=ptr;
            }
            else
            {
                ptr->prev=*E1_pptr;
                ptr->next=(*E1_pptr)->next;
                (*E1_pptr)->next=ptr;
                if(ptr->next!=NULL)
                {
                    next_ptr=ptr->next;
                    next_ptr->prev=ptr;
                    next_ptr=NULL;// making next_ptr NULL if any further freeing memory will not effect it
                }
                else
                {
                    *tpptr=ptr;
                }
            }
            *E1_pptr=ptr;
        }
        else if( ptr->idtype == 2 )
        {
            ptr->prev=*tpptr;
            (*tpptr)->next=ptr;
            if( *S2_pptr == NULL )
            {
                *S2_pptr=ptr;
            }
            *E2_pptr=ptr;
            *tpptr=ptr;
        }
    }
    else
    {
        printf("Space is not present in the heap!");
    }
}

// Qd-->creating index Linked list
void create_index(Employee_record *fptr,index **s_i_pptr,index **l_i_pptr)
{
    index *nptr=NULL,*tptr=NULL;
    while(fptr!=NULL)
    {
        nptr=(index*)malloc(sizeof(index));
        nptr->prev=NULL;
        nptr->next=NULL;
        nptr->index_ptr=fptr;
        if(tptr==NULL)
        {
            tptr=nptr;
            *s_i_pptr=nptr;
        }
        else
        {
            tptr->next=nptr;
            nptr->prev=tptr;
            tptr=nptr;
        }
        fptr=fptr->next;
    }
    *s_i_pptr=merge_sort_name(*s_i_pptr);
    tptr=*s_i_pptr;
    while(tptr->next!=NULL)
    {
        tptr=tptr->next;
    }
    *l_i_pptr=tptr;
}

// Qe-->search a given employee first name and print all of them in alphabetical order
void search(index* ptr)
{
    Employee_record *name_ptr;
    char emp_name[50];
    printf("Enter employee name:");
    scanf(" %s",emp_name);
    int flag=1;
    int i;
    while(ptr!=NULL&&flag)
    {
        name_ptr=ptr->index_ptr;
        i=strcmp(name_ptr->firstname,emp_name);
        if(i==1) 
        {
            /*
                starting name of the particular record is after the given name 
                that implies there is no record of that given name from this record 
                because records are sorted in alphabetic order in index linked list
            */
            flag=0;
        }
        else
        {
            // As they are sorted they will be printed in the alphabetical order
            if(i==0)
            {
                print_Employee_record(name_ptr);
            }
            ptr=ptr->next;
        }
    }
}

Employee_record* mid_node_employee(Employee_record *start,Employee_record *end)
{
    Employee_record *slow=start;
    Employee_record *fast=start->next;
    if(fast!=end->next)
    {
        fast=fast->next;
    }
    while(fast!=end->next)
    {
        slow=slow->next;
        fast=fast->next;
        if(fast!=end->next)
        {
            fast=fast->next;
        }
    }
    return slow;
}
Employee_record* search_idno(Employee_record *head,Employee_record *tail,Employee_record *nptr)
{
    Employee_record *mid_ptr;
    int i;
    if(head!=NULL&&tail!=NULL)
    {
    	if(id_compare(head,tail)!=0)
    	{
        	mid_ptr = mid_node_employee(head,tail);
        	i=id_compare(mid_ptr,nptr);
        	if(i==0)
        	{
            	return mid_ptr;
        	}
        	else if(i==1)
        	{
            	mid_ptr=search_idno(head,mid_ptr->prev,nptr);
        	}
        	else if(i==-1)
        	{
            	mid_ptr=search_idno(mid_ptr->next,tail,nptr);
        	}
    	}
    	else
    	{
        	if(id_compare(head,nptr)==0)
        	{
            	mid_ptr = head;
        	}
        	else
        	{
            mid_ptr = NULL;
        	}
    	}
    }
    else
    {
    	mid_ptr=NULL;
	}
    return mid_ptr;
}

index* mid_node(index *start,index *end)
{
    index *slow=start;
    index *fast=start->next;
    if(fast!=end->next)
    {
        fast=fast->next;
    }
    while(fast!=end->next)
    {
        slow=slow->next;
        fast=fast->next;
        if(fast!=end->next)
        {
            fast=fast->next;
        }
    }
    return slow;
}

index* search_name(index *head,index *tail,Employee_record *nptr)
{
    index *mid_ptr;
    int i;
    if(head!=NULL&&tail!=NULL)
    {
    	if(name_compare(head->index_ptr,tail->index_ptr)!=0)
    	{
        	mid_ptr = mid_node(head,tail);
        	i=name_compare(mid_ptr->index_ptr,nptr);
        	if(i==0)
        	{
            	return mid_ptr;
        	}
        	else if(i==1)
        	{
            	mid_ptr=search_name(head,mid_ptr->prev,nptr);
        	}
        	else if(i==-1)
        	{
            	mid_ptr=search_name(mid_ptr->next,tail,nptr);
        	}
    	}
    	else
    	{
        	if(name_compare(head->index_ptr,nptr)==0)
        	{
            	mid_ptr = head;
        	}
        	else
        	{
            	mid_ptr = NULL;
        	}
        }
    }
    else
    {
    	mid_ptr=NULL;
	}
    return mid_ptr;
}

// Qf-->deleting a given record and updating index LL

void delete_node_data_base(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr,Employee_record *result)
{
    // for updating record pointers
    int flag1=1,flag2=1,flag3=1;
    
    Employee_record *next_ptr,*prev_ptr,*traverse;
    
	index *prev_ind,*next_ind;
    if(result->prev==NULL)//first node to be deleted
    {
        *fpptr=(*fpptr)->next;
        if(result->next!=NULL)//not single node
        {
            (*fpptr)->prev=NULL;
        }
    }
    if(result->next==NULL)//last node to be deleted
    {
        *tpptr=(*tpptr)->prev;
        if(result->prev!=NULL)//not single node case
        {
            (*tpptr)->next=NULL;
        }
    }
    else
    {
        next_ptr=result->next;
        next_ptr->prev=result->prev;
        if(result->prev!=NULL)//not first node
        {
            prev_ptr=result->prev;
            prev_ptr->next=next_ptr;
        }
    }
    traverse=*fpptr;
    // updating pointers that are pointing to idtype records
    while(traverse!=NULL)
    {
        if(traverse->idtype==0)
        {
            if(flag1)
            {
                (*S0_pptr)=traverse;
                flag1=0;
            }
            (*E0_pptr)=traverse;
        }
        else if(traverse->idtype==1)
        {
            if(flag2)
            {
                (*S1_pptr)=traverse;
                flag2=0;
            }
            (*E1_pptr)=traverse;
        }
        else if(traverse->idtype)
        {
            if(flag3)
            {
                (*S2_pptr)=traverse;
                flag3=0;
            }
            (*E2_pptr)=traverse;
        }
        traverse=traverse->next;
    }
    // freeing the memory allocated to respective record
    delete_allocation(result);
    free(result);
}

void delete_node_index_list(index **s_i_pptr,index **l_i_pptr,index *search_ptr)
{
    
    index *prev_ind,*next_ind;
    search_ptr->index_ptr=NULL;
    // updating index LL after deletion
    if(search_ptr->prev==NULL)//first node to be deleted
    {
        *s_i_pptr=(*s_i_pptr)->next;
        if(search_ptr->next!=NULL)//not single node
        {
            (*s_i_pptr)->prev=NULL;
        }
    }
    if(search_ptr->next==NULL)//last node to be deleted
    {
        *l_i_pptr=(*l_i_pptr)->prev;
        if(search_ptr->prev!=NULL)//not single node case
        {
            (*l_i_pptr)->next=NULL;
        }
    }
    else
    {
        next_ind=search_ptr->next;
        next_ind->prev=search_ptr->prev;
        if(search_ptr->prev!=NULL)//not first node
        {
            prev_ind=search_ptr->prev;
            prev_ind->next=next_ind;
        }
    }
    free(search_ptr);
}

index* search_pointer_to_employee_record(index **s_i_pptr,index **l_i_pptr,Employee_record *result)
{
    index *ind_fptr,*ind_lptr;
    index *search_ptr=NULL;
    if(result!=NULL)
    {
    	// binary search for searching record for updating Linked List
    	ind_fptr=*s_i_pptr;
    	ind_lptr=*l_i_pptr;
    	search_ptr=search_name(ind_fptr,ind_lptr,result);
    }
    return search_ptr;
}

// to search record of a employee using idno
Employee_record* search_employee_record(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr,Employee_record *record_ptr)
{
    Employee_record *nptr=record_ptr;
    
    Employee_record *head=NULL,*tail=NULL;
    Employee_record *result=NULL;
    
    if(nptr->idtype==0)
    {
        head=*S0_pptr;
        tail=*E0_pptr;
    }
    else if(nptr->idtype==1)
    {
        head=*S1_pptr;
        tail=*E1_pptr;
    }
    else if(nptr->idtype==2)
    {
        head=*S2_pptr;
        tail=*E2_pptr;
    }

    // binary search for employee record
	result=search_idno(head,tail,nptr);
}

status_code deleteRecord(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr,index **s_i_pptr,index **l_i_pptr,Employee_record *record_ptr)
{
    status_code s = SUCCESS;
    Employee_record *result=search_employee_record(fpptr,tpptr,S0_pptr,E0_pptr,S1_pptr,E1_pptr,S2_pptr,E2_pptr,record_ptr);

    if(result!=NULL)
    {
        index *ind_search_ptr=search_pointer_to_employee_record(s_i_pptr,l_i_pptr,result);
        delete_node_data_base(fpptr,tpptr,S0_pptr,E0_pptr,S1_pptr,E1_pptr,S2_pptr,E2_pptr,result);
        delete_node_index_list(s_i_pptr,l_i_pptr,ind_search_ptr);
    }
    else
    {
        s=FAILURE;
    }
    return s;
}

void update_record_id(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr,index **s_i_pptr,index **l_i_pptr,index *search_ptr,Employee_record *result)
{
    Employee_record *ptr=(Employee_record*)malloc(sizeof(Employee_record));

    assign_null(ptr);

    strcpy(ptr->firstname,result->firstname);
    strcpy(ptr->lastname,result->lastname);
    strcpy(ptr->accommodation_type,result->accommodation_type);
    strcpy(ptr->address,result->address);
    ptr->next=NULL;
    ptr->prev=NULL;
	printf("Enter new id_type:");
	scanf("%d",&ptr->idtype);
	printf("Enter changed id");
	switch(ptr->idtype)
	{
		case 0:scanf(" %s",ptr->id.aadhaar);
			break;
		case 1:scanf(" %s",ptr->id.passport);
			break;
		case 2:scanf(" %s",ptr->id.empcode);
		    break;
    }
    search_ptr->index_ptr=ptr;
    delete_node_data_base(fpptr,tpptr,S0_pptr,E0_pptr,S1_pptr,E1_pptr,S2_pptr,E2_pptr,result);
    insert_record(fpptr,tpptr,S0_pptr,E0_pptr,S1_pptr,E1_pptr,S2_pptr,E2_pptr,ptr);
}

void update_index_linked_list(index **s_i_pptr,index **l_i_pptr, index *search_ptr,Employee_record *ptr)
{
    index *tptr,*prev_ind=NULL,*next_ind=NULL;

    int flag=1;
    int i=name_compare(search_ptr->index_ptr,ptr);
    Employee_record *emp_ptr=search_ptr->index_ptr;
    
    strcpy(emp_ptr->firstname,ptr->firstname);
    strcpy(emp_ptr->lastname,ptr->lastname);

    if((*s_i_pptr)->next!=NULL)
    {
        if(i!=0)
        {
            if(search_ptr->prev==NULL)
            {
            	if(i!=1)
            	{
            		*s_i_pptr=(*s_i_pptr)->next;	
				}
				else
				{
					flag=0;
				}
            }
            if(search_ptr->next==NULL)
            {
            	if(i!=-1)
            	{
                	*l_i_pptr=(*l_i_pptr)->prev;
                	(*l_i_pptr)->next=NULL;
                }
                else
                {
                	flag=0;
				}
            }
            else
            {
                next_ind=search_ptr->next;
                next_ind->prev=search_ptr->prev;
                if(search_ptr->prev!=NULL)
                {
                    prev_ind=search_ptr->prev;
                    prev_ind->next=next_ind;
                }
            }
            if(flag)
            {
            	search_ptr->prev=NULL;
            	search_ptr->next=NULL;
            	*s_i_pptr=merge_name(search_ptr,*s_i_pptr);
            	tptr=*s_i_pptr;
    			while(tptr->next!=NULL)
    			{
        			tptr=tptr->next;
    			}
    			*l_i_pptr=tptr;
    		}
    	}
    }
}

void updateRecord(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr,index **s_i_pptr,index **l_i_pptr,Employee_record *record_ptr)
{
    Employee_record *ptr=(Employee_record*)malloc(sizeof(Employee_record));

    Employee_record *result=search_employee_record(fpptr,tpptr,S0_pptr,E0_pptr,S1_pptr,E1_pptr,S2_pptr,E2_pptr,record_ptr);

    index *search_ptr=NULL;

    int field_type,flag=0;

    if(result!=NULL)
    {
    	search_ptr=search_pointer_to_employee_record(s_i_pptr,l_i_pptr,result);
    	
		printf("Enter the field to be changed:");
		printf("\n0-name\n1-idtype\n2-Address\n");
		scanf("%d",&field_type);
		switch(field_type)
		{
			case 0:
				printf("Enter firstname:");
				scanf(" %s",ptr->firstname);
				printf("Enter  lastname:");
				scanf(" %s",ptr->lastname);
                flag=1;
				break;
			case 1:
				update_record_id(fpptr,tpptr,S0_pptr,E0_pptr,S1_pptr,E1_pptr,S2_pptr,E2_pptr,s_i_pptr,l_i_pptr,search_ptr,result);
                result=NULL;
				break;
			case 2:
				printf("Enter new address:");
				scanf("\n%[^\n]%*c",result->address);
				break;
			default :printf("You have selected wrong option");
				break;
		}
		if(flag)
		{
			update_index_linked_list(s_i_pptr,l_i_pptr,search_ptr,ptr);
		}
	}
	else
	{
		printf("No record found regarding the entered data");
	}

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
status_code specialRequestAllocation(Employee_record **fpptr,Employee_record **tpptr,Employee_record **S0_pptr,Employee_record **E0_pptr,Employee_record **S1_pptr,Employee_record **E1_pptr,Employee_record **S2_pptr,Employee_record **E2_pptr)
{
    Employee_record *record_ptr = input_record();
    Employee_record *result=search_employee_record(fpptr,tpptr,S0_pptr,E0_pptr,S1_pptr,E1_pptr,S2_pptr,E2_pptr,record_ptr);
	status_code s=SUCCESS;
	if(result!=NULL)
	{
        char acc_type_request[20];
        printf("Enter new accomodation type:");
        scanf(" %s",acc_type_request);
        int i,flag=1;
        if(acc_type_request[7]=='I')
	    {
	    	i=2;
	    }
	    else if(acc_type_request[6]=='I')
	    {
	    	i=1;
	    }
	    else if(acc_type_request[5]=='I')
	    {
	    	i=0;
	    }
	    else if(acc_type_request[6]=='V')
	    {
	    	i=3;
	    }
        switch(i)
	    {
	    	case 0:
	    		if(!type1->a)
                {
                    type1->a=YES;
                    if(type1->next!=NULL)
                    {
                        type1=type1->next;
                    }
                    flag=0;
                }
                break;
	    	case 1:
	    		if(!type2->a&&flag)
                {
                    type2->a=YES;
                    if(type2->next!=NULL)
                    {
                        type2=type2->next;
                    }
                    flag=0;
                }
                break;
	    	case 2:
	    		if(!type3->a&&flag)
                {
                    type3->a=YES;
                    if(type3->next!=NULL)
                    {
                        type3=type3->next;
                    }
                    flag=0;
                }
                break;
	    	case 3:
                if(!type4->a&&flag)
                {
                    type4->a=YES;
                    if(type4->next!=NULL)
                    {
                        type4=type4->next;
                    }
                    flag=0;
                }
                break;
        }
        if(!flag)
        {
            strcpy(result->accommodation_type,acc_type_request);
        }
        else
        {
            s=FAILURE;
        }
    }
    else
    {
        printf("No record found of given employee\n");
        s=FAILURE;
    }
    return s;
}

int main()
{
    status_code s;
	Employee_record *first_ptr = NULL ;
	Employee_record *traverse_ptr = NULL ; //pointer to traverse the Employee record

    Employee_record *record_ptr=NULL; // for pointing a record created in heap
	

    Employee_record *start_ptr_id0 = NULL ; // to point to the start of the Employee record whose idtype is 0
	Employee_record *start_ptr_id1 = NULL ; // to point to the start of the Employee record whose idtype is 1
	Employee_record *start_ptr_id2 = NULL ; // to point to the start of the Employee record whose idtype is 2

    Employee_record *end_ptr_id0 = NULL ; // to point to the end of the Employee record whose idtype is 0
	Employee_record *end_ptr_id1 = NULL ; // to point to the end of the Employee record whose idtype is 1
	Employee_record *end_ptr_id2 = NULL ; // to point to the end of the Employee record whose idtype is 2
    
    create_node_acc_type(); // for creating nodes of type accomodation type
    // for index linked list
    index *start_index=NULL,*last_index=NULL;

    int field_type=1;
    printf("Insert atleast one record to the data base\nPlease select once option 4 before going to options above 4 to create index linked list\n");
    while(field_type)
    {
		switch(field_type)
		{
			case 1:
                record_ptr=create_record();
        	    insert_record(&first_ptr,&traverse_ptr,&start_ptr_id0,&end_ptr_id0,&start_ptr_id1,&end_ptr_id1,&start_ptr_id2,&end_ptr_id2,record_ptr);
				break;
			case 2:
                //Qb-->remove_duplicates
                remove_duplicates(&first_ptr,&traverse_ptr,&start_ptr_id0,&end_ptr_id0,&start_ptr_id1,&end_ptr_id1,&start_ptr_id2,&end_ptr_id2);
				break;
			case 3:
                //Qc-->print records
				printRecords(first_ptr);
				break;
            case 4:
                // Qd-->create index linked list
				create_index(first_ptr,&start_index,&last_index);
                printSortedRecords(start_index);
				break;
            case 5:
				// Qe-->search for given record
                search(start_index);
				break;
            case 6:
				// Qf-->deletion of given record
                record_ptr = input_record();
                s=deleteRecord(&first_ptr,&traverse_ptr,&start_ptr_id0,&end_ptr_id0,&start_ptr_id1,&end_ptr_id1,&start_ptr_id2,&end_ptr_id2,&start_index,&last_index,record_ptr);

                if(s==0)
                {
                    printf("No record found for given data\n");
                }
                else
                {
                    printf("Deletion successful\n");
                }
				break;
            case 7:
                // Qg-->update of given record
                record_ptr = input_record();
                updateRecord(&first_ptr,&traverse_ptr,&start_ptr_id0,&end_ptr_id0,&start_ptr_id1,&end_ptr_id1,&start_ptr_id2,&end_ptr_id2,&start_index,&last_index,record_ptr);
                printSortedRecords(start_index);
				break;
            case 8:
				// Qh-->
                specialRequestAllocation(&first_ptr,&traverse_ptr,&start_ptr_id0,&end_ptr_id0,&start_ptr_id1,&end_ptr_id1,&start_ptr_id2,&end_ptr_id2);
				 if(s==0)
                {
                    printf("Allocation successful\n");
                }
                else
                {
                    printf("Allocation failed no block found\n");
                }
                break;
			default :printf("You have selected wrong option");
				break;
		}
        printf("Select one option of the following:");
		printf("\n0-To quit\n1->Insert new record\n2->removeDuplicates\n3->printrecord\n4->printsortedrecords\n5->searchrecord\n6->deleterecord\n7->updaterecord\n8->specialrequestallocation\n");
		scanf("%d",&field_type);
	}
	return 0;
}

