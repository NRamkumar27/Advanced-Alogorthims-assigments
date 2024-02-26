#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

// Circular right shift (32-bit)
#define ROTR(x, n) ((x >> n) | (x << (32 - n)))

// Right shift (32-bit)
#define SHR(x, n) (x >> n)

// Sigma0 and Sigma1 functions
#define SIGMA0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIGMA1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define sigma0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define sigma1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

// Ch and Maj functions
#define CH(x, y, z) ((x & y) ^ (~x & z))
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

// Initial hash values (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19)
const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// SHA-256 compression function
void sha256(const std::string& message, uint32_t hash[]) {
    // Initial hash values
    uint32_t H[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // Non-const string for padding
    std::string padded_message = message;
    
    // Pre-processing: Padding the message
    size_t original_len = padded_message.length();
    uint64_t bit_len = original_len * 8;
    padded_message += static_cast<char>(0x80);
    size_t new_len = padded_message.length();
    size_t padding_len = (new_len + 64 - (new_len % 64)) - new_len;
    padded_message += std::string(padding_len, 0);
    for (int i = 7; i >= 0; --i)
        padded_message += static_cast<char>((bit_len >> (i * 8)) & 0xFF);

    // Process the message in 512-bit chunks
    for (size_t chunk = 0; chunk < padded_message.length(); chunk += 64) {
        uint32_t W[64] = {0};
        for (int i = 0; i < 16; ++i) {
            W[i] = (static_cast<uint32_t>(padded_message[chunk + i * 4]) << 24) |
                   (static_cast<uint32_t>(padded_message[chunk + i * 4 + 1]) << 16) |
                   (static_cast<uint32_t>(padded_message[chunk + i * 4 + 2]) << 8) |
                   (static_cast<uint32_t>(padded_message[chunk + i * 4 + 3]));
        }
        for (int i = 16; i < 64; ++i) {
            W[i] = sigma1(W[i - 2]) + W[i - 7] + sigma0(W[i - 15]) + W[i - 16];
        }

        uint32_t a = H[0];
        uint32_t b = H[1];
        uint32_t c = H[2];
        uint32_t d = H[3];
        uint32_t e = H[4];
        uint32_t f = H[5];
        uint32_t g = H[6];
        uint32_t h = H[7];

        for (int i = 0; i < 64; ++i) {
            uint32_t temp1 = h + SIGMA1(e) + CH(e, f, g) + K[i] + W[i];
            uint32_t temp2 = SIGMA0(a) + MAJ(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    }

    // Final hash value
    for (int i = 0; i < 8; ++i)
        hash[i] = H[i];
}

// Convert a 32-bit unsigned integer to a hexadecimal string
std::string uint32_to_hex_string(uint32_t num) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(8) << num;
    return ss.str();
}

int main() {
    std::cout << "Enter a message: ";
    std::string message;
    std::getline(std::cin, message);
    
    uint32_t hash[8];
    sha256(message, hash);
    
    std::cout << "SHA-256 hash of '" << message << "': ";
    for (int i = 0; i < 8; ++i)
        std::cout << uint32_to_hex_string(hash[i]);
    std::cout << std::endl;
    
    return 0;
}
