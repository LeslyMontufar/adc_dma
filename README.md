# Leitura programada de porta ADC com DMA ![Language grade: C](https://img.shields.io/badge/language-C-blue)

Leitura de potenciômetro com dois canais de ADC usando DMA para controlar frequência em que o led pisca.

## Índice 

* [Descrição](#descrição)
* [Desenvolvimento](#desenvolvimento)

## Descrição

Configure os pinos PA3 e PA4 como entradas analógicas e o PC13 como saída, para acionamento do LED.

Procedimento a ser realizado no firmware:

1. Criar um timer de um segundo para amostragem dos sinais analógicos

2. A cada segundo, os valores analógicos das portas PA3 e PA4 devem ser lidos, utilizando
a estratégia de DMA. Programe o DMA para fazer 5 medidas de PA3 e 5 medidas de PA4,
usando a média de cada grupo de 5 para gerar o valor de entrada final de PA3 e PA4.

3. Uma média entre os valores medidos (os valores finais) deve ser calculada e o valor
resultante usado para determinar o tempo de piscada do LED, segundo a seguinte
relação:
  * ADC com valor 4095 gera o tempo máximo de 600ms de tempo de on/off.
  * ADC com valor 0 gera o tempo mínimo de 200ms de tempo de on/off.
  * Valores intermediários devem gerar um tempo proporcional no processo de
piscada do LED (crie uma equação para isso)

Não se esqueça de fazer a calibração do ADC antes, partida. Use jumpers para simular os valores,
aterrando ou colocando em 3V3. Como é feita uma média, será uma boa forma de conseguir ver
pelo menos 3 valores diferentes de piscada, na situação de um jumper em GND e o outro em
3V3. Caso possua, use um potenciômetro ou dois com valores preferencialmente abaixo de 10k.
