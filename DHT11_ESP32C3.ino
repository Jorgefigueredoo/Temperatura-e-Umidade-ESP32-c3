/*
 * Projeto: Leitura de Temperatura e Umidade
 * Hardware: ESP32-C3 + DHT11 (versão de 4 pinos)
 *
 * Ligação:
 *   DHT11 Pino 1 (VCC)  -> 3V3
 *   DHT11 Pino 2 (DATA) -> GPIO 4
 *   DHT11 Pino 3 (NC)   -> não conectado
 *   DHT11 Pino 4 (GND)  -> GND
 *
 * ATENÇÃO: este teste foi feito SEM resistor de pull-up entre DATA e VCC.
 * Caso o sensor não responda (erro "Guru Meditation" / watchdog timeout),
 * adicione um resistor de aproximadamente 10 kOhm entre DATA e 3V3.
 *
 * Biblioteca necessária: "DHT sensor library" (Adafruit)
 * Instale em: Arduino IDE > Sketch > Include Library > Manage Libraries
 * Pode ser necessário também instalar a dependência "Adafruit Unified Sensor".
 */

#include <DHT.h>

// Pino digital do ESP32-C3 conectado ao DATA do DHT11
#define DHTPIN 4

// Modelo do sensor utilizado (DHT11)
#define DHTTYPE DHT11

// Cria o objeto do sensor, associando o pino e o tipo definidos acima
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Inicia a comunicação serial em 115200 baud (mesma taxa usada no
  // Monitor Serial da Arduino IDE)
  Serial.begin(115200);

  // Pequeno atraso para dar tempo do Monitor Serial conectar e
  // do sensor estabilizar após ligar
  delay(2000);

  Serial.println();
  Serial.println("================================");
  Serial.println("   TESTE DHT11 - ARROCHA!");
  Serial.println("================================");

  // Inicializa o sensor DHT11
  dht.begin();
}

void loop() {
  Serial.println("Lendo o sensor...");

  // Tenta ler a temperatura (em graus Celsius) e a umidade relativa (%)
  // OBS: é aqui que o projeto vem travando com "Guru Meditation Error"
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  // isnan() verifica se a leitura falhou (Not a Number).
  // Se qualquer uma das duas leituras falhar, exibe mensagem de erro.
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("ERRO! DHT11 nao respondeu.");
  } else {
    // Leitura bem-sucedida: imprime os valores no Monitor Serial
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");
  }

  Serial.println("----------------------------");

  // O DHT11 só pode ser lido a cada ~1-2 segundos, por isso o delay
  delay(2000);
}
