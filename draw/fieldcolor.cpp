#include "fieldcolor.h"
#include "../core/engine/algs/threads.h"
#include <thread>

namespace Draw
{

PClrField initClrField(const unsigned w, const unsigned h, const QColor &base)
{
    PClrField pf(new ClrField);
    pf->reserve(w);
    for (unsigned i = 0; i < w; i++)
    {
        (*pf)[i].reserve(h);
        for (unsigned j = 0; j < h; j++)
            (*pf)[i][j] = base;
    }

    return pf;
}

static void Field2ClrThread(const Eng::Field& in, ClrField& out, const CellColor& cc, const Eng::ThreadInfo ti)
{
    const auto rng = Eng::getRngOfThread(ti, in.getMatrixLen());
    for (int i = rng.first; i < rng.second; i++)
    {
        int x = i % in.m.size();
        int y = i / in.m.size();

        out[x][y] = cc.getQColor(in.m[x][y]);
    }
}

PClrField convertField2Clr(const Eng::PField in, const CellColor& cc, const Eng::TCount countThreads)
{
    std::list<std::thread> threads;
    Eng::ThreadInfo ti(0, countThreads);
    PClrField pClrField = initClrField(in->m.size(), in->getH());

    for (Eng::TCount i = 0; i < countThreads; i++)
    {
        ti.indexThread = i;
        threads.push_back(
                    std::thread(
                        Field2ClrThread,
                        std::cref(*in),
                        std::ref(*pClrField),
                        std::cref(cc),
                        ti)
                    );
    }

    for (auto& thr : threads)
        thr.join();

    return pClrField;
}

}
