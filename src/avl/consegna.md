Si richiede l'implementazione di un albero binario di ricerca di tipo AVL, in
cui ciascun nodo contiene una chiave numerica (di tipo intero) e un valore
alfanumerico (di tipo stringa). Un albero binario di ricerca di tipo AVL
supporta le classiche operazioni di inserimento, ricerca, e rimozione di nodi,
garantendo allo stesso tempo la proprietà di bilanciamento seguente: 


Per ogni nodo x, le altezze dei sotto-alberi di sinistra e di destra nel nodo x
differiscono al più di 1. Tale proprietà viene garantita eseguendo opportune
rotazioni sui nodi sbilanciati, partendo dal nodo sbilanciato più profondo (ad
esempio, il "nonno" del nodo appena inserito) e procedendo risalendo lungo il
cammino di accesso a quel nodo. Per le operazioni di ribilanciamento sarà
necessario mantenere l'informazione relativa all'altezza di ciascun nodo, in
modo da evitare il calcolo diretto di essa (tale calcolo prenderebbe tempo
lineare nella dimensione del sotto-albero).


Più precisamente, il ribilanciamento di un nodo x avviene nell'ipotesi che:

* le altezze dei figli di x siano note e differiscano esattamente di 2 unità 
* entrambi i sotto-alberi radicati nei figli di x soddisfino la proprietà di
  bilanciamento. 

L'effetto dell'operazione di ribilanciamento su x sarà che
l'intero sotto-albero radicato in x soddisfa la proprietà di bilanciamento.

L'operazione di ribilanciamento su x effettua una distinzione di casi, a seconda
di quale figlio di x abbia il sotto-albero più alto. Si consideri il caso in cui
il sotto-albero del figlio sinistro di x abbia altezza maggiore di quello del
figlio destro (il caso simmetrico può essere trattato in modo del tutto
analogo). Sia y il figlio sinistro di x e siano z1 e z2 i figli sinistro e
destro di y (quindi due "nipoti" di x). Se il sotto-albero radicato in z1 ha
altezza maggiore o uguale a quella del sotto-albero radicato in z2, allora
basterà effettuare una rotazione verso destra sul nodo x. Altrimenti, se il
sotto-albero radicato in z1 ha altezza minore di quella del sotto-albero
radicato in z2, allora, prima di effettuare una rotazione verso destra sul nodo
x, sarà opportuno effettuare una rotazione verso sinistra sul nodo y, in modo da
riportarsi al caso analizzato precedentemente.

A seguito delle operazioni di ribilanciamento, un albero di ricerca di tipo AVL
mantiene un'altezza proporzionale al **logaritmo del numero dei suoi nodi**. In
particolare, tutte le operazioni supportate da un albero di ricerca di tipo AVL
avranno complessità logaritmica rispetto al numero di nodi.



Come nel precedente esercizio 17, il programma che implementa le operazioni di
un albero di ricerca di tipo AVL dovrà essere di tipo interattivo: a ogni
iterazione, l'utente potrà indicare un'operazione (ad esempio, insert 5 five,
remove 5, find 5, clear, show) e in output verrà fornito eventualmente il
risultato dell'operazione. In particolare, l'operazione show produce come
risultato la rappresentazione in notazione polacca dell'albero, in cui ogni nodo
è rappresentato da una stringa che ne descrive la chiave, il valore, e l'altezza
dell'albero in esso radicato (ad esempio, "5:five:15"). Il programma terminerà
ogni qualvolta l'utente inserisca un'operazione non supportata (ad esempio,
"exit").


* L'inserimento e la cancellazione possono far sbilanciare entrabe l'albero
