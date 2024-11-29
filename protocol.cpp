typedef struct {
    uint8_t signature[64];           // Ed25519 signature
    uint8_t encrypted_payload[256];  // Encrypted beacon data
    uint8_t nonce[24];               // Cryptographic nonce
} SecureBeaconPacket;

void encryptBeaconPacket(BeaconPacket& beacon) {
    // Use libsodium-style authenticated encryption
    crypto_aead_chacha20poly1305_encrypt(
        encrypted_payload, 
        beacon_data, 
        beacon_length, 
        additional_data
    );
}
