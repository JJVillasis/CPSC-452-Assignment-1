#include "Playfair.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
{
	//iterates through the key and checks to see if there are invalid characters
	for(int set_key_index = 0; set_key_index < key.length(); set_key_index++)
	{
  		if(!isalpha(key[set_key_index]))
  		{
	    return false;
	  	}
}

	return true;
}

//run this assuming that the setKey function returns true, meaning that all elements of the key entered
//is an upper or lowercase_index character
void Playfair::set_matrix(const string& key)
{
	string no_dup_key = "";
	vector<string> letter_list;

	//converts all characters to lowercase
	for(int lowercase_index; lowercase_index < key.length(); lowercase_index++)
	{
			key[index] = tolower(key[index]);
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
	string alphabet = "abcdefghijklmnopqrstuvwxyz";

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

							alphabet.erase(remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
							alphabet.erase(remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

							continue;
					}

					matrix[x][y] = no_dup_key.at(no_dup_key_index);
					x++;

					//removes character appended to the matrix from the alphabet
					alphabet.erase(remove(alphabet.begin(), alphabet.end(), no_dup_key.at(no_dup_key_index)), alphabet.end());
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

							alphabet.erase(remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
							alphabet.erase(remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

							continue;
					}

					matrix[x][y] = no_dup_key.at(no_dup_key_index);
					y++;
					x = 0;

					//removes character appended to the matrix from the alphabet
					alphabet.erase(remove(alphabet.begin(), alphabet.end(), no_dup_key.at(no_dup_key_index)), alphabet.end());
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

								alphabet.erase(remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
								alphabet.erase(remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

								continue;
						}

						matrix[x][y] = alphabet.at(alphabet_index);
						x++;

						alphabet.erase(remove(alphabet.begin(), alphabet.end(), alphabet.at(alphabet_index)), alphabet.end());
				}

				if(x == 5)
				{
						//accounts for i/j case
						if(alphabet.at(alphabet_index) == "i" || alphabet.at(alphabet_index) == "j")
						{
								matrix[x][y] = "i/j";
								y++;
								x = 0;

								alphabet.erase(remove(alphabet.begin(), alphabet.end(), "i"), alphabet.end());
								alphabet.erase(remove(alphabet.begin(), alphabet.end(), "j"), alphabet.end());

								continue;
						}

						matrix[x][y] = no_dup_key.at(no_dup_key_index);
						y++;
						x = 0;

						//removes character appended to the matrix from the alphabet
						alphabet.erase(remove(alphabet.begin(), alphabet.end(), alphabet.at(alphabet_index)), alphabet.end());
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

/*--------------------------------------start converts the plaintext into 2 char chunks---------------------------------------*/

		vector<string> reformatted_plaintext;
		string placeholder = "";

		for(int plaintext_index = 0; plaintext_index < plaintext.length(); plaintext_index++)
		{

				if(plaintext_index % 2 == 0)
				{
						placeholder.append(plaintext.at(plaintext_index));
				}

				//checks to see if the 2nd letter in the plaintext is a duplicate of the previous letter
				if(plaintext_index % 2 == 1)
				{
						if(plaintext.at(plaintext_index) == plaintext.at(plaintext_index - 1))
						{
								//if duplicate letters in a sequence, turn 2nd letter into x and adds it to reformatted_plaintext
								placeholder.append("x");
								reformatted_plaintext.push_back(placeholder);

								//next clear placeholder and append the original
								placeholder = "";
								placeholder.append(plaintext.at(plaintext_index));
						}
				}
		}

		//checks to see if the length of the plaintext is even or no_dup_key_index, if it's odd add an x to the end
		if(plaintext.length() % 2 == 1)
		{
			placeholder.append("x");
			reformatted_plaintext.push_back(placeholder);
		}

/*--------------------------------------end converts the plaintext into 2 char chunks---------------------------------------*/

/*--------------------------------------start plaintext to ciphertext conversion via matrix---------------------------------*/

		int x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0;
		int search_row = 0, search_column = 0;
		string cipher_text = "";

		for(int vector_index = 0; vector_index < reformatted_plaintext.size(); vector_index++)
		{
				//searches for the location of the first character of the block in the matrix
				if(playfair_matrix[search_row][search_column] == reformatted_plaintext.at(vector_index)).at(0))
				{
						x_1 = search_row;
						y_1 = search_column;
				}
				if(playfair_matrix[search_row][search_column] != reformatted_plaintext.at(vector_index)).at(0))
				{
						if(search_column == 5)
						{
								search_column = 0;
								search_row++;
						}
						if(search_column < 5)
						{
								search_column++;
						}
				}

				search_row = 0;
				search_column = 0;

				//searches for the location of the second character of the block in the matrix
				if(playfair_matrix[search_row][search_column] == reformatted_plaintext.at(vector_index).at(1))
				{
						x_2 = search_row;
						y_2 = search_column;
				}
				if(playfair_matrix[search_row][search_column] != reformatted_plaintext.at(vector_index).at(1))
				{
						if(search_column == 5)
						{
								search_column = 0;
								search_row++;
						}
						if(search_column < 5)
						{
								search_column++;
						}
				}

				search_row = 0;
				search_column = 0;

				cipher_text.append(playfair_matrix[x_2][y_1]);
				cipher_text.append(playfair_matrix[x_1][y_2]);
		}
/*----------------------------------------end plaintext to ciphertext conversion via matrix---------------------------------*/

		return cipher_text;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText)
{

		int x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0;
		int search_row = 0, search_column = 0;
		string plain_text = "";

		for(int cipher_text_index = 0; cipher_text_index < cipherText.size(); cipher_text_index++)
		{

				//for odd index to represent the end of the block
				if(cipher_text_index % 2 == 0)
				{

						if(playfair_matrix[search_row][search_column] == cipherText.at(cipher_text_index).at(cipher_text_index))
						{
								x_1 = search_row;
								y_1 = search_column;
						}
						if(playfair_matrix[search_row][search_column] != cipherText.at(cipher_text_index).at(cipher_text_index))
						{
								if(search_column == 5)
								{
										search_column = 0;
										search_row++;
								}
								if(search_column < 5)
								{
										search_column++;
								}
						}
				}

				search_row = 0;
				search_column = 0;

				//for even index to represent the end of the block
				if(cipher_text_index % 2 == 1)
				{
						if(playfair_matrix[search_row][search_column] == cipherText.at(cipher_text_index).at(cipher_text_index))
						{
								x_2 = search_row;
								y_2 = search_column;
						}
						if(playfair_matrix[search_row][search_column] != cipherText.at(cipher_text_index).at(cipher_text_index))
						{
								if(search_column == 5)
								{
										search_column = 0;
										search_row++;
								}
								if(search_column < 5)
								{
										search_column++;
								}
						}
				}

				search_row = 0;
				search_column = 0;

				plain_text.append(playfair_matrix[x_2][y_1]);
				plain_text.append(playfair_matrix[x_1][y_2]);
		}

		return plain_text;
}
