/************************/
/*                      */
/* NUMARA: 22100011013  */
/* AD: BARAN            */
/* SOYAD: KANAT         */
/*                      */
/************************/

#include <stdio.h>
#include <stdlib.h>

struct islem{

    char aciklama[100];
    int gider;
    int gelir;

};

struct araba{

    char plaka[15];
    char sahip[30];
    char tarih[15];
    int islem_sayisi;
    struct islem *islemler;

};

/* Listeleme Fonksiyonu */
void listele(struct araba *arabalar, int adet){

    int i, j;

    printf("\n~~~~~~ARAC LISTESI~~~~~~\n\n");

    printf("NO   TARIH         PLAKA       SAHIP\n");

    for(i=0; i<adet; i++)
    {
        printf("(%d) %s | %s | %s \n", i+1,(arabalar+i)->tarih,(arabalar+i)->plaka,(arabalar+i)->sahip);


        for (j = 0; j <(arabalar+i)->islem_sayisi ; j++)
        {
            printf("  --> %s  Gelir: %dTL, Gider: %dTL \n", (((arabalar+i)->islemler)+j)->aciklama,(((arabalar+i)->islemler)+j)->gelir,(((arabalar+i)->islemler)+j)->gider);
        }
    printf("\n");
    }

    printf("\n\n");

}
/* Listeleme Fonskiyonu */

/* Duzenleme Fonskiyonu */
void duzenle(struct araba *arabalar){

    printf("\n :::::ARAC DUZENLE:::::\n\n");

    int duzenle,i;
    printf("Hangi Aracta Duzenleme Yapacaksiniz? ");
    scanf("%d", &duzenle);
    duzenle = duzenle - 1;

    printf("%d.Aracin Plakasi: %s / Guncel Plakasini Girin: ", duzenle+1,(arabalar+duzenle)->plaka);
    scanf(" %30[^\n]", (arabalar+duzenle)->plaka);

    printf("%d.Aracin Sahibi: %s / Guncel sahibini Girin: ", duzenle+1,(arabalar+duzenle)->sahip);
    scanf(" %30[^\n]", (arabalar+duzenle)->sahip);

    printf("%d.Aracin Islem Tarihi: %s / Guncel Tarihi Girin: ", duzenle+1,(arabalar+duzenle)->tarih);
    scanf(" %30[^\n]", (arabalar+duzenle)->tarih);

    printf("\n\tIslemler\n");

    for( i = 0; i<(arabalar+duzenle)->islem_sayisi; i++)
    {

        printf("\t  %d.Islemin Eski isim: %s / Guncel Ismi: ", i+1,(((arabalar+duzenle)->islemler)+i)->aciklama);
        scanf(" %100[^\n]", (((arabalar+duzenle)->islemler)+i)->aciklama);

        printf("\t  %d.Islemin Eski Gideri: %d / Guncel Gideri: ", i+1,(((arabalar+duzenle)->islemler)+i)->gider);
        scanf("%d", &((((arabalar+duzenle)->islemler)+i)->gider));

        printf("\t  %d.Islemin Eski Geliri: %d / Guncel Geliri: ", i+1,(((arabalar+duzenle)->islemler)+i)->gelir);
        scanf("%d", &((((arabalar+duzenle)->islemler)+i)->gelir));
        printf("\n");

    }

}
/* Duzenleme Fonskiyonu */

/* Silme Fonksiyonu */
void sil(struct araba *arabalar, int *adet){

    int silinecek_arac;
    printf("\nKacinci Araci Silmek Istersin? ");
    scanf("%d", &silinecek_arac);

    free((arabalar+(silinecek_arac-1))->islemler);

    int i = silinecek_arac-1;

    for(; i<(*adet)-1; i++)
    {
        arabalar[i] = arabalar[i+1];
    }
    (*adet)--;

    arabalar = (struct araba*) realloc(arabalar, (*adet) * sizeof(struct araba));

}
/* Silme Fonksiyonu */

/* ekleme fonksiyonu */
void arac_ekle(struct araba **Arabalar,int *adet)
{

    printf("\n +++++ YENI ARAC EKLE +++++ \n");


    int ekstra,i,j,yeni = 1;
    printf("Kac Adet Arac Eklemek Istersin? ");
    scanf("%d", &ekstra);
    ekstra = *adet + ekstra;
    *Arabalar = (struct araba*) realloc(*Arabalar, (ekstra) * sizeof(struct araba));

    if(*Arabalar == NULL)
    {
        printf("Bellek bolgenizde yeterli alan bulamadýk!");
        exit(1);
    }

    for(i = *adet; i<(ekstra) ; i++)
    {
        printf("\n%d.Aracin Plaka Numarasini Girin: ", yeni);
        scanf(" %30[^\n]", (*Arabalar+i)->plaka);

        printf(" --> %s Plakali Aracin Sahibini Girin: ", (*Arabalar+i)->plaka );
        scanf(" %100[^\n]", (*Arabalar+i)->sahip);

        printf(" --> %s Plakali Araci Islem Tarihini Girin: ", (*Arabalar+i)->plaka);
        scanf(" %30[^\n]", (*Arabalar+i)->tarih);

        printf(" --> %s Plakali Arac Kac farkli islem Gordu? ", (*Arabalar+i)->plaka);
        scanf("%d", &((*Arabalar+i)->islem_sayisi));


        (*Arabalar+i)->islemler = (struct islem*) malloc((*Arabalar+i)->islem_sayisi*sizeof(struct islem));

        for(j = 0; j<(*Arabalar+i)->islem_sayisi; j++)
        {
            printf("\n");
            printf("%d.Islemin Aciklamasi Girin: ", j+1);
            scanf(" %100[^\n]", (((*Arabalar+i)->islemler)+j)->aciklama);

            printf(" --> %s Giderini Girin: ", (((*Arabalar+i)->islemler)+j)->aciklama);
            scanf("%d", &((((*Arabalar+i)->islemler)+j)->gider) );

            printf(" --> %s Gelirini Girin: ", (((*Arabalar+i)->islemler)+j)->aciklama);
            scanf("%d", &((((*Arabalar+i)->islemler)+j)->gelir));

        }
        yeni++;
        printf("\n");
    }
    *adet = ekstra;
}
/* ekleme fonksiyonu */


/* Kar-Zarar hesaplama fonksiyonu */
void hesapla(struct araba *Arabalar, int adet)
{
    char aranacak_tarih[15];
    int durum = 1,i,k,j,l,yeni = 1,uzunluk,kar_zarar,tkar_zarar = 0;

    printf("\n ***** KAR-ZARAR HESAPLA ***** \n");

    printf("Kar-Zarar'i Hesaplamak Istediginiz Tarih? ");
    scanf(" %30[^\n]", aranacak_tarih);

    printf("\nNO   TARIH         PLAKA       SAHIP\n");

    for(i=0; i<adet; i++)
    {
        durum = 1;
        l  = 0;
        uzunluk = 0;
        kar_zarar = 0;

        while( (Arabalar+i)->tarih[l] != '\0' )
        {
            l++;
            uzunluk++;
        }

        for (k = 0; k < uzunluk; k++)
        {
            if ((Arabalar+i)->tarih[k] != aranacak_tarih[k] && (Arabalar+i)->tarih[k] != '\0')
            {
                durum = 0;
                break;
            }
        }


        if (durum == 1)
        {

        printf("(%d) %s | %s | %s \n", i+1,(Arabalar+i)->tarih,(Arabalar+i)->plaka,(Arabalar+i)->sahip);

            for (j = 0; j <(Arabalar+i)->islem_sayisi ; j++)
            {

            printf("  --> %s  Gelir: %dTL, Gider: %dTL \n", (((Arabalar+i)->islemler)+j)->aciklama,(((Arabalar+i)->islemler)+j)->gelir,(((Arabalar+i)->islemler)+j)->gider);
            printf("      %s islemin Kar-Zarari: %dTL\n\n", (((Arabalar+i)->islemler)+j)->aciklama,((((Arabalar+i)->islemler)+j)->gelir)-((((Arabalar+i)->islemler)+j)->gider));

                kar_zarar = kar_zarar + (((((Arabalar+i)->islemler)+j)->gelir)-((((Arabalar+i)->islemler)+j)->gider));
            }

            printf("Aracin Kar-Zarari: %dTL", kar_zarar);
            printf("\n\n");
        yeni++;
        }

        tkar_zarar = tkar_zarar + kar_zarar;
        printf("\n");
    }

    printf("**Tarihin Toplam Kar-Zarari: %dTL**\n", tkar_zarar);
}
/* Kar-Zarar hesaplama fonksiyonu */

/* Arama Fonskiyonu */
void arama(struct araba *arabalar, int adet)
{
    char aranacak_plaka[15];
    char aranacak_tarih[15];
    int i,j,yeni = 1,plaka_eslesme = 1,tarih_eslesme = 1,bulundu = 0,l,k,uzunluk_plaka,uzunluk_tarih;

    printf("\n ***** FILTRELI ARAMA ***** \n");

    printf("Aranacak Plakayi Girin: ");
    scanf(" %30[^\n]", aranacak_plaka);

    printf("Aranacak tarihi Girin: ");
    scanf(" %30[^\n]", aranacak_tarih);

    printf("\n\nNO   TARIH         PLAKA       SAHIP\n");


    for(i=0; i<adet; i++)
    {

        l = 0,uzunluk_plaka = 0;
        while( (arabalar+i)->plaka[l] != '\0' )
        {
            l++;
            uzunluk_plaka++;
        }
        for(j=0; j<uzunluk_plaka; j++)
        {
            if((arabalar+i)->plaka[j] != aranacak_plaka[j])
            {
                plaka_eslesme = 0;
                break;
            }
        }


        k = 0, uzunluk_tarih = 0;
        while( (arabalar+i)->tarih[k] != '\0' )
        {
            k++;
            uzunluk_tarih++;
        }
        for(j=0; j<uzunluk_tarih; j++)
        {
            if((arabalar+i)->tarih[j] != aranacak_tarih[j])
            {
                tarih_eslesme = 0;
                break;
            }
        }

        if(plaka_eslesme == 1 && tarih_eslesme == 1)
        {


        printf("(%d) %s | %s | %s \n", i+1,(arabalar+i)->tarih,(arabalar+i)->plaka,(arabalar+i)->sahip);

            for (j = 0; j <(arabalar+i)->islem_sayisi; j++)
            {

            printf("  --> %s  Gelir: %dTL, Gider: %dTL \n", (((arabalar+i)->islemler)+j)->aciklama,(((arabalar+i)->islemler)+j)->gelir,(((arabalar+i)->islemler)+j)->gider);

            }

            bulundu = 1;
            yeni++;
            printf("\n");
        }


        plaka_eslesme = 1;
        tarih_eslesme = 1;

    }

    if(bulundu == 0)
    {
      printf("Aradiginiz araba bulunamadi.\n");
    }

}
/* Arama Fonksiyonu */




int main()
{
    int *durum = 0;
    int secenek,adet = 0,i,j,alt_secenek = 0;
    struct araba *Arabalar;
    Arabalar = (struct araba*) malloc(sizeof(struct araba));

    if(Arabalar == NULL)
    {
        printf("Bellek bolgenizde yeterli alan bulamadýk!");
        exit(1);
    }

    baslangic:
    system("cls");
    printf("\n*******************************\n");
    printf("*  YETKILI SERVIS OTOMASYONU  *\n");
    printf("*******************************\n\n");
    printf("\tISLEMLER     SEC\n");
    printf("________________________\n");
    printf("* Araclari Listele   (1)\n");
    printf("* Araclari DUzenle   (2)\n");
    printf("* Yeni Arac Ekle     (3)\n");
    printf("* Arac Sil           (4)\n");
    printf("* Kar-Zarar Belirle  (5)\n");
    printf("* Filtreli Arama     (6)\n");
    printf("* Cikis Yap!         (7)\n");
    printf("________________________\n");
    printf("\n\n");

    printf("Lutfen! Bir Secenek Seciniz: ");
    scanf("%d", &secenek);

    switch(secenek)
    {
        case 1:
            /** Arac listeleme (Start)*/
            baslangic_listele:
            if(adet != 0)
            {
                listele(Arabalar,adet);
            }
            else
            {
                printf("Listelenecek arac yok.\n");
            }
            printf("\n(1) Tekrar Listele (1)\n");
            printf("(2) Ana Menuye Don (2)\n");
            printf("(3) Cikis Yap!     (3)\n");
            printf("Secim Yapin:  ");
            scanf("%d", &alt_secenek);

            if(alt_secenek == 1)
            {
                alt_secenek = 0;
                goto baslangic_listele;
            }
            else if(alt_secenek == 2)
            {
                alt_secenek = 0;
                goto baslangic;
            }
            else if(alt_secenek == 3)
            {
                alt_secenek = 0;
                exit(0);
            }
            else
            {
                printf("Gecersiz Secim! Ana menuye aktariliyorsunuz!..\n");
                goto baslangic;
            }

            /** Arac listeleme (End)*/
            break;

        case 2:
            /** Arac Duzenle (Start)*/
            baslangic_duzenle:
            if(adet != 0)
            {
                duzenle(Arabalar);
                printf("Basarili Sekilde Duzenlendi\n");
            }
            else
            {
                printf("Duzenlenecek Arac yok!\n");
            }

            printf("\n(1) Tekrar Duzenle (1)\n");
            printf("(2) Ana Menuye Don (2)\n");
            printf("(3) Cikis Yap!     (3)\n");
            printf("Secim Yapin:  ");
            scanf("%d", &alt_secenek);

            if(alt_secenek == 1)
            {
                alt_secenek = 0;
                goto baslangic_duzenle;
            }
            else if(alt_secenek == 2)
            {
                alt_secenek = 0;
                goto baslangic;
            }
            else if(alt_secenek == 3)
            {
                alt_secenek = 0;
                exit(0);
            }
            else
            {
                printf("Gecersiz Secim! Ana menuye aktariliyorsunuz!..\n");
                goto baslangic;
            }
            /** Arac Duzenle (End)*/
            break;

        case 3:
            /** Arac Ekle (Start)*/

            baslangic_ekle:
            arac_ekle(&Arabalar, &adet);
            printf("Ekleme Islemi Basarili Sekilde Gerceklesti.\n");

            printf("\n(1) Tekrar Ekle    (1)\n");
            printf("(2) Ana Menuye Don (2)\n");
            printf("(3) Cikis Yap!     (3)\n");
            printf("Secim Yapin:  ");
            scanf("%d", &alt_secenek);


            if(alt_secenek == 1)
            {
                alt_secenek = 0;
                goto baslangic_ekle;
            }
            else if(alt_secenek == 2)
            {
                alt_secenek = 0;
                goto baslangic;
            }
            else if(alt_secenek == 3)
            {
                alt_secenek = 0;
                exit(0);
            }
            else
            {
                printf("Gecersiz Secim! Ana menuye aktariliyorsunuz!..\n");
                goto baslangic;
            }
            /** Arac Ekle (End)*/
            break;

        case 4:
            /** Arac Sil (Start)*/
            baslangic_sil:
            if(adet != 0)
            {
            sil(Arabalar,&adet);
            printf("Silme islemi Basarili Sekilde Gerceklesti.\n");
            }
            else
            {
                printf("Silinecek Arac bulunamadi!\n");
            }
            printf("\n(1) Tekrar Sil     (1)\n");
            printf("(2) Ana Menuye Don (2)\n");
            printf("(3) Cikis Yap!     (3)\n");
            printf("Secim Yapin:  ");
            scanf("%d", &alt_secenek);

            if(alt_secenek == 1)
            {
                alt_secenek = 0;
                goto baslangic_sil;
            }
            else if(alt_secenek == 2)
            {
                alt_secenek = 0;
                goto baslangic;
            }
            else if(alt_secenek == 3)
            {
                alt_secenek = 0;
                exit(0);
            }
            else
            {
                printf("Gecersiz Secim! Ana menuye aktariliyorsunuz!..\n");
                goto baslangic;
            }
            /** Arac Sil (End)*/
            break;

        case 5:
            /** Kar-Zarar Belirleme (Start)*/
            baslangic_hesapla:
            if(adet != 0)
            {
                hesapla(Arabalar,adet);
            }
            else
            {
                printf("Hesaplama Icin Arac Bulunamadi!\n");
            }

            printf("\n(1) Tekrar Hesapla (1)\n");
            printf("(2) Ana Menuye Don (2)\n");
            printf("(3) Cikis Yap!     (3)\n");
            printf("Secim Yapin:  ");
            scanf("%d", &alt_secenek);

            if(alt_secenek == 1)
            {
                alt_secenek = 0;
                goto baslangic_hesapla;
            }
            else if(alt_secenek == 2)
            {
                alt_secenek = 0;
                goto baslangic;
            }
            else if(alt_secenek == 3)
            {
                alt_secenek = 0;
                exit(0);
            }
            else
            {
                printf("Gecersiz Secim! Ana menuye aktariliyorsunuz!..\n");
                goto baslangic;
            }
            /** Kar-Zarar Belirleme (End) */
            break;

        case 6:
            /** Filtreli Arama (Start)*/
            baslangic_ara:
            if(adet != 0)
            {
                arama(Arabalar,adet);
            }
            else
            {
                printf("Arama icin Arac Bulunamadi!\n");
            }

            printf("\n(1) Tekrar Ara     (1)\n");
            printf("(2) Ana Menuye Don (2)\n");
            printf("(3) Cikis Yap!     (3)\n");
            printf("Secim Yapin:  ");
            scanf("%d", &alt_secenek);

            if(alt_secenek == 1)
            {
                alt_secenek = 0;
                goto baslangic_ara;
            }
            else if(alt_secenek == 2)
            {
                alt_secenek = 0;
                goto baslangic;
            }
            else if(alt_secenek == 3)
            {
                alt_secenek = 0;
                exit(0);
            }
            else
            {
                printf("Gecersiz Secim! Ana menuye aktariliyorsunuz!..\n");
                goto baslangic;
            }

            /** Filtreli Arama (End)*/
            break;

        case 7:
            /** Cikis (Star)*/
            exit(0);
            /** Cikis (End)*/

        default:
            printf("%d Gecerli bir secenek degildir!..\nLutfen gecerli bir secenek secin!\n", secenek);
            goto baslangic;
    }


    free(Arabalar);
    return 0;
}
