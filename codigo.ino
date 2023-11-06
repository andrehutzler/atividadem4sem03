//ESSE CÓDIGO FOI FEITO NO ARDUINO IDE

#include <Arduino.h>

const int LED1 = 16;
const int LED2 = 17;
const int LED3 = 21;
const int LED4 = 22;

const int BOTAO1 = 27;
const int BOTAO2 = 26;
const int BOTAO3 = 25;
const int BOTAO4 = 33;
const int BOTAORESET = 35;

const int MAX_LEVEL = 5;

int leds[4] = {LED1, LED2, LED3, LED4};
int botoes[4] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4};

int sequencia[MAX_LEVEL];
int player_sequence[MAX_LEVEL];
int nivel = 0;
int velocidade = 1000;

void configurarPinos() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }
  pinMode(BOTAORESET, INPUT_PULLUP);
}

void iniciarJogo() {
  nivel = 1;
  randomSeed(analogRead(0));
  for (int i = 0; i < MAX_LEVEL; i++) {
    sequencia[i] = random(0, 4);
  }
  delay(1000);
}

void mostrarSequencia() {
  for (int i = 0; i < nivel; i++) {
    int led_a_acender = sequencia[i];
    digitalWrite(leds[led_a_acender], HIGH);
    delay(velocidade);
    digitalWrite(leds[led_a_acender], LOW);
    delay(200);
  }
  delay(500);
}

void obterSequenciaJogador() {
  int indice_jogador = 0;

  while (indice_jogador < nivel) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(botoes[i]) == LOW) {
        player_sequence[indice_jogador] = i;
        digitalWrite(leds[i], HIGH);
        delay(200);
        digitalWrite(leds[i], LOW);
        indice_jogador++;
        delay(200);
      }
    }
  }

  verificarSequenciaJogador();
}

void verificarSequenciaJogador() {
  for (int i = 0; i < nivel; i++) {
    if (player_sequence[i] != sequencia[i]) {
      nivel = 0;
      return;
    }
  }
  nivel++;
  delay(500);
}

void reiniciarJogo() {
  nivel = 0;
}

void setup() {
  configurarPinos();
}

void loop() {
  if (nivel == 0) {
    if (digitalRead(BOTAORESET) == LOW) {
      iniciarJogo();
    }
  } else if (nivel <= MAX_LEVEL) {
    mostrarSequencia();
    obterSequenciaJogador();
  } else {
    reiniciarJogo();
  }
}