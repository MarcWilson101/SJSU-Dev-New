#include "stdio.h"

class mp3
{

private:
    
public:
    void mp3Init(uint8_t volumeUpper, uint8_t volumeLower);

    bool checkDREQ();

    void selectCS();

    void deselectCS();

    void selectDCS();

    void deselectDCS();

};