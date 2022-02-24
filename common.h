#ifndef COMMON_H
#define COMMON_H

#include <array>
#include <memory>
#include <QMetaType>

#define MATW 40
#define MATH 40

typedef unsigned char Byte;
typedef unsigned short UShort;
typedef unsigned int UINT;
typedef unsigned long long UINT64;

struct Cell
{
    Cell(UShort w = 0) : water(w) {}
    UShort water;
};

struct MSize
{
    UShort h;
    UShort w;
    MSize(UShort H, UShort W) :
        h(H), w(W) {}
};

struct Point
{
    short x;
    short y;
    Point(short x=0, short y=0) : x(x), y(y) {}
};

struct MaxMin
{
    MaxMin(int max = -1, int min = -1):
        max(max), min(min) {}
    int max;
    int min;
};

typedef std::array<std::array<Cell, MATH>, MATW> CellMatrix;

class GMatrix
{
public:
    CellMatrix mat;

public:
    GMatrix(UINT ind) : index(ind) {}
    UINT getIndex()const {return index;}
    std::array<Cell, MATH>& operator[](int y)
    {return mat[y % MATH];}

    const MaxMin &getMMWater() const;
    void setMMWater(const MaxMin &newMMWater);

private:
        UINT index;
        MaxMin MMWater;

};

inline const MaxMin &GMatrix::getMMWater() const
{
    return MMWater;
}

inline void GMatrix::setMMWater(const MaxMin &newMMWater)
{
    MMWater = newMMWater;
}

typedef std::shared_ptr<GMatrix> PtrGMat;
Q_DECLARE_METATYPE(PtrGMat)
#endif // COMMON_H
