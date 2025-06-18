#include "database.h"
#include <zlib.h>
#include <fstream>
#include <gcrypt.h>
#include "blob.h"


string Database::sha1(const string& data) {
    gcry_md_hd_t hd;
    gcry_md_open(&hd, GCRY_MD_SHA1, 0);
    gcry_md_write(hd, data.c_str(), data.size());

    unsigned char* hash = gcry_md_read(hd, GCRY_MD_SHA1);

    ostringstream oss;
    for (int i = 0; i < gcry_md_get_algo_dlen(GCRY_MD_SHA1); ++i)
        oss << hex << setw(2) << setfill('0') << (int)hash[i];

    gcry_md_close(hd);
    return oss.str();
}


