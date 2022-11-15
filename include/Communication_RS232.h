#ifndef UART_ECHO_COMMUNICATION_RS232_H
#define UART_ECHO_COMMUNICATION_RS232_H
#include <driver/uart.h>

typedef struct{
    uart_config_t uart_config;
    QueueHandle_t *MsgQueue;
}APPS_Communication;

typedef struct{
    uint8_t cmd;
    uint8_t reg;
    uint8_t data;
}APPS_Communication_MSG;

void setup_apps_rs232_listener(APPS_Communication COM);

APPS_Communication_MSG get_communication_msg(APPS_Communication COM);

esp_err_t send_communication_resp(APPS_Communication_MSG);

#endif //UART_ECHO_COMMUNICATION_RS232_H
