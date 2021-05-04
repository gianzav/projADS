Si richiede l'implementazione di un albero binario di ricerca di tipo Red-Black
("rosso-neri"), in cui ciascun nodo contiene 

* una chiave numerica (di tipo intero)
* un valore alfanumerico (di tipo stringa). 

Come nei precedenti esercizi, il programma che implementa le operazioni di un
albero di ricerca di tipo Red-Black dovrà essere di tipo interattivo: a ogni
iterazione, l'utente potrà indicare un'operazione (ad esempio, insert 5 five,
find 5, clear, show) e in output verrà fornito eventualmente il risultato
dell'operazione. In particolare, l'operazione show produce come risultato la
rappresentazione in notazione polacca dell'albero, in cui ogni nodo è
rappresentato da una stringa che ne descrive la chiave, il valore, e il colore
(ad esempio, "5:five:red", oppure "3:three:black"). Il programma terminerà ogni
qualvolta l'utente inserisca un'operazione non supportata (ad esempio, "exit").


**Nota bene**: al fine di semplificare l'esercizio, non è richiesta
l'implementazione dell'operazione di rimozione di un nodo. I test automatici
sono preparati in modo da non eseguire mai l'istruzione di rimozione.
