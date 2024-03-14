# Control de Temperatura Residencial con Sensores DHT11

Este proyecto consiste en un sistema de control de temperatura para una casa utilizando sensores DHT11 para medir la temperatura y la humedad tanto en un tanque como en el interior de la casa. El sistema utiliza relevadores para regular la temperatura de la casa según una temperatura deseada, activando o desactivando una placa Peltier y una bomba de agua.

## Componentes necesarios:

1. Arduino Uno o compatible
2. Sensores DHT11 (2 unidades)
3. Relevadores (3 unidades)
4. Placa Peltier
5. Bomba de agua
6. Cableado y componentes varios según el diseño específico  

## Configuración del código:

- Se debe instalar la librería DHT.h para la gestión de los sensores DHT11.
- Se deben definir los pines de conexión de los sensores, los relevadores y otros componentes según la disposición física del proyecto.
- Es posible ajustar la temperatura deseada modificando la variable desired_temperature.

## Funcionamiento del código:

1. Se realizan lecturas de los sensores DHT11 para obtener la temperatura y la humedad tanto del tanque como del interior de la casa.
2. Se calculan los índices de calor para cada sensor.
3. Los datos obtenidos se envían a través de la comunicación serial para su visualización.
4. Se comparan las temperaturas medidas con la temperatura deseada y se controlan los relevadores para activar o desactivar la placa Peltier y la bomba de agua según sea necesario para alcanzar la temperatura deseada en la casa.
   
## Notas adicionales:

- Los relevadores utilizan lógica negativa, es decir, un estado HIGH los apaga y un estado LOW los enciende.
- Se incluyen comentarios en el código para facilitar su comprensión y modificación.
- El tiempo de espera de 2 segundos entre lecturas de sensores puede ajustarse según las necesidades del proyecto.

