#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace config
{
	constexpr auto path = "Z:\\my.dll"; // 2 MB
	constexpr auto botToken = ""; // token
	constexpr auto chatID = ""; // /getUpdates path to get ur chat id from that
}

int main()
{
	httplib::Client cli("https://api.telegram.org");
	std::ifstream input(config::path, std::ios::binary);
	std::stringstream buffer;
	buffer << input.rdbuf();

	std::stringstream url;
	url << "/bot" << config::botToken << "/sendDocument";

	httplib::MultipartFormDataItems items{
		{ "document", buffer.str(), "my.dll", "application/octet-stream"},
		{ "chat_id", config::chatID, "", "" },
	};
	auto res = cli.Post(url.str().data(), items);
	if (res && res->status == 200)
	{
        std::cout << "Success" << std::endl;
	}

	return 0;
}
