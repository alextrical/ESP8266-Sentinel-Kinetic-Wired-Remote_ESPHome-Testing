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

CONF_FACTORY_UP1 = "up1"
# CONF_DOWN = "down1"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    cv.Optional(CONF_FACTORY_UP1): button.button_schema(
        Up1Button,
        device_class=DEVICE_CLASS_RESTART,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RESTART_ALERT,
    ),
}


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if factory_reset_up1 := config.get(CONF_FACTORY_UP1):
        b = await button.new_button(factory_reset_up1)
        await cg.register_parented(b, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_up1_button(b))
        
