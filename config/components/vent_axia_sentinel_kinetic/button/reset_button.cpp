#include "reset_button.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void ResetButton::press_action() { this->parent_->down(); }

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
