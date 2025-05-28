#include "parser.h"

Parser::Parser()
{
    checksum_len_ = 0;
    total_len_ = 0;
}

Parser::~Parser()
{
}

bool Parser::add_header(const unsigned char header)
{
    header_.push_back(header);
    return true;
}

bool Parser::add_headers(const std::vector<unsigned char>& header)
{
    if (header.empty()) return false;
    header_.insert(header_.end(), header.begin(), header.end());
    return true;
}

bool Parser::parse_byte(const unsigned char byte)
{
    buffer_.push_back(byte);
    if (total_len_ > 0 && buffer_.size() > total_len_)
    {
        buffer_.erase(buffer_.begin());
    }
    if (parse_header() == false)
    {
        buffer_.clear();
        return false;
    }
    if (parse_length() == true) return true;
    return false;
}

bool Parser::verify_checksum(const std::vector<unsigned char>& checksum)
{
    if (checksum_len_ != checksum.size()) return false;
    if (buffer_.size() < checksum.size()) return false;
    return std::equal(buffer_.end() - checksum.size(), buffer_.end(), checksum.begin());
}

void Parser::clear()
{
    buffer_.clear();
}

bool Parser::parse_header()
{
    if (header_.empty()) return true;
    std::vector<unsigned char> masked_buffer = apply_mask(buffer_, header_mask_);
    size_t size = masked_buffer.size() < header_.size() ? masked_buffer.size() : header_.size();
    return std::equal(masked_buffer.begin(), masked_buffer.begin() + size, header_.begin());
}

const std::vector<unsigned char> Parser::apply_mask(const std::vector<unsigned char>& data, const std::vector<unsigned char>& mask)
{
    if (mask.empty()) return data;
    std::vector<unsigned char> masked_data = data;
    for (size_t i = 0, j = 0; i < data.size() && j < mask.size(); i++, j++)
    {
        masked_data[i] &= mask[j];
    }
    return masked_data;
}

bool Parser::parse_length()
{
    if (total_len_ == 0) return false;
    if (buffer_.size() != total_len_) return false;
    if (checksum_len_ > 0) return false;
    return true;
}

bool Parser::available()
{
    if (buffer_.empty()) return false;
    return true;
}

const std::vector<unsigned char> Parser::header()
{
    if (header_.empty()) return {};
    size_t header_size = header_.size();
    if (buffer_.size() < header_size) header_size = buffer_.size();
    return std::vector<unsigned char>(buffer_.begin(), buffer_.begin() + header_size);
}

const std::vector<unsigned char> Parser::data(const std::vector<unsigned char>& mask)
{
    size_t offset = checksum_len_;
    if (buffer_.size() < header_.size() + offset) return {};
    return apply_mask(std::vector<unsigned char>(buffer_.begin() + header_.size(), buffer_.end() - offset), mask);
}

const std::vector<unsigned char> Parser::buffer()
{
    return buffer_;
}

void Parser::set_checksum_len(size_t len)
{
    checksum_len_ = len;
}

void Parser::set_total_len(size_t len)
{
    total_len_ = len;
}