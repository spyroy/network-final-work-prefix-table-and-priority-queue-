#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXC 256

struct process{
	int slack;
	int value;
	int amount;
	int time;
};

int compare_ints(const struct process* a, const struct process* b)
{
    if (a->slack < b->slack) return -1;
    if (a->slack > b->slack) return 1;
    return 0;
 
}

int main(int argc, char** argv){
    	char*  line = NULL;
    	size_t len = 0;
    	ssize_t read;
	int* values [MAXC];
	int t =1;
	int nval=0;
	int index = 0;
	int readDigits = 0;
	int i;
	int j = 0;
	int numOfProcess = 0;
	struct process processes [MAXC];

	if(argc != 3){
		fprintf (stderr, "error: incorect number of arguments" );
	}

    	FILE *fp = argc > 1 ? fopen (argv[2], "r") : stdin;
    	if (!fp) { 
        	fprintf (stderr, "error: file open failed '%s'.\n", argv[1]);
        	return 1;
    	}

	printf("input:\n");
    	while ((read = getline(&line, &len, fp)) != -1) {
		int val;
		printf("%s",line);
		while(index < read){
			if(line[index] <= '9' && line[index] >= '0'){
				if(sscanf(line + index, "%d%n", values + nval, &readDigits) == 1){
					index += readDigits;
					nval++;
            			}	
			}	
			index++;
    		}
		if(nval%3 != 0)
			fprintf (stderr, "invalid number of values");		
		
		for(i = 0; i < nval; i=i+3){
			processes[j].amount = values[i];
			processes[j].slack = values[i+1];
			processes[j].value = values[i+2];
			processes[j].time = t;
			j++;
			numOfProcess++;
		}
		t++;
		index = 0;
		nval =0;
	}

    	if (fp != stdin) fclose (fp);
	printf("procesess:\n");
	for(i =0; i < numOfProcess; i++){
		printf("amount - %d slack - %d value - %d time - %d \n",processes[i].amount,processes[i].slack,processes[i].value,processes[i].time);
	}
	t = processes[numOfProcess-1].time;
	printf("\ntime units: %d\n\n",t);
	printf("starting transimission... \n\n");
	int SizeOfQueue = atoi(argv[1]);
	int amount;
	int k;
	int l;
	bool full = false;
	int out = 0;
	int total_value=0;
	bool isZero = false;
	int total_process=0;
	struct process queue [SizeOfQueue];
	for(i = 0; i < SizeOfQueue; i++){
		queue[i].slack = 0;
		queue[i].value = 0;
		queue[i].amount = 0;
		queue[i].time = 0;
	}
	for(i=1; i<= t; i++){
		int current= 0;
		for(j=0; j< numOfProcess; j++){
			if(processes[j].time == i){
				current++;
			}
		}
		struct process pqueue [current];
		int x = 0;
		for(j=0; j< SizeOfQueue; j++){
			if(processes[j].time == i){
				pqueue[x].slack = processes[j].slack;
				pqueue[x].value = processes[j].value;
				pqueue[x].amount = processes[j].amount;
				pqueue[x].time = processes[j].time;	
				x++;
			}
		}
		for(j=0; j < current; j++){
			for(amount = 0; amount < pqueue[j].amount; amount++){
				for(k = 0; k < SizeOfQueue; k++){
					qsort(queue, SizeOfQueue, sizeof(struct process), compare_ints);
					// if queue is not full accept process
					if(queue[k].slack == 0){
						queue[k].slack = pqueue[j].slack;
						queue[k].value = pqueue[j].value;
						queue[k].amount = 1;
						queue[k].time = i;
						for(l=0; l < SizeOfQueue; l++){
							if(queue[l].slack == 0) {
								full=false;
								break;
							}
							full = true;
						}
						break;
					}
					// if the queue is full and the current process has 
					// greater slack than drop the process with smallest slack
					else if(full && pqueue[j].slack > queue[k].slack){ // queue[0].slack
						queue[k].slack = pqueue[j].slack;
						queue[k].value = pqueue[j].value;
						queue[k].amount = 1;
						queue[k].time = i;
						out++;
						printf("process dropped\n\n");
						break;
					}
					// if the queue is full and the current process does not
					// have greater slack from every other procesess than the
					// current process droped
					else if(full){
						out++;
						printf("process dropped\n\n");
						break;
					}
				}
			}
			// all procesess with same time added to the queue
			if(j == current-1){	
				qsort(queue, SizeOfQueue, sizeof(struct process), compare_ints);
				for(k = 0; k<SizeOfQueue; k++){
					queue[k].slack--;
				}
				for(k=0;k<SizeOfQueue;k++){
					if(queue[k].slack == 0){
						out++;
						printf("process dropped\n\n");
						continue;
					}
					else{
						total_value+=queue[k].value;
						printf("%d added to total value\n\n",queue[k].value);
						queue[k].slack = 0;
						queue[k].value = 0;
						queue[k].amount = 0;
						queue[k].time = 0;
						total_process++;
						break;
					}				
				}
			}
		}
		// last process entered
		if(i == t){
			qsort(queue, SizeOfQueue, sizeof(struct process), compare_ints);
			for(j = 0; j < SizeOfQueue; j++){
				if(queue[j].slack != 0){	
					isZero = false;
					break;
				}
				isZero = true;
			}
			if(isZero){
				break;
			}
			for(j = 1; j < SizeOfQueue; j++){
				for(k = j; k<SizeOfQueue; k++){
					queue[k].slack--;
				}
				for(k=j;k<SizeOfQueue;k++){
					if(queue[k].slack == 0){
						out++;
						j++;
						printf("process dropped\n\n");
						continue;
					}
					else{
						total_value+=queue[k].value;
						printf("%d added to total value\n\n",queue[k].value);
						queue[k].slack = 0;
						queue[k].value = 0;
						queue[k].amount = 0;
						queue[k].time = 0;
						total_process++;
						break;
					}
				}
			}
		}
	}	
	printf("\ntotal arrived processes - %d, total dropped processes - %d,\ntotal transmited processes - %d, total transimitted value - %d.\n",total_process,out,total_process + out,total_value);			
	return 0;
}
