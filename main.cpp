#include <QCoreApplication>
#include <QDebug>
#include <stdio.h>
using namespace std;

class Light
{
public:
    Light();
    bool isOn;
};

Light::Light()
{
    isOn=false;
}

//класс стратегии
class IStrategy
{
public:
    virtual bool doPrisonerBehavior (Light* L)=0;
};

//стратегия обычных заключенных
class DefaultBehavior: public IStrategy
{
private:
    bool isFirst = true;
public:
    bool doPrisonerBehavior (Light* L)
    {
        if(L->isOn == false && isFirst == true)
        {
            L->isOn=true;
            isFirst = false;
        }
        return false;
    }

};

//стратегия счетчика
class CounterBehavior: public IStrategy
{
private:
    int count=0;
public:
    bool doPrisonerBehavior (Light* L)
    {
        if(L->isOn == true)
        {
            L->isOn = false;
            count ++;
            if(count == 4){
                return true;
            }
            else{
                return false;
            }
        }
        else return false;
    }
};

//класс заключенных
class Prisoner
{
public:
    virtual bool enterRoom(Light* L);
    void setStrategy (IStrategy* s);

private:
    IStrategy* Strategy;

};

bool Prisoner::enterRoom(Light* L)
{
    return Strategy->doPrisonerBehavior(L);
}
void Prisoner::setStrategy (IStrategy* s)
{
    this->Strategy = s;
}

//класс надзирателя
class Guard
{
private:
    Light* b;
    Prisoner p[5];
public:
    Guard()
    {
        b = new Light;
    }
    void startExperiment ();
    void findStrategy();
};

void Guard::startExperiment()
{
     bool isEnd = false;
     while(isEnd==false)
     {
         int n = rand()%5;
         qDebug() << n;
         isEnd = p[n].enterRoom(b);
     }
     qDebug()<< "Freedom!!!";

}

void Guard::findStrategy()
{
    p[0].setStrategy(new CounterBehavior);
    p[1].setStrategy(new DefaultBehavior);
    p[2].setStrategy(new DefaultBehavior);
    p[3].setStrategy(new DefaultBehavior);
    p[4].setStrategy(new DefaultBehavior);
}

int main(int argc, char *argv[])
{
    Guard guard;
    guard.findStrategy();
    guard.startExperiment();
    QCoreApplication a(argc, argv);
    return a.exec();
}
