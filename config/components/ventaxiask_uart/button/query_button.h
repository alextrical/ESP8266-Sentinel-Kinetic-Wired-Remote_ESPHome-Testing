#pragma once

#include "esphome/components/button/button.h"
#include "../ventaxiask_uart.h"

namespace esphome {
namespace ventaxiask_uart {

class QueryButton : public button::Button, public Parented<LD2410Component> {
 public:
  QueryButton() = default;

 protected:
  void press_action() override;
};

}  // namespace ventaxiask_uart
}  // namespace esphome
