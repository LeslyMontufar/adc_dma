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

bool app_started = false;

void (*app_set_adc_finished)(void) = NULL;

void app_process_samples(){
//	delay =
}

void app_init(void){
	app_started = true;
	hw_register_app_set_adc_finished(app_process_samples);
}

void app_loop(void){

}
