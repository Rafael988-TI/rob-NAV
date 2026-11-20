/**
  Robô NAV (desvia obstáculos)
  @author Rafael cardoso de lira
  @version 1.0
  @link https://github.com/Rafael988-TI/rob-NAV.wiki.git
*/

// sensor ultrassônico
#define echo 11  //recebe o pulso
#define trig 12  //envia pulso
// led indicador
#define led 13  //led indicador
// Motores
#define M1A 5   //motor esquerda
#define M1B 6   //motor esquerda
#define M2A 10  //motor direita
#define M2B 9   //motor direita

int velM1 = 255;  //velocidade do motor M1 (0 a 255)
int velM2 = 255;  //velocidade do motor M2 (0 a 255)


void setup() {
  pinMode(led, OUTPUT);   // Led indicador
  pinMode(trig, OUTPUT);  //sensor
  pinMode(echo, INPUT);   //sensor
  pinMode(M1A, OUTPUT);   //Motor Esquerda
  pinMode(M1B, OUTPUT);   //Motor Esquerda
  pinMode(M2A, OUTPUT);   //Motor Direita
  pinMode(M2B, OUTPUT);   //Motor Direita
  Serial.begin(9600);     //teste do sonar
}

void loop() {
  // executa a função ping (dispara o pulso) e guarda na variável distancia
  int distancia = ping();
  Serial.print(distancia);
  Serial.println(" cm");

  //lógica principal
  if (distancia < 30) {
    digitalWrite(led, HIGH);
    parar();
    delay(1000);  //ficar parado por 1 segundo
    direita();    //girar sentido horário
    delay(300);   //por 300ms
  } else {
    digitalWrite(led, LOW);
    frente();
  }

  delay(60);  //60ms entre leituras para evitar eco residual
}

// função para ler o sensor e retornar o valor em cm.
int ping() {
  // iniciar o trig desligado
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // enviar pulso de 10 microsegundos
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // ler o tempo de duração(retorno) no echo
  long duracao = pulseIn(echo, HIGH);
  // converter para centímetros
  int distancia = duracao / 58.0;
  //retorna o valor da distância em cm
  return distancia;
}

// Função para mover o robô para a frente
void frente() {
  analogWrite(M1A, velM1);
  analogWrite(M1B, 0);
  analogWrite(M2A, velM2);
  analogWrite(M2B, 0);
}

//função para mover o robô de ré
void re() {
  analogWrite(M1B, velM1);
  analogWrite(M1A, 0);
  analogWrite(M2B, velM2);
  analogWrite(M2A, 0);
}

//função para girar o robô no sentido horário(esquerda)
void esquerda() {
  analogWrite(M1B, velM1);
  analogWrite(M1A, 0);
  analogWrite(M2A, velM2);
  analogWrite(M2B, 0);
}

//função para girar o robô no sentido anti-horário(direita)
void direita() {
  analogWrite(M1A, velM1);
  analogWrite(M1B, 0);
  analogWrite(M2B, velM2);
  analogWrite(M2A, 0);
}

// Função parar o robô
void parar() {
  analogWrite(M1A, 0);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, 0);
}
