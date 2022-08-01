/*
 * app.h
 *
 *  Created on: July 21, 2022
 *      Author: lesly
 */

#ifndef APP_H_
#define APP_H_

void app_adc_it(uint32_t tmp);
void app_led_fade_percent(uint32_t percent);
void app_init(void);
void app_loop(void);

#endif /* APP_H_ */
