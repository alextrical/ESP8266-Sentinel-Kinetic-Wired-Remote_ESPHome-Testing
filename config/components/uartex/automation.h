#pragma once

#include "uartex.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace uartex {

class ReadTrigger : public Trigger<const uint8_t*, const uint16_t>
{
public:
    explicit ReadTrigger(UARTExComponent *parent)
    {
        parent->add_on_read_callback([this](const uint8_t *data, const uint16_t len)
        {
            this->trigger(data, len);
        });
    }
};

}  // namespace uartex
}  // namespace esphome
