/*
 * hw.c
 * Abstrai as funções do HAL e CMSIS
 *
 *  Created on: July 21, 2022
 *      Author: lesly
 */

#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "app.h"
#include "hw.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;


void hw_timer_start(TIM_HandleTypeDef *htim) {
	HAL_TIM_Base_Start_IT(htim);
}

void hw_blink_timer_init(){
	hw_timer_start(&htim1);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim1) {
		__HAL_TIM_SET_COUNTER(&htim1, 0);
	}
//	else if(htim == &htim3)	{
////		HAL_ADC_Start_DMA(hadc, pData, Length);
//		__HAL_TIM_SET_COUNTER(&htim2, 0);
//	}
}

void hw_register_app_set_adc_finished(void (*callback)(void)){
	app_set_adc_finished = callback;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	app_set_adc_finished();
}

void hw_cpu_sleep(){
	__WFI();
}

