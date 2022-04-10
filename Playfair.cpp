#include "Playfair.h"
#include <iostream>


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

	cipherKey = key;
	set_matrix(cipherKey);

	return true;
}

//run this assuming that the setKey function returns true, meaning that all elements of the key entered
//is an upper or lowercase_index character
void Playfair::set_matrix(const string& key)
{
	string no_dup_key = "";
	bool dup = false;
	string matrix[5][5];
	int row = 0, col = 0;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";

	//converts all characters to lowercase
	for(int lowercase_index; lowercase_index < key.length(); lowercase_index++)
	{
			tolower(key[lowercase_index]);
	}

	//removes duplicates from the key and puts it into no_dup_key
	for(int keyIndex = 0; keyIndex < key.length(); ++keyIndex)
	{
		dup = false;
		for(int dupKeyI = 0; dupKeyI < no_dup_key.length(); ++dupKeyI)
		{
			if(key[keyIndex] == no_dup_key[dupKeyI])
			{
				dup = true;
			}
		}

		if(!dup)
		{
			no_dup_key += key[keyIndex];
		}
	}


	//for each character in no_dup_key (key with duplicates removed), begins to add it to the playfair matrix
	for(int no_dup_key_index = 0; no_dup_key_index < no_dup_key.length(); no_dup_key_index++)
	{
		//if there is space in the current row of the matrix, populates it column by column
		if(col < 5)
		{
			//accounts for i/j case
			if(no_dup_key[no_dup_key_index] == 'i' || no_dup_key[no_dup_key_index] == 'j')
			{
					matrix[row][col] = "i/j";
					col++;

					alphabet.erase(alphabet.find("i"), 1);
					alphabet.erase(alphabet.find("j"), 1);
			}

			else
			{
				matrix[row][col] = no_dup_key[no_dup_key_index];
				col++;

				//removes character appended to the matrix from the alphabet
				alphabet.erase(alphabet.find(no_dup_key[no_dup_key_index]),1);
			}
		}

		//if there is no space in the current row of the matrix, moves down one row, resets the column index
		else
		{
			row++;
			col = 0;

			//accounts for i/j case
			if(no_dup_key[no_dup_key_index] == 'i' || no_dup_key[no_dup_key_index] == 'j')
			{
					matrix[row][col] = "i/j";
					col++;

					alphabet.erase(alphabet.find("i", 1));
					alphabet.erase(alphabet.find("j", 1));
			}

			else
			{
				matrix[row][col] = no_dup_key[no_dup_key_index];
				col++;

				//removes character appended to the matrix from the alphabet
				alphabet.erase(alphabet.find(no_dup_key[no_dup_key_index]), 1);
			}
		}
	}

	//start filling in rest of the matrix via alphabet
	while(alphabet.length() > 0)
	{
		if(col < 5)
		{
			//accounts for i/j case
			if(alphabet[0] == 'i' || alphabet[0] == 'j')
			{
				matrix[row][col] = "i/j";
				col++;

				alphabet.erase(0, 2);
			}

			else
			{
				matrix[row][col] = alphabet[0];
				col++;

				alphabet.erase(0,1);
			}
		}

		//if there is no space in the current row of the matrix, moves down one row, resets the column index
		else
		{
			row++;
			col = 0;

			//accounts for i/j case
			if(alphabet[0] == 'i' || alphabet[0] == 'j')
			{
					matrix[row][col] = "i/j";
					col++;

					alphabet.erase(0, 2);
			}

			else
			{
				matrix[row][col] = alphabet[0];
				col++;

				//removes character appended to the matrix from the alphabet
				alphabet.erase(0,1);
			}
		}
	}

	copy(&matrix[0][0], &matrix[0][0] + 5 * 5, &playfair_matrix[0][0]);
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
			if(placeholder.length() % 2 == 0)
			{
				if(plaintext.substr(plaintext_index, 3).compare("i/j") == 0)
				{
					placeholder += "i";
					plaintext_index += 2;
				}
				else
					placeholder += plaintext[plaintext_index];
			}

			//checks to see if the 2nd letter in the plaintext is a duplicate of the previous letter
			else
			{
				if(plaintext.substr(plaintext_index, 3).compare("i/j") == 0)
				{
					if(plaintext[plaintext_index] == plaintext[plaintext_index - 1])
					{
							//if duplicate letters in a sequence, turn 2nd letter into x and adds it to reformatted_plaintext
							placeholder.append("x");
							reformatted_plaintext.push_back(placeholder);

							//next clear placeholder and append the original
							placeholder = "";
							placeholder += "i";
							plaintext_index += 2;
					}

					else
						placeholder += "i";
						plaintext_index += 2;
				}

				else
				{
					if(plaintext[plaintext_index] == plaintext[plaintext_index - 1])
					{
							//if duplicate letters in a sequence, turn 2nd letter into x and adds it to reformatted_plaintext
							placeholder.append("x");
							reformatted_plaintext.push_back(placeholder);

							//next clear placeholder and append the original
							placeholder = "";
							placeholder += plaintext[plaintext_index];
					}

					else
					{
						placeholder += plaintext[plaintext_index];
						reformatted_plaintext.push_back(placeholder);
						placeholder = "";
					}
				}
			}
		}

		//checks to see if the length of the plaintext is even or no_dup_key_index, if it's odd add an x to the end
		if(placeholder.length() % 2 == 1)
		{
			placeholder.append("x");
			reformatted_plaintext.push_back(placeholder);
		}

/*--------------------------------------end converts the plaintext into 2 char chunks---------------------------------------*/

/*--------------------------------------start plaintext to ciphertext conversion via matrix---------------------------------*/

		int row_1 = 0, col_1 = 0, row_2 = 0, col_2 = 0;
		string cipher_text = "";

		for(int vector_index = 0; vector_index < reformatted_plaintext.size(); vector_index++)
		{
			for(int mRow = 0; mRow < 5; ++mRow)
			{
				for(int mCol = 0; mCol < 5; ++mCol)
				{
					if(playfair_matrix[mRow][mCol].compare("i/j") == 0)
					{
						if(reformatted_plaintext[vector_index][0] == 'i' || reformatted_plaintext[vector_index][0] == 'j')
						{
							row_1 = mRow;
							col_1 = mCol;
						}
					}

					else if(playfair_matrix[mRow][mCol].compare(reformatted_plaintext[vector_index].substr(0,1)) == 0)
					{
							row_1 = mRow;
							col_1 = mCol;
					}
				}
			}

			//searches for the location of the second character of the block in the matrix
			for(int mRow = 0; mRow < 5; ++mRow)
			{
				for(int mCol = 0; mCol < 5; ++mCol)
				{

					if(playfair_matrix[mRow][mCol].compare("i/j") == 0)
					{
						if(reformatted_plaintext[vector_index][1] == 'i' || reformatted_plaintext[vector_index][1] == 'j')
						{
							row_2 = mRow;
							col_2 = mCol;
						}
					}

					else if(playfair_matrix[mRow][mCol].compare(reformatted_plaintext[vector_index].substr(1)) == 0)
					{
							row_2 = mRow;
							col_2 = mCol;
					}
				}
			}

			//If both letters fall into the same ROW
			if(row_1 == row_2)
	    {
        cipher_text += playfair_matrix[row_1][(col_1+1) % 5];
	      cipher_text += playfair_matrix[row_2][(col_2+1) % 5];
	    }
			//If both letters fall into the same COL
			else if(col_1 == col_2)
			{
				cipher_text += playfair_matrix[(row_1+1) % 5][col_1];
	      cipher_text += playfair_matrix[(row_2+1) % 5][col_2];
			}
			else
			{
				cipher_text += playfair_matrix[row_1][col_2];
				cipher_text += playfair_matrix[row_2][col_1];
			}
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

	vector<string> reformatted_plaintext;
	string placeholder = "";

	for(int plaintext_index = 0; plaintext_index < cipherText.length(); plaintext_index++)
	{
		if(placeholder.length() % 2 == 0)
		{
			if(cipherText.substr(plaintext_index, 3).compare("i/j") == 0)
			{
				placeholder += "i";
				plaintext_index += 2;
			}
			else
				placeholder += cipherText[plaintext_index];
		}

		//checks to see if the 2nd letter in the plaintext is a duplicate of the previous letter
		else
		{
			if(cipherText.substr(plaintext_index, 3).compare("i/j") == 0)
			{
				if(cipherText[plaintext_index] == cipherText[plaintext_index - 1])
				{
						//if duplicate letters in a sequence, turn 2nd letter into x and adds it to reformatted_plaintext
						placeholder.append("x");
						reformatted_plaintext.push_back(placeholder);

						//next clear placeholder and append the original
						placeholder = "";
						placeholder += "i";
						plaintext_index += 2;
				}

				else
					placeholder += "i";
					plaintext_index += 2;
			}

			else
			{
				if(cipherText[plaintext_index] == cipherText[plaintext_index - 1])
				{
						//if duplicate letters in a sequence, turn 2nd letter into x and adds it to reformatted_plaintext
						placeholder.append("x");
						reformatted_plaintext.push_back(placeholder);

						//next clear placeholder and append the original
						placeholder = "";
						placeholder += cipherText[plaintext_index];
				}

				else
				{
					placeholder += cipherText[plaintext_index];
					reformatted_plaintext.push_back(placeholder);
					placeholder = "";
				}
			}
		}
	}

	//checks to see if the length of the plaintext is even or no_dup_key_index, if it's odd add an x to the end
	if(placeholder.length() % 2 == 1)
	{
		placeholder.append("x");
		reformatted_plaintext.push_back(placeholder);
	}

	int row_1 = 0, col_1 = 0, row_2 = 0, col_2 = 0;
	string plaintext = "";

	for(int vector_index = 0; vector_index < reformatted_plaintext.size(); vector_index++)
	{
		for(int mRow = 0; mRow < 5; ++mRow)
		{
			for(int mCol = 0; mCol < 5; ++mCol)
			{
				if(playfair_matrix[mRow][mCol].compare("i/j") == 0)
				{
					if(reformatted_plaintext[vector_index][0] == 'i' || reformatted_plaintext[vector_index][0] == 'j')
					{
						row_1 = mRow;
						col_1 = mCol;
					}
				}

				else if(playfair_matrix[mRow][mCol].compare(reformatted_plaintext[vector_index].substr(0,1)) == 0)
				{
						row_1 = mRow;
						col_1 = mCol;
				}
			}
		}

		//searches for the location of the second character of the block in the matrix
		for(int mRow = 0; mRow < 5; ++mRow)
		{
			for(int mCol = 0; mCol < 5; ++mCol)
			{

				if(playfair_matrix[mRow][mCol].compare("i/j") == 0)
				{
					if(reformatted_plaintext[vector_index][1] == 'i' || reformatted_plaintext[vector_index][1] == 'j')
					{
						row_2 = mRow;
						col_2 = mCol;
					}
				}

				else if(playfair_matrix[mRow][mCol].compare(reformatted_plaintext[vector_index].substr(1)) == 0)
				{
						row_2 = mRow;
						col_2 = mCol;
				}
			}
		}

		//If both letters fall into the same ROW
		if(row_1 == row_2)
		{
			plaintext += playfair_matrix[row_1][(5 + col_1-1) % 5];
			plaintext += playfair_matrix[row_2][(5 + col_2-1) % 5];
		}

		//If both letters fall into the same COL
		else if(col_1 == col_2)
		{
			plaintext += playfair_matrix[(5 + row_1-1) % 5][col_1];
			plaintext += playfair_matrix[(5 + row_2-1) % 5][col_2];
		}

		else
		{
			plaintext += playfair_matrix[row_1][col_2];
			plaintext += playfair_matrix[row_2][col_1];
		}
	}

	return plaintext;
}
