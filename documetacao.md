EXPLICAÇÃO DO CÓDIGO:
Parte 1-
const int LED1 = 16;
const int LED2 = 17;
const int LED3 = 21;
const int LED4 = 22;

const int BOTAO1 = 27;
const int BOTAO2 = 26;
const int BOTAO3 = 25;
const int BOTAO4 = 33;
const int BOTAORESET = 35;

Nessa parte eu defini os pinos dos LEDs e os Botões.

Parte 2-
const int MAX_LEVEL = 5;

Nessa parte eu defini o nível máximo do jogo.

Parte 3-
int leds[4] = {LED1, LED2, LED3, LED4};
int botoes[4] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4};

Nessa parte eu defini os arrays que armazenam o pinos dos LEDs e dos Botões. Com esses arrays, fica mais fácil de acessar os respectivos LEDs e Botões dentro do código.

Parte 4-
int sequencia[MAX_LEVEL];
int player_sequence[MAX_LEVEL];
int nivel = 0;
int velocidade = 1000;

Nessa parte eu defini os arrays que armazenam as sequências dos LEDs dentro do jogo junto com a sequência que o jogador botou.
O "int nivel = 0;" controla o nível atual do jogador.
O "int velocidade = 1000;" define o tempo que os LEDs ficam acesos.

Parte 5-
void configurarPinos() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }
  pinMode(BOTAORESET, INPUT_PULLUP);
}

Essa parte defini os pinos dos LEDs como saída e os pindos de Botões como entrada usando usando o PULLUP.

Parte 6-
void iniciarJogo() {
  nivel = 1;
  randomSeed(analogRead(0)); // Inicializa o gerador de números aleatórios.
  for (int i = 0; i < MAX_LEVEL; i++) {
    sequencia[i] = random(0, 4); // Preenche a sequência com números aleatórios.
  }
  delay(1000);
}

Essa parte é responsável por iniciar o jogo.
A parte "randomSeed(analogRead(0));" é responsável por randomizar a sequência de LEDs
E a parte "sequencia[i] = random(0, 4);\" é responsável por preencher a sequência com números aleatórios.

Parte 7-
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

Essa parte é responsável por mostrar a sequência atual dos LEDs(faz o LED piscar)

Parte 8-
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
Essa parte é responsável por captar a sequência que dos LEDs que o jogador escolheu

Parte 9-
void verificarSequenciaJogador() {
  for (int i = 0; i < nivel; i++) {
    if (player_sequence[i] != sequencia[i]) { // Se houver diferença, reinicia o jogo.
      nivel = 0;
      return;
    }
  }
  nivel++;
  delay(500);
}

Essa parte verifica a sequência que o jogador apertou dos LEDs
A parte "if (player_sequence[i] != sequencia[i])" é responsável por verificar se o jogador fez uma escolha de LEDs diferente da que foi pedida.
A parte "nivel++" avança de nível se o jogador acertar a sequência de LEDs

Parte 10-
void reiniciarJogo() {
  nivel = 0;
}

Essa parte é responsável por mudar o nível para 0 quando o jogo precisar reiniciar.

Parte 11-
void setup() {
  configurarPinos();
}

Essa parte é ativada uma vez quando o jogo for iniciado.

Parte 12-
void loop() {
  if (nivel == 0) {
    if (digitalRead(BOTAORESET) == LOW) {
      iniciarJogo();
    }
  } else if (nivel <= MAX_LEVEL) {
  } else {
    reiniciarJogo();
  }
}

Essa parte fica rodando continuamente após o "void setup()" ser executado"
A parte "if (nivel == 0) {
    if (digitalRead(BOTAORESET) == LOW) {
      iniciarJogo();
    }}" fica responsável por iniciar o jogo seo jogador apertar o botão de reset, ou seja, se o jogador perder o jogo, ou quiser iniciar o game, o jogador aperta o botão reset, e o jogo se (re)inicia.
A parte "else if (nivel <= MAX_LEVEL) {
  } else {
    reiniciarJogo();
  }" é responsável por verificar o nível que o jogador está(se o jogador não estiver no nível máximo, o jogo continua e se ele estiverno máximo o jogo reinicia)e também por determinar quando que o jogo deve ser reiniciado, ou seja, quando o jogo chegar no ível máximo, o jogador ganha o jogo e o jogo é reiniciado.