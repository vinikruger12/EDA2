import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('resultados_buscas.csv')

# Aplica uma Média Móvel para suavizar o ruído das 23.000 linhas
df_smooth = df.rolling(window=100, on='N').mean().dropna()

plt.figure(figsize=(10, 6))

plt.plot(df_smooth['N'], df_smooth['Sequencial'], label='Busca Sequencial', color='#d62728', linewidth=2)
plt.plot(df_smooth['N'], df_smooth['Sentinela'], label='Busca com Sentinela', color='#2ca02c', linewidth=2)
plt.plot(df_smooth['N'], df_smooth['Binario'], label='Busca Binária', color='#ff7f0e', linewidth=2)
plt.plot(df_smooth['N'], df_smooth['Interpolacao'], label='Busca por Interpolação', color='#1f77b4', linewidth=2)

plt.yscale('log') # Mantém a escala logarítmica

plt.title('Comparação de Algoritmos de Busca (Com Suavização)', fontsize=13, fontweight='bold')
plt.xlabel('Tamanho do Vetor (N)', fontsize=11)
plt.ylabel('Média de Iterações (Log10)', fontsize=11)
plt.grid(True, which="both", linestyle='--', alpha=0.5)
plt.legend(fontsize=10)

plt.tight_layout()
plt.savefig('grafico_limpo.png', dpi=300)
plt.show()