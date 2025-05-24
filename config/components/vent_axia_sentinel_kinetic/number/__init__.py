import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_TIMEOUT,
    DEVICE_CLASS_DISTANCE,
    DEVICE_CLASS_ILLUMINANCE,
    DEVICE_CLASS_SIGNAL_STRENGTH,
    ENTITY_CATEGORY_CONFIG,
    ICON_LIGHTBULB,
    ICON_MOTION_SENSOR,
    ICON_TIMELAPSE,
    UNIT_PERCENT,
    UNIT_SECOND,
)

from .. import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent, vent_axia_sentinel_kinetic_ns

GateThresholdNumber = vent_axia_sentinel_kinetic_ns.class_("GateThresholdNumber", number.Number)
LightThresholdNumber = vent_axia_sentinel_kinetic_ns.class_("LightThresholdNumber", number.Number)
MaxDistanceTimeoutNumber = vent_axia_sentinel_kinetic_ns.class_("MaxDistanceTimeoutNumber", number.Number)

CONF_MAX_STILL_DISTANCE_GATE = "max_still_distance_gate"
CONF_LIGHT_THRESHOLD = "light_threshold"

TIMEOUT_GROUP = "timeout"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
        cv.Inclusive(CONF_TIMEOUT, TIMEOUT_GROUP): number.number_schema(
            MaxDistanceTimeoutNumber,
            unit_of_measurement=UNIT_SECOND,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_TIMELAPSE,
        ),
        cv.Inclusive(CONF_MAX_STILL_DISTANCE_GATE, TIMEOUT_GROUP): number.number_schema(
            MaxDistanceTimeoutNumber,
            device_class=DEVICE_CLASS_DISTANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_MOTION_SENSOR,
        ),
        cv.Optional(CONF_LIGHT_THRESHOLD): number.number_schema(
            LightThresholdNumber,
            device_class=DEVICE_CLASS_ILLUMINANCE,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_LIGHTBULB,
        ),
    }
)


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if timeout_config := config.get(CONF_TIMEOUT):
        n = await number.new_number(
            timeout_config, min_value=0, max_value=65535, step=1
        )
        await cg.register_parented(n, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_timeout_number(n))
    if max_still_distance_gate_config := config.get(CONF_MAX_STILL_DISTANCE_GATE):
        n = await number.new_number(
            max_still_distance_gate_config, min_value=2, max_value=8, step=1
        )
        await cg.register_parented(n, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_max_still_distance_gate_number(n))
    if light_threshold_config := config.get(CONF_LIGHT_THRESHOLD):
        n = await number.new_number(
            light_threshold_config, min_value=0, max_value=255, step=1
        )
        await cg.register_parented(n, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_light_threshold_number(n))
