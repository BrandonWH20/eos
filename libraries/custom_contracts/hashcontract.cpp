//
// Created by Brandon Prof on 2/26/22.
//
#include <eosio/eosio.hpp>
#include "hashcontract.h"

using namespace eosio;
using namespace std;

CONTRACT hashcontract : Public contract {
    public :
        ACTION hashItUp(name user){
        print("Hello world, ", user, "!" )

        TABLE:
    }

    private:
};