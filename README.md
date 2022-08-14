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

## Desenvolvimento

1. Utilizei dois timers, um para o blink do led e outro para a coleta dos sinais analógicos dos potênciometros. O adc usa dma, e possui desabilitada a interrupção Half Transfer, já que não se utiliza sinais perdidos ou pela metade.
```
void app_init(void){
	app_started = true;
	hw_adc_calibration();
	hw_adc_timer_start();

	hw_set_delay(delay);
	hw_blink_timer_start();
}

void app_loop(void){

}
```
```
void hw_adc_calibration(void){
	HAL_ADCEx_Calibration_Start(&hadc1);
	__HAL_DMA_DISABLE_IT(&hdma_adc1, DMA_IT_HT);
}
```
```
void hw_timer_start(TIM_HandleTypeDef *htim) {
	HAL_TIM_Base_Start_IT(htim);
}

void hw_blink_timer_start(void){
	hw_timer_start(&htim1);
}

void hw_adc_timer_start(void){
	hw_timer_start(&htim2);
}
```
2. O delay foi inicializado em 800ms, e modifica-se seu valor pela função `hw_set_delay`.
```
volatile uint16_t delay = 800;
```
```
void hw_set_delay(uint16_t delay) {
	uint16_t arr = (CLKINT*delay/1000)-1;

	if(__HAL_TIM_GET_COUNTER(&htim1) >= arr)
		__HAL_TIM_SET_COUNTER(&htim1, 0);

	__HAL_TIM_SET_AUTORELOAD(&htim1, arr);

}
```
3. As coletas e mudanças de estado do led são realizadas após o tempo de cada temporizador.

```
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim1) {
		hw_toggle_led();
		__HAL_TIM_SET_COUNTER(&htim1, 0);
	}
	if(htim == &htim2){
//		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		app_get_adc_values();
		__HAL_TIM_SET_COUNTER(&htim2, 0);
	}
}
```
4. A função `app_get_adc_values` é responsável pela coleta via DMA.
```
void app_get_adc_values(void){
	hw_adc_start(adc_data, ADC_SAMPLES);
	app_process_samples();
}
```
```
void hw_adc_start(uint16_t *values, uint32_t size){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)values, size);
}
```
```
static void app_process_samples(void){
	uint16_t adc_avg_ch1, adc_avg_ch2;
	app_average_adc_value(adc_data, &adc_avg_ch1, &adc_avg_ch2);
	delay = 200 + 600*((adc_avg_ch1 + adc_avg_ch2)/2)/ 4095.0;
	hw_set_delay(delay);
}
```
```
void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_ch1, uint16_t *adc_avg_ch2){
	uint16_t cnt = 0;
	uint32_t sum_temp[ADC_CHANNELS] = {0,0};

	while(cnt < ADC_SAMPLES){
		for(uint8_t i=0; i<ADC_CHANNELS; i++)
			sum_temp[i] += adc_raw_val[cnt+i];
		cnt += ADC_CHANNELS;
	}

	for(uint8_t i=0; i<ADC_CHANNELS; i++)
		sum_temp[i] /= (ADC_SAMPLES/ADC_CHANNELS);

	*adc_avg_ch1 = (uint16_t) sum_temp[0];
	*adc_avg_ch2 = (uint16_t) sum_temp[1];
}
```
5. Quando o adc finaliza a coleta de amostras o adc é parado, na função do HAL chamada `HAL_ADC_ConvCpltCallback`.
```
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	hw_adc_stop();
}
```
```
void hw_adc_stop(void){
	HAL_ADC_Stop_DMA(&hadc1);
}
```
6. Circuito funcionando.

![adc-dois-pot](https://github.com/LeslyMontufar/adc_dma/blob/main/img/funcionando.jpg)
