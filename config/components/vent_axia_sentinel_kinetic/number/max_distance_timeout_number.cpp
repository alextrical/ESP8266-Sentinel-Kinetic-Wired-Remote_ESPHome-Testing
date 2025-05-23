#include "max_distance_timeout_number.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void MaxDistanceTimeoutNumber::control(float value) {
  this->publish_state(value);
  // this->parent_->set_max_distances_timeout();
}

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
