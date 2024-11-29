// main/security_manager.h
#pragma once

#include <cstdint>
#include <array>
#include <mbedtls/sha256.h>
#include <esp_system.h>

class SecurityManager {
public:
    static SecurityManager& getInstance();

    bool initialize();
    bool verifyPeer(const uint8_t* peerId);
    
    // Cryptographic primitives
    std::array<uint8_t, 32> generateSecureHash(const uint8_t* data, size_t length);
    bool encryptPayload(uint8_t* payload, size_t length);
    bool decryptPayload(uint8_t* payload, size_t length);

private:
    SecurityManager() = default;
    
    std::array<uint8_t, 32> masterKey;
    std::array<uint8_t, 32> nodeIdentityHash;

    void generateMasterKey();
    void deriveNodeIdentity();
};
