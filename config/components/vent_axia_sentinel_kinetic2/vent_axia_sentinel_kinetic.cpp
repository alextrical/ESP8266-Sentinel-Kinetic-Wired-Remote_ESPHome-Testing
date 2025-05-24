#include "esphome/core/log.h"
#include "vent_axia_sentinel_kinetic.h"

#define highbyte(val) (uint8_t)((val) >> 8)
#define lowbyte(val) (uint8_t)((val) & 0xff)

namespace esphome {
namespace vent_axia_sentinel_kinetic {

static const char *TAG = "vent_axia_sentinel_kinetic.component";

void VentAxiaSentinelKineticComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up VentAxiaSentinelKinetic...");
  this->send_alive_str_();
//   ESP_LOGCONFIG(TAG, "Mac Address : %s", const_cast<char *>(this->mac_.c_str()));
//   ESP_LOGCONFIG(TAG, "Firmware Version : %s", const_cast<char *>(this->version_.c_str()));
  ESP_LOGCONFIG(TAG, "VentAxiaSentinelKinetic setup complete.");
}

void VentAxiaSentinelKineticComponent::loop() {

}

void VentAxiaSentinelKineticComponent::dump_config(){
  ESP_LOGCONFIG(TAG, "VentAxiaSentinelKinetic:");
#ifdef USE_BUTTON
  // LOG_BUTTON("  ", "UpButton", this->up_button_);
#endif
}

void VentAxiaSentinelKineticComponent::send_alive_str_() { this->send_command_(CMD_ALIVE_HEADER, 4, CMD_ALIVE_DATA); }

void VentAxiaSentinelKineticComponent::send_command_(const uint16_t *command_value, int command_value_len, uint8_t command) {
  ESP_LOGV(TAG, "Sending COMMAND %02X", command);

  // frame start bytes
  this->write_byte(CMD_FRAME_HEADER);
  uint16_t crc = 0xFFFF - CMD_FRAME_HEADER;

  // command value bytes
  if (command_value != nullptr) {
    for (int i = 0; i < command_value_len; i++) {
      this->write_byte(command_value[i]);
      crc -= command_value[i];
    }
  }

  // command
  this->write_byte(command);
  crc -= command;

  // frame end bytes
  //Write CRC
  this->write_byte(lowbyte(crc));
  this->write_byte(highbyte(crc));
  
  // FIXME to remove
  // delay(50);  // NOLINT
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome