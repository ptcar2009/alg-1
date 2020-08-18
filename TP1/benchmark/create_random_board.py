from random import randrange
from argparse import ArgumentParser


parser = ArgumentParser("generate random board")
parser.add_argument("--x", type=int, default=10)
parser.add_argument("--output_file", "-o",
                    dest="of", type=str, default="board")
parser.add_argument("--y", type=int, default=10)
parser.add_argument("--n_players", "-n",
                    dest="n_players", type=int, default=2)
parser.add_argument("--worst_case", action='store_true')


args = parser.parse_args()

x = args.x
y = args.y
if args.worst_case:
    n_players = 2
else:
    n_players = args.n_players


with open(args.of, 'w') as file:
    file.write(f'{y} {x}\n')
    file.write(f'{n_players}\n')
    for i in range(y):
        for i in range(x):
            if args.worst_case:
                tile = max(x, y)
            else:
                tile = randrange(3)
            file.write(f'{tile} ')
        file.write('\n')

    if args.worst_case:
        file.write('0 0\n0 1\n')
    else:
        for i in range(n_players):
            file.write(f'{randrange(y)} {randrange(x)}\n')
