#include <bits/stdc++.h>
#include <openssl/md5.h>
#include <openssl/evp.h>
#include <regex>

using namespace std;

// https://adventofcode.com/2015/day/4


std::string generateMD5(const std::string& input) {
	static EVP_MD_CTX* mdctx = nullptr;
	static const EVP_MD* md = nullptr;

	// Create the context and initialize it if it's not already initialized
	if (mdctx == nullptr) {
		mdctx = EVP_MD_CTX_new();
		md = EVP_md5();
	}
		EVP_DigestInit_ex(mdctx, md, nullptr);

	// Perform the digest calculation
	EVP_DigestUpdate(mdctx, input.c_str(), input.length());
	unsigned char digest[MD5_DIGEST_LENGTH];
	EVP_DigestFinal_ex(mdctx, digest, nullptr);

	// Clear the context for the next usage
	EVP_MD_CTX_reset(mdctx);

	// Convert the digest to hexadecimal string representation
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
		ss << std::setw(2) << static_cast<unsigned>(digest[i]);
	}

	return ss.str();
}




int main()
{	
	string hash = "";
    int i = 0;

    while(hash.substr(0, 6) != "000000")
	{
		string in = "ckczppom" + to_string(i++);
		hash = generateMD5(in);
	}

	std::cout << "hash: " << hash << '\n';
	printf("res: %d\n", i-1);
	return(0);
}

// g++ -lssl -lcrypto -O3 main.cpp && time ./a.out ; rm -f a.out