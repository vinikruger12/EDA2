# Trabalho final de EDA2 - Árvores AVL, rubro-negra e B

Vinicius Moreira Krüger, Gustavo Bada Zanatta, Lucas da Silva e Gustavo Holderegger

## Pastas

- `codigo`: árvores (`avl`, `rubronegra`, `arvoreb`, cada uma com `.c` e `.h`), `main.c`, `graficos.py` e `chaves.csv`
- `resultados`: `resultado_adicao.csv`, `resultado_remocao.csv` e os gráficos
- `relatorio`: relatório em LaTeX e o `Relatorio.pdf`

## Como rodar

Dentro da pasta `codigo`:

```
gcc -Wall -Wextra -std=c11 -O2 main.c avl.c rubronegra.c arvoreb.c -o main
./main
python3 graficos.py
```

Na primeira execução, se não existir o `chaves.csv`, o programa gera as chaves com `rand` e salva no arquivo. Depois disso ele sempre usa o mesmo arquivo.
