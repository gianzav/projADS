#include "Generazione.h"
#include "period.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <math.h>
/* #include <stdio.h> */
/* #include <stdlib.h> */
#include <string>
#include <time.h>

using namespace std;
using namespace std::chrono;

/* Formato in cui esprimere le misure (conversione in secondi e
* rappresentazione a doppia precisione) */
typedef duration<double, seconds::period> secs;


double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);

    /* Conversione dei tick della CPU contati in secondi */
    return duration_cast<secs>(end - start).count();
}


/**
 * Misurazione dei tempi medi di calcolo del periodo frazionario per stringhe
 * di lunghezza crescente
 */
int misurazioneTempiMedi(int (*periodFunc)(std::string), std::string funcName) {
    int nMin = 1000;
    int nMax = 500000;                         
    double A = nMin;                           // A * e^(B*0) = nMin
    /* B ricavato forzando la funz. esponenziale a passare nelle ordinate nMin
    * e nMax */
    double B = exp((log(nMax) - log(A)) / 99); // A * e^(B*99) = nMax

    double m;
    int n, k, period;
    double R;                                   // Risoluzione clock
    double Emax = 0.001;                        // Errorre relativo massimo ammesso
    steady_clock::time_point start;             // = clock start;
    steady_clock::time_point end;               // = clock end;
    double tn;
    double conversion;
    double nSeconds;

    cout << "---New Test-" << funcName << "---" << endl;
    cout << "Grandezza stringa,Tempo (sec)" << endl;

    for (int j = 0; j <= 99; j++) {
        R = getResolution();
        m = A * pow(B, j);

        /* n viene generato in base alla funzione esponenziale passante per i
        * punti (x1, nMin) e (x2, nMax) */
        n = (int)m;

        start = steady_clock::now();
        /* k = numero di iterazioni necessarie in modo che valga la disequazione 
        *   (kx~) >= (R/Emax) + R dove x~ è il tempo misurato */
        k = 0;

        do {
            string stringaGenerata = generazioneStringaB(n);
            period = periodFunc(stringaGenerata);
            end = steady_clock::now();

            /* Incremento k finchè la disequazione non è vera */
            k = k + 1;

            /* Conversione in secondi del tempo di calcolo, moltiplicato per la
            * costante k */
            conversion = duration_cast<secs>(end-start).count();

        } while (conversion < ((R / Emax) + R));

        /* tn = tempo impiegato per terminare la computazione calcolato con
        * errore relativo <= Emax */
        tn = (conversion) / k;


        /* Stampa delle misurazioni */
        cout << n << "," << tn << endl;
    }

    return 0;
}


/**
 * Calcolo della deviazione standard del tempo medio di calcolo del periodo
 * frazionario con lunghezza della stringa fissata
 */
void deviazioneStandardPeriodo(int (*periodFunc)(std::string), std::string funcName) {
    int n, k, period, nTest;
    double R;                       // Risoluzione  clock
    double Emax = 0.001;            // Errorre relativo massimo ammesso
    steady_clock::time_point start; // = clock start;
    steady_clock::time_point end;   // = clock end;
    double tn;
    double conversion;
    double nSeconds;
    double meanTime = 0;
    double sd = 0;

    cout << "---New Test-" << funcName << "---" << endl;

    /* n fissato */
    n = 1000;
    /* Vettore per memorizzare i tempi di ogni iterazione */ 
    nTest = 100;
    double times[nTest];

    for (int j = 0; j < nTest; j++) {
        R = getResolution();

        start = steady_clock::now();
        k = 0;

        do {
            string stringaGenerata = generazioneStringaA(n);
            period = periodFunc(stringaGenerata);
            end = steady_clock::now();
            k = k + 1;
            conversion = duration_cast<secs>(end-start).count();
        } while (conversion < ((R / Emax) + R));

        /* Calcolo del tempo impiegato con errore relativo <= Emax */
        tn = (conversion) / k;

        /* Memorizzazione del tempo impiegato per la singola esecuzione */
        times[j] = tn;
    }

    /* Calcolo della media dei tempi */
    for (int i=0; i<100; i++) {
        meanTime += times[i];
    }
    meanTime = meanTime/100;

    /* Calcolo della deviazione standard */
    for (int i=0; i<100; i++) {
        sd += pow((times[i] - meanTime), 2);
    }

    sd = sqrt(sd/n);

    cout << "Lunghezza stringa,Numero test,Deviazione standard" << endl;
    cout << n << "," << nTest << "," << sd << endl;

}




int main() {

    /* Nuovo seed per cambiare sequenza pseudo-casuale */
    srand(time(0));

    misurazioneTempiMedi(PeriodNaive, "PeriodNaive");
    misurazioneTempiMedi(PeriodSmart, "PeriodSmart");

    return 0;
}
