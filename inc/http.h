/**
 * Copyright, 2022.
 * This file is 
 * Author: Changhyun Son <xoowoo35@gmail.com>
*/
#include "save.h"


#define PORT 16851


using namespace std;
using namespace dlib;

class WebInterface : public dlib::threaded_object
{
  
public:
WebInterface();
~WebInterface();
void TryExit();

private:


void thread();
bool is_exited_;
  
};


class fifa_server : public dlib::server_http
{
const std::string on_request(
    const dlib::incoming_things& incoming, 
    dlib::outgoing_things& outgoing);
public:
  fifa_server();
  string ReadFileIntoString(const string& path);
  string url_login(
      const dlib::incoming_things& incoming, string message);
  string url_signup(
      const dlib::incoming_things& incoming, string message);
  string process_response_menu(
      const dlib::incoming_things& incoming, string message);
  string process_response_return(
      const dlib::incoming_things& incoming, string message);
  string localchangetime();
};


