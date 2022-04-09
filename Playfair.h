#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <vector>   /* For vectors */
#include <string>   /* For C++ strings */
#include <stdio.h>  /* For standard I/O */
#include <stdlib.h> /* For miscellenous C functions */
#include <array>
#include "CipherInterface.h"

using namespace std;

/**
 * This class implements the playfair cipher.
 * The class extends the abstract class
 * CipherInterface.
 */

class Playfair: public CipherInterface
{
	/** The public members **/
	public:

		std::string key;
		std::string playfair_matrix[5][5];

		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual bool setKey(const string& key);

		/*
		takes the key provided and removes duplicates and then fills out the playfair matrix
		*/

		virtual void set_matrix(const string& key);

		/*
		returns the playfair_matrix
		*/
		//virtual string** get_matrix();

		/**
		 * Encrypts a plaintext string
		 * @param plaintext - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual string encrypt(const string& plaintext);

		/**
		 * Decrypts a string of ciphertext
		 * @param ciphertext - the ciphertext
		 * @return - the plaintext
		 */
		virtual string decrypt(const string& ciphertext);

		/**
		 * Prints the Playfair matrix
		 * @param fp - the file pointer
		 */
		void printMatrix(FILE* fp);

		/* The protected members */
	protected:


};

#endif
