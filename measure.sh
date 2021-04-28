#!/bin/sh
# Prende come argomento il numero di test da effettuare e il numero iniziale
# con cui numerare i file 

# ATTENZIONE: se esistono file gia' numerati 0...n va a sovrascriverli

[ $# -lt 2 ] && exit 1

# La numerazione parte dal valore passato come secondo parametro
i=$2
# Vengono fatti tanti test quanti indicati nel primo parametro
lim=$(($1 + $2))

while test $i -lt $lim
do
    ./bin/MisurazioneTempi > "./measures/measure$i"
    i=$((i+1))
done
