#pragma once

#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "vent_axia_sentinel_kinetic.h"

namespace esphome {
namespace vent_axia_sentinel_kinetic {

template<typename... Ts> class BluetoothPasswordSetAction : public Action<Ts...> {
 public:
  explicit BluetoothPasswordSetAction(VentAxiaSentinelKineticComponent *vent_axia_sentinel_kinetic_comp) : vent_axia_sentinel_kinetic_comp_(vent_axia_sentinel_kinetic_comp) {}
  TEMPLATABLE_VALUE(std::string, password)

  void play(Ts... x) override { this->vent_axia_sentinel_kinetic_comp_->set_bluetooth_password(this->password_.value(x...)); }

 protected:
  VentAxiaSentinelKineticComponent *vent_axia_sentinel_kinetic_comp_;
};

}  // namespace vent_axia_sentinel_kinetic
}  // namespace esphome
