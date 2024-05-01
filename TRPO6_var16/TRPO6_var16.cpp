//Вариант 16 (10 баллов) Разработайте следующие иерархии классов : рыбы (например, барбусы, карпы, сомы), 
// моллюски(большие и малые улитки), водоросли. Для каждого объекта учитывается название.
// Все объекты составляют аквариум (рыбы, моллюски и водоросли могут входить туда списком, 
// или вектором, или как - то иначе).При помощи паттерна Visitor узнайте состав аквариумных обитателей, 
// подсчитайте количество особей в аквариуме.

#include <iostream>
#include <vector>
using namespace std;

class AquariumVisitor;

class AquaticCreature { //Водные обитатели
public:
    AquaticCreature() {}
    virtual ~AquaticCreature() {}
    virtual void print() = 0;
    virtual void join(AquariumVisitor* visitor) = 0;
};


class Fish : public AquaticCreature { //Рыба
public:
    ~Fish() { }
    virtual void print() = 0;
    virtual void swim() = 0;
};

class Carp : public Fish { //Карп
    std::string name_;

public:
    Carp(std::string name) : name_(name) {}
    ~Carp() {}
    std::string getName() {
        return this->name_;
    }

    void print() {
        std::cout << "Карп " + this->name_ << std::endl;
    }

    void swim() {
        std::cout << "Плывёт карп " + this->name_ << std::endl;
    }

    void join(AquariumVisitor* visitor);
};

class Catfish : public Fish { //Сом
    std::string name_;

public:
    Catfish(std::string name) : name_(name) {}
    ~Catfish() {}
    std::string getName() {
        return this->name_;
    }

    void print() {
        std::cout << "Сом " + this->name_ << std::endl;
    }

    void swim() {
        std::cout << "Плывёт сом " + this->name_ << std::endl;
    }

    void join(AquariumVisitor* visitor);
};

class Pike : public Fish { //Щука
    std::string name_;

public:
    Pike(std::string name) : name_(name) {}
    ~Pike() {}
    std::string getName() {
        return this->name_;
    }

    void print() {
        std::cout << "Щука " + this->name_ << std::endl;
    }

    void swim() {
        std::cout << "Плывёт щука " + this->name_ << std::endl;
    }

    void join(AquariumVisitor* visitor);
};

class Shellfish : public AquaticCreature { //Моллюск
public:
    ~Shellfish() {}
    virtual void move() = 0;
};

class LargeSnail : public Shellfish { //Большая улитка
    std::string name_;

public:
    LargeSnail(std::string name) : name_(name) {}
    ~LargeSnail() {}
    std::string getName() {
        return this->name_;
    }

    void print() {
        std::cout << "Большая улитка " + this->name_ << std::endl;
    }

    void move() {
        std::cout << "Движется большая улитка " + this->name_ << std::endl;
    }

    void join(AquariumVisitor* visitor);
};

class SmallSnail : public Shellfish { //Маленькая улитка
    std::string name_;

public:
    SmallSnail(std::string name) : name_(name) {}
    ~SmallSnail() {}
    std::string getName() {
        return this->name_;
    }

    void print() {
        std::cout << "Маленькая улитка " + this->name_ << std::endl;
    }

    void move() {
        std::cout << "Движется маленькая улитка " + this->name_ << std::endl;
    }

    void join(AquariumVisitor* visitor);
};

class Seaweed : public AquaticCreature { //Водоросли
    std::string color_;
    std::string name_;

public:
    Seaweed(std::string name) : name_(name) {}
    ~Seaweed() {}
    std::string getName() {
        return this->name_;
    }
    std::string getColor() {
        return this->color_;
    }

    void print() {
        std::cout << "Водоросль " + this->name_ << std::endl;
    }

    void tearOff() {
        std::cout << "Оторвали водоросль " + this->name_ << std::endl;
    }

    void join(AquariumVisitor* visitor);
};

class Aquarium {
    std::vector<AquaticCreature*> creatures_;

public:
    std::vector<AquaticCreature*> getCreatures() {
        return this->creatures_;
    }

    void newCreature(AquaticCreature* creature) {
        this->creatures_.push_back(creature);
    }

    void printCreatures() {
        std::cout << "В этом аквариуме:" << endl;
        int size = this->creatures_.size();
        for (int i = 0; i < size; ++i) {
            this->creatures_[i]->print();
        }
        std::cout << std::endl;
    }
};

//Создаём Visitor

class AquariumVisitor {
public:
    virtual void visitCarp(Carp* carp) = 0;
    virtual void visitCatfish(Catfish* catfish) = 0;
    virtual void visitPike(Pike* pike) = 0;
    virtual void visitLargeSnail(LargeSnail* largeSnail) = 0;
    virtual void visitSmallSnail(SmallSnail* smallSnail) = 0;
    virtual void visitSeaweed(Seaweed* seaweed) = 0;
};

//Конкретный визитор-счётчик
class CountVisitor : public AquariumVisitor {
    int count_;

public:
    CountVisitor() : count_(0) { }
    int getCount() { return this->count_; }

    void visitCarp(Carp* carp) { count_++; }
    void visitCatfish(Catfish* catfish) { count_++; }
    void visitPike(Pike* pike) { count_++; }
    void visitLargeSnail(LargeSnail* largeSnail) { count_++; }
    void visitSmallSnail(SmallSnail* smallSnail) { count_++; }
    void visitSeaweed(Seaweed* seaweed) { count_++; }
};

//Добавим методы join в классы морских обитателей

void Carp::join(AquariumVisitor* visitor) {
    visitor->visitCarp(this);
}

void Catfish::join(AquariumVisitor* visitor) {
    visitor->visitCatfish(this);
}

void Pike::join(AquariumVisitor* visitor) {
    visitor->visitPike(this);
}

void LargeSnail::join(AquariumVisitor* visitor) {
    visitor->visitLargeSnail(this);
}

void SmallSnail::join(AquariumVisitor* visitor) {
    visitor->visitSmallSnail(this);
}

void Seaweed::join(AquariumVisitor* visitor) {
    visitor->visitSeaweed(this);
}


int main()
{
    setlocale(LC_ALL, "Russian");

    Carp* firstCarp = new Carp("Инокентий");
    Catfish* firstCatfish = new Catfish("Лаврентий");
    Pike* firstPike = new Pike("Марта");
    /*firstCarp->swim();
    firstCatfish->swim();
    firstPike->swim();
    std::cout << std::endl;*/
    LargeSnail* firstLSnail = new LargeSnail("Фиона");
    SmallSnail* firstSSnail = new SmallSnail("Дарина");
    /*firstLSnail->move();
    firstSSnail->move();
    std::cout << std::endl;*/
    Seaweed* firstSeaweed = new Seaweed("Харофиты");
    /*firstSeaweed->tearOff();
    std::cout << std::endl;*/

    //Добавим обитателей в аквариум 
    Aquarium* firstAquarium = new Aquarium();
    firstAquarium->newCreature(firstCarp);
    firstAquarium->newCreature(firstCatfish);
    firstAquarium->newCreature(firstPike);
    firstAquarium->newCreature(firstLSnail);
    firstAquarium->newCreature(firstSSnail);
    firstAquarium->newCreature(firstSeaweed);
    firstAquarium->printCreatures();

    //Проверка работы счётчика особей в аквариуме
    CountVisitor firstCountVisitor;
    for (AquaticCreature* creature : firstAquarium->getCreatures()) {
        creature->join(&firstCountVisitor);
    }
    std::cout << "Количество особей в аквариуме: " << firstCountVisitor.getCount() << std::endl;


    return 0;
}