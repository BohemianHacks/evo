// main/swarm_node.h
#pragma once

#include <cstdint>
#include <array>
#include <vector>

#include "network_manager.h"
#include "security_manager.h"
#include "ai_model_manager.h"

class SwarmNode {
public:
    static constexpr size_t NODE_ID_LENGTH = 16;
    static constexpr size_t MAX_PEERS = 50;
    static constexpr uint32_t BEACON_INTERVAL_MS = 5000;

    struct PeerInfo {
        std::array<uint8_t, NODE_ID_LENGTH> nodeId;
        int8_t rssi;
        uint32_t lastSeen;
        bool isActive;
        std::vector<float> capabilities;
    };

    SwarmNode();
    void begin();
    void stop();

private:
    NetworkManager networkManager;
    SecurityManager& securityManager;
    AIModelManager aiModelManager;

    std::array<uint8_t, NODE_ID_LENGTH> nodeId;
    std::array<PeerInfo, MAX_PEERS> peers;

    void generateNodeId();
    void sendBeacon();
    void processPeerBeacon(const PeerInfo& beacon);
    void updatePeerDatabase(const PeerInfo& beacon);
};
