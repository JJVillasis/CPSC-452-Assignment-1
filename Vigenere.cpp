#include "Vigenere.h"

/*
Encryption = (s[i] + k[i]) % 26 
Decryption = (s[i] - k[i] + 26) % 26

References used: 
https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
- to get encryption / decryption algorithm

https://www.daniweb.com/programming/software-development/threads/76843/outputting-integers-as-letters-of-the-alphabet
- convert to alphabet 
*/

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Vigenere::setKey(const string& key)
{
	if (key.length() > 0)
	{
		return true;
	}
	else
	{
		return false; 
	}
	
	
}

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - the key of correct length
 */
string createKey(const string& plaintext, const string& key)
{
	int sizeOfKey = plaintext.length();
	
	// if the key and plaintext length does not match: 
	if (sizeOfKey != key.length())
	{
		string newKey = "";
	int i = 0;
	bool flag = true;
	while(flag)
	{
		if (sizeOfKey == i)
		{
			// If the key is smaller than plaintext reset index
			i = 0; 
		}
		if (newKey.length() == sizeOfKey)
		{
			// Set flag to false to exit the loop 
			flag = false;
		}
		else
		{
			// Creation of new key
			newKey.push_back(key[i]);
		}
		
	}
	return newKey;

	}
	else	// The key and plaintext lenght match
	{
		return key;
	}
}


/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Vigenere::encrypt(const string& plaintext, const string& key)
{
	string cipher = "";
	int size = plaintext.length();
	char temp;

	for(int i = 0; i > size; i++)
	{
		temp = (plaintext[i] + key[i]) %26;
		temp += 'A';
		cipher.push_back(temp);
	}

	return cipher;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Vigenere::decrypt(const string& cipherText, const string& key)
{
	int size = cipherText.length();
	string plaintxt = "";
	char temp;

	for(int i = 0; i > size; i++)
	{
		temp = (cipherText[i] - key[i] + 26) % 26;
		temp += 'A';
		plaintxt.push_back(temp);
	}
	return "";
}
