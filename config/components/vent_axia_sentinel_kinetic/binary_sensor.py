import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_HAS_TARGET,
    DEVICE_CLASS_MOTION,
    DEVICE_CLASS_OCCUPANCY,
    DEVICE_CLASS_PRESENCE,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_ACCOUNT,
    ICON_MOTION_SENSOR,
)

from . import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent

DEPENDENCIES = ["vent_axia_sentinel_kinetic"]

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    cv.Optional(CONF_HAS_TARGET): binary_sensor.binary_sensor_schema(
        device_class=DEVICE_CLASS_OCCUPANCY,
        icon=ICON_ACCOUNT,
    ),
}


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if has_target_config := config.get(CONF_HAS_TARGET):
        sens = await binary_sensor.new_binary_sensor(has_target_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_target_binary_sensor(sens))
