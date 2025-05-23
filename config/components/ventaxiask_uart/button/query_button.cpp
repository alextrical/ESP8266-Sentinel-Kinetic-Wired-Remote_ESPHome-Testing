#include "query_button.h"

namespace esphome {
namespace ventaxiask_uart {

void QueryButton::press_action() { this->parent_->read_all_info(); }

}  // namespace ventaxiask_uart
}  // namespace esphome
