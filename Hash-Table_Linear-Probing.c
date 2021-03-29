#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    char name[20+1];
    struct Node *next;
} *head[26];

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
    for(int i=0; i<26; i++){
        if(head[index] == NULL){ //pushFirst
            head[index] = new_node;
            new_node->next = NULL;
            return;
        }
        else{//bukan push pertama kali
            index = (index+1) % 26;
        }
    }
    puts("Hash Table sudah penuh!");
}

void visualize(){
    for(int i=0; i<26; i++){
        // printf("%d\n", i);
        if(head[i] == NULL){
            printf("%d. NULL\n", i);
            continue;
        }
        else{
            printf("%d. %s\n", i, head[i]->name);
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
