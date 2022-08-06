/*
 * Lesly Montúfar
 * app.c
 *
 *
*/

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"

#define ADC_CHANNELS	2
#define ADC_SAMPLES 	(5*ADC_CHANNELS)

bool app_started = false;
uint16_t adc_data[ADC_SAMPLES] = {0};
volatile uint16_t delay = 1000;

static void app_process_samples(void){
	uint16_t adc_avg_ch1, adc_avg_ch2;
	app_average_adc_value(adc_data, &adc_avg_ch1, &adc_avg_ch2);
	delay = 200 + 600*((adc_avg_ch1 + adc_avg_ch2)/2)/ 4095.0;
	hw_set_delay(delay);
}


void app_get_adc_values(void){
	hw_adc_start(adc_data, ADC_SAMPLES);
	app_process_samples();
}

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

void app_init(void){
	app_started = true;
	hw_adc_calibration();
	hw_adc_timer_start();

	hw_set_delay(delay);
	hw_blink_timer_start();
}

void app_loop(void){

}
