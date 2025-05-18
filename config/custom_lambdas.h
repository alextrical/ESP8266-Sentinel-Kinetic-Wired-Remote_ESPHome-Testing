// custom_lambdas.h
#pragma once

/* function: VentAxiaCrcCalc 
*  - Calculate CRC for VentAxia packets
*/
auto VentAxiaCrcCalc = [](uint8_t* buffer) -> uint16_t {
    uint16_t crc = 0xFFFF;
    for (int i = 0; i < 6; i++) {
    crc -= buffer[i];
    }
    return crc;
};

/* function: VentAxiaPacket
*  - Generate keyboard press packet with correct CRC 
*/
void VentAxiaPacket() {
    // KeyPress Packet: 04 05 AF EF FB [KEY_CODE] [CRC_BYTE1] [CRC_BYTE2]
    // Orther version:  04 06 FF FF FF [KEY_CODE] [CRC_BYTE1] [CRC_BYTE2]
    id(va_out_buff)[5] = id(button_sum);
    uint16_t crc = VentAxiaCrcCalc(id(va_out_buff)); // calculate & attach CRC
    id(va_out_buff)[6] = crc >> 8;
    id(va_out_buff)[7] = crc & 0xFF;
};

/* function: VentAxiaSendKeyPress 
*  - Send packet out over serial
*/
void VentAxiaSendKeyPress() {
    VentAxiaPacket();
    id(uart_bus).write_array(id(va_out_buff), 8);
}