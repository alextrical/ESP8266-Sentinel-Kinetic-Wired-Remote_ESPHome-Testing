#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

// Commands
static const uint8_t CMD_FRAME_HEADER = 0x04;
static const uint8_t CMD_ALIVE_HEADER[4] = {0x06, 0xFF, 0xFF, 0xFF};
static const uint8_t CMD_KEY_HEADER[4] = {0x05, 0xAF, 0xEF, 0xFB};
static const uint8_t CMD_ALIVE_DATA = 0x10;

class VentAxiaSentinelKineticComponent : public uart::UARTDevice, public Component {
  public:
    void setup() override;
    void loop() override;
    void dump_config() override;

  protected:
    void send_command_(const uint16_t *command_value, int command_value_len, uint8_t command_str);
    void send_alive_str_();
};


}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome