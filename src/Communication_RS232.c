#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include <Communication_RS232.h>
#include <rom/crc.h>


#define ECHO_TEST_TXD (CONFIG_EXAMPLE_UART_TXD)
#define ECHO_TEST_RXD (CONFIG_EXAMPLE_UART_RXD)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM      (CONFIG_EXAMPLE_UART_PORT_NUM)
#define ECHO_UART_BAUD_RATE     (CONFIG_EXAMPLE_UART_BAUD_RATE)
#define ECHO_TASK_STACK_SIZE    (CONFIG_EXAMPLE_TASK_STACK_SIZE)
#define BUF_SIZE (1024)


#define NO_MSG_AVAILABLE {0xFF, 0xFF, 0xFF}


bool checkCRC(char *msg, char crc){
return crc8_le(0, msg, 3) == crc;
}

static void uart_listener(void *arg) {
    APPS_Communication *COM = (APPS_Communication *) arg;
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
//
    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, BUF_SIZE, 20 / portTICK_RATE_MS);

    }
}
void setup_apps_rs232_listener(APPS_Communication COM){
    int intr_alloc_flags = 0;
    COM.uart_config.baud_rate = ECHO_UART_BAUD_RATE;
    COM.uart_config.data_bits = UART_DATA_8_BITS;
    COM.uart_config.parity = UART_PARITY_DISABLE;
    COM.uart_config.stop_bits=UART_STOP_BITS_1;
    COM.uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    COM.uart_config.source_clk=UART_SCLK_APB;
    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &COM.uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));
    xTaskCreate(uart_listener, "uart_listener_task", ECHO_TASK_STACK_SIZE, (void*)&COM, 10, NULL);
}

APPS_Communication_MSG get_communication_msg(APPS_Communication COM){
    return (APPS_Communication_MSG)NO_MSG_AVAILABLE;
}

esp_err_t send_communication_resp(APPS_Communication_MSG){
    return ESP_OK;
}
