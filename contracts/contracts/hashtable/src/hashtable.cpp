/// @tiltle GAN (Genome assigned name) for managing tables
/// Brandon H
///
/// using
/// title eosio.nft public interface
/// dev See https://github.com/jafri/eosio.nft/blob/master/README.md

#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <set>
#include <string>

using namespace  eosio;
using namespace std;

// we should design eacb GAN to have 10 sequences used as a table/siblings.

// would allow us to create a family, basically they can be no different than 10% of the other 9
// This number should be reconsidered with further research.

// Tho goal of this contract is to create a set of each genome, each set

class [[eosio::contract("hashtable")]] hashtable : public eosio::contract {
public:
    using contract::contract

    TABLE gan
            {
            // Table row id
            // strain name
            // url to genome folder still massive file size right now.
            time_point_sec timestamp;
            uint64_t id;
            name    assigned_producer;
            string  strain;
            string  genomehash;
            string  genomefile;

            // Define primary key
            auto primary_key() const { return id; }
            uint64_t by_time() const { return timestamp.sec_since_epoch(); }

            // need to define how to (de)serialize this structure
            // otherwise saving data will produce a WASM Runtime Error
            // gan being a custom datatype "Genome assigned name"
            EOSLIB_SERIALIZE(gan, (id)(assigned_producer)(strain)(genomehash)(genomefile)(timestamp))
            };

    // define genomelist as the multi_index storing the genome
    // first argument is the table name
    // and must match the name of the table in the ABI
    // second argument is the struct used as a row in genomelist

    typedef eosio::multi_index<
            "gans"_n,
            gan,
            indexed_by<"time"_n, const_mem_fun < tweet, uint64_t, &gan::by_time>>>
    gans;

    /// Creates token with a symbol name for the specified issuer account.
    /// Throws if token with specified symbol already exists.
    /// @param issuer Account name of the token issuer
    /// @param symbol Symbol code of the token

    ACTION issue(name from, name assigned_producer, const string &strain, const string &genomehash, const string genomefile) {
        // authenticate 'from account to check gans integrity
        // will check if the action has the permission of 'from' account
        require_auth(from);

        // initialize table attributes
        // code is the contract account that owns the table
        name code = _self;

        // scope refers to the account that owns this data
        name scope = _slef;
        gans gans_table(code, scope.value)

        // place the genome assigned name from action
        // first arg pays for entry
        // need to authorize from paying account
        gans_table.emplace(from, [&](gan &t) {
            //increment key id
            t.id = gans_table.available_primary_key();
            t.from = from;
            t.strin = strain;
            t.genomehash = genomehash;
            t.genomefile = genomefile;
            t.timestamp = time_point_sec(time_in_seconds);

        });
        print("GAN from ", name(from), ": \n", "STRAIN: ", strain, "\n")
    }

    ACTION transfer(name from, name to, string id, string memo){

    }
};