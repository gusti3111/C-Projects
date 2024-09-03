#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//deksripsikan attribut yang ada pada barang
//barang disini bertindak sebagai node
struct Barang{
  struct Barang *prev;
  int id;
  char name[50];
  int stock;
  float price;
   struct Barang *next;
};

//alokasikan attribut yang ada di struct Barang ke node baru
struct Barang*NewBarang(int id,char*name,int stock,float price){
  struct Barang *new = (struct Barang*)malloc(sizeof(struct Barang));
  new->id=id;
  strcpy(new->name,name);
  new->stock= stock;
  new->price=price;
  new->prev=NULL;
  new->next=NULL;
 return new;
  

}


//Tambahkan barang baru diawal
void TambahkanBarangAwal(struct Barang **head,int id,char *name,int stock,float price){
  struct Barang *avail=NewBarang(id,name,stock,price);
  if(avail == NULL){
    printf("OVERFLOW\n");
    return;
  }
  // Step 2: SET new(barang_baru) =  
  struct Barang *newNode = avail;
  // Step 3: SET AVAIL = AVAIL NEXT (Here, next available node concept is generally not needed)
    // In this context, we can skip this step.

    // Step 4: SET DATA = VALUE
    newNode->id = id;
    strcpy(newNode->name,name);
    newNode->stock=stock;
    newNode->price=price;
 // Step 5: SET PREV = NULL
    newNode->prev = NULL;

    // Step 6: SET = START (Set the new node next pointer to current start)
    newNode->next = *head;

    // Step 7: SET START -> PREV = NEW_NODE
    if (*head != NULL){
        (*head)->prev = newNode;
    }
    // Step 8: SET START = NEW_NODE
    *head = newNode;

    //Step 9: EXIT
    return;
 }

void hapusBarang(struct Barang** head, int id){

    struct Barang* ptr = *head;

    // Mencari node dengan ID yang sesuai
    while (ptr != NULL && ptr->id != id) {
        ptr = ptr->next;
    }

    // Jika node dengan ID yang dimaksud tidak ditemukan
    if (ptr == NULL) {
        printf("Barang dengan id %d tidak ditemukan.\n", id);
        return;
    }

    // Jika node yang akan dihapus adalah head (node pertama)
    if (ptr == *head) {
        *head = ptr->next;
    }

    // Menghubungkan node sebelumnya dengan node berikutnya
    if (ptr->prev != NULL) {
        ptr->prev->next = ptr->next;
    }

    if (ptr->next != NULL) {
        ptr->next->prev = ptr->prev;
    }

    // Membebaskan memori dari node yang dihapus
    free(ptr);

    printf("Node dengan id %d berhasil dihapus.\n", id);



}


void CetakBarang(struct Barang *barang){
    while (barang != NULL) {
         printf("ID: %d, Nama: %s, Stock: %d, Harga: %.2f\n", barang->id, barang->name, barang->stock, barang->price);
        barang = barang->next;
    }
}

int main(){
   struct Barang* head = NULL;
    int pilihan;
    int id;
    char name[50];
    int stock;
    float price;
    printf("Masukkan ID bahan: ");
    scanf("%d", &id);
    printf("Masukkan nama bahan: ");
    scanf("%s", name);
    printf("Masukkan jumlah stock: ");
    scanf("%d", &stock);
    printf("Masukkan harga: ");
    scanf("%f", &price);
    TambahkanBarangAwal(&head, id, name, stock, price);

    printf("Daftar bahan sembako:\n");
    CetakBarang(head);

    printf("Masukkan nama bahan yang ingin dihapus: ");
    scanf("%d", &id);
    hapusBarang(&head, id);


  
}




  


  



