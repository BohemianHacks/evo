// main/main.cpp
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <esp_log.h>

#include "swarm_node.h"
#include "security_manager.h"

static const char* TAG = "SWARM_MAIN";

extern "C" void app_main() {
    // Initialize non-volatile storage
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize security subsystem
    SecurityManager& securityManager = SecurityManager::getInstance();
    if (!securityManager.initialize()) {
        ESP_LOGE(TAG, "Security initialization failed");
        return;
    }

    // Create and initialize Swarm Node
    try {
        SwarmNode swarmNode;
        swarmNode.begin();
    } catch (const std::exception& e) {
        ESP_LOGE(TAG, "Swarm node initialization failed: %s", e.what());
    }
}
