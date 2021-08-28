#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include<iomanip>
#include<conio.h>
#include<string>


using namespace std;
typedef struct Kartu
{
    int JenisKartu;
    int NoKartu;
}Kartu;

typedef struct TumpukanKartu
{
    struct Kartu K;
    struct TumpukanKartu * next;
}TumpukanKartu;

struct TumpukanKartu * BuatNodeBaru()
{
    TumpukanKartu* NodeBaru= (TumpukanKartu*) malloc(sizeof(TumpukanKartu));
    return NodeBaru;
}


struct TumpukanKartu * Push(struct TumpukanKartu *  PtrPush,
                            int JenisKartu, int NoKartu)
{
    struct TumpukanKartu * PtrBef;
    PtrBef = PtrPush;
    PtrPush = BuatNodeBaru();
    PtrPush->next = PtrBef;
    PtrPush->K.JenisKartu= JenisKartu;
    PtrPush->K.NoKartu= NoKartu;
    return PtrPush;
}

TumpukanKartu * Pop(struct TumpukanKartu * PtrPush )
{
    PtrPush = PtrPush->next;
    return PtrPush;
}

TumpukanKartu * List(TumpukanKartu * Pemain,int JenisKartu,int NoKartu,int NoPemain){

    TumpukanKartu *temp;
    temp = BuatNodeBaru();
    temp->K.JenisKartu = JenisKartu ;
    temp->K.NoKartu = NoKartu;
    temp->next = Pemain;
    Pemain = temp;
    return Pemain;
}

//Cuma ada atau tidak dan dikembalikan alamat pertama jika ada, NULL jika tidak
TumpukanKartu * CekKartu (TumpukanKartu * Pemain, int JenisKartu){
    TumpukanKartu *p;
    p = Pemain;
    while(p != 0){
        if(p->K.JenisKartu == JenisKartu){
            return p;
            break;
        }
        p = p->next;
    }
}

//Kembalian berupa alamat node kartu yang mau di cetak
TumpukanKartu * CariKartu(TumpukanKartu * KartuKeluarP2,int JenisKartu, int NomorKartuKeluar){
    TumpukanKartu * p = KartuKeluarP2;
    while(p != 0){
    if(p->K.JenisKartu == JenisKartu && p->K.NoKartu == NomorKartuKeluar){
        return p;
        break;
    }
    p = p->next;
    }
}

//Hapus list
TumpukanKartu * Hapus (TumpukanKartu *Pemain, int JenisKartu, int NoKartu){
    TumpukanKartu * temp;
    TumpukanKartu  * p;
    p = Pemain;

    if(p->K.JenisKartu == JenisKartu && p->K.NoKartu == NoKartu){
            temp = p;
            p = p->next;
            free(temp);
            return p;
    }

    while (p->next != 0){
        if(p->next->K.JenisKartu == JenisKartu && p->next->K.NoKartu == NoKartu){
            temp = p->next;
            p->next = temp->next;
            free(temp);
            return Pemain;
            break;

        }
        p=p->next;
    }

}

int SisaKartu(TumpukanKartu * Pemain){
    TumpukanKartu * P;
    P = Pemain;
    int JmlKartu = 0;
    while(P !=0){
        JmlKartu +=1;
        P = P->next;
    }
    return JmlKartu;

}
//fungsi untuk mengatur warna text
string setcolor(unsigned short color){
HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hcon, color);
return "";

}
int main()
{
    int ya;
    string nama;
    srand(time(0));
    MenuAwal:
        setcolor(10);cout<<"========================================================================="<<endl;
        setcolor(13);cout<<setw(50)<<"= ANGGOTA KELOMPOK ="<<endl;
        setcolor(11);cout<<"1. BURHANUDDIN BAGASKARA "<<endl;
        setcolor(11);cout<<"2. GAGAH PUTRA HARYO SATRIO "<<endl;
        setcolor(11);cout<<"3. LUBNA KHALIDAH "<<endl;
        setcolor(11);cout<<"4. MERIL LIA PRIDAY RISKIANA "<<endl;
        setcolor(10);cout<<"========================================================================="<<endl;
        setcolor(13);cout<<"Selamat datang di game kelompok kami"<<endl;
        setcolor(15);cout<<"Silahkan Masukkan Nama Anda :\n";
        cin>>nama;
        setcolor(13);cout<<"\nApakah Anda Ingin Bermain?"<<endl;
        setcolor(15);cout<<"Main"<<endl;
        setcolor(15);cout <<"Tidak"<<endl;
        setcolor(13);cout<<"\njika iya silahkan tekan angka 1 \njika tidak silahkan tekan angka selain 1\n";
        cin >> ya;
        setcolor(15);
        a:
            if (ya == 1)
        {
        system ("cls");
        goto game;}
        else {return 0;}


    game:
    setcolor(13);cout<<"Jenis Kartu : \n";
    setcolor(13);cout<<"1 --> Keriting \n2 --> Love \n3 --> Waru \n4 --> Wajik\n";

    setcolor(15);cout<<"\n\nHALO "<<nama << "!!!";
    setcolor(11);
    //Memasukkan JenisKartu dan NoKartu ke array
    Kartu IKartu[15];
    //printf("\n\nUrutan kartu sebelum di suffle :\n");
    for(int i=0; i<52; i++){
        IKartu[i].JenisKartu = i/13 +1;
        IKartu[i].NoKartu = i%13 +2;
        //printf("%d->%d\n",IKartu[i].JenisKartu, IKartu[i].NoKartu);
    }

    //Suffle isi IKartu di array
    for(int i=0; i<3999; i++){
    Kartu Tempat;
    int a, b;
    a = rand() % 52;
    b = rand() % 52;
    Tempat = IKartu[a];
    IKartu[a] = IKartu[b];
    IKartu[b] = Tempat;
    }

    //Memasukkan kartu yang telah di suffle ke bandar
    TumpukanKartu * Bandar;
    Bandar = NULL;
    //printf("Urutan kartu setelah suffle :\n");
    for(int i=0; i<52; i++){
    Bandar = Push(Bandar,IKartu[i].JenisKartu,IKartu[i].NoKartu);
    //printf("%d->%d\n",IKartu[i].JenisKartu, IKartu[i].NoKartu);
    }

     //Mengambil Kartu pembuka
    TumpukanKartu * Pembuka;
    Pembuka = Bandar;

    //Membagi 5 kartu ke pemain 1 dan pemain 2 dan memasukkan ke linked list
    TumpukanKartu * Pemain1;
    TumpukanKartu * Pemain2;
    Pemain1 = NULL;
    Pemain2 = NULL;
    for(int i=0; i<5; i++){
    Bandar = Pop(Bandar);
    Pemain1 = List(Pemain1,Bandar->K.JenisKartu,Bandar->K.NoKartu,1);
    Bandar = Pop(Bandar);
    Pemain2 = List(Pemain2,Bandar->K.JenisKartu,Bandar->K.NoKartu,2);
    }

    //Alamat pertama bandar setelah diambil 1+5+5 kartu (Kartu Teratas)
    Bandar = Bandar->next;
    //printf("Kartu teratas di Bandar : %d-->%d\n",Bandar->K.JenisKartu,Bandar->K.NoKartu);

    //Tanda tiap babak
    int Babak = 1 ;
    printf("\n\n\n---------------------PERMAINAN DIMULAI--------------------\n");
    printf("Permainan Babak : %d\n",Babak);

    //Melihat kartu setiap pemain
    TumpukanKartu * P1 = Pemain1;
    TumpukanKartu * P2 = Pemain2;
    int JmlKartu1, JmlKartu2;
    JmlKartu1 = SisaKartu(P1);
    printf("Kartu Pemain 1 : \nAda %d kartu\n",JmlKartu1);
    printf("Kartu Pemain 2 : \n");
    while(P2 != 0){
        printf("%d->%d\n",P2->K.JenisKartu, P2->K.NoKartu);
        P2 = P2->next;
    }

    //Mencetak kartu pembuka
    printf("Kartu Pembuka : %d->%d\n",Pembuka->K.JenisKartu, Pembuka->K.NoKartu);

    //Cek kartu pemain 1 ada atau tidak)
    TumpukanKartu * KartuKeluarP1 = CekKartu (Pemain1,Pembuka->K.JenisKartu);
    if(KartuKeluarP1 != NULL){
        printf("Kartu Pemain 1 : %d-->%d\n",KartuKeluarP1->K.JenisKartu,KartuKeluarP1->K.NoKartu);
    }else{//saat tidak ada, minum dari bandar
        while(Bandar != 0){
        Pemain1 = List(Pemain1,Bandar->K.JenisKartu,Bandar->K.NoKartu,2);
        if(Pemain1->K.JenisKartu == Pembuka->K.JenisKartu){
            KartuKeluarP1 = Pemain1;
            break;
        }
        Bandar = Pop(Bandar);
        }
        Bandar = Bandar->next;
        printf("Kartu Pemain 1 : %d-->%d\n",KartuKeluarP1->K.JenisKartu,KartuKeluarP1->K.NoKartu);
    }

    //Cek kartu pemian 2(ada atau tidak)
    TumpukanKartu * KartuKeluarP2 = CekKartu (Pemain2,Pembuka->K.JenisKartu);
    int NomorKartuKeluar;
    //saat ada
    if(KartuKeluarP2 != NULL){
        printf("Kartu Anda : %d-->",Pembuka->K.JenisKartu);
        scanf ("%d",&NomorKartuKeluar);
        //mencari kartu sesuai permintaan pemain 2
        KartuKeluarP2 = CariKartu(KartuKeluarP2,Pembuka->K.JenisKartu,NomorKartuKeluar);
        printf("Kartu Pemain 2 : %d-->%d\n",KartuKeluarP2->K.JenisKartu,KartuKeluarP2->K.NoKartu);
    }else{//saat tidak ada, minum dari bandar
        int Minum;
        printf("Tekan angka 1 untuk minum : ");
        scanf("%d",&Minum);
        if(Minum == 1){
             while(Bandar != 0){
        Pemain2 = List(Pemain2,Bandar->K.JenisKartu,Bandar->K.NoKartu,2);
        if(Pemain2->K.JenisKartu == Pembuka->K.JenisKartu){
            KartuKeluarP2 = Pemain2;
            break;
        }
        Bandar = Pop(Bandar);
        }
        Bandar = Bandar->next;
        printf("Kartu Pemain 2 : %d-->%d\n",KartuKeluarP2->K.JenisKartu,KartuKeluarP2->K.NoKartu);
        }

    }

    //ambil kartu yang akan dihapus
    TumpukanKartu * HpsKartuP1 = KartuKeluarP1;
    TumpukanKartu * HpsKartuP2 = KartuKeluarP2;

    //Hapus kartu yang sudah keluar dari pemain1 dan pemain2
    Pemain1 = Hapus (Pemain1, HpsKartuP1->K.JenisKartu, HpsKartuP1->K.NoKartu);
    Pemain2 = Hapus (Pemain2, HpsKartuP2->K.JenisKartu, HpsKartuP2->K.NoKartu);

    //tanda tiap babak
    Babak +=1;
    printf("\n\n\n---------------------ooOoo--------------------\n");
    printf("Permainan Babak : %d\n",Babak);

    //Melihat kartu setiap pemain
    P1 = Pemain1;
    P2 = Pemain2;;
    JmlKartu1 = SisaKartu(P1);
    printf("Kartu Pemain 1 : \nAda %d kartu\n",JmlKartu1);
    printf("Kartu Pemain 2 : \n");
    while(P2 != 0){
        printf("%d->%d\n",P2->K.JenisKartu, P2->K.NoKartu);
        P2 = P2->next;
    }

    //Melihat pemain mana yang nomor kartunya besar
       if(KartuKeluarP1->K.NoKartu>KartuKeluarP2->K.NoKartu){
            printf("Kartu Pemain 1 lebih besar\n");
            KartuKeluarP1 = Pemain1;
            Pembuka = KartuKeluarP1;
            printf("Kartu Pemain 1 : %d-->%d\n",KartuKeluarP1->K.JenisKartu,KartuKeluarP1->K.NoKartu);

        }else{
            printf("Kartu Pemain 2 lebih besar\n");
            int Jenis, Nomor;
            printf("Anda ingin mengeluarkan kartu :\n");
            printf("Berjenis : ");
            scanf("%d",&Jenis);
            printf("Bernomor : ");
            scanf("%d",&Nomor);
            KartuKeluarP2 = CariKartu(Pemain2,Jenis,Nomor);
            Pembuka = KartuKeluarP2;
            printf("Kartu Pemain 2 : %d-->%d\n",KartuKeluarP2->K.JenisKartu,KartuKeluarP2->K.NoKartu);
        }


    Babak +=1;


//keadaan yang terus berulang jika masih ada pemain yang kartunya belum habis
while(Pemain1!=0 || Pemain2!=0){
    if(Pembuka == Pemain1){//jika yang mengeluarkan kartu pemain1
    //Cek kartu pemian 2(ada atau tidak)
    KartuKeluarP2 = CekKartu (Pemain2,Pembuka->K.JenisKartu);
    //saat ada
    if(KartuKeluarP2 != NULL){
        printf("Kartu Anda : %d-->",Pembuka->K.JenisKartu);
        scanf ("%d",&NomorKartuKeluar);
        //mencari kartu sesuai permintaan pemain 2
        KartuKeluarP2 = CariKartu(KartuKeluarP2,Pembuka->K.JenisKartu,NomorKartuKeluar);
        printf("Kartu Pemain 2 : %d-->%d\n",KartuKeluarP2->K.JenisKartu,KartuKeluarP2->K.NoKartu);
    }else{//saat tidak ada
        //minum dari bandar
        //jika kartu di bandar belum habis
        if(Bandar !=0){
        int Minum;
        printf("Tekan angka 1 untuk minum : ");
        scanf("%d",&Minum);
        if(Minum == 1){
            while(Bandar != 0){
            Pemain2 = List(Pemain2,Bandar->K.JenisKartu,Bandar->K.NoKartu,2);
            if(Pemain2->K.JenisKartu == Pembuka->K.JenisKartu){
            KartuKeluarP2 = Pemain2;
            break;
        }
        Bandar = Pop(Bandar);
        }
        Bandar = Bandar->next;
        printf("Kartu Pemain 2 : %d-->%d\n",KartuKeluarP2->K.JenisKartu,KartuKeluarP2->K.NoKartu);
        }
        }

        if(Bandar == 0){//jika kartu di bandar habis
             printf("Pemain 2 mengambil kartu buangan Pemain 1\n");
             Pemain2 = List(Pemain2,Pembuka->K.JenisKartu,Pembuka->K.NoKartu,2);
             KartuKeluarP2->K.JenisKartu = 0;
             KartuKeluarP2->K.NoKartu = 0;
        }


    }
    }else{//jika yang mengeluarkan kartu adaalah pemain2
    //Cek kartu pemain 1 ada atau tidak)
    KartuKeluarP1 = CekKartu (Pemain1,Pembuka->K.JenisKartu);
    if(KartuKeluarP1 != NULL){
        printf("Kartu Pemain 1 : %d-->%d\n",KartuKeluarP1->K.JenisKartu,KartuKeluarP1->K.NoKartu);
    }else{//saat tidak ada
        //minum dari bandar
        if(Bandar !=0){//jika kartu di bandar belum habis
        printf("Pemain 1 minum dari Bandar\n");
        while(Bandar != 0){
        Pemain1 = List(Pemain1,Bandar->K.JenisKartu,Bandar->K.NoKartu,2);
        if(Pemain1->K.JenisKartu == Pembuka->K.JenisKartu){
            KartuKeluarP1 = Pemain1;
            break;
        }
        Bandar = Pop(Bandar);
        }
        Bandar = Bandar->next;
        printf("Kartu Pemain 1 : %d-->%d\n",KartuKeluarP1->K.JenisKartu,KartuKeluarP1->K.NoKartu);
        }
        if(Bandar == 0){//jika kartu di bandar habis
             printf("Pemain 1 mengambil kartu buangan Pemain \n");
             Pemain1 = List(Pemain1,Pembuka->K.JenisKartu,Pembuka->K.NoKartu,1);
             KartuKeluarP1->K.JenisKartu = 0;
             KartuKeluarP1->K.NoKartu = 0;
        }
    }
    }


    //hapus kartu yang sudah dikeluarkan dari tiap pemain
    TumpukanKartu * HpsKartuP1;
    TumpukanKartu * HpsKartuP2;
    if(KartuKeluarP1 == Pembuka){//jika sebelumnya pemain1 yang no kartunya besrar
        //ambil kartu yang akan dihapus
        HpsKartuP1 = KartuKeluarP1;
        //Hapus kartu yang sudah keluar dari pemain1
        Pemain1 = Hapus (Pemain1, HpsKartuP1->K.JenisKartu, HpsKartuP1->K.NoKartu);
        if(Pemain2 != Pembuka){
            //ambil kartu yang akan dihapus
            HpsKartuP2 = KartuKeluarP2;
            //Hapus kartu yang sudah keluar dari pemain2
            Pemain2 = Hapus (Pemain2, HpsKartuP2->K.JenisKartu, HpsKartuP2->K.NoKartu);
        }
    }else if(KartuKeluarP2 == Pembuka){//jika sebelumnya pemain2 yang no kartunya besrar
        //ambil kartu yang akan dihapus
        HpsKartuP2 = KartuKeluarP2;
        //Hapus kartu yang sudah keluar dari pemain2
        Pemain2 = Hapus (Pemain2, HpsKartuP2->K.JenisKartu, HpsKartuP2->K.NoKartu);
        if(Pemain1 != Pembuka){
            //ambil kartu yang akan dihapus
            HpsKartuP1 = KartuKeluarP1;
            //Hapus kartu yang sudah keluar dari pemain2
            Pemain1 = Hapus (Pemain1, HpsKartuP1->K.JenisKartu, HpsKartuP1->K.NoKartu);
        }
    }

    //tanda tiap babak
    printf("\n\n\n---------------------ooOoo--------------------\n");
    printf("Permainan Babak : %d\n",Babak);

    //Melihat kartu setiap pemain
    P1 = Pemain1;
    P2 = Pemain2;
    JmlKartu1 = SisaKartu(P1);
    printf("Kartu Pemain 1 : \nAda %d kartu\n",JmlKartu1);
    printf("Kartu Pemain 2 : \n");
    if(P2 == 0){
        JmlKartu2 = SisaKartu(P2);
        printf("Ada %d kartu\n",JmlKartu2);
    }
    while(P2 != 0){
        printf("%d->%d\n",P2->K.JenisKartu, P2->K.NoKartu);
        P2 = P2->next;
    }


     //Melihat apakah ada pemain yang habis kartunya
    if(Pemain1 == 0 && Pemain2 == 0){
        printf("Kartu Semua pemain Habis");
        if(KartuKeluarP2 == Pembuka){
            printf("Pemain 2 menang!!!");
            break;
        }else{
        printf("Pemain 1 Menang !!!");
        break;
        }
    }else if(Pemain1 == 0 || Pemain2 == 0){
        if(Pemain1 == 0){
            printf("Pemain 1 menang!!!\n\n\n");
            break;
        }else{
        printf("Pemain 2 Menang !!!\n\n\n");
        break;
        }
    }else if (Pemain1 != 0 && Pemain2 != 0){
       if(KartuKeluarP1->K.NoKartu>KartuKeluarP2->K.NoKartu){
            printf("Kartu Pemain 1 lebih besar\n");
            KartuKeluarP1 = Pemain1;
            Pembuka = KartuKeluarP1;
            printf("Kartu Pemain 1 : %d-->%d\n",KartuKeluarP1->K.JenisKartu,KartuKeluarP1->K.NoKartu);

        }else{
            printf("Kartu Pemain 2 lebih besar\n");
            int Jenis, Nomor;
            printf("Anda ingin mengeluarkan kartu :\n");
            printf("Berjenis : ");
            scanf("%d",&Jenis);
            printf("Bernomor : ");
            scanf("%d",&Nomor);
            KartuKeluarP2 = CariKartu(Pemain2,Jenis,Nomor);
            Pembuka = KartuKeluarP2;
            printf("Kartu Pemain 2 : %d-->%d\n",KartuKeluarP2->K.JenisKartu,KartuKeluarP2->K.NoKartu);
        }
    }
     Babak+=1;
}
    setcolor(13);cout << "\nPERMAINAN BERAKHIR!!!";
    setcolor(15);cout << "\n\nApakah anda ingin Bermain lagi?";
    setcolor(15);cout<<"\nMain"<<endl;
    setcolor(15);cout <<"Tidak"<<endl;
    setcolor(10);cout<<"\njika iya silahkan tekan angka 1 \njika tidak silahkan tekan angka selain 1\n";
	cin >> ya;
    MainLagi:
    if (ya == 1)
    {
    system ("cls");
    goto MenuAwal;}
    else{return 0;}
}
