import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_LIGHT,
    DEVICE_CLASS_DISTANCE,
    DEVICE_CLASS_ILLUMINANCE,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_FLASH,
    ICON_LIGHTBULB,
    ICON_MOTION_SENSOR,
    ICON_SIGNAL,
    UNIT_CENTIMETER,
    UNIT_PERCENT,
)

from . import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent

DEPENDENCIES = ["vent_axia_sentinel_kinetic"]
CONF_MOVING_DISTANCE = "moving_distance"
CONF_STILL_DISTANCE = "still_distance"
CONF_MOVING_ENERGY = "moving_energy"
CONF_DETECTION_DISTANCE = "detection_distance"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
        cv.Optional(CONF_MOVING_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_SIGNAL,
        ),
        cv.Optional(CONF_STILL_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_SIGNAL,
        ),
        cv.Optional(CONF_MOVING_ENERGY): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            icon=ICON_MOTION_SENSOR,
        ),
        cv.Optional(CONF_LIGHT): sensor.sensor_schema(
            device_class=DEVICE_CLASS_ILLUMINANCE,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            icon=ICON_LIGHTBULB,
        ),
        cv.Optional(CONF_DETECTION_DISTANCE): sensor.sensor_schema(
            device_class=DEVICE_CLASS_DISTANCE,
            unit_of_measurement=UNIT_CENTIMETER,
            icon=ICON_SIGNAL,
        ),
    }
)

async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if moving_distance_config := config.get(CONF_MOVING_DISTANCE):
        sens = await sensor.new_sensor(moving_distance_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_moving_target_distance_sensor(sens))
    if still_distance_config := config.get(CONF_STILL_DISTANCE):
        sens = await sensor.new_sensor(still_distance_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_still_target_distance_sensor(sens))
    if moving_energy_config := config.get(CONF_MOVING_ENERGY):
        sens = await sensor.new_sensor(moving_energy_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_moving_target_energy_sensor(sens))
    if light_config := config.get(CONF_LIGHT):
        sens = await sensor.new_sensor(light_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_light_sensor(sens))
    if detection_distance_config := config.get(CONF_DETECTION_DISTANCE):
        sens = await sensor.new_sensor(detection_distance_config)
        cg.add(vent_axia_sentinel_kinetic_component.set_detection_distance_sensor(sens))
