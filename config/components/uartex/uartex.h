#pragma once
#include "esphome/core/automation.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "uartex_device.h"
#include "parser.h"
#include "version.h"
namespace esphome {
namespace uartex {

enum ERROR {
    ERROR_NONE,
    ERROR_SIZE,
    ERROR_HEADER,
    ERROR_FOOTER,
    ERROR_CHECKSUM,
    ERROR_RX_TIMEOUT
};

enum CHECKSUM {
    CHECKSUM_NONE,
    CHECKSUM_CUSTOM,
    CHECKSUM_XOR,
    CHECKSUM_ADD,
    CHECKSUM_SUBTRACT,
    CHECKSUM_XOR_NO_HEADER,
    CHECKSUM_ADD_NO_HEADER,
    CHECKSUM_XOR_ADD
};

struct header_t
{
    std::vector<uint8_t> data;
    std::vector<uint8_t> mask;
};

class UARTExComponent : public uart::UARTDevice, public Component
{
public:
    UARTExComponent() = default;
    void set_rx_header(header_t header);
    void set_rx_footer(std::vector<uint8_t> footer);
    void set_rx_checksum_2(CHECKSUM checksum);
    void set_rx_checksum_2(std::function<std::vector<uint8_t>(const uint8_t *data, const uint16_t len)> &&f);
    void set_version(text_sensor::TextSensor *version) { this->version_ = version; }
    void set_error(text_sensor::TextSensor *error) { this->error_ = error; }
    void set_log(text_sensor::TextSensor *log) { this->log_ = log; }
    void set_log_ascii(bool ascii) { this->log_ascii_ = ascii; }
    void add_on_read_callback(std::function<void(const uint8_t *data, const uint16_t len)> &&callback) { this->read_callback_.add(std::move(callback)); }
    void add_on_error_callback(std::function<void(const ERROR)> &&callback) { this->error_callback_.add(std::move(callback)); }
    std::vector<uint8_t> get_rx_checksum(const std::vector<uint8_t> &data, const std::vector<uint8_t> &header);
    void dump_config() override;
    void setup() override;
    void loop() override;
    float get_setup_priority() const override { return setup_priority::BUS - 1.0f; }
    void write_flush();
    void register_device(UARTExDevice *device);
    void set_rx_length(uint16_t rx_length);
    void set_rx_timeout(uint16_t timeout);
    void write_command(cmd_t cmd);

protected:
    ERROR validate_data();
    bool verify_data();
    bool publish_error(ERROR error_code);
    void publish_rx_log(const std::vector<unsigned char>& data);
    void publish_log(std::string msg);
    void read_from_uart();
    void publish_to_devices();
    void publish_data();
    uint16_t get_checksum(CHECKSUM checksum, const std::vector<uint8_t> &header, const std::vector<uint8_t> &data);

protected:
    std::vector<UARTExDevice *> devices_{};
    uint16_t conf_rx_timeout_{10};
    uint16_t conf_rx_length_{0};
    optional<header_t> rx_header_{};
    optional<std::vector<uint8_t>> rx_footer_{};
    CHECKSUM rx_checksum_2_{CHECKSUM_NONE};
    optional<std::function<std::vector<uint8_t>(const uint8_t *data, const uint16_t len)>> rx_checksum_f_2_{};
    CallbackManager<void(const uint8_t *data, const uint16_t len)> read_callback_{};
    ERROR error_code_{ERROR_NONE};
    CallbackManager<void(const ERROR)> error_callback_{};
    unsigned long rx_time_{0};

    Parser rx_parser_{};
    text_sensor::TextSensor* version_{nullptr};
    text_sensor::TextSensor* error_{nullptr};
    text_sensor::TextSensor* log_{nullptr};
    bool log_ascii_{false};
    std::string last_log_{""};
    uint32_t log_count_{0};
    optional<cmd_t> command_{};
};

} // namespace uartex
} // namespace esphome