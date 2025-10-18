#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int main() {
    ofstream input("./inputs/input_grande.txt");
    ofstream output("./outputs/output_grande_esperado.txt");
    
    random_device rd;
    mt19937 gen(rd());
    
    // gerar vários casos de teste
    for (int caso = 0; caso < 10; caso++) {
        int n = 15 + (gen() % 6); // entre 15 e 20 pessoas
        if (caso == 0) n = 20; // primeiro caso com 20 pessoas
        
        input << n << endl;
        
        // gerar grafo de amizades
        vector<vector<int>> amigos(n + 1);
        
        for (int i = 1; i <= n; i++) {
            vector<int> todos_amigos;
            // lista de todos possíveis amigos
            for (int j = 1; j <= n; j++) {
                if (j != i) todos_amigos.push_back(j);
            }
            
            // embaralhar e pegar os primeiros
            shuffle(todos_amigos.begin(), todos_amigos.end(), gen);
            int num_amigos = 3 + (gen() % 4); // 3 a 6 amigos
            
            for (int j = 0; j < num_amigos && j < todos_amigos.size(); j++) {
                amigos[i].push_back(todos_amigos[j]);
                input << todos_amigos[j] << " ";
            }
            input << "0" << endl;
        }
        
        // gerar mensagens de spam
        int num_mensagens = 100;
        vector<vector<string>> atributos_por_pessoa(n + 1);
        
        for (int m = 0; m < num_mensagens; m++) {
            int p = 1 + (gen() % n);
            int t1 = 2 + (gen() % 5);  // t1 entre 2-6
            int t2 = t1 + 3 + (gen() % 5); // t2 entre t1+3 e t1+7
            
            string a1 = "a1_" + to_string(m);
            string a2 = "a2_" + to_string(m);
            string a3 = "a3_" + to_string(m);
            
            input << p << " " << t1 << " " << t2 << " " << a1 << " " << a2 << " " << a3 << endl;
            
            // bfs para propagação da mensagem
            vector<bool> recebido(n + 1, false);
            vector<int> fila;
            
            fila.push_back(p);
            recebido[p] = true;
            
            for (size_t idx = 0; idx < fila.size(); idx++) {
                int u = fila[idx];
                for (int amigo : amigos[u]) {
                    if (!recebido[amigo]) {
                        recebido[amigo] = true;
                        fila.push_back(amigo);
                    }
                }
            }
            
            // atribuir atributos para cada pessoa
            for (int pessoa = 1; pessoa <= n; pessoa++) {
                string atributo;
                
                if (!recebido[pessoa]) {
                    atributo = a1;
                } else {
                    int t = amigos[pessoa].size();
                    if (t < t1) {
                        atributo = a1;
                    } else if (t < t2) {
                        atributo = a2;
                    } else {
                        atributo = a3;
                    }
                }
                atributos_por_pessoa[pessoa].push_back(atributo);
            }
        }
        input << "0" << endl;
        
        // gerar nomes das pessoas
        for (int i = 1; i <= n; i++) {
            string nome = "pessoa_" + to_string(i + caso * 100);
            input << nome << endl;
        }
        
        // escrever saída esperada
        for (int i = 1; i <= n; i++) {
            output << "pessoa_" << (i + caso * 100) << ": ";
            if (!atributos_por_pessoa[i].empty()) {
                for (size_t j = 0; j < atributos_por_pessoa[i].size(); j++) {
                    output << atributos_por_pessoa[i][j] << " "; 
                }
            }
            output << endl;
        }

    }
    
    input << "0" << endl;
    input.close();
    output.close();
    
    cout << "gerados: input_grande.txt e output_grande_esperado.txt" << endl;
    return 0;
}