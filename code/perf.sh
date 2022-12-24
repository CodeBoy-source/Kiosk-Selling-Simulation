#!/bin/bash
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}"; )" &> /dev/null && pwd 2> /dev/null; )";

declare -a arr=('A' 'B' 'C')
declare -a arr2=(0 1 2 3)
reps=${#arr[@]}
length=${#arr2[@]}
for (( j = 0; j < reps; j++ )); do
    for (( i = 0; i < length; i++ )); do
        $SCRIPT_DIR/perf ${arr[j]} ${arr2[i]}
    done
done
