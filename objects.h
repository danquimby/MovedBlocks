#ifndef OBJECTS_H
#define OBJECTS_H

struct IDrawaibleObjects {
    virtual void Render() = 0;
    virtual void Process() = 0;
};

#endif // OBJECTS_H