#include "query_button.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

void QueryButton::press_action() { this->parent_->read_all_info(); }

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
