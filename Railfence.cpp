#include "Railfence.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Railfence::setKey(const string& key)
{


	for(int x = 0; x < key.length(); x++)
			if(isalpha(key[x]))
				return false;

	cipherKey = stoi(key);

	if (cipherKey <= 0)
		return false;
	else
		return true;
}




/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Railfence::encrypt(const string& plaintext)
{
	// creating a matrix to hold the plaintext
	char railMatrix[cipherKey][plaintext.length()];

	// filling railMatrix with blank spaces
	for (int i=0; i < cipherKey; i++)
		for (int j=0; j < plaintext.length(); j++)
			railMatrix[i][j] = '\n';

	for (int i = 0; i < plaintext.length(); i++){
		// fill with the correct letter
		railMatrix[row][col++] = plaintext[i];

		// if we just filled the top or bottom row reverse direction
		if(row == 0 || row == cipherKey-1)
			direction = direction * (-1);

		// move onto next row
		row = row + direction;
	}

	string result;
	for (int i=0; i < cipherKey; i++)
		for (int j=0; j < plaintext.length(); j++)
			if (railMatrix[i][j] != '\n')
				result.push_back(railMatrix[i][j]);

	return result;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Railfence::decrypt(const string& cipherText)
{
	// creating a matrix to hold the cipherText
	char railMatrix[cipherKey][cipherText.length()];

	// filling railMatrix with blank spaces
	for (int i=0; i < cipherKey; i++)
		for (int j=0; j < cipherText.length(); j++)
			railMatrix[i][j] = '\n';
	
	for (int i=0; i < cipherText.length(); i++){
		// mark spaces that should hold text with a placeholder
		railMatrix[row][col++] = '*';

		// if we just filled the top or bottom row reverse direction
		if(row == 0 || row == cipherKey-1)
			direction = direction * (-1);

		//move onto next row
		row = row + direction;
	}

	// fill in the positions indicated with * with letters
	for(int i=0; i < cipherKey; i++)
		for(int j=0; j < cipherText.length(); j++)
			if(railMatrix[i][j] == '*')
				railMatrix [i][j] = cipherText[index++];

	row = col = 0;
	direction = -1;	

	string result;

	for (int i = 0; i < cipherText.length(); i++){
		result.push_back(railMatrix[row][col++]);
 
        if(row == 0 || row == cipherKey-1)
            direction = direction * (-1);
 
        row = row + direction;
	}

	return result;

}
