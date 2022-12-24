#!/bin/bash
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}"; )" &> /dev/null && pwd 2> /dev/null; )";

declare -a arr=(10 )
declare -a arr2=(1 5 8)
declare -a arr3=(10 100 1000)
declare -a arr4=('A' 'B' 'C')
reps=${#arr[@]}
length=${#arr2[@]}
prices=${#arr3[@]}
politicas=${#arr4[@]}
for (( j = 0; j < reps; j++ )); do
    for (( i = 0; i < length; i++ )); do
        for (( x = 0; x < prices; x++ )); do
            for (( p = 0; p < politicas; p++ )) do
                $SCRIPT_DIR/modf ${arr[j]} ${arr2[i]} ${arr3[x]} ${arr4[p]}
            done
        done
    done
done
