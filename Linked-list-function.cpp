#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    float ipk;
    char name[50+1];
    struct Node *next;
} *head, *tail;

void insert(float ipk, char name[]){
    struct Node *new_node = (struct Node *) malloc(sizeof(Node));// Deklarasi

    //Inisialisasi
    (*new_node).ipk = ipk; //new_node->ipk = ipk;
    strcpy((*new_node).name, name);
    (*new_node).next = NULL;

    //Masukin ke linked list
    if(head == NULL){
        head = tail = new_node;
    }
    else if(tail != NULL){
        (*tail).next = new_node;
        tail = new_node; //tail = (*tail).next;
    }
}

void print(){
    struct Node *current = (struct Node *) malloc(sizeof(Node));
    current = head;
    while(current != NULL){
        printf("%s --> ", (*current).name);
        current = (*current).next;
    }
    printf("NULL\n\n");
}

int main(){
    for(;;){
        int temp_ipk;
        char temp_name[50+1];
        printf("Isi ipk: ");
        scanf("%f", &temp_ipk);
        getchar();

        printf("Isi nama: ");
        scanf("%[^\n]", temp_name);
        getchar();

        insert(temp_ipk, temp_name);
        print();
    }
    return 0;
}