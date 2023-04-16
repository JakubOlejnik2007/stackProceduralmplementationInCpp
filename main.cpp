/**
    Nazwa: Stos
    @authr: Jakub Olejnik
    @description:
    Program implementujacy strukturê stosu (LIFO) w paradygmacie proceduralnym.

*/
#include <iostream>
#include <iomanip>
/**
    Po co iomanip?
    Chcac zachowac w miare estetyczny wyglad wyniku
    funkcji wyswietlacej zawartosc stosu natrafilem na pewien problem.
    Mianowicie chcac zrobic "tabelke" w konsoli trzeba sie liczyc z
    faktem, ze dlugosc wartosci wpisywanej w "pole" tej tabeli moze byc
    rozna. Moze to byc 1 znak, byc moze 10. Szukajac w internecie
    pomyslu na rozwiazanie tego problemu trafilem na funckje setw(n),
    ktora znajduje sie w iomanip. Ta konkretna funkcja pozwala wraz
    z cout stworzyc pewnego rodzaju pole o dlugosci n, ktore moze
    zostac napisane przy uzyciu wartosci po strumieniu wysylania, np.
    cout << setw(20) << "Hello world";
    Mozna zauwazyc, ze napis "Hello world" ma 11 znakow. Zarezerwowalismy
    20 znakow, wiec 9 pierwszych znakow tego pola zostanie pustych, a potem
    wypisany zostanie powyzszy napis (napis pojawia sie od prawej strony pola).
    Pozwala to na zachowanie odpowiednich odstepow wewnatrz pola "tabeli".
*/
#include <windows.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

/**
    Zmienna MAX_STACK_SIZE przechowuje informacje o tym,
    jaki rozmiar maksymalnie mo¿e przyj¹æ utworzony stos.

    Zmienna globalna stack_size przechowuje informacje
    o obecnym rozmiarze stosu (o liczbie elementow, ktore
    znajduja sie obecnie na stosie). Zmienna ta jest globalna
    w celu uproszczenia struktury kodu.
*/

int MAX_STACK_SIZE = 0;
int stack_size = 0;

/**
    conf - ustawienie rozmiaru stosu.
    menu - wypisanie listy funckji obslugujacych stos
*/
void conf();
void menu();
void wybor(int *stack_tab);
void show_stack(int *stack_tab);

/**
    Funkcje obslugi stosu:
    push - wlozenie wartosci na stos.
    pop - zdjecie wartosci ze stosu.
    top - wypisanie elementu znajdujacego sie na wierzchu bez jego zdejmowania.
    sizeofstack - liczba elementow na stosie.
    isFull - wypisuje informacje czy stos jest pelny.
    isEmpty - wypisuje informacje czy stos jest pusty.
*/
void push(int *stack_tab);
void pop(int *stack_tab);
void top(int *stack_tab);
void sizeofstack();
void isFull();
void isEmpty();



char kontynuacja();

int main()
{
    conf();
    srand(time(NULL));

    char kont;
    int tab[MAX_STACK_SIZE];

    do {
        menu();
        show_stack(tab);
        wybor(tab);
        kont = kontynuacja();
    } while(kont == 'Y' || kont == 'y');

    SetConsoleTextAttribute(h, 0x00);
    return 0;
}

void conf(){
    while(MAX_STACK_SIZE<=0){
        SetConsoleTextAttribute(h, 0x0D);
        cout << "Jak duzo elementow ma przechowywac stos?\t";
        SetConsoleTextAttribute(h, 0x0B);
        scanf("%d", &MAX_STACK_SIZE);
        system("cls");
    }
    SetConsoleTextAttribute(h, 0x0E);
}

void menu(){
    SetConsoleTextAttribute(h, 0x0E);
    string options[6] = {"Push", "Pop", "Top", "Size", "isFull", "isEmpty"};
    cout << "*----------MENU----------*\n";
    for(int i = 1; i<= 6; i++){
        cout << "|"<< setw(4) << i <<"." << setw(14) << options[i-1] << "\t |" << "\n";
        if (6-i>=1) cout << "*------------------------*\n";
    }
    cout << "*------------------------*\n";
}
void show_stack(int *stack_tab){
    SetConsoleTextAttribute(h, 0x0A);
    cout << "*----------STOS----------*\n";
    if (stack_size == 0) cout << "|"<< setw(26) << "|\n";
    for(int i = stack_size; i > 0; i--){

        cout << "|";
        SetConsoleTextAttribute(h, 0x0F);
        cout << setw(4) << stack_size-i+1 <<"." << setw(14) << *(stack_tab+i-1);
        SetConsoleTextAttribute(h, 0x0A);
        cout << "\t |" << "\n";

        if (i>1) cout << "*------------------------*\n";
    }

    SetConsoleTextAttribute(h, 0x0A);
    cout << "*------------------------*\n";
}

void wybor(int *stack_tab){
    SetConsoleTextAttribute(h, 0x0D);
    cout << "\n\t\aJaka opcje wybierasz?\t ";
    int opcja;
    SetConsoleTextAttribute(h, 0x0B);
    scanf("%d", &opcja);
    system("cls");
    switch (opcja){
    case 1:
        push(stack_tab); break;
    case 2:
        pop(stack_tab); break;
    case 3:
        top(stack_tab); break;
    case 4:
        sizeofstack(); break;
    case 5:
        isFull(); break;
    case 6:
        isEmpty(); break;
    }

    SetConsoleTextAttribute(h, 0x0E);

}

void push(int *stack_tab){
    if(stack_size == MAX_STACK_SIZE){
        SetConsoleTextAttribute(h, 0x0C);
        cout << "Stos jest pelny." << endl;
    }


    else {
        int value;
        SetConsoleTextAttribute(h, 0x0D);
        cout << "\n\t\aJaka wartosc polozyc na wierz stosu?\t ";
        SetConsoleTextAttribute(h, 0x0B);
        scanf("%d", &value);
        *(stack_tab+stack_size) = value;
        stack_size++;
        show_stack(stack_tab);
    }
    SetConsoleTextAttribute(h, 0x0E);

}
void pop(int *stack_tab){
    if(stack_size == 0){
        SetConsoleTextAttribute(h, 0x0C);
        cout << "Stos jest pusty." << endl;
    }

    else {
        stack_size--;
        show_stack(stack_tab);
    }
    SetConsoleTextAttribute(h, 0x0E);
}

void top(int *stack_tab){
    SetConsoleTextAttribute(h, 0x0E);
    cout << "Na wierzchu stosu znajduje sie wartosc:\t" << *(stack_tab+stack_size-1) << ".\n";
}

void sizeofstack(){
    SetConsoleTextAttribute(h, 0x0E);
    cout << "Na stosie znajduje sie:\t" << stack_size << " elementow." << endl;
}

void isFull(){
    SetConsoleTextAttribute(h, 0x0E);
    if(stack_size == MAX_STACK_SIZE)
        cout << "Stos jest pelny." << endl;
    else
        cout << "Stos nie jest pelny." << endl;
}

void isEmpty(){
    SetConsoleTextAttribute(h, 0x0E);
    if(stack_size == 0)
        cout << "Stos jest pusty." << endl;
    else
        cout << "Stos nie jest pusty." << endl;
}

char kontynuacja(){
    char value;
    SetConsoleTextAttribute(h, 0x0D);
    cout << "\n\t\aCzy chcesz kontynuowac? [Y/N] \t ";
    SetConsoleTextAttribute(h, 0x0B);
    cin >> value;
    system("cls");
    SetConsoleTextAttribute(h, 0x0E);
    return value;
}
