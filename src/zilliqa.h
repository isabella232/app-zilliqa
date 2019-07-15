#ifndef ZIL_NANOS_ZILLIQA_H
#define ZIL_NANOS_ZILLIQA_H

// Use Zilliqa's DER decode function for signing?
// (this shouldn't have any functional impact).
#define DER_DECODE_ZILLIQA 0

// MACROS
#define P() PRINTF("\n%s - %s:%d \n", __FILE__, __func__, __LINE__);

// Constants
#define SHA256_HASH_LEN 32
#define PUB_ADDR_BYTES_LEN 20
#define PUBLIC_KEY_BYTES_LEN 33
// https://github.com/Zilliqa/Zilliqa/wiki/Address-Standard#specification
#define BECH32_ADDRSTR_LEN (3 + 1 + 32 + 6)

// exception codes
#define SW_DEVELOPER_ERR 0x6B00
#define SW_INVALID_PARAM 0x6B01
#define SW_IMPROPER_INIT 0x6B02
#define SW_USER_REJECTED 0x6985
#define SW_OK            0x9000

// macros for converting raw bytes to uint64_t
#define U8BE(buf, off) (((uint64_t)(U4BE(buf, off))     << 32) | ((uint64_t)(U4BE(buf, off + 4)) & 0xFFFFFFFF))
#define U8LE(buf, off) (((uint64_t)(U4LE(buf, off + 4)) << 32) | ((uint64_t)(U4LE(buf, off))     & 0xFFFFFFFF))

// FUNCTIONS

// Get the seed key for Zilliqa BIP32 path
uint8_t * getKeySeed(uint32_t index);

// Convert un-compressed zilliqa public key to a compressed form.
void compressPubKey(cx_ecfp_public_key_t *publicKey);

// pubkeyToZilAddress converts a Ledger pubkey to a Zilliqa wallet address.
void pubkeyToZilAddress(uint8_t *dst, cx_ecfp_public_key_t *publicKey);

// deriveZilPubKey derives an Ed25519 key pair from an index and the Ledger
// seed. Returns the public key (private key is not needed).
void deriveZilPubKey(uint32_t index, cx_ecfp_public_key_t *publicKey);

// deriveAndSign derives an ECFP private key from an user specified index and the
// Ledger seed, and uses it to produce a 72-byte signature of the provided hash.
// The key is cleared from memory after signing.
int deriveAndSign(uint8_t *dst, uint32_t index, const uint8_t *hash, unsigned int hashLen);

// BYTE UTILS

// bin2hex converts binary to hex and appends a final NUL byte.
void bin2hex(uint8_t *dst, uint64_t dstlen, uint8_t *data, uint64_t inlen);

// bin2dec converts an unsigned integer to a decimal string and appends a
// final NUL byte. It returns the length of the string.
int bin2dec(uint8_t *dst, uint64_t n);

// Given a hex string with numhexchar characters, convert it
// to byte sequence and place in "bin" (which must be allocated
// with at least numhexchar/2 bytes already).
void hex2bin(uint8_t *hexstr, unsigned numhexchars, uint8_t *bin);

// Equivalent to what is there in stdlib.
int strncmp( const char * s1, const char * s2, size_t n );
// Equivalent to what is there in stdlib.
size_t strlen(const char *str);
// Equivalent to what is there in stdlib.
char* strcpy(char *dst, const char *src);


#endif