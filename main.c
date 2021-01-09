#include <stdio.h>
#include <stdlib.h>

char plansza[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int linie[24] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,

        0, 4, 6,
        1, 4, 7,
        2, 5, 8,

        0, 4, 8,
        2, 4, 6,
};


void rysujPlansze() {
    printf("Gracz (x)  -  SI (o)\n\n\n");


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", plansza[0], plansza[1], plansza[2]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", plansza[3], plansza[4], plansza[5]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", plansza[6], plansza[7], plansza[8]);

    printf("     |     |     \n\n");
}

int czyPolePuste(int index){
    return plansza[index] != 'x' && plansza[index] != 'o';
}

void reset() {
    for (int i = 0; i <= 8; ++i) {
        plansza[i] = '1' + i;
    }
}

void ruchGracza() {
    int wybranePole;
    int wybranyIndex;
    printf("wybierz pole od 1 do 9: ");
    do {
        scanf("%d", &wybranePole);
        wybranyIndex = wybranePole - 1;
    } while (!czyPolePuste(wybranyIndex));
    plansza[wybranyIndex] = 'x';
}

void ruchBota() {
    for (int i = 0; i <= 7; ++i) {
        int pierwszyIndex = linie[i * 3];
        int drugiIndex = linie[i * 3 + 1];
        int trzeciIndex = linie[i * 3 + 2];


        int pierwszePole = plansza[pierwszyIndex] == 'x';
        int drugiePole = plansza[drugiIndex] == 'x';
        int trzeciePole = plansza[trzeciIndex] == 'x';

        if (pierwszePole && drugiePole && czyPolePuste(trzeciIndex)) {
            plansza[trzeciIndex] = 'o';
            printf("trzecie pole %i\n", i);
            return;
        }
        if (pierwszePole && trzeciePole && czyPolePuste(drugiIndex)) {
            plansza[drugiIndex] = 'o';
            printf("drugie pole %i\n", i);
            return;
        }
        if (drugiePole && trzeciePole && czyPolePuste(pierwszyIndex)) {
            plansza[pierwszyIndex] = 'o';
            printf("pierwsze pole %i\n", i);
            return;
        }
    }

    int wylosowanyIndex;

    do {
        wylosowanyIndex = rand() % 8;
    } while (!czyPolePuste(wylosowanyIndex));

    plansza[wylosowanyIndex] = 'o';
    printf("wylosowany index %i", wylosowanyIndex);
}

int sprawdz(){
    for (int i = 0; i <= 7; ++i){
        int pierwszyIndex = linie[i * 3];
        int drugiIndex = linie[i * 3 + 1];
        int trzeciIndex = linie[i * 3 + 2];

        if (plansza[pierwszyIndex] == 'x' && plansza[drugiIndex] == 'x' && plansza[trzeciIndex] == 'x') {
            printf("Gratulację, wygrałeś z upośledzonym botem.\n");
            return 1;
        }
        else if (plansza[pierwszyIndex] == 'o' && plansza[drugiIndex] == 'o' && plansza[trzeciIndex] == 'o') {
            printf("Gratulację! Po tej rozgrywce twoje IQ spadło o 70%\n");
            return 1;
        }
        else if (!czyPolePuste(0) && !czyPolePuste(1) && !czyPolePuste(2)
        && !czyPolePuste(3) && !czyPolePuste(4) && !czyPolePuste(5)
        && !czyPolePuste(6) && !czyPolePuste(7) && !czyPolePuste(8)) {
            printf("Remis. IQ bota wzrosło o 10%.");
            return 1;
        }
    }

    return 0;
}

int main() {
    int kontynuujGre=1;

    do{
        rysujPlansze();
        ruchGracza();
        ruchBota();

        if (sprawdz()) {
            printf("Czy chcesz spróbować jeszcze raz?");
            scanf("%i", &kontynuujGre);

            if (kontynuujGre) {
                reset();
            }
        }
    } while(kontynuujGre);
    return 0;
}