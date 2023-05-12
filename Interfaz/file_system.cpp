/*
 * Team: Los Pollitos
 * Cristopher Hernández (C13632)
 * Luis Solano (C17634)
 * Angie Solís (C17686)
 * Emilia Víquez (C18625)
 */

// TODO(nosotros): cambiar unidad para que tenga EOF

#include "file_system.h"
/*
 * @brief Default constructor
 */
FS::FS() {
    this->fat = new int[FAT_SIZE];
    this->directory =
        new directory_entry_t[FAT_SIZE]; // fat size because is the same maximum
        // quantity of files
    this->unit = new char[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i) {
        this->unit[i] = '\0';
        if (i < FAT_SIZE) {
            this->fat[i] = EMPTY;
            this->directory[i].block = EMPTY;
        }
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
    int block = this->search_block();
    int directory_pos = this->search_directory();
    if (directory_pos != -1 && block != -1) {
        this->directory[directory_pos].block = block;
        this->directory[directory_pos].name = name;
        this->directory[directory_pos].size = 1;
        this->directory[directory_pos].is_file = true;
        time(&this->directory[directory_pos].date);
        // Is used as a special case of EOF to indicate an empty spot
        this->fat[block] = RESERVED;
    }
    return block;
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
int FS::search_file(std::string& name) {
    int pos_directory = -1;
    for (int i = 0; i < MAX_SIZE && pos_directory == -1; ++i) {
        if (this->directory[i].name == name) {
            pos_directory = i;
        }
    }
    return pos_directory;
}

// TODO(nosotros): documentar
/*
 * @brief Searches the end of file in a given position of the FAT table
 *
 * @param fat_pos Indicates the starting position to search in the FAT table
 * @return int The position of the end of file.
 */
int FS::search_end_of_file_fat(int fat_pos, int size) {
    int counter = 0;
    while (this->fat[fat_pos] != END_OF_FILE && this->fat[fat_pos] != RESERVED /*&&
         counter < size*/) {
        fat_pos = this->fat[fat_pos];
        ++counter;
    }
    // The end of file is not what the size indicates
    // if (counter >= size) {  // TODO(nosotros): arreglar
    //   fat_pos = -1;
    // }
    return fat_pos;
}

// TODO(nosotros): documentar
int FS::search_end_of_file(int fat_block, int size) {
    int pos_eof = -1;

    for (int i = fat_block * BLOCK_SIZE;
         i < (fat_block + 1) * BLOCK_SIZE && pos_eof == -1; ++i) {
        if (this->unit[i] == END_TEXT) {
            pos_eof = i;
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
    // Leaves the method if the file does not exist
    if (directory_pos == -1) {
        return_value = -1;
    } else {
        int fat_pos = this->directory[directory_pos].block;
        // Clean the directory
        this->directory[directory_pos].block = EMPTY;
        this->directory[directory_pos].date = 0;
        this->directory[directory_pos].size = 0;
        this->directory[directory_pos].name = "";
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
    // Leaves the method if the file does not exist
    if (directory_pos == -1) {
        return_value = -1;
    } else {
        int fat_pos = this->directory[directory_pos].block;
        // Clean the directory
        this->directory[directory_pos].block = EMPTY;
        this->directory[directory_pos].date = 0;
        this->directory[directory_pos].size = 0;
        this->directory[directory_pos].name = "";
        // Clean the fat
        int aux_pos = fat_pos;
        int row = -1;
        int column = -1;
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

// TODO(us): documentar
char FS::read(std::string user, std::string name, int position) {
    char result = '\0';
    // Look for file
    int dir_pos = this->search_file(name);
    bool has_permission = this->check_permissions(user, name);
    if (has_permission && /*position < this->directory[dir_pos].size
      &&*/ this->directory[dir_pos].is_file) {
        // We need to get to the block
        int block = (int)(position / BLOCK_SIZE);
        std::cout << "Block: " << block << std::endl;
        int actual_fat = this->directory[dir_pos].block;
        int past_fat = dir_pos;
        for (int i = 0; i < block; ++i) {
            past_fat = actual_fat;
            actual_fat = this->fat[actual_fat];
        }
        std::cout << "actual_fat: " << actual_fat << std::endl;
        // We need to get to the unit
        int unit_index = -1;
        if (actual_fat == END_OF_FILE) {
            unit_index = (position % BLOCK_SIZE) + (past_fat * BLOCK_SIZE);
        } else {
            unit_index = (position % BLOCK_SIZE) + (actual_fat * BLOCK_SIZE);
        }
        std::cout << "unit_index: " << unit_index << std::endl;
        result = this->unit[unit_index];
    }
    return result;
}

// TODO(us): hacer y documentar
bool FS::check_permissions(std::string user, std::string name) { return true; }

/*
 * @brief Prints the unit
 */
void FS::print_unit() {
    std::cout << "\n\nDirectory:" << std::endl;
    for (int i = 0; i < FAT_SIZE; ++i) {
        if (this->directory[i].block != EMPTY) {
            std::cout << this->directory[i].name << "  ";
            std::cout << this->directory[i].block << "  ";
            std::cout << "Size: " << this->directory[i].size << std::endl;
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
