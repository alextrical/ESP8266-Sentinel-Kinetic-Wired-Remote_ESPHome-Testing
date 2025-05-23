#pragma once

#include "esphome/components/switch/switch.h"
#include "../vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

class EngineeringModeSwitch : public switch_::Switch, public Parented<VentAxiaSentinelKineticComponent> {
 public:
  EngineeringModeSwitch() = default;

 protected:
  void write_state(bool state) override;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
