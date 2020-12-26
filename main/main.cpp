#include <iostream>
#include <cmath>
#include <functional>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <sdkconfig.h>

#include <hal/adc_types.h>
#include <driver/adc.h>

#include "Thermistor.h"

extern "C" void app_main() {

  xTaskCreatePinnedToCore([](void* arg){ 
    auto thermistor  = static_cast<Thermistor*>(arg);
    while(true) {
      std::clog << thermistor->get_reading() << "°C\n";
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    delete thermistor;
    vTaskDelete(NULL);
    
  }, "thermistor adc6", 4096, Thermistor::Get_Thermistor(ADC1_CHANNEL_6), 1, nullptr, 0);
}
