import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

vent_axia_sentinel_kinetic_ns = cg.esphome_ns.namespace("vent_axia_sentinel_kinetic")
VentAxiaSentinelKineticComponent = vent_axia_sentinel_kinetic_ns.class_(
    "VentAxiaSentinelKineticComponent", cg.Component, uart.UARTDevice
)

CONF_VentAxiaSentinelKinetic_ID = "vent_axia_sentinel_kinetic_id"

CONFIG_SCHEMA = (
    cv.Schema({cv.GenerateID(): cv.declare_id(VentAxiaSentinelKineticComponent)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "vent_axia_sentinel_kinetic",
    require_tx=True,
    require_rx=True,
    parity="NONE",
    stop_bits=1,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
