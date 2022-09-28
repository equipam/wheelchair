//TODO #3 Identify axis boundaries (XY) on the joystick setup and map them to known scales


#include <tuple>

#define MIN_X 0
#define MAX_X 3.3
#define MIN_Y 0
#define MAX_X 3.3


struct JoystickBounds
{
    float minX = MIN_X;
    float maxX = MAX_X;
    float minY = MIN_X;
    float maxY = MAX_X;
};


class Joystick
{
private:
    JoystickBounds realBounds;
public:
    Joystick(JoystickBounds realBounds) {
        this->realBounds = realBounds;
    }
    std::tuple<float, float> joystickMapping(float vx, float vy){
        // vx and vy are real values from the joystick
        // returns normalized values of x and y on a tuple
        return std::tuple<float, float>(0,0);
    }
};




