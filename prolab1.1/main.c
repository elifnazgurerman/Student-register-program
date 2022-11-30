#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Created by Elif Naz Gürerman and Yiğit Erdinç

struct kayit {
    int ogrNo;
    int dersKodu;
    int puan;
    bool silinmis;
};

bool dosyaVarmiKontrolEt(const char *dosyaAdi) {
    bool dosyaVarmi = false;

    FILE *dosya = fopen(dosyaAdi, "r");

    if (dosya != NULL)
    {
        dosyaVarmi = true;
    }

    fclose(dosya);

    return dosyaVarmi;
}

long int dosyaBoyutuBul(FILE *dosya)
{
    fseek(dosya, 0L, SEEK_END);
    long int boyut = ftell(dosya);
    return boyut;
}

int ikiliArama(int dizi[], int x, int dusuk, int yuksek) {
  while (dusuk <= yuksek) {
    int medyan = dusuk + (yuksek - dusuk) / 2;

    if (dizi[medyan] == x)
      return medyan;

    if (dizi[medyan] < x)
      dusuk = medyan + 1;

    else
      yuksek = medyan - 1;
  }
  return -1;
}

void indeksSirala(int anahtar[], int adres[], int satirSayisi) {
    for (int i = 0; i < satirSayisi; i++) {
        for (int j = i + 1; j < satirSayisi; j++) {
            if (anahtar[i] > anahtar[j]) {
                int a = anahtar[i];
                anahtar[i] = anahtar[j];
                anahtar[j] = a;
                int b = adres[i];
                adres[i] = adres[j];
                adres[j] = b;
            }
        }
    }
}

int satirSayisiBul(const char *dosyaAdi) {
   char karakter;
   int satirSayisi = 0;

   FILE *dosya = fopen(dosyaAdi,"r");

   while((karakter = fgetc(dosya)) != EOF) {
      if(karakter == '\n')
         satirSayisi++;
   }

   fclose(dosya);

   return satirSayisi;
}

void indexDosyasiOlustur() {
    char *indexDosyasiIsmi = "indexDosyasi.txt";
    char *veriDosyasiIsmi = "veriDosyasi.bin";

    if (dosyaVarmiKontrolEt(indexDosyasiIsmi)) {
        printf("Index Dosyasi Olustur \n \n");

        printf("Index dosyasi dizinde mevcut. \n");

        int satirSayisi = satirSayisiBul(indexDosyasiIsmi);

        int anahtar[satirSayisi];
        int adres[satirSayisi];

        FILE *indexDosyasi = fopen(indexDosyasiIsmi, "r");

        for (int i = 0; i < satirSayisi; i++) {
            fscanf(indexDosyasi, "%d %d", &anahtar[i], &adres[i]);
        }

        indexDosyasi = fopen(indexDosyasiIsmi, "w");

        indeksSirala(anahtar, adres, satirSayisi);

        for (int i = 0; i < satirSayisi; i++) {
            fprintf(indexDosyasi, "%d %d", anahtar[i], adres[i]);
            fprintf(indexDosyasi, "\n");
        }

        fclose(indexDosyasi);

        printf("Index dosyasi siralandi. \n\n");
    }

    else {
        if (dosyaVarmiKontrolEt(veriDosyasiIsmi)) {
            printf("Index Dosyasi Olustur \n \n");

            FILE *indexDosyasi = fopen(indexDosyasiIsmi, "w");
            FILE *veriDosyasi = fopen(veriDosyasiIsmi, "rb");

            printf("Index dosyasi olusturuldu. \n");

            int veriSayisi = dosyaBoyutuBul(indexDosyasi) / 16;

            int anahtar[veriSayisi];
            int adres[veriSayisi];
            int silinmis[veriSayisi];

            int anahtarSirasi = 0;
            int adresSirasi = 0;
            int adresBoyutu = 0;

            fseek(indexDosyasi, 0L, SEEK_SET);

            struct kayit kayitlar;
            while(fread(&kayitlar, sizeof(struct kayit), 1, veriDosyasi)) {
                anahtar[anahtarSirasi] = kayitlar.ogrNo;
                silinmis[anahtarSirasi] = kayitlar.silinmis;
                adres[anahtarSirasi] = adresBoyutu;

                anahtarSirasi++;
                adresSirasi++;
                adresBoyutu = adresBoyutu + 16;
            }

            indeksSirala(anahtar, adres, veriSayisi);

            for (int i = 0; i < veriSayisi; i++) {
                if (silinmis[i] != true) {
                    fprintf(indexDosyasi, "%d %d", anahtar[i], adres[i]);
                    fprintf(indexDosyasi, "\n");
                }
            }

            fclose(indexDosyasi);
            fclose(indexDosyasi);

            printf("Index dosyasi siralandi. \n\n");
        }
        else {
            printf("Index Dosyasi Olustur \n \n");

            FILE *indexDosyasi = fopen(indexDosyasi, "w");

            printf("Index dosyasi olusturuldu. \n\n");

            fclose(indexDosyasi);
        }
    }
}

void kayitEkle() {
    char *veriDosyasiIsmi = "veriDosyasi.bin";
    char *indexDosyasiIsmi = "indexDosyasi.txt";

    if (dosyaVarmiKontrolEt(veriDosyasiIsmi)) {
        if (dosyaVarmiKontrolEt(indexDosyasiIsmi)) {

            int kaydedilecekOgrenciSayisi;

            printf("Kaydedilecek ogrenci sayisini giriniz: ");
            scanf("%d", &kaydedilecekOgrenciSayisi);

            for (int i = 0; i < kaydedilecekOgrenciSayisi; i++) {
                struct kayit kayitlar;

                FILE *indexDosyasi = fopen(indexDosyasiIsmi, "a+");
                FILE *veriDosyasi = fopen(veriDosyasiIsmi, "ab+");

                int ogrNo;
                int dersKodu;
                int puan;

                long int boyut = dosyaBoyutuBul(veriDosyasi);

                printf("\n\nOgrenci numarasini giriniz: ");
                scanf("%d", &ogrNo);
                kayitlar.ogrNo = ogrNo;

                printf("\nDers kodunu giriniz: ");
                scanf("%d", &dersKodu);
                kayitlar.dersKodu = dersKodu;

                printf("\nPuani giriniz: ");
                scanf("%d", &puan);
                kayitlar.puan = puan;

                fprintf(indexDosyasi, "%d %ld", ogrNo, boyut);
                fprintf(indexDosyasi, "\n");
                fwrite(&kayitlar, sizeof(struct kayit), 1, veriDosyasi);
                fclose(indexDosyasi);
                fclose(veriDosyasi);
            }

            int satirSayisi = satirSayisiBul(indexDosyasiIsmi);


            int anahtar[satirSayisi];
            int adres[satirSayisi];

            FILE *indexDosyasi = fopen(indexDosyasiIsmi, "r");


            for (int i = 0; i < satirSayisi; i++) {
                fscanf(indexDosyasi, "%d %d", &anahtar[i], &adres[i]);
            }

            indexDosyasi = fopen(indexDosyasi, "w");

            indeksSirala(anahtar, adres, satirSayisi);

            for (int i = 0; i < satirSayisi; i++) {
                fprintf(indexDosyasi, "%d %d", anahtar[i], adres[i]);
                fprintf(indexDosyasi, "\n");
            }

            fclose(indexDosyasi);
        }

        else {
            printf("\nOncelikle bir index dosyasi olusturuz.");
        }
    }

    else {
        printf("Kayit Ekle \n \n");

        printf("Kayit eklenecek bir veri dosyasi yok. \n");

        FILE *fp = fopen(veriDosyasiIsmi, "wb");
        fclose(fp);

        printf("Bos bir veri dosyasi yaratildi. \n");

        printf("Kayit eklemek icin 2 girin, ya da ana menuye donmek icin 0 girin. \n");
    }
};

void kayitBul() {
    char *veriDosyasiIsmi = "veriDosyasi.bin";
    char *indexDosyasiIsmi = "indexDosyasi.txt";

    if (dosyaVarmiKontrolEt(veriDosyasiIsmi)) {
        if (dosyaVarmiKontrolEt(indexDosyasiIsmi)) {
            int satirSayisi = satirSayisiBul(indexDosyasiIsmi);

            FILE *indexDosyasi = fopen(indexDosyasiIsmi, "r");

            int anahtar[satirSayisi];
            int adres[satirSayisi];

            int arananAnahtar;
            printf("\nAradiginiz ogrenci numarasini giriniz: ");
            scanf("%d", &arananAnahtar);

            int bulunanAnahtarlar[satirSayisi];
            int bulunanAdresler[satirSayisi];

            for (int i = 0; i < satirSayisi; i++) {
                fscanf(indexDosyasi, "%d %d", &anahtar[i], &adres[i]);
            }

            int bulunanAnahtarSayisi = 0;

            for (;;) {
                int n = sizeof(anahtar) / sizeof(anahtar[0]);
                int sonuc = ikiliArama(anahtar, arananAnahtar, 0, n-1);
                if (sonuc != -1) {
                    anahtar[sonuc] = -1;
                    bulunanAdresler[bulunanAnahtarSayisi] = adres[sonuc];
                    bulunanAnahtarSayisi++;
                    indeksSirala(anahtar, adres, satirSayisi);
                }
                else {
                    break;
                }
            }

            FILE *veriDosyasi = fopen(veriDosyasiIsmi, "rb");

            for (int i = 0; bulunanAnahtarSayisi > 0; bulunanAnahtarSayisi--) {
                fseek(veriDosyasi, bulunanAdresler[i], SEEK_SET);

                struct kayit kayitlar;
                fread(&kayitlar, sizeof(struct kayit), 1, veriDosyasi);
                printf ("Ogrenci Numarasi: %d, Ders Kodu: %d, Puan: %d \n", kayitlar.ogrNo, kayitlar.dersKodu, kayitlar.puan);
                i++;
            }
            fclose(veriDosyasi);
            fclose(indexDosyasi);
            printf("\n");
        }

        else {
            printf("\nOncelikle bir index dosyasi olusturuz.");
        }
    }

    else {
        printf("Kayit Bul \n \n");

        printf("Kayit bulunacak bir veri dosyasi yok. \n");

        FILE *fp = fopen(veriDosyasiIsmi, "wb");
        fclose(fp);

        printf("Bos bir veri dosyasi yaratildi. \n");

        printf("Kayit eklemek icin 2 girin, ya da ana menuye donmek icin 0 girin. \n");
    }
};

void kayitSil() {
    char *veriDosyasiIsmi = "veriDosyasi.bin";
    char *indexDosyasiIsmi = "indexDosyasi.txt";

    if (dosyaVarmiKontrolEt(veriDosyasiIsmi)) {
        if (dosyaVarmiKontrolEt(indexDosyasiIsmi)) {
            int satirSayisi = satirSayisiBul(indexDosyasiIsmi);

            FILE *indexDosyasi = fopen(indexDosyasiIsmi, "r");

            int anahtar[satirSayisi];
            int eksikAnahtar[satirSayisi];
            int adres[satirSayisi];

            int arananAnahtar;
            printf("Silinecek ogrenci numarasini giriniz: ");
            scanf("%d", &arananAnahtar);

            int bulunanAnahtarlar[satirSayisi];
            int bulunanAdresler[satirSayisi];

            for (int i = 0; i < satirSayisi; i++) {
                int temp;
                fscanf(indexDosyasi, "%d %d", &temp, &adres[i]);
                anahtar[i] = temp;
                eksikAnahtar[i] = temp;
            }

            int bulunanAnahtarSayisi = 0;
            int silinebilenAnahtarlar[satirSayisi];

            for (;;) {
                int n = sizeof(anahtar) / sizeof(anahtar[0]);
                int sonuc = ikiliArama(anahtar, arananAnahtar, 0, n);
                if (sonuc != -1) {
                    silinebilenAnahtarlar[bulunanAnahtarSayisi] = sonuc;
                    bulunanAdresler[bulunanAnahtarSayisi] = adres[sonuc];
                    anahtar[sonuc] = -1;

                    bulunanAnahtarSayisi++;
                    indeksSirala(anahtar, adres, satirSayisi);
                }
                else {
                    break;
                }
            }

            FILE *veriDosyasi = fopen(veriDosyasiIsmi, "rb+");

            int silinecekSira;
            int numaralar[bulunanAnahtarSayisi];
            int dersKodlari[bulunanAnahtarSayisi];
            int puanlar[bulunanAnahtarSayisi];

            for (int i = 0; bulunanAnahtarSayisi > 0; bulunanAnahtarSayisi--) {
                fseek(veriDosyasi, bulunanAdresler[i], SEEK_SET);

                struct kayit kayitlar;
                fread(&kayitlar, sizeof(struct kayit), 1, veriDosyasi);
                numaralar[i] = kayitlar.ogrNo;
                dersKodlari[i] = kayitlar.dersKodu;
                puanlar[i] = kayitlar.puan;
                printf ("Sira: %d, Ders Kodu: %d, Puan: %d \n", i, kayitlar.dersKodu, kayitlar.puan);
                i++;
            }

            printf("Silinecek dersin sirasini giriniz: ");
            scanf("%d", &silinecekSira);

            struct kayit silinenecekKayit;
            silinenecekKayit.ogrNo = numaralar[silinecekSira];
            silinenecekKayit.dersKodu = dersKodlari[silinecekSira];
            silinenecekKayit.puan = puanlar[silinecekSira];
            silinenecekKayit.silinmis = true;

            int silinenSira = silinebilenAnahtarlar[silinecekSira];

            eksikAnahtar[silinenSira] = -1;

            fseek(veriDosyasi, bulunanAdresler[silinecekSira], SEEK_SET);

            fwrite(&silinenecekKayit, sizeof(struct kayit), 1, veriDosyasi);

            indexDosyasi = fopen(indexDosyasiIsmi, "w");

            indeksSirala(anahtar, adres, satirSayisi);

            for (int i = 0; i < satirSayisi; i++) {
                if (eksikAnahtar[i] != -1) {
                    fprintf(indexDosyasi, "%d %d", eksikAnahtar[i], adres[i]);
                    fprintf(indexDosyasi, "\n");
                }
            }

            fclose(veriDosyasi);
            fclose(indexDosyasi);
            printf("\n");
        }

        else {
            printf("\nOncelikle bir index dosyasi olusturuz.");
        }
    }

    else {
        printf("Kayit Sil \n \n");

        printf("Kayit silinecek bir veri dosyasi yok. \n");

        FILE *fp = fopen(veriDosyasiIsmi, "wb");
        fclose(fp);

        printf("Bos bir veri dosyasi yaratildi. \n");

        printf("Kayit eklemek icin 2 girin, ya da ana menuye donmek icin 0 girin. \n");
    }
};

void kayitGuncelle() {
    char *veriDosyasiIsmi = "veriDosyasi.bin";
    char *indexDosyasiIsmi = "indexDosyasi.txt";

    if (dosyaVarmiKontrolEt(veriDosyasiIsmi)) {
        if (dosyaVarmiKontrolEt(indexDosyasiIsmi)) {
            int satirSayisi = satirSayisiBul(indexDosyasiIsmi);

            FILE *indexDosyasi = fopen(indexDosyasiIsmi, "r");

            int anahtar[satirSayisi];
            int adres[satirSayisi];

            int arananAnahtar;
            printf("Guncellenecek ogrenci numarasini giriniz: ");
            scanf("%d", &arananAnahtar);

            int bulunanAnahtarlar[satirSayisi];
            int bulunanAdresler[satirSayisi];

            for (int i = 0; i < satirSayisi; i++) {
                fscanf(indexDosyasi, "%d %d", &anahtar[i], &adres[i]);
            }

            int bulunanAnahtarSayisi = 0;

            for (;;) {
                int n = sizeof(anahtar) / sizeof(anahtar[0]);
                int sonuc = ikiliArama(anahtar, arananAnahtar, 0, n-1);
                if (sonuc != -1) {
                    anahtar[sonuc] = -1;
                    bulunanAdresler[bulunanAnahtarSayisi] = adres[sonuc];
                    bulunanAnahtarSayisi++;
                    indeksSirala(anahtar, adres, satirSayisi);
                }
                else {
                    break;
                }
            }

            FILE *veriDosyasiPointer = fopen(veriDosyasiIsmi, "rb+");

            int guncellenecekSira;
            int numaralar[bulunanAnahtarSayisi];
            int dersKodlari[bulunanAnahtarSayisi];

            for (int i = 0; bulunanAnahtarSayisi > 0; bulunanAnahtarSayisi--) {
                fseek(veriDosyasiPointer, bulunanAdresler[i], SEEK_SET);

                struct kayit kayitlar;
                fread(&kayitlar, sizeof(struct kayit), 1, veriDosyasiPointer);
                numaralar[i] = kayitlar.ogrNo;
                dersKodlari[i] = kayitlar.dersKodu;
                printf ("Sira: %d, Ders Kodu: %d, Puan: %d \n", i, kayitlar.dersKodu, kayitlar.puan);
                i++;
            }

            printf("\nGuncellemek dersin sirasini giriniz: ");
            scanf("%d", &guncellenecekSira);

            struct kayit guncellenecekKayit;
            guncellenecekKayit.ogrNo = numaralar[guncellenecekSira];
            guncellenecekKayit.dersKodu = dersKodlari[guncellenecekSira];

            int yeniPuan;
            printf("\nYeni puani giriniz: ");
            scanf("%d", &yeniPuan);
            guncellenecekKayit.puan = yeniPuan;

            fseek(veriDosyasiPointer, bulunanAdresler[guncellenecekSira], SEEK_SET);

            fwrite(&guncellenecekKayit, sizeof(struct kayit), 1, veriDosyasiPointer);

            fclose(veriDosyasiPointer);
            fclose(indexDosyasi);
            printf("\n");
        }

        else {
            printf("\nOncelikle bir index dosyasi olusturuz.");
        }
    }

    else {
        printf("Kayit Guncelle \n \n");

        printf("Kayit guncelleyecek bir veri dosyasi yok. \n");

        FILE *fp = fopen(veriDosyasiIsmi, "wb");
        fclose(fp);

        printf("Bos bir veri dosyasi yaratildi. \n");

        printf("Kayit eklemek icin 2 girin, ya da ana menuye donmek icin 0 girin. \n");
    }
}

void veriDosyasiniGoster() {
    char *veriDosyasiIsmi = "veriDosyasi.bin";

    if (dosyaVarmiKontrolEt(veriDosyasiIsmi)) {
        printf("Veri Dosyasini Goster \n \n");

        FILE *veriDosyasi = fopen(veriDosyasiIsmi, "rb");

        struct kayit kayitlar;

        while(fread(&kayitlar, sizeof(struct kayit), 1, veriDosyasi)) {
            if (kayitlar.silinmis != true) {
                printf ("Ogrenci Numarasi: %d, Ders Kodu: %d, Puan: %d \n", kayitlar.ogrNo, kayitlar.dersKodu, kayitlar.puan);
            }
        }
		fclose(veriDosyasi);
    }

    else {
        printf("Veri Dosyasini Goster \n \n");

        printf("Kayit gosterilecek bir veri dosyasi yok. \n");

        printf("Lutfen kayit ekleyiniz. \n");
    }
}

void indeksDosyasiniGoster() {
    char *indexDosyasiIsmi = "indexDosyasi.txt";

    if (dosyaVarmiKontrolEt(indexDosyasiIsmi)) {
        FILE *indexDosyasi = fopen(indexDosyasiIsmi, "r");

        const unsigned MAX_LENGTH = 256;
        char buffer[MAX_LENGTH];

        printf("Index Dosyasini Goster \n \n");

        while (fgets(buffer, MAX_LENGTH, indexDosyasi)) {
            printf("%s", buffer);
        }
        fclose(indexDosyasi);
    }

    else {
        printf("Index Dosyasini Goster \n \n");
        printf("Index gosterilecek bir index dosyasi yok. \n\n");
    }
}

void indeksDosyasiniSil() {
    char *indexDosyasiIsmi = "indexDosyasi.txt";

    if (dosyaVarmiKontrolEt(indexDosyasiIsmi)) {
        remove(indexDosyasiIsmi);
        printf("Index Dosyasini Sil \n \n");
        printf("Index dosyasi silindi. \n\n");
    }

    else {
        printf("Index Dosyasini Sil \n \n");
        printf("Silinecek bir index dosyasi yok. \n\n");
    }
}

void sayfaGoster(int page) {
    int secilenSayfa;
    switch (page) {
        case 0:
        system("cls");
        printf("Lutfen seciniz:\n");
        printf("1. Index Dosyasi Olustur \n");
        printf("2. Kayit Ekle \n");
        printf("3. Kayit Bul \n");
        printf("4. Kayit Sil \n");
        printf("5. Kayit Guncelle \n");
        printf("6. Veri Dosyasini Goster \n");
        printf("7. Indeks Dosyasini Goster \n");
        printf("8. Indeks Dosyasini Sil \n");
        printf("9. Cikis \n");

        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 1:
        system("cls");

        indexDosyasiOlustur();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 2:
        system("cls");
        printf("Kayit Ekle \n \n");

        kayitEkle();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 3:
        system("cls");

        kayitBul();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 4:
        system("cls");

        kayitSil();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 5:
        system("cls");

        kayitGuncelle();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 6:
        system("cls");

        veriDosyasiniGoster();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 7:
        system("cls");

        indeksDosyasiniGoster();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 8:
        system("cls");

        indeksDosyasiniSil();

        printf("\nAna menuye donmek icin 0 giriniz.\n");
        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);

        case 9:
        exit(0);

        default:
        system("cls");
        printf("Lutfen seciniz:\n");
        printf("1. Index Dosyasi Olustur \n");
        printf("2. Kayit Ekle \n");
        printf("3. Kayit Bul \n");
        printf("4. Kayit Sil \n");
        printf("5. Kayit Guncelle \n");
        printf("6. Veri Dosyasini Goster \n");
        printf("7. Indeks Dosyasini Goster \n");
        printf("8. Indeks Dosyasini Sil \n \n");
        printf("Lutfen belirtilen aralikta sayi giriniz. \n");

        printf("Seciminiz: ");
        scanf("%d", &secilenSayfa);
        sayfaGoster(secilenSayfa);
    }
}

int main() {
    sayfaGoster(0);
}
