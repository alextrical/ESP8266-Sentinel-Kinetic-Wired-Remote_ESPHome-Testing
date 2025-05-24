#include "engineering_mode_switch.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void EngineeringModeSwitch::write_state(bool state) {
  this->publish_state(state);
  this->parent_->set_engineering_mode(state);
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
