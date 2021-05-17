#include "old/AvlNode.h"
#include "old/RbNode.h"
#include "old/BstNode.h"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <ratio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <thread>
#include <stdint.h>

/**
*
* n: # operazioni di inserimento
* m: # operazioni di ricerca
*
* Nell'ipotesi che i numeri generati siano in un dominio sufficientemente
* grande il valore di m sarà probabilmente simile a n e quindi potrà essere
* sostituito con n
*
* 1. Si genera in modo pseudo-casuale un valore k
* 2. Si cerca un nodo con chiave k nell'albero
*   - Se non esiste si inserisce un nodo con chiave k
* 4. Calcolo del tempo medio di esecuzione
* 3. Calcolo del tempo ammortizzato con errore relativo limitato superiormente
*    da 0.01 (1%) e la sua deviazione standard
*
*    tempo ammortizzato = (tempo tot.)/(n+m)
*
* Consigli:
*
* - Generare circa 100 campioni di dimensione che varia gra 1000 e 100000 con
*   una distrubuzione esponenziale o geometrica
*/

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

template <class T>
void treeTimes(BiNode<T>* tree, string treeType) {
    int nMin = 1000;
    int nMax = 100000;
    double A = nMin;                            // ricavo A
    double B = exp((log(nMax) - log(A)) / 99);  // ricavo B
    double m;
    int n, k;
    double R;                                   // Risoluzione  clock
    double Emax = 0.01;                         // Errorre relativo massimo ammesso
    steady_clock::time_point start;             // = clock start;
    steady_clock::time_point end;               // = clock end;
    steady_clock::duration diff;
    double tn;
    double conversione;
    double nseconds;
    int randKey; 
    double sd = 0;                                  // deviazione standard
    double timeTot = 0;
    double meanTime = 0; 
    BiNode<T>* node;
    BiNode<T>* rootCopy = tree;

    cout << "Misurazione tempi con " << treeType << endl;
    cout << "Numero operazioni,Tempo totale,Tempo ammortizzato,Deviazione standard" << endl;

    for (int j = 0; j <= 99; j++) {
        R = getResolution();
        m = A * pow(B, j);
        n = (int)m;
        double times[n];
        

        for (int i=0; i<n; i++) {
            start = steady_clock::now();
            k = 0;

            do {
                /* Vengono eseguite n operazioni di ricerca ed m <= n inserimenti */
                /* TODO Bisogna memorizzare in times[] il tempo impiegato in ogni
                * iterazione in modo da calcolare la deviazione standard */
                randKey = rand();
                /* TODO Ricerca nodo di chiave randKey */
                /* TODO Eventuale inserimento */

                node = tree->find(randKey);
                if (node == NULL || node->isNull()) {
                    tree = tree->insert(k, "");
                }

                end = steady_clock::now();
                k = k + 1;
                diff = end - start;
                conversione = double(diff.count());
            } while (conversione < ((R / Emax) + R)); // end-start -> ^kx^   //sottrarre il tempo
               // medio della generazione per
            tn = (conversione) / k; // tn = x^ con errore relativo <= Emax

            nseconds = tn * steady_clock::period::num / steady_clock::period::den; // conversione in secondi
            times[i] = nseconds;
        }
        cout << "k = " << k << endl;

        tree = tree->clear();

        for (int i=0; i<n; i++) {
            timeTot += times[i];
        }

        meanTime = timeTot/n;

        /* Calcolo deviazione standard */
        for (int i=0; i<n; i++) {
            sd += pow((times[i] - meanTime), 2);
        }

        sd = sqrt(sd/n);

        /* Stampa dei valori calcolati
        * N, Tempo totale, Tempo ammortizzato, Deviazione standard */
        cout << n << "," << timeTot << "," << meanTime << "," << sd << endl;

    }
}


int main() {

    srand(time(0));

    BstNode<string> bst = BstNode<string>::NULLNODE;
    AvlNode<string> avl = AvlNode<string>::NULLNODE;
    RbNode<string> rb = RbNode<string>::NULLNODE;

    treeTimes(&avl, "AVL");
    treeTimes(&rb, "REDBLACK");
    treeTimes(&bst, "BST");

    return 0;
}
