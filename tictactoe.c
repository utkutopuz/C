#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//global degiskenler
char Tahta[3][3];//3x3lük alan
const char OYUNCU = 'X'; //biz x'i kullanıcaz
const char RAKIP = 'O';//rakip o'yu kullanıcak

void resetTahta();// 2D karakter dizisi resetlenmesi
void printTahta();//2D karakter dizisi yazdırma
int bosKontrol();//tahtada boş yer olmasını kontrol
void oyuncuMove();//oyuncunun oynama sırası gelince çalış
void rakipMove();//yapay zekanın sırası gelince çalış
char kazananKontrol();//kazanan oyuncu kontrol
void printKazanan(char);//kazananı printler
//fonksiyonların bodyleri main'in altındadır.

int main() {
    char kazanan = ' ';
    char tekrar = ' ';
    resetTahta();
    do {
        char kazanan = ' ';
        char tekrar = ' ';//tekrar oynanmak istenmesi halinde 
        resetTahta();//oyun başlamadan tahta resetlensin

        while (kazanan == ' ' && bosKontrol() != 0) {
            printTahta();//tahtayı göster, bastır.

            oyuncuMove();//oyuncu hamlesini yapar.
            kazanan = kazananKontrol();//kazanan var mı yok mu

            if (kazanan != ' ' || bosKontrol() == 0) {
                //eğer bir kazanan varsa veya tahtada boş yer yoksa durdur
                break;
            }
            rakipMove();//rakibin oyunu
            kazanan = kazananKontrol();//her hamleden sonra kazanan kontrol
            if (kazanan != ' ' || bosKontrol() == 0) {
                break;
            }
        }
        printTahta();//tahtanın son durumunu yazdırır.
        printKazanan(kazanan);//kazanan'ı yazdırır

        printf("\nTekrar oynamak ister misin? (E/H): ");
        scanf(" %c", &tekrar);
        tekrar = toupper(tekrar);
    } while (tekrar == 'E');
    printf("Oynadığın için teşekkürler.\n");
    return 0;
}

void resetTahta() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Tahta[i][j] = ' ';//bütün yerler boş olsun 
        }
    }
}

void printTahta() {
    printf("%c | %c | %c\n", Tahta[0][0], Tahta[0][1], Tahta[0][2]);
    printf("---|---|---\n");
    printf("%c | %c | %c\n", Tahta[1][0], Tahta[1][1], Tahta[1][2]);
    printf("---|---|---\n");
    printf("%c | %c | %c\n", Tahta[2][0], Tahta[2][1], Tahta[2][2]);
}

int bosKontrol() {
    int bosAlan = 9;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (Tahta[i][j] != ' ') {
                bosAlan--;//boş alan başta 9du.
                //iç ve dış döngü 3 kere döneceğinden toplamda 9 kere azaltacak.
            //0 olduğunda ise boş alan kalmamış olacak.
            }
        }
    }
    return bosAlan;
}

void oyuncuMove() {
    int x, y;

    do {
        printf("Satır giriniz (1-3): ");
        scanf("%d", &x);
        x--;

        printf("Sütun giriniz (1-3): ");
        scanf("%d", &y);
        y--;

        if (Tahta[x][y] != ' ') {//ilgili kısım boş mu
            printf("Geçersiz hamle!\n");
        } else {
            Tahta[x][y] = OYUNCU;//oyuncu isteği üzerine olan kısmı doldur
            break;
        }

    } while (Tahta[x][y] != ' ');//boş değil ise
}

void rakipMove() {
    srand(time(NULL));
    int x, y;

    if (bosKontrol() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;//rastgele atama

        } while (Tahta[x][y] != ' ');

        Tahta[x][y] = RAKIP;//rakibin hamlesi
    } else {
        printKazanan(' ');
    }
}

char kazananKontrol() {
    //kazanma senaryolarını içerir
    for (int i = 0; i < 3; i++) {
        if (Tahta[i][0] == Tahta[i][1] && Tahta[i][0] == Tahta[i][2]) {
            return Tahta[i][0];
        }
    }

    for (int i = 0; i < 3; i++) {
        if (Tahta[0][i] == Tahta[1][i] && Tahta[0][i] == Tahta[2][i]) {
            return Tahta[0][i];
        }
    }

    if (Tahta[0][0] == Tahta[1][1] && Tahta[0][0] == Tahta[2][2]) {
        return Tahta[0][0];
    }

    if (Tahta[0][2] == Tahta[1][1] && Tahta[0][2] == Tahta[2][0]) {
        return Tahta[0][2];
    }

    return ' ';
}

void printKazanan(char kazanan) {
    if (kazanan == OYUNCU) {
        printf("Kazandın!\n");
    } else if (kazanan == RAKIP) {
        printf("Kaybettiniz!\n");

    } else {
        printf("Berabere!\n");
    }
}
