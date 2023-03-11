#include <memory>
#include <iostream>
#include <string>

class Toy {
public:
    Toy(std::string _name) : name(_name) {}
    Toy() : name("SameToy") {}
private:
    std::string name;
};

class shared_ptr_toy {
private:
    Toy* obj;
    int linkCount;
public:
    shared_ptr_toy() { //конструктор по умолчанию
        obj = new Toy("SomeName");
        linkCount = 1;
    }
    shared_ptr_toy(std::string name) { //конструктор от строки
        obj = new Toy(name);
        linkCount = 1;
    }
    shared_ptr_toy(const shared_ptr_toy& oth) { //конструктор копирования
        obj = new Toy(*oth.obj);
        linkCount = oth.linkCount;
        linkCount++;
    }
    shared_ptr_toy& operator = (const shared_ptr_toy& oth) { //оператор присваивания
        if (this == &oth)
            return *this;
        if (obj != nullptr) {
            delete obj;
            linkCount--;
        }
        obj = new Toy(*oth.obj);
        linkCount = oth.linkCount;
        linkCount++;
        return *this;
    }
    ~shared_ptr_toy() {
        linkCount--;
        if (linkCount == 0)
            delete obj;
        std::cout << "I am deleting Shared_ptr_toy and it`s obj\n";
    }
};

shared_ptr_toy make_shared_toy(class shared_ptr_toy& toy) {
    shared_ptr_toy toy2(toy);
    return toy2;
}
shared_ptr_toy make_shared_toy(std::string toyname) {
    shared_ptr_toy toy1(toyname);
    return toy1;
}

int main() {
    shared_ptr_toy bone;

    make_shared_toy("Ball");
    make_shared_toy(bone);
}
