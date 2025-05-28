import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_RESTART,
    ENTITY_CATEGORY_CONFIG,
    ICON_RESTART_ALERT,
)

from .. import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent, vent_axia_sentinel_kinetic_ns

UpButton = vent_axia_sentinel_kinetic_ns.class_("UpButton", button.Button)
DownButton = vent_axia_sentinel_kinetic_ns.class_("DownButton", button.Button)
SetButton = vent_axia_sentinel_kinetic_ns.class_("SetButton", button.Button)
MainButton = vent_axia_sentinel_kinetic_ns.class_("MainButton", button.Button)

CONF_UP_BUTTON = "up"
CONF_DOWN_BUTTON = "down"
CONF_SET_BUTTON = "set"
CONF_MAIN_BUTTON = "main"
# CONF_DOWN = "down"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    cv.Optional(CONF_UP_BUTTON): button.button_schema(
        UpButton,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
    cv.Optional(CONF_DOWN_BUTTON): button.button_schema(
        DownButton,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
    cv.Optional(CONF_SET_BUTTON): button.button_schema(
        SetButton,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
    cv.Optional(CONF_MAIN_BUTTON): button.button_schema(
        MainButton,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
}


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if up_button := config.get(CONF_UP_BUTTON):
        b = await button.new_button(up_button)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_up_button(b))
    if down_button := config.get(CONF_DOWN_BUTTON):
        b = await button.new_button(down_button)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_down_button(b))
    if set_button := config.get(CONF_SET_BUTTON):
        b = await button.new_button(set_button)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_set_button(b))
    if main_button := config.get(CONF_MAIN_BUTTON):
        b = await button.new_button(main_button)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_main_button(b))
        
