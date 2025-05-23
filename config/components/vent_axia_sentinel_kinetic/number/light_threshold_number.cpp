#include "light_threshold_number.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void LightThresholdNumber::control(float value) {
  this->publish_state(value);
  // this->parent_->set_light_out_control();
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
