#include "DHT.h" //Se agrega la libreria de los sensores DHT11

#define DHTPIN_TANK 12 //Se declara el pin de señal del sensor del tinaco
#define DHTPIN_HOUSE 11 //Y del sensor de la casa

#define DHTTYPE_TANK DHT11  //Se declaran los tipos de sensores
#define DHTTYPE_HOUSE DHT11

DHT dht_tank(DHTPIN_TANK, DHTTYPE_TANK); //Se construyen los sensores virtualmente
DHT dht_house(DHTPIN_HOUSE, DHTTYPE_HOUSE);

float desired_temperature = 45; //Se declara la temperatura deseada

float humidity_tank, temperature_tank, temperatureF_tank, HeatIndexC_tank, HeatIndexF_tank; //Se declaran las variables para el sensor del tinaco
float humidity_house, temperature_house, temperatureF_house, HeatIndexC_house, HeatIndexF_house; //Se declaran las variables para el sensor de la casa

int relay_cold = 8; //Se declaran los pines usados para cada relevador
int relay_hot = 9;
int water_bomb = 10;

void ReadSensors() {

  delay(2000); //Tiempo de espera para obtener mejores datos

  humidity_tank = dht_tank.readHumidity(); //Lectura de humedad y temperatura del sensor del tinaco
  temperature_tank = dht_tank.readTemperature();
  temperatureF_tank = dht_tank.readTemperature(true);

  humidity_house = dht_house.readHumidity(); //Lectura de humedad y temperatura del sensor de la casa
  temperature_house = dht_house.readTemperature();
  temperatureF_house = dht_house.readTemperature(true);

  if (isnan(humidity_tank) || isnan(temperature_tank) || isnan(temperatureF_tank)) { //Revision de errores
    Serial.println(F("Error al leer temperatura del tinaco"));
    return;
  } else if (isnan(humidity_house) || isnan(temperature_house) || isnan(temperatureF_house)) {
    Serial.println(F("Error al leer temperatura de la casa"));
    return;
  }

  HeatIndexF_tank = dht_tank.computeHeatIndex(temperatureF_tank, humidity_tank); //Obtencion de indices de calor del tinaco
  HeatIndexC_tank = dht_tank.computeHeatIndex(temperature_tank, humidity_tank, false);

  HeatIndexF_house = dht_house.computeHeatIndex(temperatureF_house, humidity_house); //Obtencion de indices de calor de la casa
  HeatIndexC_house = dht_house.computeHeatIndex(temperature_house, humidity_house, false);
}

void WriteData() {

  Serial.print("Datos del Tinaco: "); //Escritura de los datos obtenidos del sensor del tinaco
  Serial.println(" ");
  Serial.print(F("Temperatura: "));
  Serial.print(temperature_tank);
  Serial.print(F("°C "));
  Serial.print(temperatureF_tank);
  Serial.print(F("°F  Indice de calor: "));
  Serial.print(HeatIndexC_tank);
  Serial.print(F("°C "));
  Serial.print(HeatIndexF_tank);
  Serial.print(F("°F "));
  Serial.print(F(" Humedad: "));
  Serial.print(humidity_tank);
  Serial.println(F("%"));
  Serial.println(" ");

  delay(2000);

  Serial.print("Datos de la Casa: "); //Escritura de los datos obtenidos del sensor de la casa
  Serial.println(" ");
  Serial.print(F("Temperatura: "));
  Serial.print(temperature_house);
  Serial.print(F("°C "));
  Serial.print(temperatureF_house);
  Serial.print(F("°F  Indice de calor: "));
  Serial.print(HeatIndexC_house);
  Serial.print(F("°C "));
  Serial.print(HeatIndexF_house);
  Serial.print(F("°F "));
  Serial.print(F(" Humedad: "));
  Serial.print(humidity_house);
  Serial.println(F("%"));
  Serial.println(" ");
}

void setup() {
  Serial.begin(9600); //Comunicacion serial a 9600 Baudios

  pinMode(relay_hot, OUTPUT); //Se declaran como salida los pines de los relevadores
  pinMode(relay_cold, OUTPUT);
  pinMode(water_bomb, OUTPUT);

  digitalWrite(relay_hot, HIGH); //Se colocan en apagado todos los relevadores
  digitalWrite(relay_cold, HIGH);
  digitalWrite(water_bomb, HIGH);

  dht_tank.begin(); //Se inicializan los sensores
  dht_house.begin();
}

void loop() {

  ReadSensors(); //Funcion de lectura de sensores
  WriteData(); //Funcion de escritura de datos

  //Los relevadores funcionan con logica negativa, una señal HIGH los apaga y una señal LOW los enciende

  if (temperature_house < desired_temperature) { //Si la temperatura es mas baja de la deseada
    digitalWrite(relay_hot, LOW);
    digitalWrite(relay_cold, HIGH); //Encender la placa peltier de calefaccion, encender bomba de aguay apagar la placa de frio
    digitalWrite(water_bomb, LOW);

  } else if (temperature_house > desired_temperature) { //Si la temperatura esta arriba de la deseada
    digitalWrite(relay_hot, HIGH);
    digitalWrite(relay_cold, LOW); //Encender la placa peltier de frio, encender bomba de agua y apagar la placa de calefaccion
    digitalWrite(water_bomb, LOW); 

  } else {                          //Si la temperatura es igual a la deseada
    digitalWrite(relay_hot, HIGH);
    digitalWrite(relay_cold, HIGH); //Apagar todo
    digitalWrite(water_bomb, HIGH);
  }
}
