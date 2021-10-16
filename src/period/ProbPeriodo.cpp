#include "period.h"
#include "Generazione.h"
#include <iostream>
#include <time.h>

using namespace std;

void probPeriodo(int n, int (*periodFunc)(std::string), std::string funcName) {
    int k, period;
    /* int methodA[n]; */
    /* int methodB[n]; */

    cout << "Lunghezza del periodo minimo con n = " << n << endl;
    cout << "Metodo di generazione A:" << endl;

    for (int i = 0; i<10000; i++) {
        string s = generazioneStringaA(n);
        /* methodA[i] = periodFunc(s); */ 
        cout << periodFunc(s) << endl;
    }

    cout << "Metodo di generazione B:" << endl;

    for (int i = 0; i<10000; i++) {
        string s = generazioneStringaB(n);
        /* methodB[i] = periodFunc(s); */ 
        cout << periodFunc(s) << endl;
    }
}


int main() {

    srand(time(0));
    probPeriodo(100, PeriodSmart, "PeriodSmart");

    return 0;
}
