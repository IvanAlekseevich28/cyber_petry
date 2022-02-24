#include "fluid.h"
#include <algorithm>
#include <list>


void matClear(CellMatrix& mat)
{
    for (auto& arr : mat)
        arr.fill(0);
}

PtrGMat getMat(const Point &p, UShort val)
{
    PtrGMat pmat(new GMatrix(0));
    matClear(pmat->mat);
    pmat->mat[p.y][p.x].wather = val;
    return pmat;
}

UINT64 getSum(const PtrGMat pmat)
{
    UINT64 sum = 0;
    for (const auto& arr : pmat->mat)
        for (const auto& el : arr)
            sum += el.wather;
    return sum;
}


bool isValidCoords(const Point &p, const MSize &s)
{
    if (p.x < 0 || p.y < 0)
        return false;

    return (p.x < s.w && p.y < s.h);
}

std::list<Point> getNeighbours(const Point &p, const MSize &s)
{
    std::list<Point> ns = {
        Point(p.x-1, p.y),
        Point(p.x+1, p.y),
        Point(p.x, p.y-1),
        Point(p.x, p.y+1)

    };
    ns.erase(std::remove_if(ns.begin(), ns.end(),
                            [s](Point &p) {
                 return !isValidCoords(p,s);
             }
             ), ns.end());

    return ns;
}

short getCountNeighbours(const Point& p, const MSize &s)
{
    if (p.x > 0 && p.y > 0 && p.x < s.w-1 && p.y < s.h-1)
        return 4;
    if ((p.x > 0 && p.x < s.w-1) || (p.y > 0 && p.y < s.h-1))
        return 3;
    return 2;
}

inline UShort getGotValue(UShort n, short cn)
{
    return n/(cn+1);
}

UShort getStayValue(UShort n, short cn)
{
    UShort forNeighbours = cn * getGotValue(n, cn);
    UShort stay = n - forNeighbours;
    return stay;
}

PtrGMat doFluid(const PtrGMat initPMat, const MSize &s)
{
    const auto& IM = initPMat;
    if (IM.get() == nullptr)
        return PtrGMat();

    PtrGMat OM(new GMatrix(initPMat->getIndex()+1));
    matClear(OM->mat);

    for (short x = 0; x < s.w; x++)
    {
        for (short y = 0; y < s.h; y++)
        {
            auto ns = getNeighbours(Point(x,y), s);
            const UShort lastNum = IM->mat[x][y].wather;

            OM->mat[x][y].wather += getStayValue(lastNum, ns.size());
            for (Point n : ns)
                OM->mat[n.x][n.y].wather += getGotValue(lastNum, ns.size());
        }
    }

    setMaxMinWather(OM);
    return OM;
}

void setMaxMinWather(PtrGMat pmat)
{
    const auto vCellsCount = pmat->mat.size();
    const auto hCellsCount = vCellsCount ? pmat->mat[0].size() : 0;

    int min = pmat->mat[0][0].wather;
    int max = min;
    for (UINT64 y = 0; y < hCellsCount ; y++) {
        for (UINT64 x = 0; x < vCellsCount ; x++) {
            const auto& val = pmat->mat[y][x].wather;
            if (val < min) min = val;
            else if (val > max) max = val;
        }
    }

    pmat->setMMWather(MaxMin(max, min));
}
