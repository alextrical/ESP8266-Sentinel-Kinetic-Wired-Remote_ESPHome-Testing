#pragma once
#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif
#ifdef USE_BUTTON
#include "esphome/components/button/button.h"
#endif
#ifdef USE_SELECT
#include "esphome/components/select/select.h"
#endif
#ifdef USE_TEXT_SENSOR
#include "esphome/components/text_sensor/text_sensor.h"
#endif
#include "esphome/components/uart/uart.h"
#include "esphome/core/automation.h"
#include "esphome/core/helpers.h"

#include <map>

namespace esphome {
namespace vent_axia_sentinel_kinetic {

#define CHECK_BIT(var, pos) (((var) >> (pos)) & 1)

// Commands
static const uint16_t CMD_ENABLE_CONF = 0x00FF;
static const uint16_t CMD_DISABLE_CONF = 0x00FE;
static const uint16_t CMD_ENABLE_ENG = 0x0062;
static const uint16_t CMD_DISABLE_ENG = 0x0063;
static const uint16_t CMD_MAXDIST_DURATION = 0x0060;
static const uint16_t CMD_QUERY = 0x0061;
static const uint16_t CMD_GATE_SENS = 0x0064;
static const uint16_t CMD_VERSION = 0x1234;
static const uint16_t CMD_QUERY_DISTANCE_RESOLUTION = 0x00AB;
static const uint16_t CMD_SET_DISTANCE_RESOLUTION = 0x00AA;
static const uint16_t CMD_QUERY_LIGHT_CONTROL = 0x00AE;
static const uint16_t CMD_SET_LIGHT_CONTROL = 0x00AD;
static const uint16_t CMD_SET_BAUD_RATE = 0x00A1;
static const uint16_t CMD_BT_PASSWORD = 0x00A9;
static const uint16_t CMD_RESET = 0x00A2;
static const uint16_t CMD_RESTART = 0x00A3;
static const uint16_t CMD_BLUETOOTH = 0x00A4;

enum BaudRateStructure : uint8_t {
  BAUD_RATE_9600 = 1,
  BAUD_RATE_19200 = 2,
  BAUD_RATE_38400 = 3,
  BAUD_RATE_57600 = 4,
  BAUD_RATE_115200 = 5,
  BAUD_RATE_230400 = 6,
  BAUD_RATE_256000 = 7,
  BAUD_RATE_460800 = 8
};

static const std::map<std::string, uint8_t> BAUD_RATE_ENUM_TO_INT{
    {"9600", BAUD_RATE_9600},     {"19200", BAUD_RATE_19200},   {"38400", BAUD_RATE_38400},
    {"57600", BAUD_RATE_57600},   {"115200", BAUD_RATE_115200}, {"230400", BAUD_RATE_230400},
    {"256000", BAUD_RATE_256000}, {"460800", BAUD_RATE_460800}};

enum DistanceResolutionStructure : uint8_t { DISTANCE_RESOLUTION_0_2 = 0x01, DISTANCE_RESOLUTION_0_75 = 0x00 };

static const std::map<std::string, uint8_t> DISTANCE_RESOLUTION_ENUM_TO_INT{{"0.2m", DISTANCE_RESOLUTION_0_2},
                                                                            {"0.75m", DISTANCE_RESOLUTION_0_75}};
static const std::map<uint8_t, std::string> DISTANCE_RESOLUTION_INT_TO_ENUM{{DISTANCE_RESOLUTION_0_2, "0.2m"},
                                                                            {DISTANCE_RESOLUTION_0_75, "0.75m"}};
// Commands values
static const uint16_t CMD_MAX_MOVE_VALUE = 0x0000;
static const uint16_t CMD_MAX_STILL_VALUE = 0x0001;
static const uint16_t CMD_DURATION_VALUE = 0x0002;
// Command Header & Footer
// static const uint8_t CMD_FRAME_HEADER[4] = {0xFD, 0xFC, 0xFB, 0xFA};
// static const uint8_t CMD_FRAME_END[4] = {0x04, 0x03, 0x02, 0x01};
static const uint8_t CMD_FRAME_HEADER[5] = {0x04, 0x05, 0xAF, 0xEF, 0xFB};
static const uint8_t CMD_FRAME_END[2] = {0x00, 0x00};
// Data Header & Footer
static const uint8_t DATA_FRAME_HEADER[4] = {0xF4, 0xF3, 0xF2, 0xF1};
static const uint8_t DATA_FRAME_END[4] = {0xF8, 0xF7, 0xF6, 0xF5};
/*
Data Type: 6th byte
Target states: 9th byte
    Moving target distance: 10~11th bytes
    Moving target energy: 12th byte
    Still target distance: 13~14th bytes
    Still target energy: 15th byte
    Detect distance: 16~17th bytes
*/
enum PeriodicDataStructure : uint8_t {
  DATA_TYPES = 6,
  TARGET_STATES = 8,
  MOVING_TARGET_LOW = 9,
  MOVING_TARGET_HIGH = 10,
  STILL_TARGET_LOW = 12,
  STILL_TARGET_HIGH = 13,
  DETECT_DISTANCE_LOW = 15,
  DETECT_DISTANCE_HIGH = 16,
  MOVING_SENSOR_START = 19,
  STILL_SENSOR_START = 28,
  LIGHT_SENSOR = 37,
  OUT_PIN_SENSOR = 38,
};
enum PeriodicDataValue : uint8_t { HEAD = 0xAA, END = 0x55, CHECK = 0x00 };

enum AckDataStructure : uint8_t { COMMAND = 6, COMMAND_STATUS = 7 };

//  char cmd[2] = {enable ? 0xFF : 0xFE, 0x00};
class VentAxiaSentinelKineticComponent : public Component, public uart::UARTDevice {
#ifdef USE_SENSOR
  SUB_SENSOR(light)
#endif
#ifdef USE_BINARY_SENSOR
  SUB_BINARY_SENSOR(target)
#endif
#ifdef USE_TEXT_SENSOR
  SUB_TEXT_SENSOR(version)
#endif
#ifdef USE_SELECT
  SUB_SELECT(distance_resolution)
#endif
#ifdef USE_SWITCH
  SUB_SWITCH(bluetooth)
#endif
#ifdef USE_BUTTON
  SUB_BUTTON(reset)
  SUB_BUTTON(restart)
  SUB_BUTTON(query)
#endif
#ifdef USE_NUMBER
  SUB_NUMBER(timeout)
#endif

 public:
  VentAxiaSentinelKineticComponent();
  void setup() override;
  void dump_config() override;
  void loop() override;
#ifdef USE_NUMBER
  void set_max_distances_timeout();
  void set_gate_threshold(uint8_t gate);
#endif
#ifdef USE_SENSOR
  void set_gate_move_sensor(int gate, sensor::Sensor *s);
  void set_gate_still_sensor(int gate, sensor::Sensor *s);
#endif
  void set_throttle(uint16_t value) { this->throttle_ = value; };
  void set_bluetooth_password(const std::string &password);
  void read_all_info();
  void restart_and_read_all_info();
  void set_bluetooth(bool enable);
  void set_distance_resolution(const std::string &state);
  void factory_reset();

 protected:
  int two_byte_to_int_(char firstbyte, char secondbyte) { return (int16_t) (secondbyte << 8) + firstbyte; }
  void send_command_(uint16_t command_str, const uint8_t *command_value, int command_value_len);
  void set_config_mode_(bool enable);
  void handle_periodic_data_(uint8_t *buffer, int len);
  bool handle_ack_data_(uint8_t *buffer, int len);
  void readline_(int readch, uint8_t *buffer, int len);
  void query_parameters_();
  void get_version_();
  void get_distance_resolution_();
  void get_light_control_();
  void restart_();

  int32_t last_periodic_millis_ = millis();
  uint16_t throttle_;
  std::string version_;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
