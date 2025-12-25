# client config file
HOST = "127.0.0.1"
ALLOWED_PORTS = [5050, 8060, 3020]
BUFFER_SIZE = 1024

CLIENT_MESSAGES = [
	"Hi!\n",
	"Meow\n",
	"pspsps\n",
	"kkkkkkk\n",
]
SUS_CLIENT_MESSAGES = [
	"~Hi!\n",
	"~Meow\n",
	"~pspsps\n",
	"~kkkkkkk\n",
]

CLIENT_TEST_MESSAGES = [
	"Client is running fine... \n",
	"Client is connected to server... \n",
	"Client is sending... \n",
	"Ping from legitimate server... \n",
	"Turning the client off... \n",
]

CLIENT_DBG_FLAGS = [
	"code - 10",
	"code - 11 - system err",
	"code - 12 - network err",
	"code - 13 - connection err",
	"code - 14 - sending err",
	"code - 15 - unknown err",

]