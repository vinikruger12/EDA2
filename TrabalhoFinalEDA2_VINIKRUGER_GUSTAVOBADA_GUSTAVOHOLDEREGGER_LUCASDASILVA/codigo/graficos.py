import pandas as pd
import matplotlib.pyplot as plt

estruturas = [
    ('B10', 'Árvore B (ordem 10)', '#008300', '-.'),
    ('B5', 'Árvore B (ordem 5)', '#1baf7a', ':'),
    ('B1', 'Árvore B (ordem 1)', '#eda100', '--'),
    ('AVL', 'AVL', '#2a78d6', '-'),
    ('RubroNegra', 'Rubro-negra', '#e34948', '-'),
]


def grafico(arquivo, titulo, saida):
    df = pd.read_csv(arquivo)

    plt.figure(figsize=(10, 6))

    for coluna, nome, cor, estilo in estruturas:
        plt.plot(df['N'], df[coluna], label=nome, color=cor, linestyle=estilo, linewidth=2)

    plt.title(titulo, fontsize=15, fontweight='bold')
    plt.xlabel('Tamanho do conjunto de chaves (N)', fontsize=13)
    plt.ylabel('Esforço médio por operação', fontsize=13)
    plt.xticks(fontsize=12)
    plt.yticks(fontsize=12)
    plt.xlim(0, 10000)
    plt.ylim(bottom=0)
    plt.grid(True, linestyle='--', alpha=0.5)
    plt.legend(fontsize=12)

    plt.tight_layout()
    plt.savefig(saida, dpi=300)
    plt.close()

    print('Gerado', saida)


grafico('../resultados/resultado_adicao.csv', 'Adição de chaves', '../resultados/grafico_adicao.png')
grafico('../resultados/resultado_remocao.csv', 'Remoção de chaves', '../resultados/grafico_remocao.png')
