#include "vent_axia_sentinel_kinetic.h"

#include <utility>
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif

#define highbyte(val) (uint8_t)((val) >> 8)
#define lowbyte(val) (uint8_t)((val) &0xff)

namespace esphome {
namespace vent_axia_sentinel_kinetic {

static const char *const TAG = "vent_axia_sentinel_kinetic";

VentAxiaSentinelKineticComponent::VentAxiaSentinelKineticComponent() {}

void VentAxiaSentinelKineticComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "VentAxiaSentinelKinetic:");
#ifdef USE_BINARY_SENSOR
  LOG_BINARY_SENSOR("  ", "TargetBinarySensor", this->target_binary_sensor_);
#endif
#ifdef USE_SWITCH
  LOG_SWITCH("  ", "UpSwitch", this->up_switch_);
  LOG_SWITCH("  ", "DownSwitch", this->down_switch_);
  LOG_SWITCH("  ", "SetSwitch", this->set_switch_);
  LOG_SWITCH("  ", "MainSwitch", this->main_switch_);
#endif
#ifdef USE_BUTTON
  LOG_BUTTON("  ", "UpButton", this->up_button_);
  LOG_BUTTON("  ", "DownButton", this->down_button_);
  LOG_BUTTON("  ", "SetButton", this->set_button_);
  LOG_BUTTON("  ", "MainButton", this->main_button_);
#endif
#ifdef USE_SENSOR
  LOG_SENSOR("  ", "LightSensor", this->light_sensor_);
#endif
#ifdef USE_TEXT_SENSOR
  LOG_TEXT_SENSOR("  ", "VersionTextSensor", this->version_text_sensor_);
#endif
#ifdef USE_SELECT
  LOG_SELECT("  ", "DistanceResolutionSelect", this->distance_resolution_select_);
#endif
#ifdef USE_NUMBER
  LOG_NUMBER("  ", "TimeoutNumber", this->timeout_number_);
#endif
  this->read_all_info();
  ESP_LOGCONFIG(TAG, "  Throttle_ : %ums", this->throttle_);
  ESP_LOGCONFIG(TAG, "  Firmware Version : %s", const_cast<char *>(this->version_.c_str()));
}

void VentAxiaSentinelKineticComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up VentAxiaSentinelKinetic...");
  this->read_all_info();
  ESP_LOGCONFIG(TAG, "Firmware Version : %s", const_cast<char *>(this->version_.c_str()));
  ESP_LOGCONFIG(TAG, "VentAxiaSentinelKinetic setup complete.");
}

void VentAxiaSentinelKineticComponent::read_all_info() {
// this->set_config_mode_(true);
  this->get_version_();
//   this->get_distance_resolution_();
//   this->get_light_control_();
//   this->query_parameters_();
//   this->set_config_mode_(false);
}

void VentAxiaSentinelKineticComponent::loop() {
  const int max_line_length = 80;
  static uint8_t buffer[max_line_length];

  while (available()) {
    this->readline_(read(), buffer, max_line_length);
  }
}

void VentAxiaSentinelKineticComponent::send_command_(uint16_t command, const uint8_t *command_value, int command_value_len) {
  ESP_LOGV(TAG, "Sending COMMAND %02X", command);
  // frame start bytes
  this->write_array(CMD_FRAME_HEADER, 5);
  // // length bytes
  // int len = 2;
  // if (command_value != nullptr)
  //   len += command_value_len;
  // this->write_byte(lowbyte(len));
  // this->write_byte(highbyte(len));

  // command value bytes
  if (command_value != nullptr) {
    for (int i = 0; i < command_value_len; i++) {
      this->write_byte(command_value[i]);
    }
  }

  // command
  this->write_byte(lowbyte(command));
  this->write_byte(highbyte(command));

  // frame end bytes
  this->write_array(CMD_FRAME_END, 2);
  // FIXME to remove
  delay(50);  // NOLINT
}

void VentAxiaSentinelKineticComponent::handle_periodic_data_(uint8_t *buffer, int len) {
  if (len < 12)
    return;  // 4 frame start bytes + 2 length bytes + 1 data end byte + 1 crc byte + 4 frame end bytes
  if (buffer[0] != 0xF4 || buffer[1] != 0xF3 || buffer[2] != 0xF2 || buffer[3] != 0xF1)  // check 4 frame start bytes
    return;
  if (buffer[7] != HEAD || buffer[len - 6] != END || buffer[len - 5] != CHECK)  // Check constant values
    return;  // data head=0xAA, data end=0x55, crc=0x00

  /*
    Reduce data update rate to prevent home assistant database size grow fast
  */
  int32_t current_millis = millis();
  if (current_millis - last_periodic_millis_ < this->throttle_)
    return;
  last_periodic_millis_ = current_millis;

#ifdef USE_BINARY_SENSOR
  /*
    Target states: 9th
    0x00 = No target
    0x01 = Moving targets
    0x02 = Still targets
    0x03 = Moving+Still targets
  */
  char target_state = buffer[TARGET_STATES];
  if (this->target_binary_sensor_ != nullptr) {
    this->target_binary_sensor_->publish_state(target_state != 0x00);
  }
#endif
  /*
    Moving target distance: 10~11th bytes
    Moving target energy: 12th byte
    Still target distance: 13~14th bytes
    Still target energy: 15th byte
    Detect distance: 16~17th bytes
  */
#ifdef USE_SENSOR
  if (this->light_sensor_ != nullptr && !std::isnan(this->light_sensor_->get_state())) {
    this->light_sensor_->publish_state(NAN);
  }
#endif
}

const char VERSION_FMT[] = "%u.%02X.%02X%02X%02X%02X";

std::string format_version(uint8_t *buffer) {
  std::string::size_type version_size = 256;
  std::string version;
  do {
    version.resize(version_size + 1);
    version_size = std::snprintf(&version[0], version.size(), VERSION_FMT, buffer[13], buffer[12], buffer[17],
                                 buffer[16], buffer[15], buffer[14]);
  } while (version_size + 1 > version.size());
  version.resize(version_size);
  return version;
}

#ifdef USE_NUMBER
std::function<void(void)> set_number_value(number::Number *n, float value) {
  float normalized_value = value * 1.0;
  if (n != nullptr && (!n->has_state() || n->state != normalized_value)) {
    n->state = normalized_value;
    return [n, normalized_value]() { n->publish_state(normalized_value); };
  }
  return []() {};
}
#endif

bool VentAxiaSentinelKineticComponent::handle_ack_data_(uint8_t *buffer, int len) {
  ESP_LOGV(TAG, "Handling ACK DATA for COMMAND %02X", buffer[COMMAND]);
  if (len < 10) {
    ESP_LOGE(TAG, "Error with last command : incorrect length");
    return true;
  }
  if (buffer[0] != 0xFD || buffer[1] != 0xFC || buffer[2] != 0xFB || buffer[3] != 0xFA) {  // check 4 frame start bytes
    ESP_LOGE(TAG, "Error with last command : incorrect Header");
    return true;
  }
  if (buffer[COMMAND_STATUS] != 0x01) {
    ESP_LOGE(TAG, "Error with last command : status != 0x01");
    return true;
  }
  if (this->two_byte_to_int_(buffer[8], buffer[9]) != 0x00) {
    ESP_LOGE(TAG, "Error with last command , last buffer was: %u , %u", buffer[8], buffer[9]);
    return true;
  }

  switch (buffer[COMMAND]) {
    case lowbyte(CMD_ENABLE_CONF):
      ESP_LOGV(TAG, "Handled Enable conf command");
      break;
    case lowbyte(CMD_DISABLE_CONF):
      ESP_LOGV(TAG, "Handled Disabled conf command");
      break;
    case lowbyte(CMD_VERSION):
      this->version_ = format_version(buffer);
      ESP_LOGV(TAG, "FW Version is: %s", const_cast<char *>(this->version_.c_str()));
#ifdef USE_TEXT_SENSOR
      if (this->version_text_sensor_ != nullptr) {
        this->version_text_sensor_->publish_state(this->version_);
      }
#endif
      break;
    case lowbyte(CMD_QUERY_DISTANCE_RESOLUTION): {
      std::string distance_resolution =
          DISTANCE_RESOLUTION_INT_TO_ENUM.at(this->two_byte_to_int_(buffer[10], buffer[11]));
      ESP_LOGV(TAG, "Distance resolution is: %s", const_cast<char *>(distance_resolution.c_str()));
#ifdef USE_SELECT
      if (this->distance_resolution_select_ != nullptr &&
          this->distance_resolution_select_->state != distance_resolution) {
        this->distance_resolution_select_->publish_state(distance_resolution);
      }
#endif
    } break;
    case lowbyte(CMD_GATE_SENS):
      ESP_LOGV(TAG, "Handled sensitivity command");
      break;
    case lowbyte(CMD_SET_DISTANCE_RESOLUTION):
      ESP_LOGV(TAG, "Handled set distance resolution command");
      break;
    case lowbyte(CMD_SET_LIGHT_CONTROL):
      ESP_LOGV(TAG, "Handled set light control command");
      break;
    case lowbyte(CMD_QUERY):  // Query parameters response
    {
      if (buffer[10] != 0xAA)
        return true;  // value head=0xAA
#ifdef USE_NUMBER
      std::vector<std::function<void(void)>> updates;
      /*
        None Duration: 33~34th bytes
      */
      updates.push_back(set_number_value(this->timeout_number_, this->two_byte_to_int_(buffer[32], buffer[33])));
      for (auto &update : updates) {
        update();
      }
#endif
    } break;
    default:
      break;
  }

  return true;
}

void VentAxiaSentinelKineticComponent::readline_(int readch, uint8_t *buffer, int len) {
  static int pos = 0;

  if (readch >= 0) {
    if (pos < len - 1) {
      buffer[pos++] = readch;
      buffer[pos] = 0;
    } else {
      pos = 0;
    }
    if (pos >= 4) {
      if (buffer[pos - 4] == 0xF8 && buffer[pos - 3] == 0xF7 && buffer[pos - 2] == 0xF6 && buffer[pos - 1] == 0xF5) {
        ESP_LOGV(TAG, "Will handle Periodic Data");
        this->handle_periodic_data_(buffer, pos);
        pos = 0;  // Reset position index ready for next time
      } else if (buffer[pos - 4] == 0x04 && buffer[pos - 3] == 0x03 && buffer[pos - 2] == 0x02 &&
                 buffer[pos - 1] == 0x01) {
        ESP_LOGV(TAG, "Will handle ACK Data");
        if (this->handle_ack_data_(buffer, pos)) {
          pos = 0;  // Reset position index ready for next time
        } else {
          ESP_LOGV(TAG, "ACK Data incomplete");
        }
      }
    }
  }
}

void VentAxiaSentinelKineticComponent::set_config_mode_(bool enable) {
  uint8_t cmd = enable ? CMD_ENABLE_CONF : CMD_DISABLE_CONF;
  uint8_t cmd_value[2] = {0x01, 0x00};
  this->send_command_(cmd, enable ? cmd_value : nullptr, 2);
}

void VentAxiaSentinelKineticComponent::set_up(bool enable) {
  // this->set_config_mode_(true);
  // uint8_t enable_cmd_value[2] = {0x01, 0x00};
  // uint8_t disable_cmd_value[2] = {0x00, 0x00};
  // this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

void VentAxiaSentinelKineticComponent::set_down(bool enable) {
  // this->set_config_mode_(true);
  // uint8_t enable_cmd_value[2] = {0x01, 0x00};
  // uint8_t disable_cmd_value[2] = {0x00, 0x00};
  // this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

void VentAxiaSentinelKineticComponent::set_set(bool enable) {
  // this->set_config_mode_(true);
  // uint8_t enable_cmd_value[2] = {0x01, 0x00};
  // uint8_t disable_cmd_value[2] = {0x00, 0x00};
  // this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

void VentAxiaSentinelKineticComponent::set_main(bool enable) {
  // this->set_config_mode_(true);
  // uint8_t enable_cmd_value[2] = {0x01, 0x00};
  // uint8_t disable_cmd_value[2] = {0x00, 0x00};
  // this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

void VentAxiaSentinelKineticComponent::set_distance_resolution(const std::string &state) {
  this->set_config_mode_(true);
  uint8_t cmd_value[2] = {DISTANCE_RESOLUTION_ENUM_TO_INT.at(state), 0x00};
  this->send_command_(CMD_SET_DISTANCE_RESOLUTION, cmd_value, 2);
  // this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

void VentAxiaSentinelKineticComponent::query_parameters_() { this->send_command_(CMD_QUERY, nullptr, 0); }
void VentAxiaSentinelKineticComponent::get_version_() { this->send_command_(CMD_VERSION, nullptr, 0); }
void VentAxiaSentinelKineticComponent::get_distance_resolution_() { this->send_command_(CMD_QUERY_DISTANCE_RESOLUTION, nullptr, 0); }

void VentAxiaSentinelKineticComponent::get_light_control_() { this->send_command_(CMD_QUERY_LIGHT_CONTROL, nullptr, 0); }

#ifdef USE_NUMBER
void VentAxiaSentinelKineticComponent::set_max_distances_timeout() {
  int timeout = static_cast<int>(this->timeout_number_->state);
  uint8_t value[14] = {0x00,
                       0x00,
                       0x00,
                       0x00,
                       0x01,
                       0x00,
                       0x00,
                       0x00,
                       0x02,
                       0x00,
                       lowbyte(timeout),
                       highbyte(timeout),
                       0x00,
                       0x00};
  this->set_config_mode_(true);
  this->send_command_(CMD_MAXDIST_DURATION, value, 18);
  delay(50);  // NOLINT
  this->query_parameters_();
  // this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
  this->set_config_mode_(false);
}
#endif

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
