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
MaxDistanceTimeoutNumber = vent_axia_sentinel_kinetic_ns.class_("MaxDistanceTimeoutNumber", number.Number)
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
