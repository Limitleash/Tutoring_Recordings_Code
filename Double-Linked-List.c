#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
	char id[4+1]; //4 karakter untuk ID, 1 untuk NULL (\0)
	struct Node *next, *previous; // A (Head) <--> B <--> C (Tail)
} *head, *tail;
//struct Node *head;
//struct Node *tail;

//struct Node variabel;
//variabel.id atau (&variabel)->id


/*Insert
1. Buat Node baru (deklarasi)
2. Kita masukin nilai/value-nya ke dalam node baru tersebut (inisialisasi)
3. Sambungin panahnya (next & previousnya)
*/

void insert_node(char temp_id[]){
	//1. Buat Node baru (deklarasi)
	struct Node *node_baru = (struct Node *) malloc(sizeof(struct Node));
	
	//2. Kita masukin nilai/value-nya ke dalam node baru tersebut (inisialisasi)
	strcpy((*node_baru).id, temp_id);
//	printf("%s\n", (*node_baru).id); //Untuk debug/checking
	
	//3. Sambungin panahnya (next & previousnya)
	if(head == NULL){ //pertama kali
		head = tail = node_baru; //Garbage value <- node_baru (head, tail) -> Garbage value
		(*node_baru).next = (*node_baru).previous = NULL; //NULL <- node_baru (head, tail) -> NULL
	}	
	else{ //bukan pertama kali
		if(strcmp((*node_baru).id, (*head).id) < 0){ //pushHead
			(*node_baru).next = head;// 1. node_baru -> A (head)
			(*head).previous = node_baru;// 2. node_baru <--> A (head)
			(*node_baru).previous = NULL;// 3. NULL <- node_baru <--> A (head)
			head = node_baru;// 4. NULL <- node_baru (head) <--> A
		}
		else if(strcmp((*node_baru).id, (*tail).id) > 0){ //pushTail
			(*node_baru).previous = tail;// C (Tail) <- node_baru
			(*tail).next = node_baru;// C (Tail) <--> node_baru
			(*node_baru).next = NULL;// C (Tail) <--> node_baru -> NULL
			tail = node_baru;// C <--> node_baru (Tail) -> NULL
		}
		else{ //pushMid
			struct Node *patokan = (struct Node *) malloc(sizeof(struct Node));
			patokan = head;
			while(patokan != NULL){ //cari patokan
				if(strcmp((*node_baru).id, (*patokan).id) < 0){
					break;
				}
				patokan = (*patokan).next;
			}
			
			//patokan diperoleh
			(*node_baru).next = patokan;//C123 -> patokan (D123)
			(*node_baru).previous = (*patokan).previous;//patokan.previous (B221) <- C123 -> D123
			(*patokan).previous->next = node_baru;//patokan.previous.next (B221) <--> C123 -> D123
			(*patokan).previous = node_baru;//B221 <--> C123 <--> D123
		}
	}
	puts("");
}
// NULL <- A (Head) <--> B <--> C (Tail) -> NULL
// node_baru
// 						(current)

//pushHead //paling kecil
// NULL <- node_baru (Head) <--> A <--> B <--> C (Tail) -> NULL

//pushTail
// NULL <- A (Head) <--> B <--> C <--> node_baru (Tail) -> NULL

//pushMid
//contoh:
//D123
//B221
//C123
//D123(head, tail)
//B221 (head) <--> D123 <--> E123 (tail)
//B221 (head) <--> C123 <--> D123 <--> E123 (tail) -> NULL

//pushFirst (kalo head == NULL)



void menu(){
	puts("1. Insert"); //printf("1. Insert\n");
	puts("2. Delete");
	puts("3. Print");
	puts("4. Exit");
	printf(">> ");
}


/*Delete
1. Cari Node baru yang mau didelete (lokasinya)
2. Putusin panahnya (next & previous)
3. Hapus nilai/value-nya (free)
*/
void delete_node(char temp_id[]){
	struct Node *current = (struct Node *) malloc(sizeof(struct Node));
	current = head;
	while(current != NULL){ //1. cari lokasi node dihapus
		if(strcmp(temp_id, (*current).id) == 0){ //kalo sama
			break;
		}
		else{ //kalo beda
			current = (*current).next;
		}
	}
	
	
	//2. Putusin panahnya (next & previous)
	if(current == NULL){ //ID ga ada di linked list
		puts("ID to delete didn\'t exist in linked list! \"Enter to continue\"");
		getchar();
		return;
	}
	else{ //ID ada di linked list
		if(head == tail){
			head = tail = (*current).next = (*current).previous = NULL;
			free(current);
		}
		else if(current == head){//yg dihapus head
			head = (*current).next;//B221 <--> C123 (head) <--> D123 <--> E123 (tail)  -> NULL
			(*head).previous = (*current).next = NULL;//B221 -> NULL | NULL <- C123 (head) <--> D123 <--> E123 (tail)  -> NULL
			free(current);//NULL <- C123 (head) <--> D123 <--> E123 (tail)  -> NULL
		}
		else if(current == tail){//yg dihapus tail
			tail = (*current).previous;
			(*tail).next = (*current).previous = NULL;
			free(current);
		}
		else{//yg dihapus bukan tail, bukan head
			(*current).previous->next = (*current).next;
			(*current).next->previous = (*current).previous;
			//sambungin current.next dengan current.previous selesai
			
			//putusin rantai current ke linked list
			(*current).next = (*current).previous = NULL;
			
			//Hapus node yang diputuskan tersebut
			free(current);
		}
	}
}


void print_node(){
	struct Node *current = (struct Node *) malloc(sizeof(struct Node));
	current = head;
	for(;current != NULL;){//for(inisialisasi; persyaratan loop; perubahan setiap loop){}
		printf("%s ", (*current).id);
		current = (*current).next;
	}
	printf("\n\"Enter to Continue\""); getchar();
	puts("");
}

//NULL <- B221 (head) <--> C123 <--> D123 <--> E123 (tail) -> NULL
//			(Current)

int main(){
	char temp_id[4+1]; //tempat id sementara yang diinput user
	
	for(;;){//Loop forever
		menu();
		int choice;
		scanf("%d", &choice); //pilih menu
		getchar();
		
		if(choice == 1){//Insert
			printf("\nInsert new ID: ");
			scanf("%[^\n]", temp_id); //%s sampe space/enter
			getchar();
			insert_node(temp_id);
		}
		else if(choice == 2){//Delete
			printf("\nID to delete: ");
			scanf("%[^\n]", temp_id); //%s sampe space/enter
			getchar();
			delete_node(temp_id);
		}
		else if(choice == 3){//Print
			print_node();
		}
		else if(choice == 4){//Exit
			break;
		}
	}
    return 0;
}

/*
Insert
Delete
Traverse/Print
*/
