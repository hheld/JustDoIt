#ifndef TASKSORT_H
#define TASKSORT_H

#include "Task.h"

template<int col>
bool taskLessThan(Task *t1, Task *t2)
{
    Q_UNUSED(t1);
    Q_UNUSED(t2);

    return false;
}

template<int col>
bool taskGreaterThan(Task *t1, Task *t2)
{
    Q_UNUSED(t1);
    Q_UNUSED(t2);

    return false;
}

//----------------------------------------------------

template<> bool taskLessThan<0>(Task *t1, Task *t2)
{
    return t1->id() < t2->id();
}

template<> bool taskLessThan<1>(Task *t1, Task *t2)
{
    return t1->location() < t2->location();
}

template<> bool taskLessThan<2>(Task *t1, Task *t2)
{
    return t1->realm() < t2->realm();
}

template<> bool taskLessThan<3>(Task *t1, Task *t2)
{
    Q_UNUSED(t1);

    return t2->done();
}

template<> bool taskLessThan<4>(Task *t1, Task *t2)
{
    return t1->startDate() < t2->startDate();
}

template<> bool taskLessThan<5>(Task *t1, Task *t2)
{
    return t1->endDate() < t2->endDate();
}

template<> bool taskLessThan<6>(Task *t1, Task *t2)
{
    return t1->dueDate() < t2->dueDate();
}

template<> bool taskLessThan<7>(Task *t1, Task *t2)
{
    return t1->title() < t2->title();
}

template<> bool taskLessThan<8>(Task *t1, Task *t2)
{
    return t1->description() < t2->description();
}

//----------------------------------------------------

template<> bool taskGreaterThan<0>(Task *t1, Task *t2)
{
    return t1->id() > t2->id();
}

template<> bool taskGreaterThan<1>(Task *t1, Task *t2)
{
    return t1->location() > t2->location();
}

template<> bool taskGreaterThan<2>(Task *t1, Task *t2)
{
    return t1->realm() > t2->realm();
}

template<> bool taskGreaterThan<3>(Task *t1, Task *t2)
{
    Q_UNUSED(t1);

    return !t2->done();
}

template<> bool taskGreaterThan<4>(Task *t1, Task *t2)
{
    return t1->startDate() > t2->startDate();
}

template<> bool taskGreaterThan<5>(Task *t1, Task *t2)
{
    return t1->endDate() > t2->endDate();
}

template<> bool taskGreaterThan<6>(Task *t1, Task *t2)
{
    return t1->dueDate() > t2->dueDate();
}

template<> bool taskGreaterThan<7>(Task *t1, Task *t2)
{
    return t1->title() > t2->title();
}

template<> bool taskGreaterThan<8>(Task *t1, Task *t2)
{
    return t1->description() > t2->description();
}

#endif // TASKSORT_H
