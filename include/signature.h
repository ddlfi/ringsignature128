#include "rain.h"
#include "random_oracle.h"
#include "randomness.h"
#include "universal_hashing.h"
#include "utils.h"
#include "vole.h"
#include "path_prove.h"

class Signature {
   public:
    const int key_num_ = 8;
    const int tree_node_num_ = 16;
    const int tree_node_byte_size_ = 32;
    const int lambda_ = 256;
    const int lambda_bytes_ = 32;
    const int iv_size_ = 16;

   public:
    Signature()
        : pkey_(key_num_, std::vector<uint8_t>(tree_node_byte_size_)),
          tree_(tree_node_num_, std::vector<uint8_t>(tree_node_byte_size_)) {
        keygen();
        treegen();
        params_.lambda = 256;
        params_.k1 = 8;
        params_.k0 = 8;
        params_.tau0 = 0;
        params_.tau1 = 32;
        params_.tau = 32;
    }
    void sign(const uint8_t signer_index, const std::vector<uint8_t>& msg);
    void verify();

   private:
    void keygen();

    void treegen();

    void hash_1(const std::vector<uint8_t>& input_0,
                const std::vector<uint8_t>& input_1,
                const std::vector<uint8_t>& s_byte,
                std::vector<uint8_t>& output, uint8_t* witness, bool flag);

    void hash_pk_msg(const std::vector<uint8_t>& msg, std::vector<uint8_t>& mu);

    void hash_challenge_1(const std::vector<uint8_t>& mu,
                          const std::vector<uint8_t>& hcom,
                          const std::vector<uint8_t>& c,
                          const std::vector<uint8_t>& iv,
                          std::vector<uint8_t>& chall_1, unsigned int ell,
                          unsigned int tau);

    void gen_rootkey_iv(const std::vector<uint8_t>& mu,
                        const uint8_t signer_index,
                        std::vector<uint8_t>& rootkey,
                        std::vector<uint8_t>& iv);

    public:
    void gen_witness(uint8_t* witness, uint8_t index);

   private:
    const std::vector<std::vector<uint8_t>> skey_ = {
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0},
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1},
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2},
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3},
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf4},
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5},
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6},
        {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7}};

    const std::vector<uint8_t> rain_msg_ = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    const std::vector<uint8_t> s_0_ = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    const std::vector<uint8_t> s_1_ = {
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    std::vector<std::vector<uint8_t>> pkey_;

    std::vector<std::vector<uint8_t>> tree_;

    paramset_t params_;
};