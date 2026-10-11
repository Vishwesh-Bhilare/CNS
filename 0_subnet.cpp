#include <stdio.h>
#include <stdint.h>

int main() {
    unsigned int a, b, c, d;
    int prefix;

    printf("Enter IP address (e.g. 192.168.1.10): ");
    scanf("%u.%u.%u.%u", &a, &b, &c, &d);

    printf("Enter prefix length (0-32), e.g. 24: ");
    scanf("%d", &prefix);

    if (a > 255 || b > 255 || c > 255 || d > 255 ||
        prefix < 0 || prefix > 32) {
        printf("Invalid IP address or prefix length.\n");
        return 1;
    }

    // Convert IP address into a 32-bit number
    uint32_t ip = (a << 24) | (b << 16) | (c << 8) | d;

    // Calculate subnet mask
    uint32_t mask;

    if (prefix == 0)
        mask = 0;
    else
        mask = 0xFFFFFFFF << (32 - prefix);

    // Calculate network and broadcast addresses
    uint32_t network = ip & mask;
    uint32_t broadcast = network | (~mask);

    printf("\n--- Subnet Information ---\n");

    printf("IP Address       : %u.%u.%u.%u/%d\n",
           a, b, c, d, prefix);

    printf("Subnet Mask      : %u.%u.%u.%u\n",
           (mask >> 24) & 255,
           (mask >> 16) & 255,
           (mask >> 8) & 255,
           mask & 255);

    printf("Network Address  : %u.%u.%u.%u\n",
           (network >> 24) & 255,
           (network >> 16) & 255,
           (network >> 8) & 255,
           network & 255);

    printf("Broadcast Address: %u.%u.%u.%u\n",
           (broadcast >> 24) & 255,
           (broadcast >> 16) & 255,
           (broadcast >> 8) & 255,
           broadcast & 255);

    if (prefix <= 30) {
        uint32_t firstHost = network + 1;
        uint32_t lastHost = broadcast - 1;

        printf("First Host       : %u.%u.%u.%u\n",
               (firstHost >> 24) & 255,
               (firstHost >> 16) & 255,
               (firstHost >> 8) & 255,
               firstHost & 255);

        printf("Last Host        : %u.%u.%u.%u\n",
               (lastHost >> 24) & 255,
               (lastHost >> 16) & 255,
               (lastHost >> 8) & 255,
               lastHost & 255);

        uint64_t total = 1ULL << (32 - prefix);

        printf("Total Addresses  : %llu\n",
               (unsigned long long)total);

        printf("Usable Hosts     : %llu\n",
               (unsigned long long)(total - 2));
    } else {
        printf("Usable host calculation is special for /31 and /32.\n");
    }

    return 0;
}
