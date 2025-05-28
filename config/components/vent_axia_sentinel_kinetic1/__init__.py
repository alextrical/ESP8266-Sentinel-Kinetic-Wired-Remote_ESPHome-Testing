from esphome import automation
from esphome.automation import maybe_simple_id
import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PASSWORD, CONF_THROTTLE, CONF_TIMEOUT

DEPENDENCIES = ["uart"]
CODEOWNERS = ["@sebcaps", "@regevbr"]
MULTI_CONF = True

vent_axia_sentinel_kinetic_ns = cg.esphome_ns.namespace("vent_axia_sentinel_kinetic")
VentAxiaSentinelKineticComponent = vent_axia_sentinel_kinetic_ns.class_("VentAxiaSentinelKineticComponent", cg.Component, uart.UARTDevice)

CONF_VentAxiaSentinelKinetic_ID = "vent_axia_sentinel_kinetic_id"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(VentAxiaSentinelKineticComponent),
        cv.Optional(CONF_THROTTLE, default="1000ms"): cv.All(
            cv.positive_time_period_milliseconds,
            cv.Range(min=cv.TimePeriod(milliseconds=1)),
        ),
        cv.Optional(CONF_TIMEOUT): cv.invalid(
            f"The '{CONF_TIMEOUT}' option has been moved to the '{CONF_TIMEOUT}'"
            f" number component"
        ),
    }
)

CONFIG_SCHEMA = cv.All(
    CONFIG_SCHEMA.extend(uart.UART_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)
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
    cg.add(var.set_throttle(config[CONF_THROTTLE]))


CALIBRATION_ACTION_SCHEMA = maybe_simple_id(
    {
        cv.Required(CONF_ID): cv.use_id(VentAxiaSentinelKineticComponent),
    }
)
