#!/bin/bash

if [ $# != 2 ]; then
        echo "Brak wymaganych argumentów. Prawidłowe użycie skryptu:    ./test.sh <prog> <dir>"
else
    BINARY=$1
    DIRECTORY=$2

    if [ -f $BINARY ]; then
        if [ -d $DIRECTORY ]; then
            i=0
            j=0
            for file in $DIRECTORY/*.in; do
                echo "======= Sprawdzanie poprawności testów dla '$file' ======="
                < $file ./$BINARY > tmp.out 
                sed -i -e '/ERROR/w tmp.err' -e '//d' tmp.out
                
                if diff tmp.out ${file%.in}.out && diff tmp.err ${file%.in}.err; then
                    Poprawny[i]="$file"
                    ((i++))
                else
                    Niezaliczony[j]="$file"
                    ((j++))
                fi
                
                echo "======= Sprawdzanie wycieków pamięci dla testu '$file' ======="
                valgrind --leak-check=full < $file ./main
            done
            rm tmp.out tmp.err
            echo "Testy zaliczone:"
            for i in "${Poprawny[@]}"; do echo "$i"; done
            echo "Testy niezaliczone:"
            for i in "${Niezaliczony[@]}"; do echo "$i"; done
        else
            echo "Katalog o nazwie $DIRECTORY nie istnieje!"
        fi
    else
        echo "Program o nazwie '$BINARY' nie istnieje!"
    fi
fi
