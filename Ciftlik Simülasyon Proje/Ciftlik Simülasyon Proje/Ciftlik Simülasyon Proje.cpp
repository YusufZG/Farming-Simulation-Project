/****************************************************************************
**
SAKARYA ÜNİVERSİTESİ
**
**
**
**
**
**
**
**
BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
PROGRAMLAMAYA GİRİŞİ DERSİ
ÖDEV NUMARASI:2.Odev
ÖĞRENCİ ADI:Yusuf Ziya Gök
ÖĞRENCİ NUMARASI:B231210046
DERS GRUBU:1.Ogretim A grubu
****************************************************************************/


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Tavuk {
private:
    int yumurtasizGun;
    int toplamYumurta;
    int gelisGunSayisi; //tavuk classının degiskenleri

public:
    Tavuk() : yumurtasizGun(0), toplamYumurta(0), gelisGunSayisi(0) {}


    void yemYe(double& yemDeposu, double& toplamYemTuketimi, double yemFiyati) {
        double gunlukYemTuketimi = (rand() % 21 + 100) / 1000.0; // 100-120 gram
        if (yemDeposu >= gunlukYemTuketimi) {
            yemDeposu -= gunlukYemTuketimi;
            toplamYemTuketimi += gunlukYemTuketimi;
        }
    }//yem yedirme fonksiyonu


    int yumurtla() {
        if (gelisGunSayisi >= 3) {
            int yumurtaSayisi = rand() % 3; // 0, 1 veya 2 yumurta
            toplamYumurta += yumurtaSayisi;
            if (yumurtaSayisi == 0) {
                yumurtasizGun++;
            }
            else {
                yumurtasizGun = 0;
            }
            return yumurtaSayisi;
        }
        gelisGunSayisi++;
        return 0;//yumurtlama fonksiyonu talimatlardaki gibi 3 gün olana kadar yumurtasız günü sayıyor
    }





    bool kesimDurumu() const {
        return yumurtasizGun >= 3 || toplamYumurta >= 100;
    }//kesim durumuna bakan fonksiyon

    void reset() {
        yumurtasizGun = 0;
        toplamYumurta = 0;
        gelisGunSayisi = 0;
    }//yeni tavuk gelince degerleri 0 layan fonksiyon
};

class Ciftlik {
private:
    double sermaye;
    double yemDeposu;
    double yemFiyati;
    double yumurtaFiyati;
    double tavukFiyati;
    vector<Tavuk> tavuklar;
    //çiftlik classında kullanıcıdan alınacak degiskenler

public: //sermayeye duruma göre yapılan degisimler ve 
    Ciftlik(double baslangicSermaye, int tavukSayisi, double yemFiyati, double yumurtaFiyati, double tavukFiyati)
        : sermaye(baslangicSermaye), yemDeposu(700), yemFiyati(yemFiyati), yumurtaFiyati(yumurtaFiyati), tavukFiyati(tavukFiyati) {
        tavuklar = vector<Tavuk>(tavukSayisi);
        sermaye -= tavukSayisi * tavukFiyati;
    }

    void simulasyonYap(int gunSayisi) {
        for (int gun = 1; gun <= gunSayisi; ++gun) {
            double toplamYemTuketimi = 0;
            int toplamYumurta = 0;

            for (auto& tavuk : tavuklar) {
                tavuk.yemYe(yemDeposu, toplamYemTuketimi, yemFiyati);
                toplamYumurta += tavuk.yumurtla();
                if (tavuk.kesimDurumu()) {
                    sermaye += tavukFiyati / 2; // Kesim geliri
                    sermaye -= tavukFiyati; // Yeni tavuk alım
                    tavuk.reset();
                }
            }

            if (yemDeposu < 70) {
                double yemSatinAlmaMaliyeti = 700 * yemFiyati;
                sermaye -= yemSatinAlmaMaliyeti;
                yemDeposu += 700;
            }

            double yumurtaGeliri = toplamYumurta * yumurtaFiyati;
            sermaye += yumurtaGeliri; //yumurta geliri



            cout << "Gün " << gun << ": "
                << "Yem tüketimi: " << toplamYemTuketimi << " kg, "
                << "Yumurta sayısı: " << toplamYumurta << ", "
                << "Gelir: " << yumurtaGeliri << ", "
                << "Kalan sermaye: " << sermaye << endl;

            if (sermaye < 0) {
                cout << "İflas ettiniz" << endl;
                break;
            }//sermayenin 0 altına düşmesi durumunda simülasyonu bitirme
        }
    }
};

int main() {
    setlocale(LC_ALL, "Turkish");//türkçe karakterlerin sorun çıkarmaması için
    srand(time(0));

    double baslangicSermaye, yemFiyati, yumurtaFiyati, tavukFiyati;
    int tavukSayisi, simulasyonGunleri;

    cout << "Başlangıç sermayesi: ";
    cin >> baslangicSermaye;

    cout << "Çiftlikte kaç tavuk olacak (en fazla 500): ";
    cin >> tavukSayisi;
    if (tavukSayisi > 500) {
        cout << "Maksimum tavuk sayısı 500 olabilir!" << endl;
        return 1;
    }

    cout << "Tavuk yeminin kilogram fiyatı: ";
    cin >> yemFiyati;

    cout << "Yumurtanın satış fiyatı: ";
    cin >> yumurtaFiyati;

    cout << "Tavuk alım fiyatı: ";
    cin >> tavukFiyati;

    cout << "Simülasyon yapılacak gün sayısı: ";
    cin >> simulasyonGunleri;

    Ciftlik ciftlik(baslangicSermaye, tavukSayisi, yemFiyati, yumurtaFiyati, tavukFiyati);
    ciftlik.simulasyonYap(simulasyonGunleri);

    return 0;
}
