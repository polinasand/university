#include "test.h"
#include "Cryptography.h"
#include "prime_gen.h"
void Test::assert(bool received, bool expected, string num){
    if(received != expected){
        cout << "assertion failed: number - " << num << endl;
    }
    else
        cout << "passed " << num <<'\n';
}

void Test::testPrime() {
    std::cout << "Checking Miller–Rabin primality test\n";
    assert(Cryptography::isPrime(BigInt(13)), true, "13");
    assert(Cryptography::isPrime(BigInt(31)), true, "31");
    assert(Cryptography::isPrime(BigInt(89)), true, "89");
    assert(Cryptography::isPrime(BigInt(149)), true, "149");
    assert(Cryptography::isPrime(BigInt(2459)), true, "2459");
    assert(Cryptography::isPrime(BigInt(71129)), true, "71129");
    assert(Cryptography::isPrime(BigInt("3245611")), true, "3245611");
    assert(Cryptography::isPrime(BigInt("87178291199")), true, "87178291199");
    assert(Cryptography::isPrime(BigInt("265252859812191058636308479999999")), true, "265252859812191058636308479999999");
    assert(Cryptography::isPrime(BigInt("8683317618811886495518194401279999999")), true, "8683317618811886495518194401279999999");
    std::cout << "all test passed \n";

    std::cout << "Checking Baillie–PSW primality test\n";
    assert(Cryptography::isPrimeBPSW(BigInt(13)), true, "13");
    assert(Cryptography::isPrimeBPSW(BigInt(31)), true, "31");
    assert(Cryptography::isPrimeBPSW(BigInt(149)), true, "149");
    assert(Cryptography::isPrimeBPSW(BigInt(2459)), true, "2459");
    assert(Cryptography::isPrimeBPSW(BigInt(71129)), true, "71129");
    assert(Cryptography::isPrimeBPSW(BigInt("3245611")), true, "3245611");
    assert(Cryptography::isPrimeBPSW(BigInt("87178291199")), true, "87178291199");
    assert(Cryptography::isPrimeBPSW(BigInt("265252859812191058636308479999999")), true, "265252859812191058636308479999999");
    assert(Cryptography::isPrimeBPSW(BigInt("8683317618811886495518194401279999999")), true, "8683317618811886495518194401279999999");
    std::cout << "all test passed \n";
}

void Test::testInverse(){
    BigInt p = prime_gen::nextPrime(40);
    BigInt q = prime_gen::nextPrime(40);
    BigInt phi = lcm(p-1,q-1);
    BigInt d = prime_gen::nextPrime(27);
    BigInt e = Cryptography::inverseEl(d, phi);
    cout << d << ' ' << e << ' ' << phi << ' ' << (d * e) % phi << endl;
}
