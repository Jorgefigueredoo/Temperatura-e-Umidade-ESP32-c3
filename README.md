# ESP32-C3 + DHT11 — Leitura de Temperatura e Umidade

Projeto de leitura de temperatura e umidade relativa do ar utilizando o
microcontrolador **ESP32-C3** e o sensor **DHT11 (versão de 4 pinos)**.

> ⚠️ **Status atual: em diagnóstico.** O sensor ainda não está retornando
> leituras válidas — o projeto trava com `Guru Meditation Error` ao tentar ler
> o DHT11. Veja a seção [Diagnóstico](#-diagnóstico-atual) abaixo.

## 👥 Equipe

- Jorge Antonio
- Davi Clemente
- Pedro Valença
- Ygor Sampaio
- Nicolas Tavares

## 🎯 Objetivo

Realizar a comunicação entre o ESP32-C3 e o sensor DHT11, obtendo:

- Temperatura em graus Celsius (°C)
- Umidade relativa do ar (%)

## 🔧 Hardware

| Item | Especificação |
|---|---|
| Microcontrolador | ESP32-C3 |
| Sensor | DHT11 — versão de **4 pinos** (não é o módulo de 3 pinos) |
| Pino de dados | GPIO 4 |
| IDE utilizada | Arduino IDE |

### Pinagem do DHT11 (4 pinos)

Olhando o sensor pela frente, com a grade voltada para o usuário:

```
DHT11
┌─────────┐
│ ▦▦▦▦ │
└─────────┘
 1  2  3  4

Pino 1 → VCC
Pino 2 → DATA
Pino 3 → NC (não conectado)
Pino 4 → GND
```

### Ligação utilizada no projeto

| DHT11 | ESP32-C3 |
|---|---|
| Pino 1 — VCC | 3V3 |
| Pino 2 — DATA | GPIO 4 |
| Pino 3 — NC | não conectar |
| Pino 4 — GND | GND |

```
ESP32-C3
   │
   └── GPIO 4 ─── DATA do DHT11
```

> ⚠️ **Ressalva sobre pull-up:** normalmente é recomendado um resistor de
> pull-up de aproximadamente **10 kΩ** entre DATA e VCC em sensores DHT11 de
> 4 pinos. Neste projeto, **o teste foi feito sem esse resistor**, o que é um
> forte candidato à causa do problema atual (ver Diagnóstico).

## 📚 Biblioteca utilizada

- [`DHT sensor library`](https://github.com/adafruit/DHT-sensor-library) — Adafruit
- Dependência (dependendo da versão): `Adafruit Unified Sensor`

Instalação: Arduino IDE → **Sketch → Include Library → Manage Libraries** →
buscar por `DHT sensor library` (Adafruit) e instalar.

## 🐛 Problemas encontrados e soluções

### 1. `fatal error: DHT.h: No such file or directory`
**Causa:** biblioteca DHT não instalada.
**Solução:** instalada via gerenciador de bibliotecas da Arduino IDE.

### 2. `Unable to find executable file at .../sketch_aug31a.ino.elf`
Erro relacionado ao processo de compilação/upload. Para isolar o problema, foi
feito um teste independente só com comunicação serial (sem o sensor), que
confirmou que a placa, o upload e o Monitor Serial (115200 baud) estavam
funcionando normalmente.

### 3. `Guru Meditation Error: Core 0 panic'ed (Interrupt wdt timeout on CPU0)`
Ocorre ao chamar `dht.readTemperature()` ou `dht.readHumidity()`. A placa
reinicia (`rst:0xc RTC_SW_CPU_RST`) logo em seguida.

Esse erro se repetiu **mesmo em um teste de leitura direta**, sem depender da
biblioteca `DHT.h` — ou seja, o problema não é causado apenas pela biblioteca,
e sim algo na comunicação física com o sensor (ex.: ausência do resistor de
pull-up, fiação, ou o próprio sensor).

## ✅ Diagnóstico atual

| Item | Status |
|---|---|
| ESP32-C3 | ✅ Funcionando |
| Alimentação da placa | ✅ Funcionando |
| Upload de programas | ✅ Funcionando |
| Monitor Serial | ✅ Funcionando |
| Leitura do DHT11 | ❌ Falhando (watchdog timeout) |

## 🔜 Próximos passos

- [ ] Adicionar resistor de pull-up de ~10 kΩ entre DATA e VCC
- [ ] Revisar a fiação/continuidade dos 4 pinos do sensor
- [ ] Testar com outro sensor DHT11 (descartar sensor defeituoso)
- [ ] Testar em outro GPIO, caso o problema persista

## 💻 Código

O sketch atual de teste está em [`DHT11_ESP32C3.ino`](./DHT11_ESP32C3.ino).

## 📅 Data

31/08/2026
