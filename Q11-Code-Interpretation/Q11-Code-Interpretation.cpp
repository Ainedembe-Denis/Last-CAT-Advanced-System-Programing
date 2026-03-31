#include <iostream>
using namespace std;
class Test {
public:
Test() {
cout << "Constructor called\n";
}
};
int main() {
Test t1, t2;
return 0;
}
