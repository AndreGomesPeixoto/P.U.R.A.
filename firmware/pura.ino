#define RELAY_PIN 7 // pino conectado ao módulo relé

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // bomba desligada no início
}

void loop() {
  // Exemplo básico: liga a bomba por 10s, desliga 20s
  digitalWrite(RELAY_PIN, HIGH); 
  delay(10000);
  digitalWrite(RELAY_PIN, LOW);  
  delay(20000);
}
