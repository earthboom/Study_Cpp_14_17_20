#include "stdafx.h"

enum class COLOR { RED, GREEN, BLUE };
enum class JOB { WARRIOR, ARCHER, WIZARD };

enum class ALTITUDE : char
{
    HIGH = 'h',
    LOW = 'l'
};

std::ostream& operator<<(std::ostream& os, ALTITUDE _altitude)
{
    return os << static_cast<char>(_altitude);
}

int main(void)
{
    COLOR color = COLOR::GREEN;
    JOB job = JOB::WIZARD;

    int colorNum = static_cast<int>(color);
    int jobNum = static_cast<int>(job);

    std::cout << "Color Number : " << colorNum << std::endl;
    std::cout << "Job Number : " << jobNum << std::endl;

    ALTITUDE altitude = ALTITUDE::HIGH;

    std::cout << "Altitude : " << altitude << std::endl;

    return 0;
}
