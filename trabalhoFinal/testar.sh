# usar no terminal:
## /bin/bash
## ou
## chmod +x testar.sh && ./testar.sh

echo "=== GERANDO INPUT GRANDE ==="
g++ -O2 -o gerador gerador.cpp
./gerador

echo "=== COMPILANDO ==="
g++ -o programa trabalho.cpp

echo "=== EXECUTANDO ==="
# ./programa < ./inputs/input_simples.txt > output.txt
./programa < ./inputs/input_grande.txt > output.txt

echo "=== COMPARANDO ==="
# if diff output.txt ./outputs/output_simples_esperado.txt > /dev/null; then
if diff output.txt ./outputs/output_grande_esperado.txt > /dev/null; then
    echo "A saida está correta"
else
    echo "As saidas são diferentes"
    # diff -u output.txt ./outputs/output_simples_esperado.txt
    diff -u output.txt ./outputs/output_grande_esperado.txt > diferencas.txt
fi

echo "=== ESTATÍSTICAS ==="
# echo "Linhas na saída esperada: $(wc -l < ./outputs/output_simples_esperado.txt)"
echo "Linhas na saída esperada: $(wc -l < ./outputs/output_grande_esperado.txt)"
echo "Linhas na sua saída: $(wc -l < output.txt)"