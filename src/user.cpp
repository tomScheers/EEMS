#include "user.hpp"
#include <string>

User::User(SafeQueue<std::string> &inQ, SafeQueue<std::string> &outQ,
           std::string name)
    : incoming(inQ), outgoing(outQ), name(name) {

  std::random_device rd;
  private_key =
      ((uint64_t)rd() << 32) | rd();          // combine two 32-bit rd() outputs
  public_key = ((uint64_t)rd() << 32) | rd(); // combine two 32-bit rd() outputs

  shared_key = -1;
}

BigInt User::generate_shared_key(BigInt a) {
  BigInt y = pow(g.to_string(), a.to_int()) % n;
  return y;
}

void User::run() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 5000);

  while (true) {
    int random_number = dist(gen);
    std::cout << name + ", wait: " + std::to_string(random_number) << '\n';
    std::string message = name + ": Hello World";
    outgoing.push(message);
    std::string received = incoming.pop();
    std::cout << received << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(random_number));
  }
}
