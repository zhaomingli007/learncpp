#include <string>
#include <iostream>

class Base
{
public:
    Base(const std::string &n) : basename(n) {}
    std::string name()
    {
        return basename;
    }

    virtual void print(std::ostream &os)
    {
        os << basename;
    }

private:
    std::string basename;
};

class Derived : public Base
{
public:
    Derived(const std::string& n) : Base(n) {}
    void print(std::ostream &os)
    {
        Base::print(os);
        os << " " << i << '\n';
    }

private:
    int i;
};

int main(int argc, char const *argv[])
{
    Base base("base name");
    Derived d("derived");
    Base *b = &d;
    b->print(std::cout);
    Base *b1 = &base;
    b1->print(std::cout);
    return 0;
}
