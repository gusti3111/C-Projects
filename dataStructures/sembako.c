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


void hapusBarang(struct Barang** head, char *name){

    struct Barang* ptr = *head;

    // Mencari node dengan ID yang sesuai
    while (ptr != NULL && strcmp(ptr->name,name) != 0) {
        ptr = ptr->next;
    }

    // Jika node dengan ID yang dimaksud tidak ditemukan
    if (ptr == NULL) {
        printf("Barang dengan nama %s tidak ditemukan.\n", name);
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

    printf("Node dengan nama %s berhasil dihapus.\n", name);



}
struct Barang* cariBarang(struct Barang* head, char*name) {
    struct Barang* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name,name)== 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // Jika tidak ditemukan
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


     do {
        printf("\nMenu:\n");
        printf("1. Tambah bahan di awal\n");
        printf("2. Hapus bahan\n");
        printf("3. Tampilkan semua bahan\n");
        printf("4. CariBarang berdasarkan nama\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukan id barang: ");
                scanf("%d",&id);
                printf("Masukkan nama barang: ");
                scanf("%s", name);
                printf("Masukkan jumlah stock: ");
                scanf("%d", &stock);
                printf("Masukkan harga: ");
                scanf("%f", &price);
                TambahkanBarangAwal(&head,id, name, stock,price);
                break;
            case 2:
                printf("Masukkan nama barang yang ingin dihapus: ");
                scanf("%s", name);
                hapusBarang(&head, name);
                break;
            case 3:
                printf("Daftar bahan sembako:\n");
                CetakBarang(head);
                break;
            case 4:
                printf("Cari Barang berdasarkan Nama: \n");
                scanf("%s",name);
                struct Barang* barang = cariBarang(head, name);
                CetakBarang(barang);
                if (barang != NULL) {
                    printf("Barang ditemukan:\n");
                    printf("ID: %d\nNama: %s\nStock: %d\nHarga: %.2f\n", barang->id, barang->name, barang->stock, barang->price);
                 } else {
               printf("Barang dengan nama %s tidak ditemukan.\n", name);
              }
                break;
            case 5:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);

    return 0;
}





  


  



