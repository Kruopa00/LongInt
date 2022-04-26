#include <bits/stdc++.h>
#include "BigInt.h"
#include <iostream>

using namespace std;

void close_program();
void text_to_screen();
int tikrinti(int max_size, ll skaicius);
int tikrinti2(int max_size, BigInt skaicius);

int main()
{
    std::cin.sync_with_stdio(false);
    //BigInt a("123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789");
    //BigInt b("461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187461648946198864649487449198487646514313187");
    //BigInt c("111");
    //BigInt a("4");
    //BigInt b("5");
    BigInt suma;

    int max_size;

    cout << "Sveiki, si programa atlieka aritmetinius skaicius su ilgu sveiku skaiciu." << endl;
    cout << "Iveskite norima maksimalu ILGI ilgo sveiko skaiciaus, skaicius negali buti ILGESNIS nei 15 skaitmenu" << endl;
    cin >> max_size;

    if (max_size <= 0 || max_size > 15)
    {
        while(1) {
            cout << "Bloga ivestis, skaicius turi buti didesnis nei nulis ir mažesnis nei 15-lika" << endl;
            cout << "Bandykite dar karta: " << endl;
            cin >> max_size;
            if (max_size > 0)
                break;
        }
    }

    ll skaicius;

    cout << "Iveskite a: ";
    cin >> skaicius;
    if (tikrinti(max_size, skaicius) == 0)
    {
        while(1) 
        {
            cout << "Bloga ivestis, skaicius per ilgas!" << endl;
            cout << "Bandykite dar karta: " << endl;
            cin >> skaicius;
            if (tikrinti(max_size, skaicius) == 1)
                break;       
        }
    }
    BigInt a(skaicius);

    cout << "Iveskite b: ";
    cin >> skaicius;

        if (tikrinti(max_size, skaicius) == 0)
    {
        while(1) 
        {
            cout << "Bloga ivestis, skaicius per ilgas!" << endl;
            cout << "Bandykite dar karta: " << endl;
            cin >> skaicius;
            if (tikrinti(max_size, skaicius) == 1)
                break;       
        }
    }

    BigInt b(skaicius);

    int user_input;

    text_to_screen();
    while (1)
    {
        cout << "Iveskite skaiciu norimiems veiksmams atlikti: ";
        cin >> user_input;

        switch(user_input)
        {
            case 9:
                close_program();
                break;

            case 8:
                text_to_screen();
                break;

            case 7:
            {
                cout << "a: "; print(a);
                cout << "b: "; print(b);
            }break;

            case 6:
            {
                cout << "Ilgis: " << endl;
                cin >> max_size;
            }break;

            case 5:
            {
                cout << "b: ";
                cin >> skaicius;
                if (tikrinti(max_size, skaicius) == 0)
                    cout << "Bloga ivestis" << endl;
                else
                    b = skaicius;
                    
            }break;

            case 4:
            {
                cout << "a: "; 
                cin >> skaicius;
                if (tikrinti(max_size, skaicius) == 0)
                    cout << "Bloga ivestis" << endl;
                else
                    a = skaicius;
            }break;

            case 3:  
            {
                if (b == 0)
                    cout << "Dalyba is nulio negalima!" << endl;
                else 
                {
                    BigInt dalmuo3 = divide(a, b);
                    cout << "DALMUO a / b: "; print(dalmuo3);
                    BigInt liekana = a - (b * dalmuo3);
                    cout << "LIEKANA: "; print(liekana);
                }
            }break;

            case 2:  
            {   BigInt sandauga2 = multiply(b, a);
                if (tikrinti2(max_size, sandauga2) == 0)
                    cout << "Skaicius gaunasi per ilgas, sudauginti negalima!" << endl;
                else
                {
                    cout << "SANDAUGA : "; 
                    print(sandauga2);
                }
            }break;

            case 1: 
            {   BigInt skirtumas1 = subtract(a, b);
                cout << "SKIRTUMAS: "; print(skirtumas1);
            }break;

            case 0:
            {
                BigInt suma = add(a, b);
                if (tikrinti2(max_size, suma) == 0)
                    cout << "Skaicius gaunasi per ilgas, sudeti negalima!" << endl;
                else
                {
                    cout << "SUMA: "; 
                    print(suma);
                }
            }break;
        }

    }
    return 0;
}

void close_program()
{
    cout << "Viso gero!" << endl;

    system("PAUSE");
    exit(0);
}

void text_to_screen()
{
    cout << "Komandu sarasas:" << endl;
    cout << "Number 0 - atspausdinima suma a ir b." << endl;
    cout << "Number 1 - atspausdinamas skirtumas a ir b." << endl;
    cout << "Number 2 - atspausdinama sandauga a ir b" << endl;
    cout << "Number 3 - atspausdinama a ir b dalmuo, bei liekana" << endl;
    cout << "Number 4 - redaguoti skaiciu a" << endl;
    cout << "Number 5 - redaguoti skaiciu b" << endl;
    cout << "Number 6 - redaguoti maksimalu ilgi" << endl;
    cout << "Number 7 - atspausdinami skaiciai a ir b" << endl;
    cout << "Number 8 - atspausdina komandu sarasa" << endl;
    cout << "Number 9 - uzdaro programa" << endl;
}

int tikrinti(int max_size, ll skaicius)
{
    if(std::to_string(skaicius).length() > max_size)
        return 0;
    else
        return 1;
}

int tikrinti2(int max_size, BigInt skaicius)
{
    unsigned int number_of_digits = 0;
    for (number_of_digits = 0; skaicius > 0; number_of_digits++) {
        skaicius = skaicius / 10;
    }

    if(number_of_digits > max_size)
        return 0;
    else
        return 1;
}