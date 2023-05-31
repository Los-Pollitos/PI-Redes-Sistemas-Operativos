#include "client.h"

client::client()
{

}

void client::adapt_data(char* data, std::string& new_info) {
    for (int i = 0; i < new_info.length(); ++i){
        data[i] = new_info[i];
    }
}

std::string client::send_and_receive(std::string to_send) {
    std::string resultado = "";
    int s = 0, n = 0; // s:socket  n: contador
    char* data = new char[CLIENT_DATA_SIZE];  // para escribir lo que se lee
    struct sockaddr_in ipServidor;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Error de creación de socket" << std::endl;
    } else {
        ipServidor.sin_family = AF_INET;
        ipServidor.sin_port = htons(1337);
        ipServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Se intenta pegar al servidor
        if (connect(s, (struct sockaddr *)&ipServidor, sizeof(ipServidor)) < 0) {
            std::cout << std::endl << "Error de conexión por IP o puerto" << std::endl;
        } else {
            // Se logró pegar, se sacan data
            memset(data, '0', CLIENT_DATA_SIZE);
            adapt_data(data, to_send);
            std::cout << "Voy a mandar: " << data << std::endl;
            write(s, data, strlen(data));

            if ((n = read(s, data, CLIENT_DATA_SIZE)) > 0) {
                // connection es socket cliente
                resultado = data;
                std::cout << "Recibi: " << data << std::endl;
            }

            memset(data, '0', CLIENT_DATA_SIZE);
            data[0] = '#';
            std::cout << "Voy a mandar: " << data << std::endl;
            write(s, data, strlen(data));
            // No se logró leer
            if (n < 0) {
                std::cout << std::endl << "Error de lectura" << std::endl;
            }
        }
        delete [] data;
    }
    return resultado;
}
