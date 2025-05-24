import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_RESTART,
    ENTITY_CATEGORY_CONFIG,
    ICON_RESTART_ALERT,
)

from .. import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent, vent_axia_sentinel_kinetic_ns

Up1Button = vent_axia_sentinel_kinetic_ns.class_("Up1Button", button.Button)
Down1Button = vent_axia_sentinel_kinetic_ns.class_("Down1Button", button.Button)
Set1Button = vent_axia_sentinel_kinetic_ns.class_("Set1Button", button.Button)
Main1Button = vent_axia_sentinel_kinetic_ns.class_("Main1Button", button.Button)

CONF_UP1_BUTTON = "up1"
CONF_DOWN1_BUTTON = "down1"
CONF_SET1_BUTTON = "set1"
CONF_MAIN1_BUTTON = "main1"
# CONF_DOWN = "down1"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    cv.Optional(CONF_UP1_BUTTON): button.button_schema(
        Up1Button,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
    cv.Optional(CONF_DOWN1_BUTTON): button.button_schema(
        Down1Button,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
    cv.Optional(CONF_SET1_BUTTON): button.button_schema(
        Set1Button,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
    cv.Optional(CONF_MAIN1_BUTTON): button.button_schema(
        Main1Button,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
}


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if factory_reset_up1 := config.get(CONF_UP1_BUTTON):
        b = await button.new_button(factory_reset_up1)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_up1_button(b))
    if factory_reset_down1 := config.get(CONF_DOWN1_BUTTON):
        b = await button.new_button(factory_reset_down1)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_down1_button(b))
    if factory_reset_set1 := config.get(CONF_SET1_BUTTON):
        b = await button.new_button(factory_reset_set1)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_set1_button(b))
    if factory_reset_main1 := config.get(CONF_MAIN1_BUTTON):
        b = await button.new_button(factory_reset_main1)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_main1_button(b))
        
