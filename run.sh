n=1000

rm timing_*p.dat

for p in 1 2 4 8 16; do

  outputfile="timing_"$p"p.dat"
  if [ -a $outputfile ]; then
    rm $outputfile
  fi

  for N in 1 2 4 8 16 32 64 128 256 512 1024; do

    if [ "$N" -ge "$p" ]; then
      echo "run mpiexec -"$p "main.out" $N $n
      mpiexec -np $p main.out $N $n >> $outputfile
    fi

  done

done
