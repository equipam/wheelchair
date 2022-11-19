//Compile with -lserial and run with sudo 
#include <libserial/SerialPort.h>

using namespace LibSerial; 

int main(){
	SerialStream serial;
	serial.Open("/dev/ttyACM0");
	serial.SetBaudRate( BaudRate::BAUD_115200 );
	std::string aux = "Teste";
	serial << aux;
	
	serial.Close();
}
