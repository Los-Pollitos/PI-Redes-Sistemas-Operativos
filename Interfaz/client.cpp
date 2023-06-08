#include "client.h"

/**
 * @brief Construct a new client::client object
 * 
 */
client::client() {
}

/**
 * @brief Inserts a new string into data starting at received position
 * 
 * @param data Array of data into which the new info shall be placed
 * @param new_info Information that will be placed into data
 * @param pos Position to start the transfer
 */
void client::adapt_data(char* data, std::string& new_info, int pos) {
    for (int i = 0; i < CLIENT_DATA_SIZE; ++i){
        data[i] = new_info[i+pos];
    }
}

/**
 * @brief Sends and receives information to intermediary
 * 
 * @param to_send Information that needs to be sent
 * @return std::string Information received
 */
std::string client::send_and_receive(std::string to_send) {
    std::string resultado = "";
    int s = 0, n = 0; // s:socket  n: contador
    char* data = new char[CLIENT_DATA_SIZE];  // para escribir lo que se lee
    struct sockaddr_in ipServidor;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Error de creación de socket" << std::endl;
    } else {
        ipServidor.sin_family = AF_INET;
        ipServidor.sin_port = htons(PORT);
        ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Se intenta pegar al servidor
        if (connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor)) < 0) {
            std::cout << std::endl << "Error de conexión por IP o puerto" << std::endl;
        } else {
            // Se logró pegar, se sacan data
            memset(data, '\0', CLIENT_DATA_SIZE);

            int total_m = (int) (to_send.length() / CLIENT_DATA_SIZE)
                          + (((int)(to_send.length() % CLIENT_DATA_SIZE) > 0) ? 1 : 0);

            for (int i = 0; i < total_m; ++i) {
                adapt_data(data, to_send, CLIENT_DATA_SIZE * i);
                std::cout << "Voy a mandar: " << data << std::endl;
                write(s, data, CLIENT_DATA_SIZE);
            }

            memset(data, '\0', CLIENT_DATA_SIZE);
            to_send = "&";
            adapt_data(data, to_send, 0);
            std::cout << "Voy a mandar: " << data << std::endl;
            write(s, data, CLIENT_DATA_SIZE);

            data[0] = '0';
            while (((n = read(s, data, CLIENT_DATA_SIZE)) > 0) && (data[0] != '&')) {
                // connection es socket cliente
                resultado += data;
                std::cout << "Recibi: " << data << std::endl;
            }

            memset(data, '\0', CLIENT_DATA_SIZE);
            to_send = "#";
            adapt_data(data, to_send, 0);
            std::cout << "Voy a mandar: " << data << std::endl;
            write(s, data, CLIENT_DATA_SIZE);
            // No se logró leer
            if (n < 0) {
                std::cout << std::endl << "Error de lectura" << std::endl;
            }
        }
        delete [] data;
    }
    return resultado;
}


/**
 * @brief Sends and receives information to intermediary
 *
 * @param to_send Information that needs to be sent
 * @return std::string Information received
 */
std::string client::send_and_receive_cypher(std::string to_send) {
    std::string resultado = "";
    int s = 0, n = 0; // s:socket  n: contador
    char* data = new char[CLIENT_DATA_SIZE];  // para escribir lo que se lee
    struct sockaddr_in ipServidor;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Error de creación de socket" << std::endl;
    } else {
        ipServidor.sin_family = AF_INET;
        ipServidor.sin_port = htons(PORT);
        ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Se intenta pegar al servidor
        if (connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor)) < 0) {
            std::cout << std::endl << "Error de conexión por IP o puerto" << std::endl;
        } else {
            // Se logró pegar, se sacan data
            memset(data, '\0', CLIENT_DATA_SIZE);

            int total_m = (int) (to_send.length() / CLIENT_DATA_SIZE)
                          + (((int)(to_send.length() % CLIENT_DATA_SIZE) > 0) ? 1 : 0);

            for (int i = 0; i < total_m; ++i) {
                adapt_data(data, to_send, CLIENT_DATA_SIZE * i);
                std::cout << "Voy a mandar: " << data << std::endl;
                write(s, data, CLIENT_DATA_SIZE);
            }

            memset(data, '\0', CLIENT_DATA_SIZE);
            to_send = "&";
            adapt_data(data, to_send, 0);
            std::cout << "Voy a mandar: " << data << std::endl;
            write(s, data, CLIENT_DATA_SIZE);

            data[0] = '0';
            while (((n = read(s, data, CLIENT_DATA_SIZE)) > 0) && (data[0] != '&')) {
                // connection es socket cliente
                for (int pos = 0; pos < CLIENT_DATA_SIZE; ++pos) {
                    resultado += data[pos];
                }
                std::cout << "Recibi: " << data << std::endl;
            }

            memset(data, '\0', CLIENT_DATA_SIZE);
            to_send = "#";
            adapt_data(data, to_send, 0);
            std::cout << "Voy a mandar: " << data << std::endl;
            write(s, data, CLIENT_DATA_SIZE);
            // No se logró leer
            if (n < 0) {
                std::cout << std::endl << "Error de lectura" << std::endl;
            }
        }
        delete [] data;
    }
    return resultado;
}
