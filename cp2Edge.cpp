#include <Wire.h> // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h> // Biblioteca utilizada para fazer a comunicação com o display 20x4 
#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x27 // Serve para definir o endereço do display.
//a4 a5 ligar o display

LiquidCrystal_I2C lcd(ende,col,lin); // Chamada da funcação LiquidCrystal para ser usada com o I2C

#include <Adafruit_Sensor.h> // Biblioteca DHT Sensor Adafruit 
#include <DHT.h>
#include <DHT_U.h>

//#define DHTTYPE    DHT11                           // Sensor DHT11
#define DHTTYPE    DHT22                       // Sensor DHT22 ou AM2302
#define DHTPIN 2                                   // Pino do Arduino conectado no Sensor(Data) 
DHT_Unified dht(DHTPIN, DHTTYPE);                  // configurando o Sensor DHT - pino e tipo
uint32_t delayMS;                                  // variável para atraso no tempo

int ledPinVerd = 13; /// led verde
int ledPinAm = 9 ; /// led amarelo  mudar para 12 depois
int ledPinVer = 8; /// led vermelho
int valorluz = 0; /// valor que o sensor de luz manda pra placa
int ldrpin = A0; /// sensor de luz
int buzzer = 7; /// buzina
int valorluz_prc = 0; // valor da luminosidade em porcentagem

void setup(){
    //display
    lcd.init(); // Serve para iniciar a comunicação com o display já conectado
    lcd.backlight(); // Serve para ligar a luz do display
    lcd.clear(); // Serve para limpar a tela do display
    lcd.setCursor(0, 1); // Move o cursor para a segunda linha
    
    //leds
    pinMode(ledPinVerd, OUTPUT); // Define o pino do LED verde como saída
    pinMode(ledPinAm, OUTPUT);   // Define o pino do LED amarelo como saída
    pinMode(ledPinVer, OUTPUT);  // Define o pino do LED vermelho como saída

    //sensor de temperatura e umidade
    Serial.begin(9600);                             // monitor serial 9600 bps
    dht.begin();                                    // inicializa a função
    Serial.println("Usando o Sensor DHT");
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);           // imprime os detalhes do Sensor de Temperatura
    Serial.println("------------------------------------");
    Serial.println("Temperatura");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println(" *C");
    Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println(" *C");
    Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println(" *C");
    Serial.println("------------------------------------");
    dht.humidity().getSensor(&sensor);            // imprime os detalhes do Sensor de Umidade
    Serial.println("------------------------------------");
    Serial.println("Umidade");
    Serial.print  ("Sensor:       "); Serial.println(sensor.name);
    Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println("%");
    Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println("%");
    Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println("%");
    Serial.println("------------------------------------");
    delayMS = sensor.min_delay / 1000;            // define o atraso entre as leituras
}

void loop() {
    delay(delayMS); // Aguarda o tempo mínimo entre leituras
    sensors_event_t event;

    // Leitura dos sensores
    dht.temperature().getEvent(&event); // Lê temperatura
    float temperatura = isnan(event.temperature) ? -999 : event.temperature; // Se leitura inválida, retorna -999
    
    dht.humidity().getEvent(&event); // Lê umidade
    float umidade = isnan(event.relative_humidity) ? -1 : event.relative_humidity; // Se leitura inválida, retorna -1

    valorluz = analogRead(ldrpin); // Lê valor do sensor de luz
    valorluz_prc = valorluz * 0.098; // Converte valor para porcentagem

    // Controle dos LEDs e buzzer (novas regras)
    bool condicaoCritica = false; // Condição para buzzer

    // 1. Controle de Luminosidade (LED Verde)
    if (valorluz <= 600) {
        digitalWrite(ledPinVerd, HIGH); // Liga LED verde
        digitalWrite(ledPinAm, LOW);    // Desliga LED amarelo
        digitalWrite(ledPinVer, LOW);   // Desliga LED vermelho
    } else if (valorluz <= 801) {
        digitalWrite(ledPinVerd, LOW);  // Desliga LED verde
        digitalWrite(ledPinAm, HIGH);   // Liga LED amarelo (alerta médio)
        digitalWrite(ledPinVer, LOW);   // Desliga LED vermelho
    } else {
        digitalWrite(ledPinVerd, LOW);  // Desliga LED verde
        digitalWrite(ledPinAm, LOW);    // Desliga LED amarelo
        digitalWrite(ledPinVer, HIGH);  // Liga LED vermelho (alerta alto)
        condicaoCritica = true;         // Seta condição crítica
    }

    // 2. Controle de Temperatura (LED Amarelo + Buzzer)
    if (temperatura != -999 && (temperatura < 10 || temperatura > 15)) {
        digitalWrite(ledPinAm, HIGH);  // Liga LED amarelo (alerta temperatura)
        condicaoCritica = true;        // Seta condição crítica
    }

    // 3. Controle de Umidade (LED Vermelho + Buzzer)
    if (umidade != -1 && (umidade < 50 || umidade > 70)) {
        digitalWrite(ledPinVer, HIGH); // Liga LED vermelho (alerta umidade)
        condicaoCritica = true;        // Seta condição crítica
    }

    // Ativa buzzer se qualquer condição crítica for atendida
    if (condicaoCritica) {
        tone(buzzer, 1000); // Buzina em 1kHz
    } else {
        noTone(buzzer);      // Desliga buzzer
    }

    // Exibição no LCD - Temperatura
    lcd.clear(); // Limpa display
    if(temperatura == -999) {
        lcd.print("Erro temp!"); // Erro de leitura
    } else if(temperatura < 10) {
        lcd.print("Temp. Baixa:"); // Temperatura baixa
    } else if(temperatura <= 15) {
        lcd.print("Temp. Ok:"); // Temperatura normal
    } else {
        lcd.print("Temp. Alta:"); // Temperatura alta
    }
    
    lcd.setCursor(0, 1); // Vai para segunda linha
    if(temperatura != -999) {
        lcd.print(temperatura); // Mostra valor da temperatura
        lcd.print("*C");
    }
    delay(2000); // Aguarda 2 segundos

    // Exibição no LCD - Umidade
    lcd.clear(); // Limpa display
    if(umidade == -1) {
        lcd.print("Erro umidade!"); // Erro de leitura
    } else if(umidade < 50) {
        lcd.print("Umidade Baixa:"); // Umidade baixa
    } else if(umidade <= 70) {
        lcd.print("Umidade Ok:"); // Umidade normal
    } else {
        lcd.print("Umidade Alta:"); // Umidade alta
    }
    
    lcd.setCursor(0, 1); // Vai para segunda linha
    if(umidade != -1) {
        lcd.print(umidade); // Mostra valor da umidade
        lcd.print("%");
    }
    delay(2000); // Aguarda 2 segundos

    // Exibição no LCD - Luminosidade
    lcd.clear(); // Limpa display
    if(valorluz <= 600) {
        lcd.print("Lumino. Boa:"); // Luminosidade boa
    } else if(valorluz <= 801) {
        lcd.print("Lumino. Ok:"); // Luminosidade ok
    } else {
        lcd.print("Muito Claro:"); // Muito claro
    }
    
    lcd.setCursor(0, 1); // Vai para segunda linha
    lcd.print(valorluz_prc); // Mostra valor da luminosidade em porcentagem
    lcd.print("%");
    delay(2000); // Aguarda 2 segundos
}
