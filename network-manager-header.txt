// main/network_manager.h
#pragma once

#include <cstdint>
#include <array>
#include <esp_now.h>
#include <esp_wifi.h>

class NetworkManager {
public:
    enum class TransmissionStatus {
        SUCCESS,
        FAILURE,
        TIMEOUT
    };

    NetworkManager();
    
    bool initialize();
    TransmissionStatus broadcastMessage(const uint8_t* data, size_t length);
    void registerReceiveCallback(esp_now_recv_cb_t callback);

private:
    void configureESPNOW();
    void configureWiFi();

    esp_now_peer_info_t peerInfo;
};
