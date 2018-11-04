#include "randommoviegenerator.h"

int randomMovieGenerator::generateRandomNum()
{
    int num = 0;
    num = rand() % 9000000 + 1000000;


    return num;
}


QString randomMovieGenerator::getPrefix()
{
    int num = 0;
    num = rand() % 4;
    return prefix[num];
}

void randomMovieGenerator::setKeyValue()
{
    int num = generateRandomNum();
    QString s = QString::number(num);
    QString prefix = getPrefix();

    keyValue = "tt" + s;

}

QString randomMovieGenerator::getKeyValue()
{
    setKeyValue();
    return keyValue;
}
