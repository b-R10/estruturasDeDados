#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    // otimiza input/output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; // numero de pessoas no grupo
    
    // loop para processar os casos
    while (cin >> n && n > 0) {
        // armazena uma lista de amigos para cada pessoa
        // amigos[i] contém a lista de amigos da pessoa i
        vector<vector<int>> amigos(n + 1);
        
        // le a lista de amigos para cada pessoa
        for (int i = 1; i <= n; ++i) {
            int amigo;
            // le amigo até encontrar 0
            while (cin >> amigo && amigo != 0) {
                // verifica se amigo é valido
                if (amigo >= 1 && amigo <= n) {
                    // add amigo a ao fim do vetor(lista)
                    amigos[i].push_back(amigo); 
                }
            }
        }
        
        // atributos[i] armazena todos os atributos da pessoa i
        vector<vector<string>> atributos(n + 1);
        // visitado controla quem recebeu a mensagem atual
        vector<bool> visitado(n + 1);
        // fila para o BFS (busca em largura)
        queue<int> fila;
        
        int origem; // pessoa originadora do spam
        // processa cada spam até encontrar origem = 0
        while (cin >> origem && origem != 0) {
            int t1, t2; // limites dos atributos
            string a1, a2, a3; // atributos possíveis
            
            // le parâmetros da mensagem, sair se houver erro na leitura
            if (!(cin >> t1 >> t2 >> a1 >> a2 >> a3)) break;
            
            // reseta o vetor de visitados para o novo spam
            fill(visitado.begin(), visitado.end(), false);
            // limpa a fila
            while (!fila.empty()) fila.pop();
            
            // inicia BFS a partir da origem
            fila.push(origem);
            visitado[origem] = true; // marca como recebido o spam
            
            // BFS para mandar o spam
            while (!fila.empty()) {
                int atual = fila.front(); // proxima pessoa da fila
                fila.pop(); // remove da fila
                
                // para cada amigo da pessoa atual
                for (int amigo : amigos[atual]) {
                    // verifica se o amigo é válido e não recebeu o spam
                    if (amigo >= 1 && amigo <= n && !visitado[amigo]) {
                        visitado[amigo] = true; // marca como recebido
                        fila.push(amigo); // adiciona a fila para processar depois
                    }
                }
            }
            
            // para cada pessoa, determina qual atributo ela ganha no spam
            for (int i = 1; i <= n; i++) {
                if (!visitado[i]) {
                    // se nao recebeu o spam: a1
                    atributos[i].push_back(a1);
                } else {
                    // se recebeu, aplicar regra padrao
                    int num_amigos = amigos[i].size(); // numero de amigos da pessoa
                    if (num_amigos < t1) {
                        atributos[i].push_back(a1);
                    } else if (num_amigos < t2) {
                        atributos[i].push_back(a2);
                    } else {
                        atributos[i].push_back(a3);
                    }
                }
            }
        }
        
        // armazena os nomes das pessoas
        vector<string> nomes(n + 1);
        // le os nomes das pessoas na ordem dos ids
        for (int i = 1; i <= n; i++) {
            if (!(cin >> nomes[i])) break; // sair se houver erro na leitura
        }
        
        // gera saida final: atributos/pessoa
        for (int i = 1; i <= n; i++) {
            // so imprimir se a pessoa tem pelo menos um atributo
            if (!atributos[i].empty()) {
                cout << nomes[i] << ": "; // Imprime nome
                // imprime todos os atributos
                for (string& atributo : atributos[i]) {
                    cout << atributo << " ";
                }
                cout << "\n"; // nova linha após cada pessoa
            }
        }
    }
    
    return 0;
}