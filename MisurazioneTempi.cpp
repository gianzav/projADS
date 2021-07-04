#include "src/period.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;
using namespace std::chrono;

double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> duration;
    return duration_cast<seconds>(end - start).count();
}

string generazioneStringa(int n) {
    string s = "";
    string p;
    for (int i = 0; i < n; i++) {
        p = 'a' + ((int)rand()) % 2;
        s = s + p;
    }
    return s;
}


int misurazioneTempiMedi(int (*periodFunc)(std::string), std::string funcName) {
    int nMin = 1000;
    int nMax = 500000;                         // 500'000
    double A = nMin;                           // ricavo A
    double B = exp((log(nMax) - log(A)) / 99); // ricavo B
    double m;
    int n, k, periodo;
    double R;                       // Risoluzione  clock
    double Emax = 0.001;            // Errorre relativo massimo ammesso
    steady_clock::time_point start; // = clock start;
    steady_clock::time_point end;   // = clock end;
    steady_clock::duration diff;
    double tn;
    double conversione;
    double nseconds;

    cout << "---New Test-" << funcName << "---" << endl;

    /* Header per file CSV (per gestire piu' facilmente i dati) */
    cout << "Tempo,grandezza stringa" << endl;

    for (int j = 0; j <= 99; j++) {
        R = getResolution();
        m = A * pow(B, j);
        n = (int)m;
        // cout<<n<<endl; //stampa lunghezza n, con distribuzione esponenziale tra
        // 1000 e 500000
        // string StringaGenerata =generazioneStringa(n);   // posso calcolare il
        // tempo medio della generazione
        start = steady_clock::now();
        k = 0;

        do {
            string StringaGenerata = generazioneStringa(n);
            periodo = periodFunc(StringaGenerata);
            end = steady_clock::now();
            k = k + 1;
            diff = end - start;
            conversione = double(diff.count());
        } while (conversione < ((R / Emax) + R)); // end-start -> ^kx^   //sottrarre il tempo
        // medio della generazione per
        tn = (conversione) / k; // tn = x^ con errore relativo <= Emax

        /*cout<<tn<<endl;*/     // cout<<tn/pow(10,9)<<" grandezza n: "<<n<<endl;

        nseconds = tn * steady_clock::period::num / steady_clock::period::den; // conversione in secondi

        // //double(diff.count())
        
        cout << nseconds << "," << n << endl;
    }

    return 0;
}


int main() {

    /* Nuovo seed per cambiare sequenza pseudo-casuale */
    srand(time(0));

    // string prova=generazioneStringa(5);// generazione  stringa fatta
    // cout<<prova;
    misurazioneTempiMedi(PeriodNaive, "PeriodNaive");
    misurazioneTempiMedi(PeriodSmart, "PeriodSmart");

    return 0;
}
