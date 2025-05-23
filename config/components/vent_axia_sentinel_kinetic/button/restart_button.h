#pragma once

#include "esphome/components/button/button.h"
#include "../vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

class RestartButton : public button::Button, public Parented<VentAxiaSentinelKineticComponent> {
 public:
  RestartButton() = default;

 protected:
  void press_action() override;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
