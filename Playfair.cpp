#include "Playfair.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
{
	//iterates through the key and checks to see if there are invalid characters
	if((key.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos) == false)
	{
			return false;
	}

	return true;
}

//run this assuming that the setKey function returns true, meaning that all elements of the key entered
//is an upper or lowercase_index character
void Playfair::set_matrix(const string& key)
{
	std::string no_dup_key = "";
	vector<std::string> letter_list;

	//converts all characters to lowercase
	for(int lowercase_index; lowercase_index < key.length(); lowercase_index++)
	{
			if(key.at(lowercase_index) > 64 && key.at(lowercase_index) < 91)
					key.at(lowercase_index) += 32;
	}

	//removes duplicates from the key and puts it into no_dup_key
	for(int key_index = 0; key_index < key.length(); key_index++)
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

	string matrix[5][5];
	int x = 0, y = 0;
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	//for each character no no_dup_key (key with duplicates removed), begins to add it to the playfair matrix
	for(int no_dup_key_index = 0; no_dup_key_index < no_dup_key.length(); no_dup_key_index++)
	{
			//if there is space in the current row of the matrix, populates it column by column
			if(x < 5)
			{
					//accounts for i/j case
					if(no_dup_key.at(no_dup_key_index) == "i" || no_dup_key.at(no_dup_key_index) == "j")
					{
							matrix[x][y] = "i/j";
							x++;

							alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
							alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

							continue;
					}

					matrix[x][y] = no_dup_key.at(no_dup_key_index);
					x++;

					//removes character appended to the matrix from the alphabet
					alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), no_dup_key.at(no_dup_key_index)), alphabet.end());
			}

			//if there is no space in the current row of the matrix, moves down one row, resets the column index
			if(x == 5)
			{
					//accounts for i/j case
					if(no_dup_key.at(no_dup_key_index) == "i" || no_dup_key.at(no_dup_key_index) == "j")
					{
							matrix[x][y] = "i/j";
							y++;
							x = 0;

							alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
							alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

							continue;
					}

					matrix[x][y] = no_dup_key.at(no_dup_key_index);
					y++;
					x = 0;

					//removes character appended to the matrix from the alphabet
					alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), no_dup_key.at(no_dup_key_index)), alphabet.end());
			}
		}

		//start filling in rest of the matrix via alphabet
		for(int alphabet_index = 0; alphabet_index < alphabet.length(); alphabet_index++)
		{
				if(x < 5)
				{
						//accounts for i/j case
						if(alphabet.at(alphabet_index) == "i" || alphabet.at(alphabet_index) == "j")
						{
								matrix[x][y] = "i/j";
								x++;

								alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
								alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

								continue;
						}

						matrix[x][y] = alphabet.at(alphabet_index);
						x++;

						alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), alphabet.at(alphabet_index)), alphabet.end());
				}

				if(x == 5)
				{
						//accounts for i/j case
						if(alphabet.at(alphabet_index) == "i" || alphabet.at(alphabet_index) == "j")
						{
								matrix[x][y] = "i/j";
								y++;
								x = 0;

								alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
								alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

								continue;
						}

						matrix[x][y] = no_dup_key.at(no_dup_key_index);
						y++;
						x = 0;

						//removes character appended to the matrix from the alphabet
						alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), alphabet.at(alphabet_index)), alphabet.end());
				}

		}

		playfair_matrix = matrix;
}

/*
returns the playfair_matrix public data member of playfair class
*/
string* Playfair::get_matrix(string matrix[][])
{
		return playfair_matrix;
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
