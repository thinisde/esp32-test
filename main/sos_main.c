/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"

#define GPIO_OUTPUT_IO_26 GPIO_NUM_26
#define GPIO_OUTPUT_PIN_SEL (1ULL << GPIO_OUTPUT_IO_26)

#define ESP_INTR_FLAG_DEFAULT 0

#define LED_SHORT_DUR 100
#define LED_LONG_DUR 500

void app_main(void) {
  gpio_config_t io_conf = {};
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;

  gpio_config(&io_conf);

  bool flag = false;
  int counter = 0;

  while (1) {
    gpio_set_level(GPIO_OUTPUT_IO_26, 1);
    vTaskDelay(pdMS_TO_TICKS(flag ? LED_LONG_DUR : LED_SHORT_DUR));
    gpio_set_level(GPIO_OUTPUT_IO_26, 0);
    vTaskDelay(pdMS_TO_TICKS(LED_SHORT_DUR));
    counter++;
    if (counter == 3) {
      counter = 0;
      flag = !flag;
    }
  }
}
