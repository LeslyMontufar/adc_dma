/*
 *  hw.c
 *  Abstrai as funções do HAL e CMSIS
 *
 *  Created on: August 06, 2022
 *      Author: lesly
 */

#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "app.h"
#include "hw.h"

#define CLKINT 			(72000000/htim1.Instance->PSC) //2000

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

/* ---------- ADC ---------- */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	hw_adc_stop();
}

void hw_adc_start(uint16_t *values, uint32_t size){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)values, size);
}

void hw_adc_stop(void){
	HAL_ADC_Stop_DMA(&hadc1);
}

void hw_adc_calibration(void){
	HAL_ADCEx_Calibration_Start(&hadc1);
	__HAL_DMA_DISABLE_IT(&hdma_adc1, DMA_IT_HT);
}

/* ---------- Timer Blink ---------- */
void hw_timer_start(TIM_HandleTypeDef *htim) {
	HAL_TIM_Base_Start_IT(htim);
}

void hw_blink_timer_start(void){
	hw_timer_start(&htim1);
}

void hw_adc_timer_start(void){
	hw_timer_start(&htim2);
}

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

void hw_toggle_led(void){
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

void hw_set_delay(uint16_t delay) {
	uint16_t arr = (CLKINT*delay/1000)-1;

	if(__HAL_TIM_GET_COUNTER(&htim1) >= arr)
		__HAL_TIM_SET_COUNTER(&htim1, 0);

	__HAL_TIM_SET_AUTORELOAD(&htim1, arr);

}

