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

void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_ch1, uint16_t *adc_avg_ch2){
	uint16_t cnt = 0;
	uint32_t sem_temp[ADC_CHANNELS] = {0,0};

	while(cnt < ADC_SAMPLES){
		for(uint8_t i=0; i<ADC_CHANNELS; i++)
			sum_temp[i] += adc_raw_val[cnt+1];
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
	hw_adc_start(adc_data, ADC_SAMPLES);
}

void app_loop(void){

}
