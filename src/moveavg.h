#ifndef _MOVEAVG_H_
#define _MOVEAVG_H_

#include <Arduino.h>
class Dataobj
{
public:
    Dataobj *prv;
    Dataobj *next;
    float value;
    int id = 0;
};

class MoveAvg
{
private:
    int size;
    int id = 0;
    float total = 0;
    Dataobj *data;
    Dataobj *index;
    Dataobj *first;

public:
    MoveAvg(int s)
    {
        this->total = 0;
        this->setsize(s);
    }
    MoveAvg()
    {
        this->total = 0;
        this->size = 0;
    }

    void setsize(int s)
    {
        this->size = s;
        this->data = NULL;
        for (int i = 0; i < size; i++)
        {
            if (this->data == NULL)
            {
#ifdef MOVEDEBUG
                Serial.println("first  object");
#endif
                this->data = new Dataobj();
                this->data->prv = NULL;
                this->data->next = NULL;
                this->data->value = 0;
                this->data->id = id++;
                this->first = data;
                this->index = data;
#ifdef MOVEDEBUG
                Serial.printf("\n1 pre %p  object %p  next %p \n", this->data->prv, this->data, this->data->next);
#endif
            }
            else
            {
#ifdef MOVEDEBUG
                Serial.println("new object");
#endif
                Dataobj *n = new Dataobj();
                n->value = 0;
                this->index = n;
                this->data->next = n;
                n->prv = this->data;
                n->next = NULL;
                n->id = id++;
                this->data = n;
#ifdef MOVEDEBUG
                Serial.printf("\npre %p  object %p  next %p \n", this->index->prv, this->index, this->index->next);
#endif
            }

            this->data->value = 0;
        }
    }
    Dataobj *getFirst()
    {
        return this->first;
    }
    float getValue()
    {
        return this->index->value;
    }
    void setValue(float v)
    {
        this->index->value = v;
    }
    int getSize()
    {
        return size;
    }
    void pushValue(float v)
    {

#ifdef MOVEDEBUG
        Serial.printf("\nset id:%d at %p current value:%f total : %f ", this->index->id, this->index, this->index->value, this->total);
#endif

        this->total = this->total - this->index->value;
        this->index->value = v;
        this->total = this->total + v;
#ifdef MOVEDEBUG
        Serial.printf(" set new  id:%d at %p current value:%f total : %f\n", this->index->id, this->index, this->index->value, this->total);
#endif
        if (this->index->next != NULL)
        {
            this->index = this->index->next;
        }
        else
        {
            this->index = this->first;
        }
    }
    float getTotal()
    {
        return this->total;
    }
};

#endif