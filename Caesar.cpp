#include "Caesar.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Caesar::setKey(const string& key)
{
	for(int x = 0; x < key.length(); ++x)
	{
			if(isalpha(key[x]))
			{
				return false;
			}
	}

	cipherKey = stoi(key);
	return true;

}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Caesar::encrypt(const string& plaintext)
{
	string cipher = "";
	int size = plaintext.length();
	char temp;

	for(int x = 0; x < size; ++x)
	{
		temp = ((tolower(plaintext[x]) + cipherKey) - 97) % 26;
    temp += 'a';
    cipher.push_back(temp);
	}

	return cipher;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Caesar::decrypt(const string& cipherText)
{

	string plaintext = "";
	int size = cipherText.length();
	char temp;

	for(int x = 0; x < size; ++x)
	{
		temp = (26 + (tolower(cipherText[x]) - cipherKey) - 97) % 26;
    temp += 'a';
    plaintext.push_back(temp);
	}

	return plaintext;
}
