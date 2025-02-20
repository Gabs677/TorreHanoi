#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Função para imprimir o estado atual das torres
void imprimirTorres(const vector<vector<int>>& torres, int movimentos) {
    cout << "Movimento #" << movimentos << endl;
    cout << "Torre 1: ";
    for (int disco : torres[0]) {
        cout << disco << " ";
    }
    cout << endl;

    cout << "Torre 2: ";
    for (int disco : torres[1]) {
        cout << disco << " ";
    }
    cout << endl;

    cout << "Torre 3: ";
    for (int disco : torres[2]) {
        cout << disco << " ";
    }
    cout << endl;

    cout << "------------------" << endl;
}

// Função para mover um disco de uma torre para outra
void moverDisco(vector<vector<int>>* torres, int origem, int destino, int& movimentos) {
    int disco = torres->at(origem).back();
    torres->at(origem).pop_back();
    torres->at(destino).push_back(disco);
    movimentos++;
}

// Função recursiva para resolver a Torre de Hanoi
void resolverHanoi(vector<vector<int>>* torres, int n, int origem, int auxiliar, int destino, int& movimentos) {
    if (n > 0) {
        resolverHanoi(torres, n - 1, origem, destino, auxiliar, movimentos);
        imprimirTorres(*torres, movimentos);
        moverDisco(torres, origem, destino, movimentos);
        resolverHanoi(torres, n - 1, auxiliar, origem, destino, movimentos);
    }
}

int main() {
    int numDiscos;
    int movimentos = 0;

    cout << "Digite o número de discos: ";
    cin >> numDiscos;

    // Calculando o número mínimo de movimentos
    int movimentosMinimos = pow(2, numDiscos) - 1;
    cout << "Número mínimo de movimentos: " << movimentosMinimos << endl;

    // Inicializando as torres
    vector<vector<int>> torres(3);
    for (int i = numDiscos; i > 0; --i) {
        torres[0].push_back(i);
    }

    // Imprimindo o estado inicial
    imprimirTorres(torres, movimentos);

    // Jogando interativamente
    while (true) {
        // Verificando se o jogo foi resolvido
        if (torres[2].size() == numDiscos) {
            cout << "Parabéns! Você resolveu a Torre de Hanoi!" << endl;
            break;
        }

        // Solicitando movimento ao jogador
        int origem, destino;
        cout << "Digite a torre de origem (1, 2, 3): ";
        cin >> origem;

        cout << "Digite a torre de destino (1, 2, 3): ";
        cin >> destino;

        // Validando movimento
        if (origem >= 1 && origem <= 3 && destino >= 1 && destino <= 3 && origem != destino &&
            !torres[origem - 1].empty() && (torres[destino - 1].empty() || torres[destino - 1].back() > torres[origem - 1].back())) {
            moverDisco(&torres, origem - 1, destino - 1, movimentos);
        } else {
            cout << "Movimento inválido. Tente novamente." << endl;
        }

        // Imprimindo o estado atual
        imprimirTorres(torres, movimentos);
    }

    // Exibindo resultados
    cout << "Torre de Hanoi resolvida em " << movimentos << " movimentos!" << endl;

    return 0;
}