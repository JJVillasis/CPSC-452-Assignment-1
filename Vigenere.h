#ifndef VIGENERE_H
#define VIGENERE_H

#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include "CipherInterface.h"

using namespace std;

/**
 * This class implements the Vigenere cipher.
 * The class extends the abstract class
 * CipherInterface.
 */

class Vigenere: public CipherInterface
{
	/** The public members **/
	public:
		/**
		 * The default constructor
		 */
		Vigenere();

		/**
		 * Return the key
		 * @return - Return the protected member v_key value
		 */
		virtual string getKey();

		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual void setKey(const string& plaintext, const string& key);

		/**
		 * Encrypts a plaintext string
		 * @param plaintext - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual string encrypt(const string& plaintext, const string& key);

		/**
		 * Decrypts a string of ciphertext
		 * @param ciphertext - the ciphertext
		 * @return - the plaintext
		 */
		virtual string decrypt(const string& ciphertext, const string& key);

		/* The protected members */
	protected:
	string v_key;
};

#endif
