#include <memory>
#include <iostream>
#include <string>

class Toy {
public:
    int linkCount = 0;
    Toy(std::string _name) : name(_name) {}
    Toy() : name("SameToy") {}
private:
    std::string name;
};

class shared_ptr_toy {
private:
    Toy* obj;
public:
    shared_ptr_toy() { //конструктор по умолчанию
        obj = new Toy("SomeName");
        obj->linkCount++;
    }
    shared_ptr_toy(std::string name) { //конструктор от строки
        obj = new Toy(name);
        obj->linkCount++;
    }
    shared_ptr_toy(const shared_ptr_toy& oth) { //конструктор копирования
        obj = new Toy(*oth.obj);
        obj->linkCount++;
    }
    shared_ptr_toy& operator = (const shared_ptr_toy& oth) { //оператор присваивания
        if (this == &oth)
            return *this;
        if (obj != nullptr) {
            delete obj;
            obj->linkCount--;
        }
        obj = new Toy(*oth.obj);
        obj->linkCount++;
        return *this;
    }
    ~shared_ptr_toy() {
        obj->linkCount--;
        if (obj->linkCount == 0)
            delete obj;
        std::cout << "I am deleting Shared_ptr_toy and it`s obj\n";
    }
};

void make_shared_toy(shared_ptr_toy* toy) {
    shared_ptr_toy toy2(*toy);
}
void make_shared_toy(std::string toyname) {
    shared_ptr_toy toy(toyname);
}

int main() {
    shared_ptr_toy bone;

    make_shared_toy("Ball");
    make_shared_toy(&bone);
 }
