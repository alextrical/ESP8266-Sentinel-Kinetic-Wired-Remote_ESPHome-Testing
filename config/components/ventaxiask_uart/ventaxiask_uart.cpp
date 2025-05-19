#include "esphome/core/log.h"
#include "ventaxiask_uart.h"

namespace esphome {
namespace ventaxiask_uart {

static const char *TAG = "ventaxiask_uart.component";

// class VentAxiaSKUART : public Component, public uart::UARTDevice {
//  public:
//   VentAxiaSKUART(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

//   TextSensor *line1_sensor{nullptr};
//   TextSensor *line2_sensor{nullptr};

//   void set_line1_sensor(TextSensor *sensor) { line1_sensor = sensor; }
//   void set_line2_sensor(TextSensor *sensor) { line2_sensor = sensor; }

//   void loop() override {
//     while (available() >= 40) {
//       uint8_t buf[40];
//       read_array(buf, 40);

//       std::string line1, line2;
//       for (int i = 7; i < 7 + 16; i++)
//         line1 += static_cast<char>(buf[i]);
//       for (int i = 24; i < 24 + 16; i++)
//         line2 += static_cast<char>(buf[i]);

//       if (line1_sensor)
//         line1_sensor->publish_state(line1);
//       if (line2_sensor)
//         line2_sensor->publish_state(line2);
//     }
//   }
// };

void VentAxiaSKUART::setup() {

}

void VentAxiaSKUART::loop() {

}

void VentAxiaSKUART::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty UART component");
}

}  // namespace ventaxiask_uart
}  // namespace esphome