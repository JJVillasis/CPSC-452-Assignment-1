#include "Playfair.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
{
		std::string no_dup_key = "";
		vector<std::string> letter_list;
		bool letter_checker;

		//iterates through the key and checks to see if there are invalid characters
		if((key.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos) == false)
		{
				return false;
		}

		//removes duplicates from the key and puts it into no_dup_key
		for(int key_index = 0; key_index < key.length(); index++)
		{
				if(letter_list.empty())
				{
						no_dup_key.append(key.at(key_index));
				}

				for(int letter_list_index = 0; letter_list_index < letter_list.size(); letter_list_index++)
				{
						//if the current letter at the key is in the list index, it stops iterating through the list index
						if(key.at(key_index) == letter_list.at(letter_list_index))
						{
							break;
						}
						if(key.at(key_index) != letter_list.at(letter_list_index))
						{
							no_dup_key.append(key.at(key_index));
						}
				}
		}

	return true;
}




/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Playfair::encrypt(const string& plaintext)
{


	return "";
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText)
{
	return "";

}
