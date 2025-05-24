import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_VERSION,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_BLUETOOTH,
    ICON_CHIP,
)

from . import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent

DEPENDENCIES = ["vent_axia_sentinel_kinetic"]

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    cv.Optional(CONF_VERSION): text_sensor.text_sensor_schema(
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC, icon=ICON_CHIP
    ),
}


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if version_config := config.get(CONF_VERSION):
        sens = await text_sensor.new_text_sensor(version_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_version_text_sensor(sens))
