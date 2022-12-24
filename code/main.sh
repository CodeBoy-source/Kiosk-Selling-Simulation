#!/bin/bash
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-$0}"; )" &> /dev/null && pwd 2> /dev/null; )";

declare -a arr=(10 )
declare -a arr2=(1 5 8)
reps=${#arr[@]}
length=${#arr2[@]}
for (( j = 0; j < reps; j++ )); do
    for (( i = 0; i < length; i++ )); do
        $SCRIPT_DIR/main ${arr[j]} ${arr2[i]}
    done
done
