i=0
while [ $i -lt 6 ]; do
  clear
  echo "Differences between C and C++ with respect to malloc, new and pointers."
  echo ""

  if [ $i -ge 1 ]; then echo "You have to tell malloc() how many bytes you want."; fi
  if [ $i -ge 2 ]; then echo "malloc() does not know how its memory is being used -- it simply allocates bytes."; fi
  if [ $i -ge 3 ]; then echo "You have to keep track of the array's size. That is inconvenient compared to a vector."; fi
  if [ $i -ge 4 ]; then 
    echo  ""
    echo "There are no reference variables in C. Parameters are always copied."
    echo " Here, it's the pointer that is being copied, not the data to which it is pointing."
    echo  ""
  fi
  if [ $i -ge 5 ]; then echo "For that reason, there is only one copy of the array in this program."; fi

  i=$(($i+1))
  read a
done

