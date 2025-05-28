#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif

namespace esphome {
namespace vent_axia_sentinel_kinetic {

// Commands
static const uint8_t CMD_FRAME_HEADER = 0x04;
static const uint8_t CMD_ALIVE_HEADER[4] = {0x06, 0xFF, 0xFF, 0xFF};
static const uint8_t CMD_KEY_HEADER[4] = {0x05, 0xAF, 0xEF, 0xFB};
static const uint8_t CMD_ALIVE_DATA = 0x10;
static uint8_t CMD_KEY_DATA = 0x00;

class VentAxiaSentinelKineticComponent : public uart::UARTDevice, public Component {
#ifdef USE_SWITCH
  SUB_SWITCH(up)
  SUB_SWITCH(down)
  SUB_SWITCH(set)
  SUB_SWITCH(main)
#endif

  public:
    void setup() override;
    void loop() override;
    void dump_config() override;
    void set_up(bool enable);
    void set_down(bool enable);
    void set_set(bool enable);
    void set_main(bool enable);
  
    uint8_t buffer[41];
    bool packet_ready = false;

  protected:
    void send_command_(const uint8_t *command_value, int command_value_len, uint8_t command_str);
    void send_alive_str_();

    int32_t last_periodic_millis_ = millis();
    bool validate_crc();
    void process_packet();
    uint8_t current_index = 0;
};


}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome