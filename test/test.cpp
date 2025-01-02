#include <Arduino.h>
#include <unity.h>
#define MOVEDEBUG 1
#include "moveavg.h"

void testAdd()
{
    Dataobj *p = new Dataobj();

    p->value = 1;
    p->next = NULL;
    p->prv = NULL;
    Dataobj *f = p;
    Dataobj *index = p;

    for (int i = 0; i < 10; i++)
    {
        Dataobj *n = new Dataobj();
        p->next = n;
        n->prv = p;
        n->next = NULL;
        n->value = i + 1;
        p = n;
        index = n;
    }
    Serial.printf("\nValue %f\n", index->value);
    if (index->next != NULL)
        Serial.printf("\nValue 2 %f\n", index->next->value);

    else

        Serial.printf("\nValue 3 %f\n", index->value);
    Serial.printf("\nValue 4 %f\n", f->value);
}
void setup()
{
    Serial.begin(9600);
    delay(2000);
    UNITY_BEGIN();

    // RUN_TEST(testAdd);
    MoveAvg ag(50);

    for (int i = 0; i < 200; i++)
        ag.pushValue(100.2 + i);

    Serial.printf("\nTotal %f\n", ag.getTotal()/ag.getSize());
    // Dataobj *n  = ag.getFirst();

    // for(int i=0;i<10;i++)
    // {
    //     if(n!=NULL)
    //     {
    //         Serial.printf("N data %f\n",n->data);
    //         n = n->next;
    //     }
    // }
    UNITY_END();
}

void loop()
{
    delay(1);
}