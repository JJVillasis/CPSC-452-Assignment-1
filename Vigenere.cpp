#include "Vigenere.h"
#include <cctype>
#include <iostream>

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
 * The default constructor
 */
Vigenere::Vigenere()
{
	v_key = "";
}

/**
 * Return the key
 * @return - Return the protected member v_key value
 */
string Vigenere::getKey()
{
	return v_key;
}

/**
 * Sets the key to use
 * @param key - the key to use
 * @param plaintext - the plaintext string
 * Create a valid key or if length of key matches plaintext key is valid
 */
void Vigenere::setKey(const string& plaintext, const string& key)
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
	v_key = newKey;

	}
	else	// The key and plaintext lenght match
	{
		v_key = key;
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

	for(int i = 0; i < size; i++)
	{
		temp = (toupper(plaintext[i]) + toupper(key[i])) %26;
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
string Vigenere::decrypt(const string& cipherText, const string& key)
{
	int size = cipherText.length();
	string plaintxt = "";
	char temp;

	for(int i = 0; i > size; i++)
	{
		temp = (toupper(cipherText[i]) - toupper(key[i]) + 26) % 26;
		temp += 'a';
		plaintxt.push_back(temp);
	}
	return "";
}
