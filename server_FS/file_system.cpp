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
  this->fat = new int[FAT_SIZE];
  this->directory = new directory_entry_t[DIR_SIZE];
  // The maximum size is the same as the directory
  this->open_file_table = new open_file_entry_t[DIR_SIZE];
  this->unit = new char[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; ++i) {
    this->unit[i] = '\0';
    if (i < FAT_SIZE) {
      this->fat[i] = EMPTY;
    }
    if (i < DIR_SIZE) {
      this->directory[i].block = EMPTY;
    }
  }
  // We create root folder
  this->actual_path = "\0";
  this->create("Root", false);
  this->actual_path = "Root";
}

/*
 * @brief Destructor
 */
FS::~FS() {
  delete[] this->fat;
  delete[] this->unit;
  delete[] this->directory;
  delete[] this->open_file_table;
}

/*
 * @brief Creates a file
 *
 * @param name Indicates the name of the file to be addded
 * @param is_file Is true if we are creating a file, false if it is a folder
 * @return int The block in which the file was added. Returns -1 if no block was
 * found or if there was already a file with that name.
 */
int FS::create(std::string name, bool is_file) {
  int block = -1;
  if (this->search_file(name) == -1) {
    int directory_pos = this->search_directory();
    block = this->search_block();
    if (directory_pos != -1 && (block != -1 || !is_file)) {
      if (is_file) {
        this->directory[directory_pos].block = block;
        // Reserved is a special case of EOF to indicate an empty spot
        this->fat[block] = RESERVED;
        this->directory[directory_pos].file_pointer =
            this->directory[directory_pos].block * BLOCK_SIZE;
        this->unit[this->directory[directory_pos].file_pointer] = END_TEXT;
        this->directory[directory_pos].size = 1;
        // Open file table setup
        this->open_file_table[directory_pos].name = name;
        this->open_file_table[directory_pos].open_count = 0;
      } else {
        this->directory[directory_pos].block = FOLDER;
        this->directory[directory_pos].size = 0;
        // the other atributes will not be accessed when treating a folder
      }
      this->directory[directory_pos].name = name;
      this->directory[directory_pos].is_file = is_file;
      time(&this->directory[directory_pos].date);
      this->directory[directory_pos].path = actual_path;
    }
  }
  return block;
}

/*
 * @brief Indicates if a user can change the permissions of a file
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file whose permissions want to be changed
 * @return bool true if the user has permissions, false if they do not
 */
bool FS::can_change_permissions(std::string user, std::string name) {
  (void)user;
  (void)name;
  return true;
}

/*
 * @brief Modifies permissions of a file
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file whose permissions want to be changed
 * @param new_user New user permissions
 * @param new_group New group permissions
 * @param new_all New other permissions
 * @return bool true if the action could be performed, false it not
 */
bool FS::modify_permissions(std::string user, std::string name, int new_user,
                            int new_group, int new_all) {
  bool result = false;
  int pos_dir = this->search_file(name);
  if (pos_dir != -1 && this->can_change_permissions(user, name)) {
    this->directory[pos_dir].permissions[0] = new_user;
    this->directory[pos_dir].permissions[1] = new_group;
    this->directory[pos_dir].permissions[2] = new_all;
    result = true;
  }
  return result;
}

/*
 * @brief Indicates the permissions of a file
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file whose permissions want to be asked
 * @param new_user variable to store user permissions
 * @param new_group variable to store group permissions
 * @param new_all variable to store other permissions
 * @return bool true if the action could be performed, false it not
 */
bool FS::get_permissions(std::string user, std::string name, int &result_user,
                         int &result_group, int &result_all) {
  bool result = false;
  int pos_dir = this->search_file(name);
  if (pos_dir != -1 && this->can_change_permissions(user, name)) {
    result_user = this->directory[pos_dir].permissions[0];
    result_group = this->directory[pos_dir].permissions[1];
    result_all = this->directory[pos_dir].permissions[2];
    result = true;
  }
  return result;
}

/*
 * @brief Searches the closest empty block
 *
 * @return int The block empty block. Returns -1 if no block was found.
 */
int FS::search_block() {
  int block = -1;
  for (int i = 0; i < FAT_SIZE && block == -1; ++i) {
    if (this->fat[i] == EMPTY) {
      block = i;
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
  for (int i = 0; i < DIR_SIZE && directory_pos == -1; ++i) {
    if (this->directory[i].block == EMPTY) {
      directory_pos = i;
    }
  }
  return directory_pos;
}

/*
 * @brief Modularizes open and close of a file
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file that will be opened or closed
 * @return int -1 if there was an error. 1 if there was no error
 */
int FS::handle_open_close(std::string user, std::string name, bool open) {
  // Assume an error
  int error = -1;
  // Check if file exists in directory
  int file_position = this->search_file(name);
  // Check if it was found, if it is a file, if the user has permission and if
  // the path is correct
  if (file_position != -1 && this->directory[file_position].is_file &&
      this->check_permission(user, name, 3) &&
      this->directory[file_position].path == this->actual_path) {
    if (open) {
      error = 1;
      ++this->open_file_table[file_position].open_count;
    } else {
      // Check if the file is open
      if (this->open_file_table[file_position].open_count > 0) {
        error = 1;
        --this->open_file_table[file_position].open_count;
      }
    }
  }
  return error;
}

/*
 * @brief Opens a file if it exists
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file that will be opened
 * @return int -1 if there was an error. 1 if there was no error
 */
int FS::open(std::string user, std::string name) {
  bool open = true;
  return handle_open_close(user, name, open);
}

/*
 * @brief Closes a file if it exists
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file that will be closed
 * @return int -1 if there was an error. 1 if there was no error
 */
int FS::close(std::string user, std::string name) {
  bool open = false;
  return handle_open_close(user, name, open);
}

/*
 * @brief Checks if a file is open
 *
 * @param name Indicates the file that will be checked
 * @return int -1 if there is an error. 0 if it is closed. 1 if it is open.
 */
int FS::is_open(std::string name) {
  // Assume error
  int answer = -1;
  int position = this->search_file(name);
  if (position != -1) {
    // Assume that it is not open
    answer = 0;
    if (this->open_file_table[position].open_count > 0) {
      // Change the answer to true
      answer = 1;
    }
  }
  return answer;
}

/*
 * @brief Write from the last file pointer position
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file that will be modified
 * @param line Indicates the data that must be added to the file
 * @return int Indicates if it was succesfully performed. It returns -1 if there
 * was an error
 */
int FS::write(std::string user, std::string name, std::string line) {
  int return_value = -1;
  int directory_position = this->search_file(name);
  // Check if it is a file, if the path is right, if the file is open,
  // and if the write position is valid
  if (directory_position != -1 && this->directory[directory_position].is_file &&
      this->directory[directory_position].path == this->actual_path &&
      this->is_open(name) == 1 && check_permission(user, name, 2)) {
    return_value = 1;
    int local_write_pointer = this->directory[directory_position].file_pointer;
    int current_fat = (int)(local_write_pointer / BLOCK_SIZE);
    if (this->fat[current_fat] != RESERVED) {
      // Write until the end of file block is found
      int i;
      for (i = 0;
           i < line.length() && this->unit[local_write_pointer] != END_TEXT;
           ++i) {
        this->unit[local_write_pointer] = line[i];
        this->add_one_local_write_pointer(local_write_pointer);
      }
      // Update file pointer
      this->directory[directory_position].file_pointer = local_write_pointer;
      // end text has been reached before the whole line was written
      if (i < line.length()) {
        line = line.substr(i);
        this->append(name, line);
        // Update the pointer
        current_fat = (int)(local_write_pointer / BLOCK_SIZE);
        int size = this->directory[directory_position].size;
        int end_fat = this->search_end_of_file_fat(current_fat, size);
        this->directory[directory_position].file_pointer =
            this->search_end_of_file(end_fat, size);
      }
    } else {
      // Equals to reserved, append
      this->append(name, line);
    }
  }
  return return_value;
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
  if (directory_pos == -1 || !this->directory[directory_pos].is_file ||
      !this->is_open(name)) {
    return_value = -1;
  } else {
    int unit_index = -1;
    int fat_index = this->directory[directory_pos].block;
    for (int i = 0; i < data.length() && return_value != -1; ++i) {
      if (this->fat[fat_index] == RESERVED) { // first in file
        this->fat[fat_index] = END_OF_FILE;
        this->unit[fat_index * BLOCK_SIZE] = data[0];
        this->unit[fat_index * BLOCK_SIZE + 1] = END_TEXT;
      } else {
        fat_index = search_end_of_file_fat(fat_index,
                                           this->directory[directory_pos].size);
        unit_index =
            search_end_of_file(fat_index, this->directory[directory_pos].size);
        if (unit_index == -1) {
          return_value = -1;
        } else {
          if ((unit_index + 1) % BLOCK_SIZE ==
              0) { // this means we need a new block
            this->fat[fat_index] = this->search_block();
            this->unit[unit_index] = data[i];
            this->fat[this->fat[fat_index]] = END_OF_FILE; // update the eof
            fat_index = this->fat[fat_index];
            unit_index = fat_index * BLOCK_SIZE;
            this->unit[unit_index] = END_TEXT;
            ++this->directory[directory_pos].size;
          } else { // this means we have space in the block
            this->unit[unit_index] = data[i];
            ++unit_index;
            this->unit[unit_index] = END_TEXT;
            ++this->directory[directory_pos].size;
          }
        }
      }
    }
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
  for (int i = 0; i < DIR_SIZE && pos_directory == -1; ++i) {
    if (this->directory[i].block != EMPTY && this->directory[i].name == name) {
      pos_directory = i;
    }
  }
  return pos_directory;
}

/*
 * @brief Searches the end of file from a given position of the FAT table
 *
 * @param fat_pos Indicates the starting position to search in the FAT table
 * @param size Indicates the size of the file. It has to be bigger than 1
 * @return int The position of the end of file.
 */
int FS::search_end_of_file_fat(int fat_pos, int size) {
  if (size > 0) {
    // The amount of FAT jumps required
    int max_jump_amount = FAT_SIZE - 1;
    int counter = 0;
    while (this->fat[fat_pos] != END_OF_FILE &&
           this->fat[fat_pos] != RESERVED && counter < max_jump_amount + 1) {
      fat_pos = this->fat[fat_pos];
      // A jump was done, add to counter
      ++counter;
    }
    // If the jumps done were bigger than the max amount of jumps
    if (counter > max_jump_amount) {
      fat_pos = -1;
    }
  } else {
    // The size is less or equal to zero
    fat_pos = -1;
  }
  return fat_pos;
}

/*
 * @brief Searches the position in the unit of the end of file
 *
 * @param fat_block Indicates the starting position to search in the FAT table
 * @param size Indicates the size of the file. It has to be bigger than 1
 * @return int The position of the unit with the end of file.
 */
int FS::search_end_of_file(int fat_block, int size) {
  int pos_eof = -1;
  if (size > 0) {
    for (int i = fat_block * BLOCK_SIZE;
         i < (fat_block + 1) * BLOCK_SIZE && pos_eof == -1; ++i) {
      if (this->unit[i] == END_TEXT) {
        pos_eof = i;
      }
    }
  }
  return pos_eof;
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
  // Leaves the method if the file does not exist, is a folder or the path is
  // not correct
  if (directory_pos == -1 || !this->directory[directory_pos].is_file ||
      this->directory[directory_pos].path != this->actual_path) {
    return_value = -1;
  } else {
    int fat_pos = this->directory[directory_pos].block;
    // Clean the directory
    this->directory[directory_pos].block = EMPTY;
    this->directory[directory_pos].date = 0;
    this->directory[directory_pos].size = 0;
    this->directory[directory_pos].name = "";
    // Clean the open file table
    this->open_file_table[directory_pos].name = "";
    this->open_file_table[directory_pos].open_count = 0;
    // Clean the fat
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
  // Leaves the method if the file does not exist, is a folder or the path is
  // not correct
  if (directory_pos == -1 || !this->directory[directory_pos].is_file ||
      this->directory[directory_pos].path != this->actual_path) {
    return_value = -1;
  } else {
    int fat_pos = this->directory[directory_pos].block;
    // Clean the directory
    this->directory[directory_pos].block = EMPTY;
    this->directory[directory_pos].date = 0;
    this->directory[directory_pos].size = 0;
    this->directory[directory_pos].name = "";
    this->directory[directory_pos].path = "";
    // Clean the open file table
    this->open_file_table[directory_pos].name = "";
    this->open_file_table[directory_pos].open_count = 0;
    // Clean the fat
    int aux_pos = fat_pos;
    while (this->fat[fat_pos] != END_OF_FILE &&
           this->fat[fat_pos] != RESERVED) {
      for (int i = fat_pos * BLOCK_SIZE; i < fat_pos * BLOCK_SIZE + BLOCK_SIZE;
           ++i) { // clean block
        this->unit[i] = '\0';
      }
      aux_pos = this->fat[fat_pos];
      this->fat[fat_pos] = EMPTY;
      fat_pos = aux_pos;
    }
    // We exit when we are still missing the last one
    this->fat[fat_pos] = EMPTY;
    for (int i = fat_pos * BLOCK_SIZE; i < fat_pos * BLOCK_SIZE + BLOCK_SIZE;
         ++i) {
      this->unit[i] = '\0';
    }
  }
  // Success
  return return_value;
}

/*
 * @brief Reads a file in an indicated position
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file name
 * @ param position Indicates the position to be read in the file
 * @return char Returns the char of the file in the indicated position. If empty
 * returns '\0'
 */
char FS::read(std::string user, std::string name, int position) {
  char result = '\0';
  // Look for file and permission
  int dir_pos = this->search_file(name);
  // Check if content is in directory and if it is open
  if (dir_pos != -1 && this->is_open(name) == 1) {
    bool has_permission = this->check_permission(user, name, 1);
    // Check the permission, position, actual file and path
    if (has_permission && position < this->directory[dir_pos].size &&
        this->directory[dir_pos].is_file &&
        this->directory[dir_pos].path == this->actual_path) {
      // We need to get to the block
      int block = (int)(position / BLOCK_SIZE);
      int actual_fat = this->directory[dir_pos].block;
      int past_fat = dir_pos;
      for (int i = 0; i < block; ++i) {
        past_fat = actual_fat;
        actual_fat = this->fat[actual_fat];
      }
      // We need to get to the unit
      int unit_index = -1;
      if (actual_fat == END_OF_FILE) {
        unit_index = (position % BLOCK_SIZE) + (past_fat * BLOCK_SIZE);
      } else {
        unit_index = (position % BLOCK_SIZE) + (actual_fat * BLOCK_SIZE);
      }
      result = this->unit[unit_index];
    }
  }
  return result;
}

/*
 * @brief Checks if a user has permission for a file
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file name
 * @param permission Indicates if the permission is to execute (4), write (2) or
 *   read (1)
 * @return bool True if the user has permission. False if not.
 */
bool FS::check_permission(std::string user, std::string name, int permission) {
  // Number Execute Write Read
  // 4   =  1       0     0   = Execute
  // 2   =  0       1     0   = Write
  // 1   =  0       0     1   = Read
  return true;
}

/*
 * @brief Moves the local read pointer one position forward
 *
 * @param local_read_pointer Indicates the pointer that will be moved
 */
void FS::add_one_local_read_pointer(int &local_read_pointer) {
  if (local_read_pointer + 1 % BLOCK_SIZE == 0) { // We need to switch block
    int aux_fat_position = (int)(local_read_pointer / BLOCK_SIZE); // actual fat
    // If the end of file was read, we should not be in this while, so
    // there should always be a new block ahead if we are in this if
    aux_fat_position = this->fat[aux_fat_position];
    local_read_pointer = aux_fat_position * BLOCK_SIZE; // new start of block
  } else {
    ++local_read_pointer; // we are still in the same block
  }
}

/*
 * @brief Moves the local write pointer one position forward
 *
 * @param local_write_pointer Indicates the pointer that will be moved
 */
void FS::add_one_local_write_pointer(int &local_write_pointer) {
  // We need to switch block
  if (local_write_pointer + 1 % BLOCK_SIZE == 0) {
    // actual fat
    int aux_fat_position = (int)(local_write_pointer / BLOCK_SIZE);
    // If the end of file was read, we should not be in this while, so
    if (this->fat[aux_fat_position != END_OF_FILE]) {
      aux_fat_position = this->fat[aux_fat_position];
      // new start of block
      local_write_pointer = aux_fat_position * BLOCK_SIZE;
    }
  } else {
    // we are still in the same block
    ++local_write_pointer;
  }
}

/*
 * @brief Reads until a \n is found in a file. If there is none the whole file
 * is read.
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file name
 * @return string Contains the line read
 */
std::string FS::read_line(std::string user, std::string name) {
  int dir_pos = this->search_file(name);
  std::string result = "\0";
  // Check if content is in directory
  if (dir_pos != -1 && this->directory[dir_pos].size > 0 &&
      this->is_open(name) == 1) {
    int local_read_pointer = this->directory[dir_pos].file_pointer;
    // Check if the user is valid, if the given name is a file, and if the path
    // is right
    if (check_permission(user, name, 1) && this->directory[dir_pos].is_file &&
        this->directory[dir_pos].path == this->actual_path) {
      while (/**this->directory[dir_pos].file_pointer < local_read_pointer &&*/
             this->unit[local_read_pointer] != '\n' &&
             this->unit[local_read_pointer] != END_TEXT) {
        result += this->unit[local_read_pointer];
        this->add_one_local_read_pointer(local_read_pointer);
      }
      if (this->unit[local_read_pointer] != END_TEXT) {
        this->add_one_local_read_pointer(local_read_pointer);
      }
      this->directory[dir_pos].file_pointer = local_read_pointer;
    }
  }
  return result;
}

/*
 * @brief Reads in the file until the separator is found
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file name
 * @param separator Indicates the separator when it has to stop reading
 * @return string Constains what was read from the file
 */
std::string FS::read_until(std::string user, std::string name, char separator) {
  int dir_pos = this->search_file(name);
  std::string result = "\0";
  if (dir_pos != -1 && this->directory[dir_pos].size > 0 &&
      this->is_open(name) == 1) {
    int local_read_pointer = this->directory[dir_pos].file_pointer;
    if (check_permission(user, name, 1) && this->directory[dir_pos].is_file &&
        this->directory[dir_pos].path == this->actual_path) {
      while (/**this->directory[dir_pos].file_pointer < local_read_pointer &&
              **/
             this->unit[local_read_pointer] != separator &&
             this->unit[local_read_pointer] != END_TEXT &&
             this->unit[local_read_pointer] != '\n') {
        result += this->unit[local_read_pointer];
        this->add_one_local_read_pointer(local_read_pointer);
      }
      if (this->unit[local_read_pointer] != END_TEXT) {
        this->add_one_local_read_pointer(local_read_pointer);
      }
      this->directory[dir_pos].file_pointer = local_read_pointer;
    }
  }
  return result;
}

/*
 * @brief Resets the file pointer to the beginning
 *
 * @param user Indicates the user, in order to check permission
 * @param name Indicates the file name
 */
void FS::reset_file_pointer(std::string user, std::string name) {
  int directory_pos = this->search_file(name);
  // Check if the file exists and if it is a file instead of a folder
  if (directory_pos != -1 && this->directory[directory_pos].is_file) {
    this->directory[directory_pos].file_pointer =
        this->directory[directory_pos].block * BLOCK_SIZE;
  }
}

/*
 * @brief Indicates if the first position of the file is the end of file
 *
 * @param Indicates the user, in order to check permission
 * @param name Indicates the file name
 * @return bool True if it is the end of file. Flase if not.
 */
bool FS::is_eof(std::string user, std::string name) {
  bool result = false;
  int directory_pos = this->search_file(name);
  if (this->directory[directory_pos].is_file) {
    result =
        this->unit[this->directory[directory_pos].file_pointer] == END_TEXT;
  }
  return result;
}

/*
 * @brief Prints the open file table
 */
void FS::print_open_file_table() {
  std::cout << "\n\nOpen File Table:" << std::endl;
  bool empty = true;
  // Print the table
  for (int i = 0; i < DIR_SIZE; ++i) {
    if (this->open_file_table[i].open_count > 0) {
      std::cout << this->open_file_table[i].name << " "
                << this->open_file_table[i].open_count << std::endl;
      if (empty) {
        empty = false;
      }
    }
  }
  // Print empty
  if (empty) {
    std::cout << "EMPTY" << std::endl;
  }
}

/*
 * @brief Prints the unit
 */
void FS::print_unit() {
  std::cout << "\n\nDirectory:" << std::endl;
  for (int i = 0; i < DIR_SIZE; ++i) {
    if (this->directory[i].block != EMPTY) {
      std::cout << this->directory[i].path << "/" << this->directory[i].name
                << "  ";
      if (this->directory[i].block != FOLDER) {
        std::cout << this->directory[i].block << "  ";
        std::cout << "Size: " << this->directory[i].size << std::endl;
      } else {
        std::cout << "Folder" << std::endl;
      }
    }
  }
  std::cout << "\nFAT:" << std::endl;
  for (int i = 0; i < FAT_SIZE; ++i) {
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
      std::cout << "_ ";
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

/*
 * @brief Returns the actual path
 *
 * @return string Indicates path
 */
std::string FS::get_actual_path() { return this->actual_path; }

/*
 * @brief Moves the path one folder above
 *
 * @return bool True indicates the path was moved. False if the path was already
 * the Root.
 */
bool FS::up_folder() {
  bool result = true;
  if (this->actual_path == "Root") {
    result = false;
  } else {
    int i = this->actual_path.length() - 1;
    while (i >= 0 && this->actual_path[i] != '/') {
      --i;
    }
    std::string new_path = "\0";
    for (int j = 0; j < i; ++j) {
      new_path += actual_path[j];
    }
    this->actual_path = "\0";
    this->actual_path = new_path;
  }
  return result;
}

/*
 * @brief Shows the content of the actual_path
 *
 * @param user Indicates the username, to check permissions
 */
void FS::list(std::string user) {
  for (int i = 0; i < DIR_SIZE; ++i) {
    if (this->directory[i].path == this->actual_path) {
      if (this->can_show(user, this->directory[i].name)) {
        std::cout << this->directory[i].name << "\t";
        if (this->directory[i].block != FOLDER) {
          std::cout << this->directory[i].size << "B\t";
        } else {
          std::cout << "Folder"
                    << "\t";
        }
        // TODO(nosotros): que la fecha se imprima bonito
        // std::cout << this->directory[i].date << "\n";
      }
      std::cout << std::endl;
    }
  }
}

/*
 * @brief Changes the path to be one folder in
 *
 * @param user Indicates the username
 * @param folder Indicates the folder
 * @return bool True if the path was changed. False if not
 */
bool FS::change_folder(std::string user, std::string folder) {
  std::string new_path = this->actual_path;
  new_path += "/";
  new_path += folder;
  bool result = false;
  if (this->is_valid_path(new_path) && this->can_show(user, new_path)) {
    this->actual_path = new_path;
    result = true;
  }
  return result;
}

/*
 * @brief Changes actual_path into a new path
 *
 * @param user Indicates the username
 * @param path Indicates the new path
 * @return bool True if the path was changed. False if not
 */
bool FS::set_path(std::string user, std::string path) {
  bool result = false;
  if (this->can_show(user, path)) {
    if (is_valid_path(path)) {
      result = true;
      this->actual_path = path;
    }
  }
  return result;
}

/*
 * @brief Searches the path to identify if it is valid
 *
 * @param path Indicates the path to be validated
 * @return bool True if it is valid. False if not
 */
bool FS::is_valid_path(std::string path) {
  bool result = false;
  for (int i = 0; i < DIR_SIZE && !result; ++i) {
    if (this->directory[i].block != EMPTY && this->directory[i].path == path) {
      result = true;
    }
  }
  // we need to check if the path was correct but empty
  if (result == false) {
    int pos_slash = -1;
    int index = 0;
    while (index <= path.length()) {
      if (path[index] == '/') {
        // We need to find the last slash to check if there is an empty folder
        // with that name
        pos_slash = index;
      }
      ++index;
    }
    if (pos_slash != -1) {
      std::string find_name = "\0";
      std::string find_path = "\0";
      for (int i = pos_slash + 1; i < path.length(); ++i) {
        find_name += path[i];
      }
      for (int i = 0; i < pos_slash; ++i) {
        find_path += path[i];
      }
      int dir_pos = this->search_file(find_name);
      if (dir_pos != -1 && this->directory[dir_pos].path == find_path) {
        // this means we were looking for an empty folder,
        // so there was no file with this folder
        result = true;
      }
    }
  }
  return result;
}

/*
 * @brief Deletes a folder. After this method, it is recomended that the user
 * sets the path in which they want to be.
 *
 * @param user Indicates the username
 * @param folder Indicates the folder that will be deleted
 * @return bool True if the folder was deleted. False if not
 */
bool FS::delete_folder(std::string user, std::string folder) {
  bool result = false;
  std::string path = "";
  int dir_folder = 0;
  if (can_show(user, folder) && folder != "ROOT") {
    for (int i = 0; i < DIR_SIZE && !result; ++i) {
      if (this->directory[i].name == folder) {
        path = this->directory[i].path + "/" + this->directory[i].name;
        dir_folder = i;
        result = true;
      }
    }
    for (int i = 0; i < DIR_SIZE; ++i) {
      if (this->directory[i].path == path) {
        if (this->directory[i].is_file)
          this->erase(this->directory[i].name);
        else
          this->delete_folder(user, this->directory[i].name);
      }
    }
    this->directory[dir_folder].name = "";
    this->directory[dir_folder].date = 0;
    this->directory[dir_folder].size = 0;
    this->directory[dir_folder].block = EMPTY;
    this->directory[dir_folder].path = "";
  }
  this->up_folder();
  return result;
}

/*
 * @brief Check if the usesr has permission to access a folder
 *
 * @param user Indicates the username, to check permissions
 * @param name Indicates the name of the folder
 * @return bool True if the user has permission. False if not
 */
bool FS::can_show(std::string user, std::string name) {
  // We need to know if the user can see that folder/file
  // This handin does not include permissions
  return true;
}

/*
 * @brief Moves a file or folder to a new path
 *
 * @param user Indicates the username, to check permissions
 * @param name Indicates the name of the file or folder to be moved
 * @param new_abs_path Indicates the new path. It has to start in Root
 * @return bool True if the file was moved. False if not
 */
bool FS::move(std::string user, std::string name, std::string new_abs_path) {
  bool result = false;
  if (this->is_valid_path(new_abs_path) && this->can_show(user, new_abs_path)) {
    int dir_pos = this->search_file(name);
    // Check if the file is in the actual_path
    if (dir_pos != -1 && this->directory[dir_pos].path == this->actual_path &&
        this->check_permission(user, name, 3)) {
      result = true;
      // We can move a file or a folder
      if (this->directory[dir_pos].is_file) {
        // When moving a file: change the path to the new path
        this->directory[dir_pos].path = new_abs_path;
      } else {
        // When moving a folder
        /* Idea:
          1. Change all paths that are the same as the old path
          2. If we find a folder inside the other folder, change
             the path of all the elements inside the folder. */
        std::string aux_path =
            this->directory[dir_pos].path + "/" + this->directory[dir_pos].name;
        std::string aux_new_path =
            new_abs_path + "/" + this->directory[dir_pos].name;
        for (int i = 0; i < DIR_SIZE; ++i) {
          if (this->directory[i].block != EMPTY) {
            if (this->directory[i].path == aux_path) {
              if (this->directory[i].is_file) {
                this->directory[i].path = aux_new_path;
              } else {
                // we are moving a folder
                for (int j = 0; j < DIR_SIZE; ++j) {
                  if (this->directory[i].path == aux_path) {
                    this->move(user, this->directory[j].name, aux_new_path);
                  }
                } // end for
              }   // end else
            }     // end if
          }       // end if
        }         // end for
        this->directory[dir_pos].path = new_abs_path;
      }
    }
  }
  return result;
}

// TODO(nosotros): documentar
void FS::write_unit() {
  std::ofstream file("fs_image.dat");
  for (int i = 0; i < FAT_SIZE; ++i) {
    file << this->fat[i];
  }
  for (int i = 0; i < MAX_SIZE; ++i) {
    file << this->unit[i];
  }
  file << std::endl;
  for (int i = 0; i < DIR_SIZE; ++i) {
    if (this->directory[i].block != EMPTY) {
      file << this->directory[i].name << this->directory[i].path
           << this->directory[i].block << this->directory[i].size
           << this->directory[i].is_file << this->directory[i].permissions[0]
           << this->directory[i].permissions[1]
           << this->directory[i].permissions[2] << std::endl;
    }
  }
}

// TODO(nosotros): documentar
void FS::load_unit() {
  std::ifstream file("fs_image.dat");
  std::string buffer;
  std::getline(file, buffer);
  int buffer_count = 0;
  for (int i = 0; i < FAT_SIZE; ++i) {
    if (buffer[buffer_count] == '-') {
      ++buffer_count;
      this->fat[i] = -1*(std::stoi(&buffer[buffer_count]));
    } else {
      this->fat[i] = (std::stoi(&buffer[buffer_count]));
    }
  }
  for (int i = 0; i < MAX_SIZE; ++i) {
    if (i >= buffer.length()) {
      this->unit[i] = '\n';
      std::getline(file, buffer);
      buffer_count = 0;
    } else {
      this->unit[i] = buffer[buffer_count];
    }
  }
  int pos_directory = 0;
  std::string temp;
  while (!file.eof()) {
    file >> this->directory[pos_directory].name >>
        this->directory[pos_directory].path >>
        this->directory[pos_directory].block >>
        this->directory[pos_directory].size;
    std::getline(file, temp, ' ');
    this->directory[pos_directory].is_file = (bool)(std::stoi(&temp[0]));
    file >> this->directory[pos_directory].permissions[0] >>
        this->directory[pos_directory].permissions[1] >>
        this->directory[pos_directory].permissions[2];
    if (this->directory[pos_directory].is_file == true) {
      this->directory[pos_directory].file_pointer =
          this->directory[pos_directory].block * BLOCK_SIZE;
    }
    ++pos_directory;
  }
}