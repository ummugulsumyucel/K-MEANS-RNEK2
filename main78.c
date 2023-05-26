                       //K-MEANS K�MELEME ALGOR�TMASI//

/*Adana, Ankara, �stanbul, Bursa, Kocaeli, Sakarya, Mersin, �zmir, Antalya ve Van illerinin g�� verilerini kullanarak K-means k�meleme
 algoritmas�n� uygular. �lleri k�melerine atar, konverjans� kontrol eder ve sonu�lar� yazd�r�r. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 3  // K�me say�s�
#define N 10  // �l say�s�

// �l yap�s�
typedef struct {
    char ad[20];  // �l ad�
    double goc;  // G�� verisi
    int kumeId;  // K�me ID'si
} Sehir;

// �ki il aras�ndaki fark� hesaplar
double mesafe(Sehir sehir1, Sehir sehir2) {
    return fabs(sehir1.goc - sehir2.goc);
}

int main() {
    // �llerin g�� verilerini tan�mlama
    Sehir iller[N] = {
        {"Adana", 1000.0, 0},
        {"Ankara", 1500.0, 0},
        {"Istanbul", 1200.0, 0},
        {"Bursa", 800.0, 0},
        {"Kocaeli", 1100.0, 0},
        {"Sakarya", 1300.0, 0},
        {"Mersin", 900.0, 0},
        {"Izmir", 1600.0, 0},
        {"Antalya", 1400.0, 0},
        {"Van", 1800.0, 0}
    };

    // K�me merkezlerini tan�mlama
    Sehir merkezler[K] = {
        {"K�me 1", 900.0, 0},
        {"K�me 2", 1500.0, 0},
        {"K�me 3", 1100.0, 0}
    };

    // �l k�meleme i�lemi
    int iterasyon = 0;
    int uyumlu = 0;
    double esik = 0.001; // Konverjans e�i�i
    while (iterasyon < 100 && !uyumlu) {
        // �lleri k�meye atama
        int i = 0;
        while (i < N) {
            double minMesafe = __DBL_MAX__;
            int enYakinMerkez = 0;
            int j = 0;
            while (j < K) {
                double mesaf = mesafe(iller[i], merkezler[j]);
                if (mesaf < minMesafe) {
                    minMesafe = mesaf;
                    enYakinMerkez = j;
                }
                j++;
            }
            // �li en yak�n k�meye atama
            iller[i].kumeId = enYakinMerkez;

            i++;
        }

        // K�me merkezlerini g�ncelleme
        int k = 0;
        while (k < K) {
            double toplamGoc = 0.0;
            int ilSayisi = 0;
            int j = 0;
            while (j < N) {
            	 // �li ait oldu�u k�meye g�re kontrol etme
                if (iller[j].kumeId == k) {
                    toplamGoc += iller[j].goc;
                    ilSayisi++;
                }
                j++;
            }
            // K�me merkezini g�ncelleme
            merkezler[k].goc = toplamGoc / ilSayisi;

            k++;
        }

        // Konverjans� kontrol etme
        uyumlu = 1;
        int l = 0;
        while (l < K) {
            double mesafeToplami = 0.0;
            int ilSayisi = 0;
            int j = 0;
            while (j < N) {
                // �li ait oldu�u k�meye g�re kontrol etme
                if (iller[j].kumeId == l) {
                    mesafeToplami += mesafe(iller[j], merkezler[l]);
                    ilSayisi++;
                }
                j++;
            }
            // Ortalama mesafeyi hesaplama
            double ortalamaMesafe = mesafeToplami / ilSayisi;
            // Konverjans kontrol�
            if (ortalamaMesafe > esik) {
                uyumlu = 0;
                break;
            }

            l++;
        }

        iterasyon++;
    }

    // Sonu�lar� yazd�rma
    printf("Kumeleme Sonuclari:\n");
    int m = 0;
    while (m < N) {
        printf("%s => Kategori: %d\n", iller[m].ad, iller[m].kumeId + 1);
        m++;
    }

    return 0;
}
