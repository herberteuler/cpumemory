#!/bin/bash

# cycles_of repeats working_set_size
function cycles_of ()
{
  local repeats=$1
  local working_set_size=$2

  echo $(perf stat -e cycles:u ./acc -r $repeats $working_set_size 2>&1 \
           | grep cycles:u \
           | awk '{ print $1 }' \
           | sed 's/,//g')
}

# normalize working_set_size
function normalize ()
{
  local working_set_size=$1
  local scale=

  if echo $working_set_size | grep -qs '[kKmM]$'; then
    scale=$(echo $working_set_size | grep -o '.$')
    if [[ $scale = 'k' || $scale = 'K' ]]; then
      scale=1024
    else
      scale=1048576
    fi
  fi

  echo $((scale * $(echo $working_set_size | sed 's/.$//')))
}

#set -x
make clean
make ACC_NPAD=${ACC_NPAD:=7}

repeats=${repeats:-500}
element_size=$((8 + ACC_NPAD * 8))
for working_set_size; do
  working_set_size=$(normalize $working_set_size)
  raw_cycles=$(cycles_of 0 $working_set_size)
  working_cycles=$(cycles_of $repeats $working_set_size)
  access_count=$((working_set_size / element_size - 1))
  cycles_per_element=$(((working_cycles - raw_cycles) / repeats / access_count))
  echo -ne "$working_set_size\t$access_count\t$raw_cycles\t$working_cycles"
  echo -e "\t$cycles_per_element"
done

# Local variables:
# mode: shell-script
# sh-basic-offset: 2
# sh-indentation: 2
# End:
