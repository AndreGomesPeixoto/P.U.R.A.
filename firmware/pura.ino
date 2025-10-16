// =======================================================
// INCLUSÃO DE BIBLIOTECAS
// =======================================================
#include <Wire.h>                 // Biblioteca para comunicação I2C
#include <Adafruit_GFX.h>         // Biblioteca gráfica principal
#include <Adafruit_SSD1306.h>     // Biblioteca do driver do display OLED

// =======================================================
// DEFINIÇÕES E PARÂMETROS
// =======================================================
// --- Pinos ---
#define RELAY_PIN 7
#define SOIL_PIN A3
#define SENSOR_POWER_PIN 8

// --- Parâmetros de Controle (AJUSTE AQUI APÓS CALIBRAR!) ---
int limiteLigarBomba = 400;
int limiteDesligarBomba = 650;

// --- Configurações do Display OLED ---
#define SCREEN_WIDTH 128 // Largura do display em pixels
#define SCREEN_HEIGHT 64 // Altura do display em pixels
#define OLED_RESET -1    // Pino de reset (-1 se estiver compartilhando o reset do Arduino)
// Cria o objeto do display usando a comunicação I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Variáveis Globais ---
int umidadeSolo = 0;
String statusBomba = "INICIANDO"; // Variável para guardar o status da bomba

// =======================================================
// Configuração Inicial - Roda apenas uma vez
// =======================================================
void setup() {
  Serial.begin(9600);
  Serial.println(">>> Sistema de Drenagem Inteligente INICIADO! <<<");

  // --- Inicialização dos pinos ---
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);      // Garante que a bomba comece desligada (para relé active LOW)
  digitalWrite(SENSOR_POWER_PIN, LOW);

  // --- INICIALIZAÇÃO DO DISPLAY OLED ---
  // Tenta iniciar o display. O endereço 0x3C é o mais comum para displays de 128x64.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Falha ao encontrar o display SSD1306"));
    while(1); // Se não encontrar, trava o código aqui. Verifique as conexões!
  }

  // Se encontrou, mostra uma tela de boas-vindas
  display.clearDisplay(); // Limpa o buffer do display
  display.setTextSize(1); // Define o tamanho da fonte
  display.setTextColor(SSD1306_WHITE); // Define a cor do texto
  display.setCursor(10, 20); // Posição (coluna, linha)
  display.println("Sistema de Drenagem");
  display.setCursor(35, 35);
  display.println("INICIANDO...");
  display.display(); // Efetivamente desenha no display!
  delay(2000);
}

// =======================================================
// Loop Principal - Roda para sempre!
// =======================================================
void loop() {
  // --- Leitura Inteligente do Sensor ---
  digitalWrite(SENSOR_POWER_PIN, HIGH);
  delay(500);
  umidadeSolo = analogRead(SOIL_PIN);
  digitalWrite(SENSOR_POWER_PIN, LOW);
  
  // --- Lógica de Decisão com HISTERESE ---
  if (umidadeSolo > limiteLigarBomba) {
    digitalWrite(RELAY_PIN, LOW); // Desliga a bomba
    statusBomba = "LIGADA";
  } else if (umidadeSolo < limiteDesligarBomba) {
    digitalWrite(RELAY_PIN, HIGH); // Liga a bomba
    statusBomba = "DESLIGADA";
  }
  // Se a umidade estiver entre os dois limites, o status da bomba não muda.

  // --- ATUALIZAÇÃO DO DISPLAY OLED ---
  display.clearDisplay(); // Limpa a tela para reescrever as informações
  
  // Título
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("CONTROLE DE UMIDADE");

  // Informação da Umidade
  display.setTextSize(2); // Fonte maior para o valor principal
  display.setCursor(0, 20);
  display.print("Valor: ");
  display.print(umidadeSolo);

  // Status da Bomba
  display.setTextSize(2); // Fonte maior
  display.setCursor(0, 43);
  display.print("Bomba: ");
  display.print(statusBomba);

  // Envia tudo para ser desenhado na tela
  display.display();

  // --- ATUALIZAÇÃO DO MONITOR SERIAL (para debug) ---
  Serial.print("Umidade do solo: ");
  Serial.print(umidadeSolo);
  Serial.print(" | Status da Bomba: ");
  Serial.println(statusBomba);
  Serial.println("------------------------------------");
  
  delay(2000); // Reduzi o delay para a tela atualizar mais rápido. Ajuste como preferir.
}
