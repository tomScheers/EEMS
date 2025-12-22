#include "user.hpp"

#include <thread>

int main() {
  SafeQueue<std::string> Q1;
  SafeQueue<std::string> Q2;

  User user1(Q1, Q2, "Bob");
  User user2(Q2, Q1, "Alice");

  std::jthread t1(&User::run, &user1);
  std::jthread t2(&User::run, &user2);

  return 0;
}
