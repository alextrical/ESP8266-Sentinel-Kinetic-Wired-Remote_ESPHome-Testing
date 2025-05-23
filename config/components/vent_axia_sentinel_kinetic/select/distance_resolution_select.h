#pragma once

#include "esphome/components/select/select.h"
#include "../vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

class DistanceResolutionSelect : public select::Select, public Parented<VentAxiaSentinelKineticComponent> {
 public:
  DistanceResolutionSelect() = default;

 protected:
  void control(const std::string &value) override;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
