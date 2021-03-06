sizes=(2 4 6 8 10 12 14 16 32 64 128 256)

echo "X,Y,T" >output
for x in ${sizes[@]}; do
    for y in ${sizes[@]}; do
        python benchmark/create_random_board.py --x $x --y $y --worst_case
        TIME=$(./tp1-bench board | grep -oP ": \K[0-9]+")
        echo "$x,$y,$TIME" >>output
    done
done
