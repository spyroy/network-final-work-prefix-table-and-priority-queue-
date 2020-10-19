#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>



static int total_nodes = 0;
struct node  
{ 
    	int data; 
	char action;
	int total_nodes;
	struct node *father;
    	struct node *zero; 
    	struct node *one; 
}; 

struct node *newNode(int data, char act) 
{ 
    	struct node *temp =  (struct node *)malloc(sizeof(struct node)); 
    	temp->data = data; 
    	temp->zero = temp->one = NULL;
	temp->action = act;
	temp->total_nodes = 1;
	temp->father = NULL;
	
    	return temp; 
} 

struct node* insert(struct node* node, int* key, char act, int mask,int* tmp) 
{ 
	int i;
	struct node *temp =  (struct node *)malloc(sizeof(struct node));
	temp = node;
	for(i = 0; i< mask; i++){
		if(key[i] == 1 && i != mask-1){
			if(temp->one == NULL){
				temp->one = newNode(key[i], ' ');
				struct node *father = temp;
				temp = temp->one;
				temp->father = father;
				//printf("1 added ");
				total_nodes++;
				continue;
			}
			else{
				temp = temp->one;
				continue;
			}
		}
		if(key[i] == 0 && i != mask-1){
			if(temp->zero == NULL){
				temp->zero = newNode(key[i], ' ');
				struct node *father = temp;
				temp = temp->zero;
				temp->father = father;
				//printf("0 added ");
				total_nodes++;
				continue;
			}
			else{
				temp = temp->zero;
				continue;
			}
		}
		if(i == mask-1){
			if(key[i] == 1){
				if(temp->one == NULL){
					temp->one = newNode(key[i], act);
					struct node *father = temp;
					temp = temp->one;
					temp->father = father;
					//printf("1 added and %c is the action ", act);
					total_nodes++;
				}
				else{
					temp->one->action = act;
					temp = temp->one;
				}
			}
			if(key[i] == 0){
				if(temp->zero == NULL){
					temp->zero = newNode(key[i], act);
					struct node *father = temp;
					temp = temp->zero;
					temp->father = father;
					//printf("0 added and %c is the action ", act);
					total_nodes++;
				}
				else{
					temp->zero->action = act;
					temp = temp->zero;
				}
			}
		}
	}
	printf("Added %d.%d.%d.%d/%d %c at depth %d, total nodes  %d",tmp[0],tmp[1],tmp[2],tmp[3],mask,act,mask,total_nodes);
	return node;
}



struct node* find(struct node** node,int* key,int* tmp,int index){
	if((*node)->one != NULL && key[index] == 1){
		index++;
		return find(&((*node)->one),key,tmp,index);
	}
	if((*node)->zero != NULL && key[index] == 0){
		index++;
		return find(&((*node)->zero),key,tmp,index);
	}
	if((*node) != NULL && (*node)->action != ' '){
		printf("found ip: ");
		printf("%d.%d.%d.%d ",tmp[0],tmp[1],tmp[2],tmp[3]);
		printf(" %c ",(*node)->action);
		printf("at depth: %d ",index);
		return *node;
	}
	while((*node) != NULL && (*node)->action == ' ' ){
		if((*node)->data == 999){
			printf("no action found on prefix ");
			return *node;;
		}
		struct node* father = (*node)->father;
		node = &father;
		index--;
	}
		printf("found ip: ");
		printf("%d.%d.%d.%d ",tmp[0],tmp[1],tmp[2],tmp[3]);
		printf(" %c ",(*node)->action);
		printf("at depth: %d ",index);
		return *node;
}

struct node* delete(struct node** node,int* key,int* tmp,int index,int mask,char act){
	if((*node)->one != NULL && key[index] == 1 && index < mask){
		//printf("in ");
		index++;
		return delete(&((*node)->one),key,tmp,index,mask,act);
	}
	if((*node)->zero != NULL && key[index] == 0 && index < mask){
		//printf("out ");
		index++;
		return delete(&((*node)->zero),key,tmp,index,mask,act);
	}
	if((*node) != NULL && (*node)->action == act && index == mask){
		printf("removed ");
		printf("%d.%d.%d.%d/%d %c ",tmp[0],tmp[1],tmp[2],tmp[3],mask,(*node)->action);
		printf("at depth: %d, ",index);
		(*node)->action = ' ';
		//return *node;
	}
	while((*node) != NULL && (*node)->one == NULL &&  (*node)->zero == NULL && (*node)->action == ' ' && (*node)->data != 999){
		//printf("delete ");
		int data = (*node)->data;
		struct node* father = (*node)->father;
		node = &father;
		if(data == 1 && (*node)->one != NULL){
			free((*node)->one);
			(*node)->one = NULL;
			total_nodes--;
		}
		if(data == 0 && (*node)->zero != NULL){
			free((*node)->zero);
			(*node)->zero = NULL;
			total_nodes--;
		}
		index--;
	}
	printf("total nodes %d ",total_nodes);	
	return *node;
}

void print_tree(struct node* root){
	if (root == NULL) 
          return; 
  
     	print_tree(root->zero); 
	
	if(root->data != 999){  
     		printf("%d ", root->data);
		if(root->action != ' ')
			printf("*%c ",root->action);
	}   
  
     	print_tree(root->one); 
}	
			
   

int main(int argc, char** argv){
	printf("\n");
	if(argc != 2){
		fprintf (stderr, "error: incorect number of arguments" );
	}

	FILE *fp = fopen (argv[1], "r");
    	if (!fp) { 
        	fprintf (stderr, "error: file open failed '%s'.\n", argv[1]);
        	return 1;
    	}

	char*  line = NULL;
	size_t len = 0;
	ssize_t read;
	
	int i,k;
	int j = 7;
	char command [6];
	int nums [4] = {0};
	int mask = 0;
	char action;
	int binary [32] = {0};
	int binaryf [32] = {0};
	int count = 0;
	struct node* root = newNode(999,' ');
	while ((read = getline(&line, &len, fp)) != -1) {
		int scan;
		printf("COMMAND %s",line);
		scan = sscanf(line,"%s %d.%d.%d.%d/%d %c",command,&nums[0],&nums[1],&nums[2],&nums[3],&mask,&action);
		//printf("%s %d %d %d %d %d %c \n",command,nums[0],nums[1],nums[2],nums[3],mask,action);
		int tmp [4];
		tmp[0] = nums[0];
		tmp[1] = nums[1];
		tmp[2] = nums[2];
		tmp[3] = nums[3];
		if(scan >= 5 && scan <= 7){
			for(i = 0; i < 4; i++){
				while(nums[i] > 0){
					binary[j] = nums[i]%2;
					nums[i] = nums[i]/2;
					count++;
					j--;
				}
				j= j+8+count;
				count = 0;
			}
			j = 7;
			
			if(strcmp(command, "ADD")==0){
				root = insert(root,binary,action,mask,tmp);
			}
			else if(strcmp(command, "FIND")==0){
				find(&root,binary,tmp,0);
			}
			else if(strcmp(command, "REMOVE")==0){
				delete(&root,binary,tmp,0,mask,action);
			}			 
			for(i = 0; i < 32; i++){
				//printf(" %d",binary[i]);
				binary[i] = 0;
			}
			printf("\n");
		}
		mask = 0;
		action = ' ';
	}
	//print_tree(root);
	free(root);
	printf("\n");
	

	return 0;
}
	
