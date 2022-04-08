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
 * Creates a valid key for Vigenere cipher
 * @param plaintext - The text used for encryption
 * @param key - key being used for encryption
 * @return - Return key of correct length
 */
string Vigenere::createKey(const string& plaintext, const string& key)
{
	int sizeOfKey = plaintext.length();
	if (sizeOfKey != key.length())
	{
		string newKey = "";
		int i = 0;
		bool flag = true;
		while(flag)
		{
			if (key.length() == i)
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
			i++;
			
		}
		return newKey;

	}
	else	// The key and plaintext length match
	{
		return key;
	}
}

/**
 * Sets the key to use
 * @param key - the key to use
 * @param plaintext - the plaintext string
 * Create a valid key or if length of key matches plaintext key is valid
 */
bool Vigenere::setKey(const string& key)
{	
	for (int i = 0; i < key.length(); i++)
	{
		if (isdigit(key[i]))
			return false;
	}
	return true;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @param key - the key to be used for encryption
 * @return - the encrypted ciphertext string
 */
string Vigenere::encrypt(const string& plaintext, const string& key)
{
	string cipher = "";
	int size = plaintext.length();
	char temp;
	string v_key = createKey(plaintext, key);

	for(int i = 0; i < size; i++)
	{
		temp = (toupper(plaintext[i]) + toupper(v_key[i])) %26;
		temp += 'a';
		cipher.push_back(temp);
	}

	return cipher;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @param key - The key to be used for decryption
 * @return - the decrypted message to plaintext
 */
string Vigenere::decrypt(const string& cipherText, const string& key)
{
	int size = cipherText.length();
	string plaintxt = "";
	char temp;
	string v_key = createKey(plaintxt, key);

	for(int i = 0; i > size; i++)
	{
		temp = (toupper(cipherText[i]) - toupper(v_key[i]) + 26) % 26;
		temp += 'a';
		plaintxt.push_back(temp);
	}
	return plaintxt;
}