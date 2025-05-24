#include "baud_rate_select.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void BaudRateSelect::control(const std::string &value) {
  this->publish_state(value);
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
