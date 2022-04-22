#include <iostream>

using namespace std;

enum EState 
{
    Off,
    Wait_cmd,
    Reverse,
    Move_straight,
    Clean,
    Error
};

class Robot
{
    EState state;
    double angle;
    double distance;
    GetCommand* robotStrategy;
public:
    Robot(GetCommand* _strategy): robotStrategy(_strategy) {};
    ~Robot()
    { 
        delete robotStrategy;
    };
    EState getState();
    void setState(EState nState);
    void processEvent(EState state);
    //void getCoordinates();
    void rotate(double angle);
    void moveStraight(double distance);
    void clean();
    void getCmd();
};

void Robot::getCmd() 
{
    robotStrategy->getEvent();
}

void Robot::rotate(double angle) 
{
    cout << "Robot turned to " << angle << " degree\n";
};

void Robot::moveStraight(double distance) 
{
    cout << "Robot moved straight to " << distance << endl;
};

void Robot::clean() 
{
    cout << "Robot cleaned the area\n";
};

void Robot::processEvent(EState state) 
{
    while (state != Off) 
    {
        Robot::getCmd();
        switch (state) 
        {
            case Wait_cmd:  
                Robot::getCmd();
                break;

            case Reverse:
                double angl;
                cin >> angl;
                Robot::rotate(angl);
                state = Wait_cmd;
                break;

            case Move_straight:
                double dist;
                cin >> dist;
                Robot::moveStraight(dist);
                state = Wait_cmd;
                break;

            case Clean:
                Robot::clean();
                state = Wait_cmd;
                break;

            case Error:
                state = Off;
                break;

            default:
                state = Wait_cmd;
                break;
        }
    }
};

EState Robot::getState() 
{
    return this->state;
};

void Robot::setState(EState nState) 
{
    state = nState;
};

class GetCommand 
{
public:
virtual ~GetCommand() {};
    virtual void getEvent() = 0;
};

class NetworkStrategy : public GetCommand 
{

};

class KeyboardStrategy : public GetCommand 
{
    void getEvent() override
    {
        int str;
        cin >> str;
        if (str >= Off && str <= Error) 
        {
            EState state = static_cast<EState>(str);
        }
        else
        {
            cout << "Wrong command!";
        }

    }
};

int main() 
{
    Robot paintRobot = new Robot(new KeyboardStrategy);
    paintRobot.setState(Wait_cmd);
    
    while (paintRobot.getState() != Off) 
    {
        paintRobot.processEvent(paintRobot.getState());
    }

    return 0;
}