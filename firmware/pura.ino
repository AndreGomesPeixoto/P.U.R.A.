#define RELAY_PIN 7      // Pino do relé ligado à bomba
#define SOIL_PIN A0      // Pino analógico do sensor de umidade

int umidadeSolo = 0;
int limiteUmidade = 700; // Ajustar conforme o sensor 

// Configuração inicial
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Bomba começa desligada
  Serial.begin(9600);
}

// Loop principal
void loop() {
  umidadeSolo = analogRead(SOIL_PIN);
  Serial.print("Umidade do solo: ");
  Serial.println(umidadeSolo);

  if (umidadeSolo < limiteUmidade) {
    // Solo está bem úmido -> ligar bomba
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Bomba LIGADA!");
  } else {
    // Solo seco ou úmido insuficiente -> desligar
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Bomba DESLIGADA!");
  }

  delay(2000); // Leitura a cada 2 segundos
}
