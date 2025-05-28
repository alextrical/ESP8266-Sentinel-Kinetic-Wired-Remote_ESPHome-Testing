#pragma once

#include "uartex.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace uartex {

class WriteTrigger : public Trigger<const uint8_t*, const uint16_t>
{
public:
    explicit WriteTrigger(UARTExComponent *parent)
    {
        parent->add_on_write_callback([this](const uint8_t *data, const uint16_t len)
        {
            this->trigger(data, len);
        });
    }
};

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

template <typename... Ts>
class UARTExWriteAction : public Action<Ts...>, public Parented<UARTExComponent>
{
public:
    void set_data_template(std::function<cmd_t(Ts...)> func)
    {
        this->data_func_ = func;
        this->static_ = false;
    }
    void set_data_static(const cmd_t &data)
    {
        this->data_static_ = data;
        this->static_ = true;
    }

protected:
    bool static_{false};
    std::function<cmd_t(Ts...)> data_func_{};
    cmd_t data_static_{};
};

}  // namespace uartex
}  // namespace esphome
