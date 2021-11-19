#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include  <bits/stdc++.h>
//TODO: сделать джоин правильно и потом гонять прогу через тесты
class Node {
    public:
    int priority;
    const char* work;
    Node *next;
};
class Node_N{
    public:
    const char* name;
    const char* work;
    Node_N *next;
};

class Args{
    public:
    char* name;
    char* job;
};

int count = 0;
int countA = 1;     //controla vystupu v rutine 
int countB = 1;     //controla vystupu v rutine 
int countC = 1;     //controla vystupu v rutine 

int count_requestA = 0;
int count_requestB = 0;
int count_requestC = 0;

Node_N *LL = NULL;
int control = 0;
int controlA = 0;
int controlB = 0;
int controlC = 0;

Node *queue_A = NULL;
Node *queue_B = NULL;
Node *queue_C = NULL;


const char *arg;
pthread_mutex_t mutex;

pthread_cond_t work;
pthread_t worker;
pthread_t worker2;
pthread_t worker3;
pthread_t worker4;
pthread_t worker5;
pthread_t worker6;


void deleteList(Node* head_ref)
{
    Node* tmp;
 
    while (head_ref != NULL){
        tmp = head_ref;   
        head_ref = tmp->next;
        delete tmp;   
    }
}

void push(Node ** head_ref, int new_priority, const char* new_work){
    Node *new_node = new Node();

    new_node->priority = new_priority;
    //new_node->name = new_name;
    new_node->work = new_work;
    new_node->next =(* head_ref);
    (*head_ref) = new_node;
    
}
void push(Node_N ** head_ref, char* new_name, const char* new_work){
    Node_N *new_node = new Node_N();

    new_node->name = new_name;
    new_node->work = new_work;
    new_node->next =(* head_ref);
    (*head_ref) = new_node;
    
}

void swap(Node *a, Node *b){
    int temp = a->priority;
    const char *temp_work = a->work;
    a->priority = b->priority;
    a->work = b->work;
    b->priority = temp;
    b->work = temp_work;
}

void Sort(Node *start){
    int swapped;
    Node *ptr1;
    Node *lptr = NULL;
    if (start == NULL) return;
    do{
        swapped = 0;
        ptr1 = start;
        while(ptr1->next != lptr){
            if(ptr1->priority > ptr1->next->priority){
                swap(ptr1,ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }while(swapped);
}

void printList(Node *start){
    Node* temp = start;
    while(temp!=NULL){
        printf("%d:%s ",temp->priority,temp->work);
        temp = temp->next;
    }
    
}

Node *find(int priority, Node * queue){
    Node *curr = queue;
    if(queue == NULL){
        return NULL;
    }
    while(curr->priority != priority){
        if(curr->next == NULL){
            return NULL;
        }else{
            curr = curr->next;
        }
    }
    return curr;
}

void deleteNode(Node * nodeBefore){
    Node *temp;
    temp = nodeBefore->next;
    nodeBefore->next = temp->next;
    delete temp;
}
/* You can use these functions and data structures to transform strings to
 * numbers and use them in arrays
 */
enum place {
    NUZKY, VRTACKA, OHYBACKA, SVARECKA, LAKOVNA, SROUBOVAK, FREZA,
    _PLACE_COUNT
};

const char *place_str[_PLACE_COUNT] = {
    [NUZKY] = "nuzky",
    [VRTACKA] = "vrtacka",
    [OHYBACKA] = "ohybacka",
    [SVARECKA] = "svarecka",
    [LAKOVNA] = "lakovna",
    [SROUBOVAK] = "sroubovak",
    [FREZA] = "freza",
};

enum product {
    A, B, C,
    _PRODUCT_COUNT
};

const char *product_str[_PRODUCT_COUNT] = {
    [A] = "A",
    [B] = "B",
    [C] = "C",
};

int find_string_in_array(const char **array, int length, char *what)
{
    for (int i = 0; i < length; i++)
        if (strcmp(array[i], what) == 0)
            return i;
    return -1;
}

/* It is not necessary to represent each working place with a dynamically
 * allocated object.  You can store only number of ready places
 *
 * int ready_places[_PLACE_COUNT];
 */

/* It is not necessary to represent each part as a dynamically allocated
 * object.  you can have only number of parts for each working phase
 *
 * #define _PHASE_COUNT 6
 * int parts[_PRODUCT_COUNT][_PHASE_COUNT]
 */
 void *routine(void *arg){
    Args* args = (Args*)arg;
    
    Node *foundA = NULL;
    Node *foundB = NULL;
    Node *foundC = NULL;

    pthread_mutex_lock(&mutex);
    while(control == 0 ){
        pthread_cond_wait(&work, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    

    while (1){
        label:
        if(controlA == 1 ){
            foundA = find(countA, queue_A);
        }
        if(controlB == 1 ){
            foundB = find(countB, queue_B);
        }
        if (controlC == 1){
            foundC = find(countC, queue_C);
        }
        
        if(foundA != NULL && controlA != 0){
            if(strcmp(args->job, foundA->work) != 0 ){

                pthread_mutex_lock(&mutex);
                pthread_cond_wait(&work, &mutex);
                pthread_mutex_unlock(&mutex);
                
                goto label;
                
            }else{
                
                printf("%s %s %d A\n", args->name, foundA->work,countA);
                if (strcmp(foundA->work, "nuzky") == 0){
                    usleep(100000);
                }else if (strcmp(foundA->work, "vrtacka") == 0){
                    usleep(200000);
                }else if (strcmp(foundA->work, "ohybacka") == 0){
                    usleep(150000);
                }else if (strcmp(foundA->work, "svarecka") == 0){
                    usleep(300000);
                }else if (strcmp(foundA->work, "lakovna") == 0) {
                    usleep(400000);
                }else if (strcmp(foundA->work, "sroubovak") == 0) {
                    usleep(250000);
                }else if (strcmp(foundA->work, "freza") == 0) {
                    usleep(500000);
                }
                if (strcmp(foundA->work, "lakovna") == 0 && countA == 6){
                    printf("done A\n");
                    
                }
                
            }
            pthread_mutex_lock(&mutex);    
            countA+=1;
            pthread_cond_broadcast(&work);
            pthread_mutex_unlock(&mutex);
            
        }
        if(foundB != NULL && controlB != 0){
            if(strcmp(args->job, foundB->work) != 0 ){

                pthread_mutex_lock(&mutex);
                pthread_cond_wait(&work, &mutex);
                pthread_mutex_unlock(&mutex);
                
                goto label;
                
            }else{
                
                printf("%s %s %d B\n", args->name, foundB->work,countB);
                if (strcmp(foundB->work, "nuzky") == 0){
                    usleep(100000);
                }else if (strcmp(foundB->work, "vrtacka") == 0){
                    usleep(200000);
                }else if (strcmp(foundB->work, "ohybacka") == 0){
                    usleep(150000);
                }else if (strcmp(foundB->work, "svarecka") == 0){
                    usleep(300000);
                }else if (strcmp(foundB->work, "lakovna") == 0) {
                    usleep(400000);
                }else if (strcmp(foundB->work, "sroubovak") == 0) {
                    usleep(250000);
                }else if (strcmp(foundB->work, "freza") == 0) {
                    usleep(500000);
                }
                if(strcmp(foundB->work, "sroubovak") == 0 && countB == 6){
                    printf("done B\n");
                    
                }
            }
            pthread_mutex_lock(&mutex);    
            countB+=1;
            pthread_cond_broadcast(&work);
            pthread_mutex_unlock(&mutex);
            
        }
        if(foundC != NULL && controlC != 0){
            if(strcmp(args->job, foundC->work) != 0 ){

                pthread_mutex_lock(&mutex);
                pthread_cond_wait(&work, &mutex);
                pthread_mutex_unlock(&mutex);
                
                goto label;
                
            }else{
                printf("%s %s %d C\n", args->name, foundC->work,countC);
                if (strcmp(foundC->work, "nuzky") == 0){
                    usleep(100000);
                }else if (strcmp(foundC->work, "vrtacka") == 0){
                    usleep(200000);
                }else if (strcmp(foundC->work, "ohybacka") == 0){
                    usleep(150000);
                }else if (strcmp(foundC->work, "svarecka") == 0){
                    usleep(300000);
                }else if (strcmp(foundC->work, "lakovna") == 0) {
                    usleep(400000);
                }else if (strcmp(foundC->work, "sroubovak") == 0) {
                    usleep(250000);
                }else if (strcmp(foundC->work, "freza") == 0) {
                    usleep(500000);
                }
                if(strcmp(foundC->work, "lakovna") == 0 && countC == 6){
                    printf("done C\n");
                }
            }
            pthread_mutex_lock(&mutex);    
            countC+=1;
            pthread_cond_broadcast(&work);
            pthread_mutex_unlock(&mutex);
        }
        
        if(foundA == NULL && controlA != 0 && foundC == NULL && foundB == NULL && controlB == 0 && controlC == 0){
            printf("1");
            break;
        } // only A error input
        if(foundA == NULL && controlB != 0 && foundC == NULL && foundB == NULL && controlC == 0 && controlA == 0){
            printf("2");
            break;
        } // only B error input
        if(foundA == NULL && controlC != 0 && foundC == NULL && foundB == NULL && controlA == 0 && controlB == 0){
            printf("4");
            break;
        } // only C error input
        if (foundA == NULL && controlA != 0 && controlB != 0 && foundC == NULL && foundB == NULL && controlC == 0){
            printf("5");
            break;
        } // only A and B error input
        if (foundA == NULL && controlA != 0 && controlC != 0 && foundC == NULL && foundB == NULL && controlB == 0){
            printf("6");
            break;
        } // only A and C error input
        if(foundA == NULL && controlB != 0 && controlC != 0 && foundC == NULL && foundB == NULL && controlA == 0){
            printf("7");
            break;
        }// only B and C error input
        if(foundA == NULL && controlA != 0 && controlB != 0 && controlC != 0 && foundC == NULL && foundB == NULL){
            printf("8");
            break;
        } // all error input
        //TODO: сделать брейк когда все пожадавки сделаны а товар не закончен
        // if(countA == 7 && controlA != 0 && controlB == 0 && controlC == 0){ // make A
            // break;
        // }else if (countA == 7 && controlA != 0 && countB == 7 && controlB != 0 && controlC == 0){ //make A make B
            // break;
        // }else if (countA == 7 && controlA != 0 && countC == 7 && controlC != 0 && controlB == 0){ // make A make C
            // break;
        // }else if (countB == 7 && controlB != 0 && controlA == 0 && controlC == 0){ // make B
            // break;
        // }else if(countB == 7 && controlB != 0 && countC == 7 && controlC != 0 && controlA == 0){ // make B make C
            // break;
        // }else if (countC == 7 && controlC != 0 && controlA == 0 && controlB == 0){ // make C
            // break;
        // }
        
        //if(countA == 7 && countB == 7 && countC == 7){ // make A make B make C
        //    break;
        //}
        
    }

    delete args;
    return (void*) 0;
 }

int main(int argc, char **argv)
{
    /* Initialize your internal structures, mutexes and conddition variables.
     */
    //int count = 0;
    pthread_cond_init(&work, NULL);
    pthread_mutex_init(&mutex, NULL);

    while (1) {
        
        char *line, *cmd, *arg1, *arg2, *arg3, *saveptr;
        int s = scanf(" %m[^\n]", &line);
        if (s == EOF)
            break;
        if (s == 0)
            continue;

        cmd  = strtok_r(line, " ", &saveptr);
        arg1 = strtok_r(NULL, " ", &saveptr);
        arg2 = strtok_r(NULL, " ", &saveptr);
        arg3 = strtok_r(NULL, " ", &saveptr);

        if (strcmp(cmd, "start") == 0 && arg1 && arg2 && !arg3) {
            Args* argForWork = new Args();
            char *name = strdup(arg1);
            char *work = strdup(arg2);
            pthread_mutex_lock(&mutex);
            push(&LL,name,work);
            argForWork->name = name;
            argForWork->job = work;
            pthread_mutex_unlock(&mutex);
            if(count == 0){
                if(pthread_create(&worker, NULL, routine, argForWork) != 0){
                    fprintf(stderr, "failed to create in line %d\n",__LINE__);
                }
                count+=1;
            }else if (count == 1){
                if(pthread_create(&worker2, NULL, routine, argForWork) != 0){
                    fprintf(stderr, "failed to create in line %d\n",__LINE__);
                }
                count+=1;
            }else if (count == 2){
                if(pthread_create(&worker3, NULL, routine, argForWork) != 0){
                    fprintf(stderr, "failed to create in line %d\n",__LINE__);
                }
                count+=1;
            }else if (count == 3){
                if(pthread_create(&worker4, NULL, routine, argForWork) != 0){
                    fprintf(stderr, "failed to create in line %d\n",__LINE__);
                }
                count+=1;
            }else if (count == 4){
                if(pthread_create(&worker5, NULL, routine, argForWork) != 0){
                    fprintf(stderr, "failed to create in line %d\n",__LINE__);
                }
                count+=1;
            }else if (count == 5){
                if(pthread_create(&worker6, NULL, routine, argForWork) != 0){
                    fprintf(stderr, "failed to create in line %d\n",__LINE__);
                }
                count+=1;
            }
            //printf("NUMBER %lu\n", worker);
            
            /* - start new thread for new worker
             * - copy (e.g. strdup()) worker name from arg1, the
             *   arg1 will be removed at the end of scanf cycle
             * - workers should have dynamic objects, you don't know
             *   total number of workers
             */
             //pthread_join(worker,NULL);
             
        } else if (strcmp(cmd, "make") == 0 && arg1 && !arg2) {
            
            if (strcmp(arg1, "A") == 0){
                pthread_mutex_lock(&mutex);
                controlA = 1;
                control = 1;
                pthread_cond_broadcast(&work);
                pthread_mutex_unlock(&mutex);
            }else if(strcmp(arg1, "B") == 0){
                pthread_mutex_lock(&mutex);
                controlB = 1;
                control = 1;
                pthread_cond_broadcast(&work);
                pthread_mutex_unlock(&mutex);
            }else if(strcmp(arg1, "C") == 0){
                pthread_mutex_lock(&mutex);
                controlC = 1;
                control = 1;
                pthread_cond_broadcast(&work);
                pthread_mutex_unlock(&mutex);
            }
            //pthread_join(worker,NULL);
            /* int product = find_string_in_array(
             *     product_str,
             *     _PRODUCT_COUNT,
             *     arg1
             * );
             *
             * if (product >= 0) {.....
             *     add the part to factory cycle
             *     you need to wakeup worker to start working if possible
             *     ...
             *     }
             */
        } else if (strcmp(cmd, "end") == 0 && arg1 && !arg2) {
            /* tell the worker to finish
             * the worker has to finish their work first
             * you should not wait here for the worker to finish
             *
             * if the worker is waiting for work
             * you need to wakeup the worker
             */
        } else if (strcmp(cmd, "add") == 0 && arg1 && !arg2) {
            
            if(strcmp(arg1, "nuzky") == 0){
                arg = "nuzky";
                
                push(&queue_A,1,arg);
                push(&queue_B,2,arg);
            }else if (strcmp(arg1,"vrtacka") == 0){
                arg = "vrtacka";
                push(&queue_A,2,arg);
                push(&queue_A,5,arg);
                push(&queue_B,1,arg);
                push(&queue_B,4,arg);
                push(&queue_C,2,arg);
                push(&queue_C,4,arg);
            }else if (strcmp(arg1, "ohybacka") == 0){
                arg = "ohybacka";
                push(&queue_A,3,arg);
            }else if (strcmp(arg1, "svarecka") == 0){
                arg = "svarecka";
                push(&queue_A,4,arg);
            }else if(strcmp(arg1, "lakovna") == 0){
                arg = "lakovna";
                push(&queue_A,6,arg);
                push(&queue_B,5,arg);
                push(&queue_C,6,arg);
            }else if(strcmp(arg1 , "freza") == 0){
                arg = "freza";
                push(&queue_B,3,arg);
                push(&queue_C,1,arg);
                push(&queue_C,5,arg);
            }else if(strcmp(arg1 , "sroubovak") == 0){
                arg = "sroubovak";
                push(&queue_B,6,arg);
                push(&queue_C,3,arg);    
            }
            
            /* add new place
             *
             * if worker and part is ready, start working - wakeup worker
             */
            Sort(queue_A);
            Sort(queue_B);
            Sort(queue_C);
        } else if (strcmp(cmd, "remove") == 0 && arg1 && !arg2) {
            /* if you cannot remove empty place you cannot wait for finish
             * work
             */
        } else {
            fprintf(stderr, "Invalid command: %s\n", line);
        }
        
        free(line);
            
    }
    
    if (count == 6){
        pthread_join(worker,NULL);
        pthread_join(worker2,NULL);
        pthread_join(worker3,NULL);
        pthread_join(worker4,NULL);
        pthread_join(worker5,NULL);
        pthread_join(worker6,NULL);
    }else if (count == 5){
        pthread_join(worker,NULL);
        pthread_join(worker2,NULL);
        pthread_join(worker3,NULL);
        pthread_join(worker4,NULL);
        pthread_join(worker5,NULL);
    }else if (count == 4){
        pthread_join(worker,NULL);
        pthread_join(worker2,NULL);
        pthread_join(worker3,NULL);
        pthread_join(worker4,NULL);
    }else if (count == 3){
        pthread_join(worker,NULL);
        pthread_join(worker2,NULL);
        pthread_join(worker3,NULL);
    }else if (count == 2){
        pthread_join(worker,NULL);
        pthread_join(worker2,NULL);
    }else if (count == 1){
        pthread_join(worker,NULL);
    }
    
    
    

    pthread_cond_destroy(&work);
    pthread_mutex_destroy(&mutex);
    
    deleteList(queue_A);
    deleteList(queue_B);
    deleteList(queue_C);
      
    return 0;
}
