/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

#include "file_system.h"

/*
 * @brief Default constructor
 */
FS::FS() {
  this->fat = new int[MAX_SIZE];
  this->directory = new directory_entry_t[MAX_SIZE];
  this->unit = new char[MAX_SIZE];

  for (int i = 0; i < MAX_SIZE; ++i) {
    this->unit[i] = '\0';
    this->fat[i] = EMPTY;
    this->directory[i].block = EMPTY;
  }
}

/*
 * @brief Destructor
 */
FS::~FS() {
  delete[] this->fat;
  delete[] this->unit;
  delete[] this->directory;
}

/*
 * @brief Creates a file
 *
 * @param name Indicates the name of the file to be addded
 * @return int The block in which the file was added. Returns -1 if no block was
 * found.
 */
int FS::create(std::string name) {
  int block = this->search_block(-1);
  int directory_pos = this->search_directory();
  if (directory_pos != -1 && block != -1) {
    this->directory[directory_pos].block = block;
    this->directory[directory_pos].name = name;
    this->directory[directory_pos].size = 1;
    time(&this->directory[directory_pos].date);
    // Is used as a special case of EOF to indicate an empty spot
    this->fat[block] = RESERVED;
  }
  return block;
}

/*
 * @brief Searches for the closest empty block or inside a block an empty
 * position
 *
 * @param position It is s the position of the last used block (if we want to
 * create a new file, position should be -1)
 * @return int The initial block of the empty block. Returns -1 if no block was
 * found.
 */
int FS::search_block(int position) {
  int block = -1;
  // Search for an empty block to reserve
  if (position == -1) {
    for (int i = 0; i < MAX_SIZE && block == -1; i += BLOCK_SIZE) {
      if (this->fat[i] == EMPTY) {
        block = i;
      }
    }
    // Find space in a block reserved
  } else {
    // Move inside the desired block size
    if (position % BLOCK_SIZE != 0) { // we are halfway through the block
      position = ((int) (position/BLOCK_SIZE)) * BLOCK_SIZE; // we get the beginning of block
    }
    for (int i = position; i < position + BLOCK_SIZE && block == -1; ++i) {
      if (this->fat[i] == EMPTY) {
        block = i;
      }
    }
    // Check if it was found, if not, then find an empty block
    if (block == -1) {
      block = search_block(-1); // if it is still -1, it is full
    }
  }
  return block;
}

/*
 * @brief Searches the closest empty directory
 *
 * @return int The directory found. Returns -1 if no directory was found.
 */
int FS::search_directory() {
  int directory_pos = -1;
  for (int i = 0; i < MAX_SIZE && directory_pos == -1; ++i) {
    if (this->directory[i].block == EMPTY) {
      directory_pos = i;
    }
  }
  return directory_pos;
}

/*
 * @brief Appends data to a file
 *
 * @param name Indicates the file that will be modified
 * @param data Indicates the data that must be added to the file
 * @return int The last block where the data was added. Returns -1 if no
 * directory was found.
 */
int FS::append(std::string name, std::string data) {
  // Value to be returned
  int return_value = 0;
  int directory_pos = search_file(name);
  if (directory_pos == -1) {
    return_value = -1;
  } else {
    // The first character is added to the file
    int block = this->directory[directory_pos].block;
    int next_empty = -1;
    bool first_time = true;
    for (int i = 0; i < data.length() && return_value != -1; ++i) {
      if (this->fat[block] != RESERVED) {
        if (first_time) {
          block = this->search_end_of_file(
              block, ++this->directory[directory_pos].size);
          first_time = false;
        }
        // A character will be inserted and a new block is required
        next_empty = this->search_block(block);
        // If an error is found
        if (next_empty == -1) {
          return_value = -1;
        } else {
          // A new end of file is set
          this->fat[next_empty] = END_OF_FILE;
          // The last block is set to point the new end of file
          this->fat[block] = next_empty;
          this->unit[next_empty] = data[i];
          ++this->directory[directory_pos].size;
          block = next_empty;
        }
      } else {
        // The first character of the file will be inserted
        this->fat[block] = END_OF_FILE;
        this->unit[block] = data[0];
        first_time = false;
      }
    }
    return_value = block;
  }
  return return_value;
}

/*
 * @brief Searches the file in the directory
 *
 * @return int The position of the directory. Returns -1 if the was not found.
 */
int FS::search_file(std::string &name) {
  int pos_directory = -1;
  for (int i = 0; i < MAX_SIZE && pos_directory == -1; ++i) {
    if (this->directory[i].name == name) {
      pos_directory = i;
    }
  }
  return pos_directory;
}

/*
 * @brief Searches the end of file in a position of the FAT table
 *
 * @param fat_pos Indicates the starting position to search in the FAT table
 * @return int The position of the end of file.
 */
int FS::search_end_of_file(int fat_pos, int size) {
  // TODO(nosotros): add size to directory and condition
  int counter = 0;
  while (this->fat[fat_pos] != END_OF_FILE && this->fat[fat_pos] != RESERVED) {
    fat_pos = this->fat[fat_pos];
    ++counter;
  }
  // The end of file is not what the size indicates
  // if (counter < size) {
  //  fat_pos = -1;
  // }
  return fat_pos;
}

/*
 * @brief Erases a file from directory and FAT table
 *
 * @param name Indicates the file that will be erased
 * @return int Returns 1 is success or -1 if the file was not found in the
 * directory
 */
int FS::erase(std::string name) {
  int return_value = 1;
  int directory_pos = search_file(name);
  // Leaves the method if the file does not exist
  if (directory_pos == -1) {
    return_value = -1;
  } else {
    int fat_pos = this->directory[directory_pos].block;
    this->directory[directory_pos].block = EMPTY;
    this->directory[directory_pos].date = 0;
    this->directory[directory_pos].name = "";

    int aux_pos = fat_pos;
    while (this->fat[fat_pos] != END_OF_FILE &&
           this->fat[fat_pos] != RESERVED) {
      aux_pos = this->fat[fat_pos];
      this->fat[fat_pos] = EMPTY;
      fat_pos = aux_pos;
    }
    this->fat[aux_pos] = EMPTY;
  }
  // Success
  return return_value;
}

/*
 * @brief Erases a file from directory, FAT table and unit
 *
 * @param name Indicates the file that will be erased
 * @return int Returns 1 is success or -1 if the file was not found in the
 * directory
 */
int FS::deep_erase(std::string name) {
  int directory_pos = search_file(name);
  int return_value = 1;
  // Leaves the method if the file does not exist
  if (directory_pos == -1) {
    return_value = -1;
  } else {
    int fat_pos = this->directory[directory_pos].block;
    this->directory[directory_pos].block = EMPTY;
    this->directory[directory_pos].date = 0;
    this->directory[directory_pos].name = "";

    int aux_pos = fat_pos;
    int row = -1;
    int column = -1;
    while (this->fat[fat_pos] != END_OF_FILE &&
           this->fat[fat_pos] != RESERVED) {
      this->unit[fat_pos] = '\0';
      aux_pos = this->fat[fat_pos];
      this->fat[fat_pos] = EMPTY;
      fat_pos = aux_pos;
    }
    this->fat[fat_pos] = EMPTY;
    this->unit[fat_pos] = '\0';
  }
  // Success
  return return_value;
}

/*
 * @brief Prints the unit
 */
void FS::print_unit() {
  std::cout << "\n\nDirectory:" << std::endl;
  for (int i = 0; i < MAX_SIZE; ++i) {
    if (this->directory[i].block != EMPTY) {
      std::cout << this->directory[i].name << "  ";
      std::cout << this->directory[i].block << std::endl;
    }
  }
  std::cout << "\nFAT:" << std::endl;
  for (int i = 0; i < MAX_SIZE; ++i) {
    if (this->fat[i] == EMPTY) {
      std::cout << "  ";
    } else if (this->fat[i] == END_OF_FILE || this->fat[i] == RESERVED) {
      std::cout << "F ";
    } else {
      std::cout << this->fat[i] << " ";
    }
    if ((i + 1) % 10 == 0) {
      std::cout << std::endl;
      for (int j = i - 9; j <= i; ++j) {
        std::cout << j << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << "\nUnit:" << std::endl;
  for (int i = 0; i < MAX_SIZE; ++i) {
    if (this->unit[i] != '\0') {
      std::cout << this->unit[i] << " ";
    } else {
      std::cout << "  ";
    }
    if ((i + 1) % 10 == 0) {
      std::cout << std::endl;
      for (int j = i - 9; j <= i; ++j) {
        std::cout << j << " ";
      }
      std::cout << std::endl;
    }
  }
}
