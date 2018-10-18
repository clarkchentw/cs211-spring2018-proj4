
if [[ $# -ne 1 ]]
then
    echo "Usage: $0 [Program Call]"
    exit 140
fi

while :
do
	clear;
        gcc -x c $1
# && ./a.out $2
        sleep 3
done

