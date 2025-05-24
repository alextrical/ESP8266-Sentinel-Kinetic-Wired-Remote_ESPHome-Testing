import esphome.codegen as cg
from esphome.components import select
import esphome.config_validation as cv
from esphome.const import (
    ENTITY_CATEGORY_CONFIG,
    ICON_LIGHTBULB,
    ICON_RULER,
    ICON_SCALE,
)

from .. import CONF_VentAxiaSentinelKinetic_ID, VentAxiaSentinelKineticComponent, vent_axia_sentinel_kinetic_ns

DistanceResolutionSelect = vent_axia_sentinel_kinetic_ns.class_("DistanceResolutionSelect", select.Select)

CONF_DISTANCE_RESOLUTION = "distance_resolution"


CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VentAxiaSentinelKinetic_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    cv.Optional(CONF_DISTANCE_RESOLUTION): select.select_schema(
        DistanceResolutionSelect,
        entity_category=ENTITY_CATEGORY_CONFIG,
        icon=ICON_RULER,
    ),
}


async def to_code(config):
    vent_axia_sentinel_kinetic_component = await cg.get_variable(config[CONF_VentAxiaSentinelKinetic_ID])
    if distance_resolution_config := config.get(CONF_DISTANCE_RESOLUTION):
        s = await select.new_select(
            distance_resolution_config, options=["0.2m", "0.75m"]
        )
        await cg.register_parented(s, config[CONF_VentAxiaSentinelKinetic_ID])
        cg.add(vent_axia_sentinel_kinetic_component.set_distance_resolution_select(s))
