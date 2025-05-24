import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_SWITCH,
    ENTITY_CATEGORY_CONFIG,
    ICON_BLUETOOTH,
    ICON_PULSE,
)

from .. import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent, vent_axia_sentinel_kinetic_ns

BluetoothSwitch = vent_axia_sentinel_kinetic_ns.class_("BluetoothSwitch", switch.Switch)
UpSwitch = vent_axia_sentinel_kinetic_ns.class_("UpSwitch", switch.Switch)

CONF_BLUETOOTH = "bluetooth"
CONF_UP = "up"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    cv.Optional(CONF_BLUETOOTH): switch.switch_schema(
        BluetoothSwitch,
        device_class=DEVICE_CLASS_SWITCH,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_BLUETOOTH,
    ),
    cv.Optional(CONF_UP): switch.switch_schema(
        UpSwitch,
        device_class=DEVICE_CLASS_SWITCH,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_BLUETOOTH,
    ),
}


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if bluetooth_config := config.get(CONF_BLUETOOTH):
        s = await switch.new_switch(bluetooth_config)
        await cg.register_parented(s, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_bluetooth_switch(s))
    if up_config := config.get(CONF_UP):
        s = await switch.new_switch(up_config)
        await cg.register_parented(s, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_up_switch(s))
