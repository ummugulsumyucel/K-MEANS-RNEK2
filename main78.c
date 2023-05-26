                       //K-MEANS KÜMELEME ALGORÝTMASI//

/*Adana, Ankara, Ýstanbul, Bursa, Kocaeli, Sakarya, Mersin, Ýzmir, Antalya ve Van illerinin göç verilerini kullanarak K-means kümeleme
 algoritmasýný uygular. Ýlleri kümelerine atar, konverjansý kontrol eder ve sonuçlarý yazdýrýr. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 3  // Küme sayýsý
#define N 10  // Ýl sayýsý

// Ýl yapýsý
typedef struct {
    char ad[20];  // Ýl adý
    double goc;  // Göç verisi
    int kumeId;  // Küme ID'si
} Sehir;

// Ýki il arasýndaki farký hesaplar
double mesafe(Sehir sehir1, Sehir sehir2) {
    return fabs(sehir1.goc - sehir2.goc);
}

int main() {
    // Ýllerin göç verilerini tanýmlama
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

    // Küme merkezlerini tanýmlama
    Sehir merkezler[K] = {
        {"Küme 1", 900.0, 0},
        {"Küme 2", 1500.0, 0},
        {"Küme 3", 1100.0, 0}
    };

    // Ýl kümeleme iþlemi
    int iterasyon = 0;
    int uyumlu = 0;
    double esik = 0.001; // Konverjans eþiði
    while (iterasyon < 100 && !uyumlu) {
        // Ýlleri kümeye atama
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
            // Ýli en yakýn kümeye atama
            iller[i].kumeId = enYakinMerkez;

            i++;
        }

        // Küme merkezlerini güncelleme
        int k = 0;
        while (k < K) {
            double toplamGoc = 0.0;
            int ilSayisi = 0;
            int j = 0;
            while (j < N) {
            	 // Ýli ait olduðu kümeye göre kontrol etme
                if (iller[j].kumeId == k) {
                    toplamGoc += iller[j].goc;
                    ilSayisi++;
                }
                j++;
            }
            // Küme merkezini güncelleme
            merkezler[k].goc = toplamGoc / ilSayisi;

            k++;
        }

        // Konverjansý kontrol etme
        uyumlu = 1;
        int l = 0;
        while (l < K) {
            double mesafeToplami = 0.0;
            int ilSayisi = 0;
            int j = 0;
            while (j < N) {
                // Ýli ait olduðu kümeye göre kontrol etme
                if (iller[j].kumeId == l) {
                    mesafeToplami += mesafe(iller[j], merkezler[l]);
                    ilSayisi++;
                }
                j++;
            }
            // Ortalama mesafeyi hesaplama
            double ortalamaMesafe = mesafeToplami / ilSayisi;
            // Konverjans kontrolü
            if (ortalamaMesafe > esik) {
                uyumlu = 0;
                break;
            }

            l++;
        }

        iterasyon++;
    }

    // Sonuçlarý yazdýrma
    printf("Kumeleme Sonuclari:\n");
    int m = 0;
    while (m < N) {
        printf("%s => Kategori: %d\n", iller[m].ad, iller[m].kumeId + 1);
        m++;
    }

    return 0;
}
