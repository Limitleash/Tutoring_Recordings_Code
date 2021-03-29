#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    char name[20+1];
    struct Node *next;
} *head[26], *tail[26];

int hash_function(char temp_name[]){
    if(temp_name[0] >= 'a' && temp_name[0] <= 'z'){
        temp_name[0] = temp_name[0] - 'a' + 'A'; //buat jadi huruf kapital awalannya
        // c - a = 2 >> 2 + A = C
    }
    int index_num = temp_name[0] - 'A'; // C - A = 2
    return index_num % 26;
}

void create_node(char temp_name[]){
    struct Node *new_node = (struct Node *) malloc(sizeof(sizeof(struct Node)));
    int index = hash_function(temp_name);
    strcpy(new_node->name, temp_name);
    // strcpy((*new_node).name, temp_name);
    if(head[index] == NULL){ //pushFirst
        head[index] = tail[index] = new_node;
        new_node->next = NULL;
    }
    else{//bukan push pertama kali
        if(strcmp(temp_name, head[index]->name) < 0){
            
            //pushHead
            //(head) cici
            //caca -> cici (head)
            new_node->next = head[index];

            //caca (head) -> cici
            head[index] = new_node;

        }
        else if(strcmp(temp_name, tail[index]->name) > 0){
            //pushTail
            //(tail) cece
            //(tail) cece --> coco
            tail[index]->next = new_node;

            //cece --> coco (tail)
            tail[index] = new_node;
            new_node->next = NULL;
        }
        else{
            //pushMid
            struct Node *before_node = (struct Node *) malloc(sizeof(struct Node));
            before_node = head[index];
            struct Node *after_node = (struct Node *) malloc(sizeof(struct Node));
            after_node = before_node->next;

            //(Node sebelum) cici --> coco (Node sesudah)
            while(after_node != NULL){
				if(strcmp((*new_node).name, (*after_node).name) < 0){
					break;
                }
                before_node = after_node;
                after_node = after_node->next;
            }

            // caca -->  (Node sebelum)  cici --> (Node sesudah) coco <-- cece
            new_node->next = after_node;

            //(Node sebelum) cici --> cece -->  coco (Node sesudah) 
            before_node->next = new_node;
        }
    }
}

void visualize(){
    for(int i=0; i<26; i++){
        // printf("%d\n", i);
        if(head[i] == NULL){
            printf("%d. NULL\n", i);
            continue;
        }
        else{
            struct Node *current = (struct Node *) malloc(sizeof(struct Node));
            current = head[i];
            printf("%d. ", i);
            while(current != NULL){
                printf("%s --> ", current->name);
                // printf("test1\n");
                current = current->next;
                // printf("test2\n");
            }
            // printf("test 3\n");
            printf("NULL\n");
        }
    }
}

int main(){
    visualize();
    for(;;){//endless loop
        char temp_name[20+1];
        scanf("%[^\n]",temp_name); getchar();
        create_node(temp_name);
        visualize();
    }
    return 0;
}

/*
Linear Probing
Chaining
*/

/*
Hash Function --> Buat nentuin akan ditaruh di linked list yang mana

Linear Probing
- (head)-->Jessica
- (head)-->Felicia
- (head)-->Marco
- (head)-->Jesslyn
- (head)-->Noufal
- (head)-->VJ


Linked List biasa
- (head) Jesslyn --> VJ --> Noufal --> Jessica --> Fellcia --> Marco (tail)


Chaining
0 (head)-->
1 (head)-->
2 (head) --> Caca --> Cici --> Cucu --> Cece
3 (head)--> 
4 (head)-->
5 (head)-->
6 (head)-->
7 (head)-->
8 (head)-->
9 (head)-->
10 (head)-->
11 (head)-->
12 (head)-->
13 (head)-->
14 (head)-->
15 (head)-->
16 (head)-->
17 (head)-->
18 (head)-->
19 (head)-->
20 (head)-->
21 (head)-->
22 (head)-->
23 (head)-->
24 (head)-->
25 (head)-->

head --> NULL, tail-->NULL
*/