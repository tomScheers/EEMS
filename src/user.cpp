#include "user.hpp"
#include <string>

User::User(SafeQueue<std::string> &inQ, SafeQueue<std::string> &outQ,
           std::string name)
    : incoming(inQ), outgoing(outQ), name(name) {

  std::random_device rd;
  private_key = rd();
  public_key = rd();

  shared_key = -1;
  std::cout << name + ": Private Key: " + std::to_string(private_key) +
                   ", Public Key: " + std::to_string(public_key) + "\n";
}

BigInt User::generate_shared_key(BigInt base, uint32_t exp, const BigInt &mod) {
  BigInt result = 1;
  base %= mod;

  while (exp > 0) {
    if (exp & 1)
      result = (result * base) % mod;

    base = (base * base) % mod;
    exp >>= 1;
  }

  return result;
}

void User::run(bool sender) {
  BigInt intermediate_key_in;
  BigInt generated_shared_key = generate_shared_key(g, private_key, n);
  if (sender) {
    outgoing.push(generated_shared_key.to_string());
    intermediate_key_in = BigInt(incoming.pop());
  } else {
    intermediate_key_in = BigInt(incoming.pop());
    outgoing.push(generated_shared_key.to_string());
  }
  shared_key = generate_shared_key(intermediate_key_in, private_key, n);
  std::cout << "Shared key " + name + ": " + shared_key.to_string() << '\n';
}
