import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_LIGHT,
    DEVICE_CLASS_ILLUMINANCE,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_LIGHTBULB,
)

from . import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent

DEPENDENCIES = ["vent_axia_sentinel_kinetic"]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
        cv.Optional(CONF_LIGHT): sensor.sensor_schema(
            device_class=DEVICE_CLASS_ILLUMINANCE,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            icon=ICON_LIGHTBULB,
        ),
    }
)

async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if light_config := config.get(CONF_LIGHT):
        sens = await sensor.new_sensor(light_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_light_sensor(sens))
