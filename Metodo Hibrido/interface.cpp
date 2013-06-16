#include <iostream>
using namespace std;
 
class Animal
{
public:
    virtual void comer() = 0;
    // Superclasses devem ter o destrutor virtual
    virtual ~Animal()
    {
    }
};
 
class Lobo: public Animal
{
public:
    void comer()
    {
        cout << "Eu me alimento como um lobo!" << endl;
    }
};
 
class Peixe: public Animal
{
public:
    void comer()
    {
        cout << "Eu me alimento como um peixe!" << endl;
    }
};
 
int main(void)
{
    Animal *a = new Lobo();
    Animal *b = new Peixe();
 
    a->comer();
    b->comer();
 
    return 0;
}
