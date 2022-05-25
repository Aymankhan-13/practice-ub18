#include <Poco/Util/ServerApplication.h>
#include <iostream>

class entry_point : public Poco::Util::ServerApplication
{
public:
  int main(const ArgVec& /*args*/) final
  {
    std::cout << "Started";
    {

      waitForTerminationRequest();
    }
    std::cout << "Stopped";
    return Application::EXIT_OK;
  }
};
POCO_SERVER_MAIN(entry_point);
