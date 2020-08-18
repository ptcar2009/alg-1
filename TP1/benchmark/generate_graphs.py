from argparse import ArgumentParser
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt

parser = ArgumentParser("generate random board")
parser.add_argument(
    "--prefix", "-p"
)
args = parser.parse_args()

df = pd.read_csv('output')
df['theoretical'] = (df['X'] * df['Y'])**2
df = df.sort_values('theoretical')
y = df.groupby('theoretical').mean()['T']
yerr = df.groupby('theoretical').std()['T']
print(df.groupby('theoretical').groups.keys())
plt.errorbar(list(df.groupby('theoretical').groups.keys()), y, yerr=yerr)
plt.savefig(f'{args.prefix}-theo-actual.png')
