#include <vector>
#include <memory>

using namespace std;

class MyClass{
public:
    MyClass(std::vector<std::unique_ptr<int>> ownedByCaller)
        : _ownedByMe(std::move(ownedByCaller))
    {

    }

private:
    std::vector<std::unique_ptr<int>> _ownedByMe;
};

std::vector<std::unique_ptr<int>> vec;