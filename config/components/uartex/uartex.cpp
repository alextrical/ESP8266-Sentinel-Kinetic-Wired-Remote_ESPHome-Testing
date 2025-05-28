#include "uartex.h"

namespace esphome {
namespace uartex {
static const char *TAG = "uartex";
void UARTExComponent::dump_config()
{
#ifdef ESPHOME_LOG_HAS_DEBUG
    log_config(TAG, "uartex count", (uint16_t)this->devices_.size());
#endif
}

void UARTExComponent::setup()
{
    this->rx_parser_.set_checksum_len(2);
    this->rx_time_ = get_time();
    this->rx_parser_.add_headers(std::vector<unsigned char>{0x02});
    this->rx_parser_.set_total_len(41);
    if (this->error_) this->error_->publish_state("None");
    if (this->version_) this->version_->publish_state(UARTEX_VERSION);
    ESP_LOGI(TAG, "Initaialize.");
    publish_log(std::string("Boot ") + UARTEX_VERSION);
}

void UARTExComponent::loop()
{
    read_from_uart();
    publish_to_devices();
}

void UARTExComponent::read_from_uart()
{
    this->rx_parser_.clear();
    if (!this->available()) return;
    unsigned long timer = get_time();
    while (elapsed_time(timer) < 10)
    {
        while (this->available())
        {
            uint8_t byte;
            if (this->read_byte(&byte))
            {
                if (this->rx_parser_.parse_byte(byte)) return;
                if (validate_data() == ERROR_NONE) return;
                timer = get_time();
            }
        }
        delay(1);
    }
}

void UARTExComponent::publish_to_devices()
{
    if (!this->rx_parser_.available()) return;
    if (!verify_data()) return;
    publish_data();
    this->rx_time_ = get_time();
}

void UARTExComponent::publish_data()
{
    bool found = false;
    auto data = this->rx_parser_.data();
    this->read_callback_.call(&this->rx_parser_.buffer()[0], this->rx_parser_.buffer().size());
    publish_rx_log(this->rx_parser_.buffer());
    for (UARTExDevice* device : this->devices_)
    {
        if (device->parse_data(data))
        {
            found = true;
        }
    }
#ifdef ESPHOME_LOG_HAS_VERBOSE
    ESP_LOGV(TAG, "Receive data-> %s, Gap Time: %lums", to_hex_string(this->rx_parser_.buffer()).c_str(), elapsed_time(this->rx_time_));
    if (!found) ESP_LOGV(TAG, "Notfound data-> %s", to_hex_string(this->rx_parser_.buffer()).c_str());
#endif
}

void UARTExComponent::register_device(UARTExDevice *device)
{
    this->devices_.push_back(device);
}

ERROR UARTExComponent::validate_data()
{
    auto data = this->rx_parser_.data();
    if (data.empty())
    {
        return ERROR_SIZE;
    }
    if (!this->rx_parser_.verify_checksum(get_rx_checksum(data, this->rx_parser_.header())))
    {
        return ERROR_CHECKSUM;
    }
    return ERROR_NONE;
}

bool UARTExComponent::verify_data()
{
    ERROR error = validate_data();
    publish_error(error);
    if (error != ERROR_NONE) this->error_callback_.call(error);
    return (error == ERROR_NONE || error == ERROR_RX_TIMEOUT);
}

bool UARTExComponent::publish_error(ERROR error_code)
{
    bool error = true;
    switch(error_code)
    {
    case ERROR_SIZE:
        ESP_LOGW(TAG, "[Read] Size error: %s", to_hex_string(this->rx_parser_.buffer()).c_str());
        if (this->error_ && this->error_code_ != ERROR_SIZE) this->error_->publish_state("Size Error");
        break;
    case ERROR_HEADER:
        ESP_LOGW(TAG, "[Read] Header error: %s", to_hex_string(this->rx_parser_.buffer()).c_str());
        if (this->error_ && this->error_code_ != ERROR_HEADER) this->error_->publish_state("Header Error");
        break;
    case ERROR_CHECKSUM:
        ESP_LOGW(TAG, "[Read] Checksum error: %s", to_hex_string(this->rx_parser_.buffer()).c_str());
        if (this->error_ && this->error_code_ != ERROR_CHECKSUM) this->error_->publish_state("Checksum Error");
        break;
    case ERROR_RX_TIMEOUT:
        ESP_LOGW(TAG, "[Read] Rx Timeout error: %s", to_hex_string(this->rx_parser_.buffer()).c_str());
        if (this->error_ && this->error_code_ != ERROR_RX_TIMEOUT) this->error_->publish_state("Rx Timeout Error");
        break;
    case ERROR_NONE:
        if (this->error_ && this->error_code_ != ERROR_NONE) this->error_->publish_state("None");
        error = false;
        break;
    }
    this->error_code_ = error_code;
    return error;
}

void UARTExComponent::publish_rx_log(const std::vector<unsigned char>& data)
{
    if (this->log_ == nullptr) return;
    if (this->log_ascii_)   publish_log("[R]" + to_ascii_string(data));
    else                    publish_log("[R]" + to_hex_string(data));
}

void UARTExComponent::publish_log(std::string msg)
{
    if (this->log_ == nullptr) return;
    if (this->last_log_ == msg)
    {
        this->log_->publish_state(msg + " (" + std::to_string(++this->log_count_) + ")");
    }
    else
    {
        this->log_count_ = 0;
        this->last_log_ = msg;
        this->log_->publish_state(msg);
    }
}

std::vector<uint8_t> UARTExComponent::get_rx_checksum(const std::vector<uint8_t> &data, const std::vector<uint8_t> &header)
{
    uint16_t crc = get_checksum(header, data);
    return { (uint8_t)(crc >> 8), (uint8_t)(crc & 0xFF) };
}

uint16_t UARTExComponent::get_checksum(const std::vector<uint8_t> &header, const std::vector<uint8_t> &data)
{
    uint16_t crc = 0xFFFF;
    uint8_t temp = 0;
    for (uint8_t byte : header) { crc -= byte; }
    for (uint8_t byte : data) { crc -= byte; }
    return crc;
}

}  // namespace uartex
}  // namespace esphome