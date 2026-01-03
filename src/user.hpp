#ifndef USER_HPP
#define USER_HPP

#include "BigInt.hpp"
#include <condition_variable>
#include <mutex>
#include <queue>

// Big prime number
inline const BigInt
    n("323170060713110073003389139264238282488179412411402391128420097514007417"
      "066343542226196894173635693471179017379097041917546058732091950288537589"
      "861856221532121754125149017745202702357960782362488842461894775876411059"
      "286460994117232454266225221932305409190376805242355191256797158701170010"
      "580558776510388618472802579760549035697325615261670813393617995413364765"
      "591603683178967290731783845896806396719009772021941686472258710314113364"
      "293195361934716365332097170774482279885885653692086452966360772502689555"
      "059283627511211740969729980684105543595848665832916421362182310789909994"
      "48652468262416972035911852507045361090559");

// Generator
inline const BigInt g(2);

template <typename T> class SafeQueue {
public:
  void push(const T &value) {
    std::cout << "push\n";
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "push\n";
    q.push(value);
    std::cout << "push\n";
    cv_consumer.notify_one();
    std::cout << "push\n";
  }

  T pop() {
    std::cout << "pop\n";
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "pop\n";
    cv_consumer.wait(lock, [this]() { return !q.empty(); });
    std::cout << "pop\n";
    T value = q.front();
    std::cout << "pop\n";
    q.pop();
    std::cout << "pop\n";
    return value;
  }

private:
  std::queue<T> q;
  std::mutex mtx;
  std::condition_variable cv_consumer;
};

class User {
private:
  uint32_t private_key;
  uint32_t public_key;

  std::string name;

  BigInt shared_key; // Changes with each connection
  BigInt generate_shared_key(BigInt base, uint32_t exp, const BigInt &mod);

  SafeQueue<std::string> &incoming;
  SafeQueue<std::string> &outgoing;

  std::string encrypt_message(std::string message);
  std::string decrypt_message(std::string message);

public:
  User(SafeQueue<std::string> &inq, SafeQueue<std::string> &outQ,
       std::string name);
  void run(bool sender);
};

#endif
