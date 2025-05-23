#pragma once

#include "esphome/components/select/select.h"
#include "../vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

class LightOutControlSelect : public select::Select, public Parented<VentAxiaSentinelKineticComponent> {
 public:
  LightOutControlSelect() = default;

 protected:
  void control(const std::string &value) override;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
