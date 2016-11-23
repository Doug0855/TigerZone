#ifndef FARMER_H
#define FARMER_H

#include "Meeple.h"

class Farmer : public Meeple{
        Farmer();
        ~Farmer();

        //Farmer will always return false because a farmer can never be completed
      /*  int countPoints(const std::vector< std::vector<Tile> >& board, bool& complete) override;*/
};

#endif
