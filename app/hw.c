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
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;

#define PWM_CHN1 TIM_CHANNEL_1

volatile uint32_t tmp = 0;

void hw_timer_adc_start(void){
	hw_timer_start(&htim2);
}

void hw_timer_start(TIM_HandleTypeDef *htim) {
	HAL_TIM_Base_Start_IT(htim);
}

void hw_pwm_start(void){
	HAL_TIM_PWM_Start(&htim1, PWM_CHN1);
}

void hw_set_duty(uint16_t duty) {
	uint16_t arr = __HAL_TIM_GET_AUTORELOAD(&htim1)+1;
	uint16_t CCR = duty*arr/100;
	__HAL_TIM_SET_COMPARE(&htim1,PWM_CHN1, CCR-1*(CCR>0));
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if(htim == &htim1) {
		__HAL_TIM_SET_COUNTER(&htim1, 0);
	}
	else if(htim == &htim2)	{
		HAL_ADC_Start_IT(&hadc1);
		__HAL_TIM_SET_COUNTER(&htim2, 0);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	tmp = HAL_ADC_GetValue(hadc);
	app_adc_it(tmp);
}

void hw_cpu_sleep(){
	__WFI();
}

