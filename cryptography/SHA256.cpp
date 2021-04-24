/*#include "SHA256.h"
using namespace std;
#include<iostream>
using byte = unsigned char;

void SHA256::init() {
    h[0] = 0x6A09E667;
	h[1] = 0xBB67AE85;
	h[2] = 0x3C6EF372;
	h[3] = 0xA54FF53A;
	h[4] = 0x510E527F;
	h[5] = 0x9B05688C;
	h[6] = 0x1F83D9AB;
	h[7] = 0x5BE0CD19;
}
unsigned long long reverseOrder(unsigned long long x){
	return (x>>56) |
		((x>>40) & 0x000000000000FF00) |
		((x>>24) & 0x0000000000FF0000) |
		((x>>8)  & 0x00000000FF000000) |
		((x<<8)  & 0x000000FF00000000) |
		((x<<24) & 0x0000FF0000000000) |
		((x<<40) & 0x00FF000000000000) |
		(x<<56);
}

void encodeLength(unsigned long long length, byte *a, unsigned int start){
	unsigned long long reversedLength = reverseOrder(length);
	unsigned int bytes = sizeof(unsigned long long), shift;
	for (int i = bytes - 1; i >= 0; i--){
		shift = i * CHAR_BIT;
		a[start + i] = byte((reversedLength>>shift) & 0xFF);
	}
}

byte* SHA256::preprocess(byte* message, int message_bytes) {
    unsigned long long message_bits = message_bytes * CHAR_BIT;
	unsigned int length_bytes = sizeof(unsigned long long);

	int zeros_bits = (blockSize - length_bytes * CHAR_BIT
		- (message_bits + CHAR_BIT)) % blockSize;

	zeros_bits = (zeros_bits + blockSize) % blockSize;
	int zeros_bytes = zeros_bits/CHAR_BIT;

	unsigned int preprocessed_bytes = message_bytes + 1 + zeros_bytes
		+ length_bytes;

	byte* preprocessed_message = new
					byte[preprocessed_bytes];

	memcpy(preprocessed_message, message, message_bytes);
	preprocessed_message[message_bytes] = endMessageByte;
	for (int i = 0; i < zeros_bytes; i++){
		preprocessed_message[message_bytes + 1 + i] = byte(0);
	}

	encodeLength(message_bits, preprocessed_message,
		preprocessed_bytes - length_bytes);
	message_bytes = preprocessed_bytes;

	return preprocessed_message;
}
unsigned int rotr(unsigned int x, unsigned int n) {
  return (x >> n) | (x << (sizeof(unsigned int) * CHAR_BIT - n));
}
unsigned int s0(unsigned int x){
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

unsigned int s1(unsigned int x){
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}
unsigned int sigma0(unsigned int x){
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

unsigned int sigma1(unsigned int x){
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

unsigned int ma(unsigned int a, unsigned int b, unsigned int c){
    return (a & b) ^ (a & c) ^ (b & c);
}

unsigned int ch(unsigned int a, unsigned int b, unsigned int c){
    return (a & b) ^ ((!a) & c);
}

void SHA256::processBlock(byte* block, unsigned int start, unsigned int * w) {
    /*for (int i=0; i<16; i++){
        w[i] = 0;
        for (int j=0; j<4; j++){
            w[i] *= 256;
            w[i] += (unsigned int)block[start+i*4+j];
        }
    }

    unsigned int _s0, _s1, _sigma0, _ma, t2, _sigma1, _ch, t1;
    for (int i=16; i<64; i++){
        _s0 = s0(w[i-15]);
        _s1 = s1(w[i-2]);
        cout << w[i];
        w[i] = ((unsigned long long)(w[i-16]+_s0)) % mod;
        w[i] = ((w[i] +(unsigned long long)w[i-7]+_s1) % mod) % mod;
        cout << w[i] << ' ';
    }
    cout << "\nend w ";
    unsigned long addh[8];
    for (int i=0; i<8; i++)
        addh[i] = h[i];
    for (int i=0; i <64; i++){
        _sigma0 = sigma0(addh[0]);
        _ma = ma(addh[0], addh[1], addh[2]);
        t2 = (_sigma0+_ma) % mod;
        _sigma1 = sigma1(addh[4]);
        _ch = ch(addh[4], addh[5], addh[6]);
        t1 = ((unsigned long long)addh[7] + _sigma1 + _ch + k[i] + w[i]) % mod;

        addh[7] = addh[6];
		addh[6] = addh[5];
		addh[5] = addh[4];
		addh[4] = ((unsigned long long)addh[3] + t1) % mod;
		addh[3] = addh[2];
		addh[2] = addh[1];
		addh[1] = addh[0];
		addh[0] = ((unsigned long long)t1 + t2) % mod;
    }
    cout << "fs ";
    for (int i=0; i<8; i++){
            cout << h[i] << ' ' << addh[i] << endl;
        addh[i] %= mod;
        h[i] += addh[i];
        h[i] %= mod;
    }
    std::cout << "\n end h ";
}


unsigned int* SHA256::hash(string message) {
    init();
    std::vector<byte> bytes;
	bytes.resize(message.size());
    for (int i=0; i<message.size(); i++){
        bytes[i] = (byte)message[i];
        cout << bytes[i] << ' ';
    }
    byte* processed_message = preprocess(&bytes[0], message.size());
    unsigned int w[64];
    for (int i=0; i<message.size(); i+=blockSize/CHAR_BIT){
        processBlock(&bytes[0], i, w);
        cout << "afesrg";
    }
    return h;
}
*/

#include "sha256.h"
#include <iostream>

const unsigned long long mod = 4294967296;

const unsigned int SHA256::k[64] =
	   {0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
	    0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
		0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
		0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
		0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
		0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
		0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
		0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
		0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
		0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
		0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
		0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
		0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
		0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
		0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
		0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

void SHA256::init() {
	h[0] = 0x6A09E667;
	h[1] = 0xBB67AE85;
	h[2] = 0x3C6EF372;
	h[3] = 0xA54FF53A;
	h[4] = 0x510E527F;
	h[5] = 0x9B05688C;
	h[6] = 0x1F83D9AB;
	h[7] = 0x5BE0CD19;
}

unsigned long long reverseEndian(unsigned long long x){
	return (x>>56) |
		((x>>40) & 0x000000000000FF00) |
		((x>>24) & 0x0000000000FF0000) |
		((x>>8)  & 0x00000000FF000000) |
		((x<<8)  & 0x000000FF00000000) |
		((x<<24) & 0x0000FF0000000000) |
		((x<<40) & 0x00FF000000000000) |
		(x<<56);
}

unsigned int rotr(unsigned int x, unsigned int n) {
  return (x >> n) | (x << (sizeof(unsigned int) * CHAR_BIT - n));
}

void encodeLength(unsigned long long length, byte *a, unsigned int begin){
	unsigned long long reversedLength = reverseEndian(length);
	unsigned int bytes = sizeof(unsigned long long), shift;
	for (int i = bytes - 1; i >= 0; i--){
		shift = i * CHAR_BIT;
		a[begin + i] = byte((reversedLength>>shift) & 0xFF);
	}
}

byte* SHA256::preprocess(byte* message, unsigned int message_bytes) {

	unsigned long long message_bits = message_bytes * CHAR_BIT;
	unsigned int length_bytes = sizeof(unsigned long long);

	int zeros_bits = (kBlockSize - length_bytes * CHAR_BIT
		- (message_bits + CHAR_BIT)) % kBlockSize;

	zeros_bits = (zeros_bits + kBlockSize) % kBlockSize;
	int zeros_bytes = zeros_bits/CHAR_BIT;

	unsigned int preprocessed_bytes = message_bytes + 1 + zeros_bytes
		+ length_bytes;

	byte* preprocessed_message = new
					byte[preprocessed_bytes];

	memcpy(preprocessed_message, message, message_bytes);
	preprocessed_message[message_bytes] = kEndMessageByte;
	for (int i = 0; i < zeros_bytes; i++){
		preprocessed_message[message_bytes + 1 + i] = kZeroByte;
	}

	encodeLength(message_bits, preprocessed_message,
		preprocessed_bytes - length_bytes);
	message_bytes = preprocessed_bytes;

	return preprocessed_message;
}

inline unsigned int smallSigma0(unsigned int x){
	return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

inline unsigned int smallSigma1(unsigned int x){
	return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

inline unsigned int sigma0(unsigned int x){
	return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

inline unsigned int sigma1(unsigned int x){
	return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

inline unsigned int maj(unsigned int x, unsigned int y,
				 unsigned int z){
	return (x & y) ^ (x & z) ^ (y & z);
}

inline unsigned int ch(unsigned int x, unsigned int y,
				 unsigned int z){
	return (x & y) ^ (~x & z);
}

void SHA256::processBlock(byte *message, int start, unsigned int *w) {
	for (int i = 0; i < 16; i ++){
		w[i] = 0;
		for (int j = 0; j < 4; j++){
			w[i] *= 256;
			w[i] += (unsigned int)( message[start + i * 4 + j]);
		}
	}

	unsigned int s0, s1, t1, t2, ma, c;

	for (int i = 16; i < 64; i++){
		s0 = smallSigma0(w[i - 15]);
		s1 = smallSigma1(w[i - 2]);
		w[i] = ((unsigned long long) w[i - 16] + s0 + w[i - 7] + s1) % mod;
	}

	int dh[8];
	for (int i = 0; i < 8; i++){
		dh[i] = this->h[i];
	}

	for (int i = 0; i < kNumRounds; i++){
		s0 = sigma0(dh[0]);
		ma = maj(dh[0], dh[1], dh[2]);
		t2 = (s0 + ma) % mod;
		s1 = sigma1(dh[4]);
		c = ch(dh[4], dh[5], dh[6]);
		t1 = ((unsigned long long) dh[7] + s1 + c + k[i] + w[i]) % mod;

		dh[7] = dh[6];
		dh[6] = dh[5];
		dh[5] = dh[4];
		dh[4] = ((unsigned long long)dh[3] + t1) % mod;
		dh[3] = dh[2];
		dh[2] = dh[1];
		dh[1] = dh[0];
		dh[0] = ((unsigned long long)t1 + t2) % mod;
	}

	for (int i = 0; i < 8; i++){
		this->h[i] += dh[i];
		this->h[i] %= mod;
	}
}

unsigned int* SHA256::hash(std::string message){
	std::vector<byte> message_bytes;
	message_bytes.resize(message.size());
	for (int i = 0; i < message.size(); i++){
		message_bytes[i] = message[i];
	}
	init();
	int nb = message_bytes.size();
	byte* internal_message = preprocess(&message_bytes[0], nb);

	unsigned int w[64];

	for (int i = 0; i < nb; i += kBlockSize/CHAR_BIT){
		processBlock(internal_message, i, w);
	}

	return h;
}

