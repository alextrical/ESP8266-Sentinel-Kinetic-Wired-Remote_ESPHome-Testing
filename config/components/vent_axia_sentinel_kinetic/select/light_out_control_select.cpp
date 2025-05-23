#include "light_out_control_select.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void LightOutControlSelect::control(const std::string &value) {
  this->publish_state(value);
  this->parent_->set_light_out_control();
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
