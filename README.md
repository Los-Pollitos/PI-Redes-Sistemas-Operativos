# **Proyecto Integrador de Redes y Sistemas Operativos**

## **Equipo Los Pollitos:**

+ Emilia Víquez Mora - C18625 

+ Angie Solís Manzano - C17686

+ Luis Solano Santamaría - C17634

+ Cristopher Hernández -C13632

## **Requerimientos de ejecución:**

1. Ubuntu 22.04.2 LTS

2. QT 6.5.0

3. OpenSSL 3.0.2

## **Comandos de compilación**

### **Intermediario**

    g++ -o server main.cpp intermediary.cpp log.cpp -lcrypto

### **Servidor de login**

    g++ -o server main.cpp file_system.cpp login_server.cpp log.cpp -lcrypto

### **Interfaz, servidor de base de datos y auditoría**

Compilación desde la interfaz de QT Creator