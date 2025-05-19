#include "esphome/core/log.h"
#include "ventaxiask_uart.h"

namespace esphome {
namespace ventaxiask_uart {

static const char *TAG = "ventaxiask_uart.component";

void VentAxiaSKUART::setup() {

}

void VentAxiaSKUART::loop() {

}

void VentAxiaSKUART::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty UART component");
}

}  // namespace ventaxiask_uart
}  // namespace esphome