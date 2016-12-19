import matplotlib.pyplot as plt
import sys  # argumentos do sistema
import os

pasta = 'Desempenho/'

def plotarDesempenho(titulo, arg_plot='kx'):
    with open(pasta + titulo) as arq:
        linhas = arq.readlines()
    nome = linhas[0]
    tempos = map(lambda l: l[:-1].split(';'), linhas[2:])
    tempos = list(map(lambda t: (int(t[0]), float(t[1])), tempos))

    plt.figure(nome)
    for n, t in tempos:
        plt.plot(n, t, arg_plot)
    plt.ylabel('tempo')
    plt.xlabel('n')
    plt.grid()
    if not os.path.exists(pasta):
        os.makedirs(pasta)
    plt.savefig(pasta + titulo[:-4] + '.png')


# plt.show()

nomeArq = sys.argv[1]
try:
    arg_plot = sys.argv[2]
    plotarDesempenho(nomeArq, arg_plot)
except:
    plotarDesempenho(nomeArq)
