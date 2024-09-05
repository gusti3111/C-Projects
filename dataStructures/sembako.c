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
//lihat ebook halaman 189 untuk pseudocode
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


// fungsi hapus barang lihat ebook halaman 194 untuk pseudocode
void hapusBarangByName(struct Barang** head, char *name) {
    //STEP 1: cek list apakah kosong atau tidak
    if (*head == NULL) { 
        printf("UNDERFLOW - Tidak ada bahan yang dapat dihapus.\n");
        return;
    }

    // Step 2: buat pointer PTR

    struct Barang* ptr = *head; 
    
    // Step 3 dan Step 4: mencari node / data barang yang dihapus berdasarkan id
    while (ptr != NULL && strcmp(ptr->name,name) == 0) {  
        ptr = ptr->next;
    }
    
    if (ptr == NULL) {  // Jika node dengan id tersebut tidak ditemukan
        printf("Bahan dengan nama %s tidak ditemukan.\n", name);
        return;
    }

    // Step 5: 
    struct Barang* temp = ptr->prev;

    // Jika barang didalam node tersebut yang dihapus adalah node pertama (head)
    if (ptr == *head) {
        *head = ptr->next;  // Ubah head ke node berikutnya
        if (*head != NULL) {
            (*head)->prev = NULL;  // Jika head baru ada, set prev-nya ke NULL
        }
    } else {
        // Step 6 dan Step 7: Update pointer node
        if (ptr->next != NULL) {  
            ptr->next->prev = temp;
        }
        if (temp != NULL) {  // Update link dari node sebelumnya
            temp->next = ptr->next;
        }
    }
    // Step 8: Bebaskan memori dari node yang dihapus
    free(ptr);  
    printf("\n Barang dengan nama %s telah dihapus.\n", name);
}


struct Barang* cariBarangByName(struct Barang* head, char*name) {
    struct Barang* temp = head;
    //cek nama pada linked list
    while (temp != NULL) {
        //karna variable name merupakan array string maka harus dicopy dulu
        if (strcmp(temp->name,name)== 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // Jika tidak ditemukan
}
//fungsi caribarang berdasarkan id
// sama seperti fungsi sebelumnnya tapi ini kita get by id nya
struct Barang* cariBarangById(struct Barang* head, int id) {
    struct Barang* temp = head;
    while (temp != NULL) {
        if (temp->id== id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; // Jika tidak ditemukan
}




// Simpan barang ke dalam sebuah file
void simpanDaftarBarang(struct Barang* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }

    struct Barang* ptr = head;
    while (ptr != NULL) {
        fprintf(file, "%d %s %d %.2f\n", ptr->id, ptr->name, ptr->stock, ptr->price);
        ptr = ptr->next;
    }

    fclose(file);
    printf("Data bahan berhasil disimpan ke file %s.\n", filename);
}



void CetakBarang(struct Barang *barang){
    while (barang != NULL) {
         printf("ID: %d, Nama: %s, Stock: %d, Harga: %.2f\n", barang->id, barang->name, barang->stock, barang->price);
        barang = barang->next;
    }
}
//fungsi input name
//kenapa kita tidak menggunakan input name seperti input data yang lainnya karna kita ingin meninput lebih dari satu kata ketika memasukan nama barang  
void InputName(char *name,int size){ 
    while (getchar() != '\n');  
    fgets(name, size, stdin);
    name[strcspn(name, "\n")] = '\0';

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
        printf("2. Tampilkan semua bahan\n");
        printf("3. Hapus barang berdasarkan nama\n");
        printf("4. Simpan barang ke dalam file\n");
        printf("5. CariBarang berdasarkan nama\n");
        printf("6  Cari barang berdasarkan id\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Masukan id barang: ");
                scanf("%d",&id);
                printf("Masukan nama barang: ");
                InputName(name,sizeof(name));
                
                printf("Masukkan jumlah stock: ");
                scanf("%d", &stock);
                printf("Masukkan harga: ");
                scanf("%f", &price);
                TambahkanBarangAwal(&head,id, name, stock,price);
                break;
            case 2:
                printf("Daftar bahan sembako:\n");
                CetakBarang(head);
                break;
            case 3:
                printf("Masukkan nama barang yang ingin dihapus: ");
                scanf("%s", name);
                hapusBarangByName(&head, name);
                break;

            case 4:
                simpanDaftarBarang(head, "data_bahan.txt");
                break;
          
            case 5:
                printf("Masukan nama barang: ");
                InputName(name,sizeof(name));
                struct Barang* barangName = cariBarangByName(head, name);
                CetakBarang(barangName);
                if (barangName != NULL) {
                    printf("Barang ditemukan:\n");
                    printf("ID: %d\nNama: %s\nStock: %d\nHarga: %.2f\n", barangName->id, barangName->name, barangName->stock, barangName->price);
                 } else {
               printf("Barang dengan nama %s tidak ditemukan.\n", name);
              }
                break;
            case 6:
                printf("masukan ID Barang: \n");
                scanf("%d",&id);
                struct Barang* barang = cariBarangById(head, id);
                CetakBarang(barang);
                if (barang != NULL) {
                    printf("Barang ditemukan:\n");
                    printf("ID: %d\nNama: %s\nStock: %d\nHarga: %.2f\n", barang->id, barang->name, barang->stock, barang->price);
                 } else {
               printf("Barang dengan id %d tidak ditemukan.\n", id);
              }
                break;
            case 7:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 7);

    return 0;
}





  


  



