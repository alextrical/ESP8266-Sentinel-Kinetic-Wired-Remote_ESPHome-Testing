import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import (
    CONF_FACTORY_RESET,
    CONF_RESTART,
    DEVICE_CLASS_RESTART,
    ENTITY_CATEGORY_CONFIG,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_DATABASE,
    ICON_RESTART,
    ICON_RESTART_ALERT,
)

from .. import CONF_VASK_ID, VentAxiaSKUARTComponent, ventaxiask_uart_ns

QueryButton = ventaxiask_uart_ns.class_("QueryButton", button.Button)

CONF_QUERY_PARAMS = "query_params"

CONFIG_SCHEMA = {
    cv.GenerateID(CONF_VASK_ID): cv.use_id(VentAxiaSKUARTComponent),
    cv.Optional(CONF_QUERY_PARAMS): button.button_schema(
        QueryButton,
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        icon=ICON_DATABASE,
    ),
}


async def to_code(config):
    vask_component = await cg.get_variable(config[CONF_VASK_ID])
    if query_params_config := config.get(CONF_QUERY_PARAMS):
        b = await button.new_button(query_params_config)
        await cg.register_parented(b, config[CONF_VASK_ID])
        cg.add(vask_component.set_query_button(b))
