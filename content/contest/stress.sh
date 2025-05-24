g++ -o $1 $1.cpp -Wall -lm -O2 -std=c++17
g++ -o $1-brute $1-brute.cpp -Wall -lm -O2 -std=c++17
g++ -o $1-gen $1-gen.cpp -Wall -lm -O2 -std=c++17
while true 
do 
    ./$1-gen > $1.in
    ./$1 < $1.in > $1.out
    ./$1-brute < $1.in > $1.ans
    diff $1.out $1.ans 
    if [ $? -ne 0 ] 
    then 
        echo "Wrong Answer" 
        exit 
    else 
        echo "Correct" 
    fi 
done