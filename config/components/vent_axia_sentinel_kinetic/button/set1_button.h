#pragma once

#include "esphome/components/button/button.h"
#include "../vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

class Set1Button : public button::Button, public Parented<VentAxiaSentinelKineticComponent> {
 public:
  Set1Button() = default;

 protected:
  void press_action() override;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
