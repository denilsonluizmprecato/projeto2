#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std; 

struct Posicao {
    int x;
    int y;
    clock_t tempo;
};

struct Velocidade {
    float velocidade;
    clock_t tempo;
};

// FUNCOES

// soma a cada ordenada de um par ordenado de posição valor aleatorio entre -10 e 10
void posicaoAleatoria(Posicao &s, unsigned seed, clock_t tempo) { 
    srand(seed);
    s.x += (rand() % 20 + 1) - 10;

    srand(seed + 50);
    s.y += (rand() % 20 + 1) - 10;
    
    s.tempo = tempo;
}

Velocidade velocidade(Posicao inicial, Posicao final) {
    Velocidade v;

    v.velocidade = sqrt( pow(final.x - inicial.x, 2) + pow(final.y - inicial.y, 2) ) / (final.tempo - inicial.tempo);
    v.tempo = clock();

    return v;
}

float aceleracao(Velocidade inicial, Velocidade final) {
    return (final.velocidade - inicial.velocidade) / (final.tempo - inicial.tempo);
}

int main() {
    int num_de_leituras = 10;

    clock_t tempo = clock();

    Posicao s;
    s.x = 0;
    s.y = 0;
    s.tempo = tempo;

    Velocidade v;
    v.velocidade = 0;
    v.tempo = tempo;

    cout << " X   Y     tempo     velocidade     aceleracao " << endl;

    for (int i=0; i<num_de_leituras; i++) {
        Posicao auxs = s;
        Velocidade auxv = v;

        posicaoAleatoria(s, clock(), clock()); // o primeiro clock() eh pra garantir deração de numero aleatorio, o segundo eh soh pra marcar o tempo em que a posicao foi somada

        v = velocidade(auxs, s);
        
        cout << s.x << "   " << s.y << "     " << s.tempo << "       " << v.velocidade << "       " << aceleracao(auxv, v) << endl;
    }
}

// iniciar uma thread pra cada sensor de posicao (camera, gps, odometria)
// em cada thread deve ocorrer: pegar a posicao, calcular a velocidade e aceleracao