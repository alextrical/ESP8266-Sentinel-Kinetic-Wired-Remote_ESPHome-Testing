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

  int32_t current_millis = millis();
  if (current_millis - last_periodic_millis_ >= 26){
    last_periodic_millis_ = current_millis;
    if (CMD_KEY_DATA != 0)
      this->send_command_(CMD_KEY_HEADER, 4, CMD_KEY_DATA);
  }
}

void VentAxiaSentinelKineticComponent::dump_config(){
  ESP_LOGCONFIG(TAG, "VentAxiaSentinelKinetic:");
#ifdef USE_SWITCH
  LOG_SWITCH("  ", "UpSwitch", this->up_switch_);
  LOG_SWITCH("  ", "DownSwitch", this->down_switch_);
  LOG_SWITCH("  ", "SetSwitch", this->set_switch_);
  LOG_SWITCH("  ", "MainSwitch", this->main_switch_);
#endif
}

void VentAxiaSentinelKineticComponent::send_alive_str_() { this->send_command_(CMD_ALIVE_HEADER, 4, CMD_ALIVE_DATA); }

void VentAxiaSentinelKineticComponent::send_command_(const uint8_t *command_value, int command_value_len, uint8_t command) {
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

void VentAxiaSentinelKineticComponent::set_up(bool enable) {
  ESP_LOGV(TAG, "UP: %s", enable ? "true" : "false");
  if (enable) {
      CMD_KEY_DATA |= (1 << 1);   // Set bit 1
  } else {
      CMD_KEY_DATA &= ~(1 << 1);  // Clear bit 1
  }
}

void VentAxiaSentinelKineticComponent::set_down(bool enable) {
  ESP_LOGV(TAG, "DOWN: %s", enable ? "true" : "false");
  if (enable) {
      CMD_KEY_DATA |= (1);   // Set bit 0
  } else {
      CMD_KEY_DATA &= ~(1);  // Clear bit 0
  }
}

void VentAxiaSentinelKineticComponent::set_set(bool enable) {
  ESP_LOGV(TAG, "SET: %s", enable ? "true" : "false");
  if (enable) {
      CMD_KEY_DATA |= (1 << 2);   // Set bit 2
  } else {
      CMD_KEY_DATA &= ~(1 << 2);  // Clear bit 2
  }
}

void VentAxiaSentinelKineticComponent::set_main(bool enable) {
  ESP_LOGV(TAG, "MAIN: %s", enable ? "true" : "false");
  if (enable) {
      CMD_KEY_DATA |= (1 << 3);   // Set bit 3
  } else {
      CMD_KEY_DATA &= ~(1 << 3);  // Clear bit 3
  }
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome