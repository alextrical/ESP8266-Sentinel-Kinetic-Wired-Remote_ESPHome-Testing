#pragma once

#include "esphome/components/number/number.h"
#include "../vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

class GateThresholdNumber : public number::Number, public Parented<VentAxiaSentinelKineticComponent> {
 public:
  GateThresholdNumber(uint8_t gate);

 protected:
  uint8_t gate_;
  void control(float value) override;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
