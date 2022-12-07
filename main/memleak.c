/**
 * @file memleak.c
 *
 * Demonstration of memory leak in esp_wifi_init()?
 */

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_heap_trace.h"
#include "esp_wifi.h"
#include "esp_system.h"

static const char *TAG = "memleak";

#define NUM_RECORDS 100
static heap_trace_record_t trace_record[NUM_RECORDS];

void app_main(void)
{
    esp_err_t ret;

    ESP_LOGI(TAG, "esp-idf: %s", esp_get_idf_version());

    // initialize non-volatile storage
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(heap_trace_init_standalone(trace_record, NUM_RECORDS));
    ESP_ERROR_CHECK(heap_trace_start(HEAP_TRACE_LEAKS));

    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    ESP_ERROR_CHECK(esp_wifi_deinit());

    ESP_ERROR_CHECK(heap_trace_stop());
    heap_trace_dump();
}
