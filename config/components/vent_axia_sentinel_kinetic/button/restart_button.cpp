#include "restart_button.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void RestartButton::press_action() { this->parent_->restart_and_read_all_info(); }

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
