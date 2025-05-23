#pragma once

#include "esphome/components/number/number.h"
#include "../vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

class MaxDistanceTimeoutNumber : public number::Number, public Parented<VentAxiaSentinelKineticComponent> {
 public:
  MaxDistanceTimeoutNumber() = default;

 protected:
  void control(float value) override;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
