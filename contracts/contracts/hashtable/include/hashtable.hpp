#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

CONTRACT hashtable : public contract {
public:
using contract::contract;

ACTION issue(name from, name assigned_producer, const string &strain, const string &genomehash,
             const string &genomefile, uint32_t time_in_seconds);

ACTION transfer(name from, name to, string id, string memo);

ACTION clear();

private:
TABLE gan
        {
                uint64_t id;
        name from;
        name assigned_producer;
        string strain;
        string genomehash;
        string genomefile;
        time_point_sec timestamp;

        // defines the primary key
        auto primary_key() const { return id; }
        uint64_t by_time() const { return timestamp.sec_since_epoch(); }

        // need to define how to (de)serialize this structure
        // otherwise saving data will produce a WASM Runtime Error
        EOSLIB_SERIALIZE(gan, (id)(from)(assigned_producer)(strain)(genomehash)(genomefile)(timestamp))
        };

typedef eosio::multi_index<
        "gans"_n,
        gan,
        indexed_by<"time"_n, const_mem_fun<gan, uint64_t, &gan::by_time>>>
gans;
};