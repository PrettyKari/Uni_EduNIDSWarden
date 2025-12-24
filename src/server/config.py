# server config file
HOST = "127.0.0.1"
ALLOWED_PORTS = {5050, 8060, 3020}
BUFFER_SIZE = 1024

SERVER_TEST_MESSAGES = [
	"Server is starting... \n",
    "Server is running fine... \n",
    "Server is receiving... \n",
	"Server is responding... \n",
	"Server received... \n",
    "Ping from legitimate client... \n",
	"Turning the server off... \n",
]

SERVER_DBG_FLAGS = [
	"code - 00",
	"code - 01 - system err",
	"code - 02 - network err",
	"code - 03 - connection err",
	"code - 04 - receiving err",
	"code - 05 - unknown err",

]