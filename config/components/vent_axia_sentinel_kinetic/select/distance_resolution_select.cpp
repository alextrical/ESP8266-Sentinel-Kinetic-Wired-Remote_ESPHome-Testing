#include "distance_resolution_select.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void DistanceResolutionSelect::control(const std::string &value) {
  this->publish_state(value);
  this->parent_->set_distance_resolution(state);
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
