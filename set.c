//Ordered Set

#include<stdio.h>
#include<stdlib.h>

//declaration of node
struct node{
    int data;
    struct node* next;
};

typedef struct node node;

//declaration of set list				
struct s_list{
	node** list;
	size_t used;
	size_t size;
}set_list;

//set functions
int isempty(node *);
void insert(int, node **);
void delete_node(int, node **);
int is_present(int,node *);
void display_set(node *);
void set(node **);

//setlist functions
void init_list();
void add_set();
void remove_set(int);
void display_list();
void edit_set(int);

int main(){
	int choice=1,size,*array,data,n;
	system("clear");
	while(choice){
		printf("\n\n Enter Choice\n\n 1. Add set\n 2. Delete Set.\n 3. Edit set\n 4. Display list of sets.\n 5. Exit\n\n : ");
		scanf("%d",&choice);
		switch(choice){
			case 1: 
				add_set();
				break;
			case 2:
				printf("\n Enter the position of set: ");
				scanf("%d",&n);
				remove_set(n);
				break;
			case 3: 
				printf("\n Enter the position of set: ");
				scanf("%d",&n);
				edit_set(n);
				break;
				
			case 4:
				display_list();
				printf("\n\nPress Enter to contiue. ");
				getchar();
				getchar();
				break;
			case 5: 
				choice=0;
			default:
				break;
		}
		system("clear");
	}
}

//function definitions

node* create_node(int data){
	node* temp = (node *)malloc(sizeof(node));
	temp->data=data;
	temp->next=NULL;
	if(temp)
		return temp;
	else
		return NULL;
}

int is_present(int data, node* temp){
	while(temp){
		if(temp->data==data){
			return 1;
		}
		temp=temp->next;
	}
	return 0;
}

node* new_set(int *data,int size){
	node *start,*prev;
	start=create_node(data[0]);
	prev=start;
	for(int i=1;i<size;i++){
		if(!is_present(data[i],start)){
			insert(data[i],&start);
		}
	}
	return start;	
}

int isempty(node *start){
    return start==NULL;
}

void insert(int data, node** start){
	if(!is_present(data, *start)){
	node* temp = create_node(data);
	if(temp!=NULL){	
		node* temp1 = *start,*prev = NULL;
		while(temp1!= NULL && data>temp1->data){
				prev=temp1;
				temp1=temp1->next;
		}
		if(prev){
		temp->next=prev->next;
		prev->next=temp;}else{
			temp->next=*start;
			*start=temp;
		}
	}else
		printf("\nError: Stack Overflow");
	}
}

void delete_node(int data,node** start){
	node* temp = *start,*prev;
	if(!isempty(*start)){
	while(temp->data<data){
		prev = temp;
		temp = temp->next;
	}
	if(temp!=NULL && temp->data==data && temp!=*start){
		prev->next=temp->next;
		free(temp);
	}else if(temp==*start){
		*start=temp->next;
		free(temp);
	}else{
		printf("\n	Error: %d not found in set",data);
	}
	}else{
		printf("\n Error: Set not found.");
	}

}

void display_set(node* temp){
	if(!isempty(temp)){
    printf(" set{");
	while(temp){
        printf("\t%d",temp->data);
		if(temp->next!=NULL){
			printf(",");
		}
        temp=temp->next;
    }
	printf("}");
	}else{
		printf("Set not defined.");
	}
}

void set(node **start){
	int choice=1,size,*array,data;
	while(choice){
		system("clear");
		printf(" Current Set: ");
		display_set(*start);
		printf("\n\n Enter Choice\n\n 1. Create/Reset set\n 2. Insert an element.\n 3. Delete an element.\n 4. Display set\n 5. Go to set list.\n");
		printf("\n Enter Choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter the number of elements.");
				scanf("%d",&size);
				array=(int *)malloc(sizeof(int)*size);
				printf("Enter the elements: ");
				for(int i=0;i<size;i++){
					scanf("%d",&array[i]);
				}
				*start=new_set(array,size);
				break;
			case 2:
				printf("Enter the element to be inserted: ");
				scanf("%d",&data);
				insert(data,start);
				break;
			case 3:
				printf("Enter the element to be deleted: ");
				scanf("%d",&data);
				delete_node(data,start);
				break;
			case 4:
				display_set(*start);
				printf("\n\nPress Enter to contiue. ");
				getchar();
				getchar();
				break;
			case 5:
				choice=0;
				break;
			default:
				break;
		}
	}
}

void init_list(){
	set_list.list=(node **)malloc(sizeof(node**));
	set_list.size=1;
	set_list.used=1;
	set(&set_list.list[0]);	
}
void add_set(){
	if(set_list.size==0){
		init_list();
	}else{
	if(set_list.used==set_list.size){
	set_list.list=(node **)realloc(set_list.list,(set_list.size+1)*sizeof(node**));
	set_list.size+=1;
	set(&set_list.list[set_list.size-1]);
	}else{
		set(&set_list.list[set_list.used]);
	}
	set_list.used+=1;
	}
}
void remove_set(int n){
	if(n>0 && n<=set_list.used){
	node *prev,*next,*set_=set_list.list[n];
	next=set_;
	while(next!=NULL){
		prev=next;
		next=next->next;
		free(prev);
	}
	for(int i=0;i<set_list.size;i++){
		if(i>=n-1){
			set_list.list[i]=set_list.list[i+1];
		}
	}
	set_list.used-=1;
	}else{
		printf("Error: Set not found");
	}
}
void display_list(){
	for(int i=0;i<set_list.used;i++){
		display_set(set_list.list[i]);
		printf("\n");
	}
}
void edit_set(int n){
	if(n>0 && set_list.used>=n)
		set(&set_list.list[n-1]);
	else
		printf("&Error: Set not found");
}